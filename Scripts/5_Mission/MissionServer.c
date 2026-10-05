// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.0
// Do not remove this header. Unauthorized redistribution is prohibited.

modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		UnesennyeServerManager.GetInstance();
		Print("[Unesennye Server] MissionServer initialized | Author: KRa Tos (Константин)");
	}

	override void OnEvent(EventType eventTypeId, Param params)
	{
		super.OnEvent(eventTypeId, params);

		// Standard DayZ RPC routing can be extended here if needed
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);
		// Client will initiate Handshake after world load
	}

	override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
	{
		UnesennyeServerManager.GetInstance().OnPlayerDisconnected(identity);
		super.PlayerDisconnected(player, identity, uid);
	}
};
