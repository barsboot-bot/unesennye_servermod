// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeServerManager
{
	protected static ref UnesennyeServerManager m_Instance;
	protected ref UnesennyeRPCHandler m_RPCHandler;

	static UnesennyeServerManager GetInstance()
	{
		if (!m_Instance) m_Instance = new UnesennyeServerManager();
		return m_Instance;
	}

	void UnesennyeServerManager()
	{
		UnesennyeConfig.Load();
		m_RPCHandler = new UnesennyeRPCHandler();
		UnesennyeMusicLibrary.LoadFromProfile();
		UnesennyeDiscordWebhook.LoadConfig();
		UnesennyeLogger.Log("Manager v" + UnesennyeConstants.MOD_VERSION + " | " + UnesennyeConstants.AUTHOR);
	}

	void NotifyStartup()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SendStartupDiscord, 3000, false);
	}

	void SendStartupDiscord()
	{
		UnesennyeDiscordWebhook.NotifyServerStart();
	}

	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		if (m_RPCHandler) m_RPCHandler.OnRPC(sender, target, rpc_type, ctx);
	}

	void OnPlayerConnected(PlayerIdentity identity)
	{
		if (identity)
			UnesennyeDiscordWebhook.NotifyPlayerConnect(identity.GetName());
	}

	void OnPlayerDisconnected(PlayerIdentity identity)
	{
		if (identity)
			UnesennyeDiscordWebhook.NotifyPlayerDisconnect(identity.GetName());
		UnesennyeAuth.RevokeAccess(identity);
		UnesennyeSDCardManager.ClearForPlayer(identity);
		UnesennyeAlbumQueue.ClearPlayer(identity);
	}
};
