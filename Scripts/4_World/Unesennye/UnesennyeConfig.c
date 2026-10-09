// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeConfig
{
	protected static ref UnesennyeConfigData m_Data;

	static UnesennyeConfigData Get()
	{
		if (!m_Data)
			Load();
		return m_Data;
	}

	static void Load()
	{
		m_Data = new UnesennyeConfigData();

		if (!FileExist(UnesennyeConstants.PROFILE_DIR))
			MakeDirectory(UnesennyeConstants.PROFILE_DIR);

		string path = UnesennyeConstants.CONFIG_FILE;
		if (FileExist(path))
		{
			JsonFileLoader<UnesennyeConfigData>.JsonLoadFile(path, m_Data);
			UnesennyeLogger.Log("Config loaded from " + path);
		}
		else
		{
			JsonFileLoader<UnesennyeConfigData>.JsonSaveFile(path, m_Data);
			UnesennyeLogger.Log("Config created: " + path);
		}

		if (!m_Data.PlaylistWhitelist)
			m_Data.PlaylistWhitelist = new array<int>;
	}

	static bool IsPlaylistAllowed(int id)
	{
		UnesennyeConfigData cfg = Get();
		if (!cfg.PlaylistWhitelistEnabled)
			return true;

		for (int i = 0; i < cfg.PlaylistWhitelist.Count(); i++)
		{
			if (cfg.PlaylistWhitelist.Get(i) == id)
				return true;
		}
		return false;
	}
};
