// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.2
// Do not remove this header. Unauthorized redistribution is prohibited.

// Простая серверная библиотека плейлистов.
// Читает meta.txt, сгенерированные generate_music_meta.bat,
// и отдаёт список треков по ID (для SD-карт и альбомов).
class UnesennyeMusicLibrary
{
	protected static ref map<int, ref array<string>> m_Playlists = new map<int, ref array<string>>;
	protected static ref map<int, string> m_PlaylistNames = new map<int, string>;
	protected static bool m_Loaded = false;

	static void LoadFromProfile()
	{
		if (m_Loaded)
			return;

		m_Playlists.Clear();
		m_PlaylistNames.Clear();

		// Путь относительно профиля сервера
		string root = "$profile:" + UnesennyeConstants.MUSIC_ROOT_DEFAULT;

		// Пытаемся загрузить sd_playlists (числовые ID)
		LoadFolder(root + "/sd_playlists");
		LoadFolder(root + "/Type");
		LoadFolder(root + "/CD");

		m_Loaded = true;
		Print("[Unesennye Server] MusicLibrary loaded | playlists=" + m_Playlists.Count().ToString() + " | Author: " + UnesennyeConstants.AUTHOR);
	}

	protected static void LoadFolder(string folderPath)
	{
		// В Enforce нет полноценного обхода директорий на сервере без расширений.
		// Поэтому ожидаем, что администратор заранее сгенерировал meta.txt
		// и прописал известные ID через конфиг или этот метод вызывается
		// после ручной регистрации.
		// Для полноценного авто-скана используйте generate_music_meta.bat
		// + внешний Python/HTTP прокси (как в полном Unesennye-Mod).

		// Здесь реализован минимальный API для ручной/полуавтоматической регистрации.
	}

	// Регистрация плейлиста вручную или из результата bat-скрипта
	static void RegisterPlaylist(int id, string displayName, array<string> tracks)
	{
		if (id <= 0)
			return;

		ref array<string> copy = new array<string>;
		foreach (string t : tracks)
		{
			copy.Insert(t);
		}

		m_Playlists.Set(id, copy);
		m_PlaylistNames.Set(id, displayName);

		Print("[Unesennye Server] Playlist registered id=" + id.ToString() + " name=" + displayName + " tracks=" + tracks.Count().ToString());
	}

	static bool HasPlaylist(int id)
	{
		return m_Playlists.Contains(id);
	}

	static string GetPlaylistName(int id)
	{
		if (m_PlaylistNames.Contains(id))
			return m_PlaylistNames.Get(id);
		return "Unknown";
	}

	static array<string> GetTracks(int id)
	{
		if (m_Playlists.Contains(id))
			return m_Playlists.Get(id);
		return new array<string>;
	}

	static string GetTracksAsString(int id)
	{
		array<string> tracks = GetTracks(id);
		string result = "";
		foreach (int i, string t : tracks)
		{
			if (i > 0)
				result += ",";
			result += t;
		}
		return result;
	}

	static void Clear()
	{
		m_Playlists.Clear();
		m_PlaylistNames.Clear();
		m_Loaded = false;
	}
};
