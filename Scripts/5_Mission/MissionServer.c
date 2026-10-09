// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.4
// Do not remove this header. Unauthorized redistribution is prohibited.

modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		UnesennyeServerManager.GetInstance();
		Print("[Unesennye Server] MissionServer.OnInit | Author: KRa Tos (Константин) | v" + UnesennyeConstants.MOD_VERSION);
	}

	override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		UnesennyeServerManager.GetInstance().OnRPC(sender, target, rpc_type, ctx);
		super.OnRPC(sender, target, rpc_type, ctx);
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);
	}

	override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
	{
		UnesennyeServerManager.GetInstance().OnPlayerDisconnected(identity);
		super.PlayerDisconnected(player, identity, uid);
	}
};
