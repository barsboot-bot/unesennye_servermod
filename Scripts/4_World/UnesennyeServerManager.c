// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.4
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeServerManager
{
	protected static ref UnesennyeServerManager m_Instance;
	protected ref UnesennyeRPCHandler m_RPCHandler;

	static UnesennyeServerManager GetInstance()
	{
		if (!m_Instance)
			m_Instance = new UnesennyeServerManager();
		return m_Instance;
	}

	void UnesennyeServerManager()
	{
		m_RPCHandler = new UnesennyeRPCHandler();
		UnesennyeMusicLibrary.LoadFromProfile();
		Print("[Unesennye Server] Manager initialized | Version: " + UnesennyeConstants.MOD_VERSION + " | Author: " + UnesennyeConstants.AUTHOR);
	}

	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		if (m_RPCHandler)
			m_RPCHandler.OnRPC(sender, target, rpc_type, ctx);
	}

	void OnPlayerDisconnected(PlayerIdentity identity)
	{
		UnesennyeAuth.RevokeAccess(identity);
		UnesennyeSDCardManager.ClearForPlayer(identity);
	}

	void OnServerShutdown()
	{
		UnesennyeAuth.ClearAll();
		UnesennyeSDCardManager.ClearAll();
		UnesennyeMusicLibrary.Clear();
		Print("[Unesennye Server] Shutdown complete. Author: " + UnesennyeConstants.AUTHOR);
	}
};
