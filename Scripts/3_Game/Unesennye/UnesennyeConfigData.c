// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeConfigData
{
	bool DiscordEnabled = true;
	bool DiscordPlayerConnect = true;
	bool DiscordPlayerDisconnect = true;
	bool DiscordSDInsert = true;
	bool DiscordHandshakeFail = false;

	float BroadcastRadius = 80.0;
	int HandshakeTimeoutMs = 4000;

	bool PlaylistWhitelistEnabled = false;
	ref array<int> PlaylistWhitelist;

	bool FileLogEnabled = true;

	void UnesennyeConfigData()
	{
		PlaylistWhitelist = new array<int>;
		PlaylistWhitelist.Insert(1);
		PlaylistWhitelist.Insert(2);
	}
};
