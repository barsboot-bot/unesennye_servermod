// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.0
// Do not remove this header. Unauthorized redistribution is prohibited.

modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		UnesennyeServerManager.GetInstance();
		Print("[Unesennye Server] MissionServer.OnInit | Author: KRa Tos (Константин) | v" + UnesennyeConstants.MOD_VERSION);
	}

	// CRITICAL: This is the entry point for all custom RPCs from clients
	override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		// Let our handler process first
		UnesennyeServerManager.GetInstance().OnRPC(sender, target, rpc_type, ctx);

		// Always call super so vanilla / other mods still receive RPCs
		super.OnRPC(sender, target, rpc_type, ctx);
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);
		// Client will send HS_REQUEST after world load
	}

	override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
	{
		UnesennyeServerManager.GetInstance().OnPlayerDisconnected(identity);
		super.PlayerDisconnected(player, identity, uid);
	}
};
