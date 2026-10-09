// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeAuth
{
	protected static ref map<string, bool> m_AuthorizedPlayers = new map<string, bool>;

	static void GrantAccess(PlayerIdentity identity)
	{
		if (!identity) return;
		string uid = identity.GetId();
		m_AuthorizedPlayers.Set(uid, true);
		UnesennyeLogger.Log("Handshake GRANTED " + identity.GetName() + " (" + uid + ")");
	}

	static void RevokeAccess(PlayerIdentity identity)
	{
		if (!identity) return;
		string uid = identity.GetId();
		if (m_AuthorizedPlayers.Contains(uid))
		{
			m_AuthorizedPlayers.Remove(uid);
			UnesennyeLogger.Log("Access REVOKED " + identity.GetName());
		}
	}

	static bool IsAuthorized(PlayerIdentity identity)
	{
		if (!identity) return false;
		string uid = identity.GetId();
		return m_AuthorizedPlayers.Contains(uid) && m_AuthorizedPlayers.Get(uid);
	}

	static void ClearAll()
	{
		m_AuthorizedPlayers.Clear();
	}
};
