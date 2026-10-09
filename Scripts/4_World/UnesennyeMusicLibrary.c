// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.4
// Do not remove this header. Unauthorized redistribution is prohibited.

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

		// Built-in default playlists (match music_db SoundSets).
		// Admins can call RegisterPlaylist() from their own scripts to add more.
		RegisterDefaultPlaylists();

		m_Loaded = true;
		Print("[Unesennye Server] MusicLibrary loaded | playlists=" + m_Playlists.Count().ToString() + " | Author: " + UnesennyeConstants.AUTHOR);
	}

	protected static void RegisterDefaultPlaylists()
	{
		array<string> p1 = new array<string>;
		p1.Insert("track_01.ogg");
		p1.Insert("track_02.ogg");
		RegisterPlaylist(1, "SD Playlist 01", p1);

		array<string> p2 = new array<string>;
		p2.Insert("track_01.ogg");
		RegisterPlaylist(2, "SD Playlist 02", p2);
	}

	static void RegisterPlaylist(int id, string displayName, array<string> tracks)
	{
		if (id <= 0)
			return;

		ref array<string> copy = new array<string>;
		for (int i = 0; i < tracks.Count(); i++)
		{
			copy.Insert(tracks.Get(i));
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
		for (int i = 0; i < tracks.Count(); i++)
		{
			if (i > 0)
				result = result + ",";
			result = result + tracks.Get(i);
		}
		return result;
	}

	static string GetSoundSetName(int playlistId, int trackIndex)
	{
		string idStr = playlistId.ToString();
		if (playlistId < 10)
			idStr = "0" + idStr;

		int n = trackIndex + 1;
		string trackStr = n.ToString();
		if (n < 10)
			trackStr = "0" + trackStr;

		return "Unesennye_SD_" + idStr + "_Track_" + trackStr + "_SoundSet";
	}

	static void Clear()
	{
		m_Playlists.Clear();
		m_PlaylistNames.Clear();
		m_Loaded = false;
	}
};
