// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.4
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeAuth
{
	protected static ref map<string, bool> m_AuthorizedPlayers = new map<string, bool>;

	static void GrantAccess(PlayerIdentity identity)
	{
		if (!identity)
			return;

		string uid = identity.GetId();
		m_AuthorizedPlayers.Set(uid, true);
		Print("[Unesennye Server] Handshake GRANTED to " + identity.GetName() + " (" + uid + ") | Author: " + UnesennyeConstants.AUTHOR);
	}

	static void RevokeAccess(PlayerIdentity identity)
	{
		if (!identity)
			return;

		string uid = identity.GetId();
		if (m_AuthorizedPlayers.Contains(uid))
		{
			m_AuthorizedPlayers.Remove(uid);
			Print("[Unesennye Server] Access REVOKED for " + identity.GetName());
		}
	}

	static bool IsAuthorized(PlayerIdentity identity)
	{
		if (!identity)
			return false;

		string uid = identity.GetId();
		return m_AuthorizedPlayers.Contains(uid) && m_AuthorizedPlayers.Get(uid);
	}

	static void ClearAll()
	{
		m_AuthorizedPlayers.Clear();
	}

	static int GetAuthorizedCount()
	{
		return m_AuthorizedPlayers.Count();
	}
};
