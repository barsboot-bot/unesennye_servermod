// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeConstants
{
	static const int HS_REQUEST            = 100;
	static const int HS_RESPONSE           = 200;
	static const int AUTH_FAIL             = 201;

	static const int HS_TIMEOUT_MS         = 4000;
	static const int HS_CHECK_INTERVAL     = 500;

	static const int TRACK_LIST_REQ        = 101;
	static const int RADIO_PLAY            = 102;
	static const int RADIO_STOP            = 103;
	static const int TRACK_LIST_RESP       = 202;
	static const int BROADCAST_PLAY        = 203;
	static const int BROADCAST_STOP        = 204;

	static const int RADIO_INSERT_CARD     = 300;
	static const int RADIO_EJECT_CARD      = 301;
	static const int RADIO_PLAY_TRACK      = 302;
	static const int RADIO_STOP_TRACK      = 303;
	static const int RADIO_BROADCAST       = 304;
	static const int RADIO_BROADCAST_STOP  = 305;

	static const int ALBUM_NEXT_TRACK      = 400;
	static const int ALBUM_PREV_TRACK      = 401;
	static const int ALBUM_SET_TRACK       = 402;
	static const int ALBUM_GET_TRACKLIST   = 403;
	static const int ALBUM_BROADCAST       = 404;
	static const int ALBUM_TRACKLIST_RESP  = 405;
	static const int ALBUM_REJECT          = 406;

	static const string SD_CARD_CLASS      = "Unesennye_SD_Card";
	static const string SD_CARD_EMPTY     = "Unesennye_SD_Card_Empty";
	static const string SD_SLOT_NAME      = "Unesennye_SDCard";
	static const string CASSETTE_CLASS    = "Unesennye_Cassette";
	static const string DISK_CLASS        = "Unesennye_Disk";

	static const string PROFILE_DIR       = "$profile:Unesennye";
	static const string CONFIG_FILE       = "$profile:Unesennye/config.json";
	static const string LOG_FILE          = "$profile:Unesennye/server.log";
	static const string DISCORD_CFG_FILE  = "$profile:Unesennye/discord_webhook.txt";

	static const string DISCONNECT_MSG = "Error: Required server mod 'unesennye_servermod' is missing.";
	static const string AUTHOR         = "KRa Tos (Константин)";
	static const string MOD_VERSION    = "1.3.0";
	static const string MOD_NAME       = "unesennye_servermod";
};
