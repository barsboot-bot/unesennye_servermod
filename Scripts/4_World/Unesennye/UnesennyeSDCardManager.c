// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.3
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeSDCardManager
{
	protected static ref map<string, int> m_InsertedPlaylistId = new map<string, int>;
	protected static ref map<string, string> m_InsertedCardClass = new map<string, string>;

	static string MakeKey(PlayerIdentity identity, Object target)
	{
		if (!identity) return "";
		string key = identity.GetId();
		if (target)
		{
			int low, high;
			target.GetNetworkID(low, high);
			key = key + "_" + low.ToString() + "_" + high.ToString();
		}
		return key;
	}

	static bool IsValidMediaClass(string cardClass)
	{
		return cardClass == UnesennyeConstants.SD_CARD_CLASS
			|| cardClass == UnesennyeConstants.SD_CARD_EMPTY
			|| cardClass == UnesennyeConstants.CASSETTE_CLASS
			|| cardClass == UnesennyeConstants.DISK_CLASS
			|| cardClass == UnesennyeConstants.CD_CLASS
			|| cardClass == UnesennyeConstants.DVD_CLASS
			|| cardClass == UnesennyeConstants.DVD_R_CLASS;
	}

	static bool ValidateAttachedMedia(Object target, out int playlistId, out string cardClass)
	{
		playlistId = 0;
		cardClass = "";
		if (!target) return false;

		EntityAI ent = EntityAI.Cast(target);
		if (!ent) return false;

		EntityAI att = ent.FindAttachmentBySlotName(UnesennyeConstants.SD_SLOT_NAME);
		if (!att) return false;

		cardClass = att.GetType();
		if (!IsValidMediaClass(cardClass))
			return false;

		playlistId = att.GetQuantity();
		if (playlistId < 0) playlistId = 0;
		return true;
	}

	static void InsertCard(PlayerIdentity identity, Object target, int playlistId, string cardClassName)
	{
		string key = MakeKey(identity, target);
		if (key == "") return;
		m_InsertedPlaylistId.Set(key, playlistId);
		m_InsertedCardClass.Set(key, cardClassName);
		UnesennyeLogger.Log("MEDIA INSERT " + identity.GetName() + " playlist=" + playlistId.ToString() + " class=" + cardClassName);

		if (UnesennyeConfig.Get().DiscordSDInsert)
			UnesennyeDiscordWebhook.NotifySDInsert(identity.GetName(), playlistId);
	}

	static void EjectCard(PlayerIdentity identity, Object target)
	{
		string key = MakeKey(identity, target);
		if (key == "") return;
		if (m_InsertedPlaylistId.Contains(key))
		{
			m_InsertedPlaylistId.Remove(key);
			m_InsertedCardClass.Remove(key);
			UnesennyeLogger.Log("MEDIA EJECT " + identity.GetName());
		}
	}

	static bool HasCard(PlayerIdentity identity, Object target)
	{
		int pid;
		string cc;
		if (ValidateAttachedMedia(target, pid, cc))
			return true;

		string key = MakeKey(identity, target);
		return m_InsertedPlaylistId.Contains(key);
	}

	static int GetPlaylistId(PlayerIdentity identity, Object target)
	{
		int pid;
		string cc;
		if (ValidateAttachedMedia(target, pid, cc))
			return pid;

		string key = MakeKey(identity, target);
		if (m_InsertedPlaylistId.Contains(key))
			return m_InsertedPlaylistId.Get(key);
		return 0;
	}

	static void ClearForPlayer(PlayerIdentity identity)
	{
		if (!identity) return;
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
