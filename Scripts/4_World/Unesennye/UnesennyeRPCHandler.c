// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeRPCHandler
{
	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		if (!sender) return;

		switch (rpc_type)
		{
			case UnesennyeConstants.HS_REQUEST: HandleHandshake(sender); break;
			case UnesennyeConstants.TRACK_LIST_REQ: HandleTrackListRequest(sender, ctx); break;
			case UnesennyeConstants.RADIO_PLAY: HandleRadioPlay(sender, target, ctx); break;
			case UnesennyeConstants.RADIO_STOP: HandleRadioStop(sender, target, ctx); break;
			case UnesennyeConstants.RADIO_INSERT_CARD: HandleRadioInsertCard(sender, target, ctx); break;
			case UnesennyeConstants.RADIO_EJECT_CARD: HandleRadioEjectCard(sender, target, ctx); break;
			case UnesennyeConstants.RADIO_PLAY_TRACK: HandleRadioPlayTrack(sender, target, ctx); break;
			case UnesennyeConstants.RADIO_STOP_TRACK: HandleRadioStopTrack(sender, target, ctx); break;
			case UnesennyeConstants.ALBUM_NEXT_TRACK: HandleAlbumNext(sender, target, ctx); break;
			case UnesennyeConstants.ALBUM_PREV_TRACK: HandleAlbumPrev(sender, target, ctx); break;
			case UnesennyeConstants.ALBUM_SET_TRACK: HandleAlbumSetTrack(sender, target, ctx); break;
			case UnesennyeConstants.ALBUM_GET_TRACKLIST: HandleAlbumGetTracklist(sender, ctx); break;
			default: break;
		}
	}

	protected void BroadcastToRadius(Object source, int rpcId, Param params)
	{
		float radius = UnesennyeConfig.Get().BroadcastRadius;
		vector pos = "0 0 0";
		if (source) pos = source.GetPosition();
		else
		{
			// fallback global
			GetGame().RPCSingleParam(null, rpcId, params, true, null);
			return;
		}

		array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);
		for (int i = 0; i < players.Count(); i++)
		{
			Man m = players.Get(i);
			if (!m) continue;
			if (vector.Distance(pos, m.GetPosition()) > radius) continue;
			PlayerIdentity id = m.GetIdentity();
			if (!id) continue;
			GetGame().RPCSingleParam(source, rpcId, params, true, id);
		}
	}

	protected void HandleHandshake(PlayerIdentity identity)
	{
		UnesennyeAuth.GrantAccess(identity);
		GetGame().RPCSingleParam(null, UnesennyeConstants.HS_RESPONSE, null, true, identity);
	}

	protected void HandleTrackListRequest(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity)) return;
		string list = UnesennyeMusicLibrary.GetTracksAsString(1);
		if (list == "") list = "track_01.ogg,track_02.ogg";
		GetGame().RPCSingleParam(null, UnesennyeConstants.TRACK_LIST_RESP, new Param1<string>(list), true, identity);
	}

	protected void HandleRadioPlay(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity)) return;
		Param1<string> data;
		if (!ctx.Read(data)) return;
		BroadcastToRadius(target, UnesennyeConstants.BROADCAST_PLAY, new Param1<string>(data.param1));
	}

	protected void HandleRadioStop(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity)) return;
		BroadcastToRadius(target, UnesennyeConstants.BROADCAST_STOP, null);
	}

	protected void HandleRadioInsertCard(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity)) return;

		int livePid;
		string liveClass;
		if (UnesennyeSDCardManager.ValidateAttachedMedia(target, livePid, liveClass))
		{
			if (!UnesennyeConfig.IsPlaylistAllowed(livePid))
			{
				UnesennyeLogger.Log("SD insert rejected whitelist playlist=" + livePid.ToString());
				return;
			}
			UnesennyeSDCardManager.InsertCard(identity, target, livePid, liveClass);
			UnesennyeAlbumQueue.SetPlaylist(identity, livePid);
			return;
		}

		// RPC fallback only if attachment not yet synced
		Param2<string, int> data;
		if (ctx.Read(data))
		{
			if (!UnesennyeConfig.IsPlaylistAllowed(data.param2)) return;
			UnesennyeSDCardManager.InsertCard(identity, target, data.param2, data.param1);
			UnesennyeAlbumQueue.SetPlaylist(identity, data.param2);
		}
	}

	protected void HandleRadioEjectCard(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity)) return;
		UnesennyeSDCardManager.EjectCard(identity, target);
	}

	protected void HandleRadioPlayTrack(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity)) return;
		if (!UnesennyeSDCardManager.HasCard(identity, target))
		{
			UnesennyeLogger.Log("PLAY rejected — no media in slot");
			return;
		}

		int playlistId = UnesennyeSDCardManager.GetPlaylistId(identity, target);
		if (!UnesennyeConfig.IsPlaylistAllowed(playlistId))
		{
			UnesennyeLogger.Log("PLAY rejected whitelist");
			return;
		}

		int trackIndex = UnesennyeAlbumQueue.GetIndex(identity);
		array<string> tracks = UnesennyeMusicLibrary.GetTracks(playlistId);
		string track = "";
		if (tracks.Count() > 0)
		{
			if (trackIndex < 0 || trackIndex >= tracks.Count()) trackIndex = 0;
			track = tracks.Get(trackIndex);
		}

		Param1<string> data;
		if (ctx.Read(data) && data.param1 != "")
			track = data.param1;

		string soundSet = UnesennyeMusicLibrary.GetSoundSetName(playlistId, trackIndex);
		Param3<int, string, string> broadcast = new Param3<int, string, string>(playlistId, track, soundSet);
		BroadcastToRadius(target, UnesennyeConstants.RADIO_BROADCAST, broadcast);
		UnesennyeLogger.Log("PLAY " + identity.GetName() + " " + soundSet);
	}

	protected void HandleRadioStopTrack(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity)) return;
		BroadcastToRadius(target, UnesennyeConstants.RADIO_BROADCAST_STOP, null);
	}

	protected void HandleAlbumNext(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity)) return;
		int idx = UnesennyeAlbumQueue.Next(identity);
		int pid = UnesennyeAlbumQueue.GetPlaylist(identity);
		string soundSet = UnesennyeMusicLibrary.GetSoundSetName(pid, idx);
		array<string> tracks = UnesennyeMusicLibrary.GetTracks(pid);
		string track = "";
		if (idx < tracks.Count()) track = tracks.Get(idx);
		BroadcastToRadius(target, UnesennyeConstants.ALBUM_BROADCAST, new Param3<int, string, string>(pid, track, soundSet));
	}

	protected void HandleAlbumPrev(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity)) return;
		int idx = UnesennyeAlbumQueue.Prev(identity);
		int pid = UnesennyeAlbumQueue.GetPlaylist(identity);
		string soundSet = UnesennyeMusicLibrary.GetSoundSetName(pid, idx);
		array<string> tracks = UnesennyeMusicLibrary.GetTracks(pid);
		string track = "";
		if (idx < tracks.Count()) track = tracks.Get(idx);
		BroadcastToRadius(target, UnesennyeConstants.ALBUM_BROADCAST, new Param3<int, string, string>(pid, track, soundSet));
	}

	protected void HandleAlbumSetTrack(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity)) return;
		Param1<string> data;
		if (!ctx.Read(data)) return;
		BroadcastToRadius(target, UnesennyeConstants.ALBUM_BROADCAST, new Param1<string>(data.param1));
	}

	protected void HandleAlbumGetTracklist(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
		{
			GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_REJECT, null, true, identity);
			return;
		}
		int pid = UnesennyeAlbumQueue.GetPlaylist(identity);
		string list = UnesennyeMusicLibrary.GetTracksAsString(pid);
		GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_TRACKLIST_RESP, new Param1<string>(list), true, identity);
	}
};
