// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.4
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeSDCardManager
{
	protected static ref map<string, int> m_InsertedPlaylistId = new map<string, int>;
	protected static ref map<string, string> m_InsertedCardClass = new map<string, string>;

	static string MakeKey(PlayerIdentity identity, Object target)
	{
		if (!identity)
			return "";

		string key = identity.GetId();
		if (target)
		{
			// Use low+high network ID for stability across sessions
			int low = 0;
			int high = 0;
			target.GetNetworkID(low, high);
			key = key + "_" + low.ToString() + "_" + high.ToString();
		}
		return key;
	}

	static void InsertCard(PlayerIdentity identity, Object target, int playlistId, string cardClassName)
	{
		string key = MakeKey(identity, target);
		if (key == "")
			return;

		m_InsertedPlaylistId.Set(key, playlistId);
		m_InsertedCardClass.Set(key, cardClassName);
		Print("[Unesennye Server] SD Card INSERT by " + identity.GetName() + " | playlistId=" + playlistId.ToString() + " | class=" + cardClassName);
	}

	static void EjectCard(PlayerIdentity identity, Object target)
	{
		string key = MakeKey(identity, target);
		if (key == "")
			return;

		if (m_InsertedPlaylistId.Contains(key))
		{
			m_InsertedPlaylistId.Remove(key);
			m_InsertedCardClass.Remove(key);
			Print("[Unesennye Server] SD Card EJECT by " + identity.GetName());
		}
	}

	static bool HasCard(PlayerIdentity identity, Object target)
	{
		string key = MakeKey(identity, target);
		return m_InsertedPlaylistId.Contains(key);
	}

	static int GetPlaylistId(PlayerIdentity identity, Object target)
	{
		string key = MakeKey(identity, target);
		if (m_InsertedPlaylistId.Contains(key))
			return m_InsertedPlaylistId.Get(key);
		return 0;
	}

	static void ClearForPlayer(PlayerIdentity identity)
	{
		if (!identity)
			return;

		string uid = identity.GetId();
		array<string> toRemove = new array<string>;

		for (int i = 0; i < m_InsertedPlaylistId.Count(); i++)
		{
			string key = m_InsertedPlaylistId.GetKey(i);
			if (key.IndexOf(uid) == 0)
				toRemove.Insert(key);
		}

		for (int j = 0; j < toRemove.Count(); j++)
		{
			string k = toRemove.Get(j);
			m_InsertedPlaylistId.Remove(k);
			m_InsertedCardClass.Remove(k);
		}
	}

	static void ClearAll()
	{
		m_InsertedPlaylistId.Clear();
		m_InsertedCardClass.Clear();
	}
};
