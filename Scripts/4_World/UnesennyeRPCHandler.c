// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.0
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeRPCHandler
{
	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		if (!sender)
			return;

		switch (rpc_type)
		{
			// ==================== HANDSHAKE ====================
			case UnesennyeConstants.HS_REQUEST:
				HandleHandshake(sender);
				break;

			// ==================== АВТО ====================
			case UnesennyeConstants.TRACK_LIST_REQ:
				HandleTrackListRequest(sender, ctx);
				break;

			case UnesennyeConstants.RADIO_PLAY:
				HandleRadioPlay(sender, ctx);
				break;

			case UnesennyeConstants.RADIO_STOP:
				HandleRadioStop(sender, ctx);
				break;

			// ==================== РАЦИИ ====================
			case UnesennyeConstants.RADIO_INSERT_CARD:
				HandleRadioInsertCard(sender, ctx);
				break;

			case UnesennyeConstants.RADIO_EJECT_CARD:
				HandleRadioEjectCard(sender, ctx);
				break;

			case UnesennyeConstants.RADIO_PLAY_TRACK:
				HandleRadioPlayTrack(sender, ctx);
				break;

			case UnesennyeConstants.RADIO_STOP_TRACK:
				HandleRadioStopTrack(sender, ctx);
				break;

			// ==================== АЛЬБОМЫ ====================
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
				// Unknown RPC - silently ignore to avoid crashes
				break;
		}
	}

	// ==================== HANDSHAKE ====================
	protected void HandleHandshake(PlayerIdentity identity)
	{
		UnesennyeAuth.GrantAccess(identity);
		GetGame().RPCSingleParam(null, UnesennyeConstants.HS_RESPONSE, null, true, identity);
	}

	// ==================== АВТО ====================
	protected void HandleTrackListRequest(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		// Example response - replace with real track list from config / music_db
		Param1<string> response = new Param1<string>("track_01,track_02,track_03");
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

		// Broadcast to nearby players
		Param1<string> broadcast = new Param1<string>(soundSet);
		GetGame().RPCSingleParam(null, UnesennyeConstants.BROADCAST_PLAY, broadcast, true, null);
	}

	protected void HandleRadioStop(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		Print("[Unesennye Server] RADIO_STOP by " + identity.GetName());
		GetGame().RPCSingleParam(null, UnesennyeConstants.BROADCAST_STOP, null, true, null);
	}

	// ==================== РАЦИИ ====================
	protected void HandleRadioInsertCard(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;
		Print("[Unesennye Server] RADIO_INSERT_CARD by " + identity.GetName());
	}

	protected void HandleRadioEjectCard(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;
		Print("[Unesennye Server] RADIO_EJECT_CARD by " + identity.GetName());
	}

	protected void HandleRadioPlayTrack(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		Param1<string> data;
		if (!ctx.Read(data))
			return;

		string track = data.param1;
		Print("[Unesennye Server] RADIO_PLAY_TRACK by " + identity.GetName() + " -> " + track);

		Param1<string> broadcast = new Param1<string>(track);
		GetGame().RPCSingleParam(null, UnesennyeConstants.RADIO_BROADCAST, broadcast, true, null);
	}

	protected void HandleRadioStopTrack(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		GetGame().RPCSingleParam(null, UnesennyeConstants.RADIO_BROADCAST_STOP, null, true, null);
	}

	// ==================== АЛЬБОМЫ ====================
	protected void HandleAlbumNext(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;
		Print("[Unesennye Server] ALBUM_NEXT_TRACK by " + identity.GetName());
	}

	protected void HandleAlbumPrev(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;
		Print("[Unesennye Server] ALBUM_PREV_TRACK by " + identity.GetName());
	}

	protected void HandleAlbumSetTrack(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
			return;

		Param1<string> data;
		if (!ctx.Read(data))
			return;

		string track = data.param1;
		Print("[Unesennye Server] ALBUM_SET_TRACK by " + identity.GetName() + " -> " + track);

		Param1<string> broadcast = new Param1<string>(track);
		GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_BROADCAST, broadcast, true, null);
	}

	protected void HandleAlbumGetTracklist(PlayerIdentity identity, ParamsReadContext ctx)
	{
		if (!UnesennyeAuth.IsAuthorized(identity))
		{
			GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_REJECT, null, true, identity);
			return;
		}

		// Example response
		Param1<string> response = new Param1<string>("album_01_track_01,album_01_track_02,album_01_track_03");
		GetGame().RPCSingleParam(null, UnesennyeConstants.ALBUM_TRACKLIST_RESP, response, true, identity);
	}
};
