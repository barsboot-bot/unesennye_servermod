// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.2
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeRPCHandler
{
	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		if (!sender)
			return;

		switch (rpc_type)
		{
			case UnesennyeConstants.HS_REQUEST:
				HandleHandshake(sender);
				break;

			case UnesennyeConstants.TRACK_LIST_REQ:
				HandleTrackListRequest(sender, ctx);
				break;

			case UnesennyeConstants.RADIO_PLAY:
				HandleRadioPlay(sender, ctx);
				break;

			case UnesennyeConstants.RADIO_STOP:
				HandleRadioStop(sender, ctx);
				break;

			case UnesennyeConstants.RADIO_INSERT_CARD:
				HandleRadioInsertCard(sender, target, ctx);
				break;

			case UnesennyeConstants.RADIO_EJECT_CARD:
				HandleRadioEjectCard(sender, target, ctx);
				break;

			case UnesennyeConstants.RADIO_PLAY_TRACK:
				HandleRadioPlayTrack(sender, target, ctx);
				break;

			case UnesennyeConstants.RADIO_STOP_TRACK:
				HandleRadioStopTrack(sender, target, ctx);
				break;

			case UnesennyeConstants.ALBUM_NEXT_TRACK:
				HandleAlbumNext(sender, ctx);
				break;

			case UnesennyeConstants.ALBUM_PREV_TRACK:
				HandleAlbumPrev(sender, ctx);
				break;

			case UnesennyeConstants.ALBUM_SET_TRACK:
				HandleAlbumSetTrack(sender, ctx);
				break;

			case UnesennyeConstants.ALBUM_GET_TRACKLIST:
				HandleAlbumGetTracklist(sender, ctx);
				break;

			default:
				break;
		}
	}

	protected void HandleHandshake(PlayerIdentity identity)
	{
		UnesennyeAuth.GrantAccess(identity);
		GetGame().RPCSingleParam(null, UnesennyeConstants.HS_RESPONSE, null, true, identity);
	}

	protected void HandleTrackListRequest(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		// Если есть зарегистрированные плейлисты — отдаём первый как пример
		string list = UnesennyeMusicLibrary.GetTracksAsString(1);
		if (list == "")
			list = "track_01,track_02,track_03";

		Param1<string> response = new Param1<string>(list);
		GetGame().RPCSingleParam(null, UnesennyeConstants.TRACK_LIST_RESP, response, true, identity);
	}

	protected void HandleRadioPlay(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		Param1<string> data;
		if (!ctx.Read(data))
			return;

		string soundSet = data.param1;
		Print("[Unesennye Server] RADIO_PLAY by " + identity.GetName() + " -> " + soundSet);

		Param1<string> broadcast = new Param1<string>(soundSet);
		GetGame().RPCSingleParam(null, UnesennyeConstants.BROADCAST_PLAY, broadcast, true, null);
	}

	protected void HandleRadioStop(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		GetGame().RPCSingleParam(null, UnesennyeConstants.BROADCAST_STOP, null, true, null);
	}

	protected void HandleRadioInsertCard(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		Param2<string, int> data;
		if (!ctx.Read(data))
		{
			UnesennyeSDCardManager.InsertCard(identity, target, 1, UnesennyeConstants.SD_CARD_CLASS);
			return;
		}

		string cardClass = data.param1;
		int playlistId = data.param2;

		if (cardClass != UnesennyeConstants.SD_CARD_CLASS && cardClass != UnesennyeConstants.SD_CARD_EMPTY)
			return;

		UnesennyeSDCardManager.InsertCard(identity, target, playlistId, cardClass);
	}

	protected void HandleRadioEjectCard(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		UnesennyeSDCardManager.EjectCard(identity, target);
	}

	protected void HandleRadioPlayTrack(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		if (!UnesennyeSDCardManager.HasCard(identity, target))
		{
			Print("[Unesennye Server] RADIO_PLAY_TRACK rejected — no SD Card");
			return;
		}

		int playlistId = UnesennyeSDCardManager.GetPlaylistId(identity, target);

		Param1<string> data;
		string track = "";
		if (ctx.Read(data))
			track = data.param1;

		// Если track пустой — берём первый трек из библиотеки
		if (track == "" && UnesennyeMusicLibrary.HasPlaylist(playlistId))
		{
			array<string> tracks = UnesennyeMusicLibrary.GetTracks(playlistId);
			if (tracks.Count() > 0)
				track = tracks.Get(0);
		}

		Print("[Unesennye Server] RADIO_PLAY_TRACK by " + identity.GetName() + " | playlist=" + playlistId.ToString() + " | track=" + track);

		Param2<int, string> broadcast = new Param2<int, string>(playlistId, track);
		GetGame().RPCSingleParam(null, UnesennyeConstants.RADIO_BROADCAST, broadcast, true, null);
	}

	protected void HandleRadioStopTrack(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		GetGame().RPCSingleParam(null, UnesennyeConstants.RADIO_BROADCAST_STOP, null, true, null);
	}

	protected void HandleAlbumNext(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;
	}

	protected void HandleAlbumPrev(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;
	}

	protected void HandleAlbumSetTrack(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		Param1<string> data;
		if (!ctx.Read(data))
			return;

		Param1<string> broadcast = new Param1<string>(data.param1);
		GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_BROADCAST, broadcast, true, null);
	}

	protected void HandleAlbumGetTracklist(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
		{
			GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_REJECT, null, true, identity);
			return;
		}

		string list = UnesennyeMusicLibrary.GetTracksAsString(1);
		if (list == "")
			list = "album_01_track_01,album_01_track_02,album_01_track_03";

		Param1<string> response = new Param1<string>(list);
		GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_TRACKLIST_RESP, response, true, identity);
	}
};
