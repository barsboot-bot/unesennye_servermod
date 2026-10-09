// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeAlbumQueue
{
	protected static ref map<string, int> m_TrackIndex = new map<string, int>;
	protected static ref map<string, int> m_PlaylistId = new map<string, int>;

	static string Key(PlayerIdentity identity)
	{
		if (!identity) return "";
		return identity.GetId();
	}

	static void SetPlaylist(PlayerIdentity identity, int playlistId)
	{
		string k = Key(identity);
		if (k == "") return;
		m_PlaylistId.Set(k, playlistId);
		m_TrackIndex.Set(k, 0);
	}

	static int GetPlaylist(PlayerIdentity identity)
	{
		string k = Key(identity);
		if (m_PlaylistId.Contains(k)) return m_PlaylistId.Get(k);
		return 1;
	}

	static int GetIndex(PlayerIdentity identity)
	{
		string k = Key(identity);
		if (m_TrackIndex.Contains(k)) return m_TrackIndex.Get(k);
		return 0;
	}

	static void SetIndex(PlayerIdentity identity, int idx)
	{
		string k = Key(identity);
		if (k == "") return;
		m_TrackIndex.Set(k, idx);
	}

	static int Next(PlayerIdentity identity)
	{
		int pid = GetPlaylist(identity);
		array<string> tracks = UnesennyeMusicLibrary.GetTracks(pid);
		if (tracks.Count() == 0) return 0;
		int idx = GetIndex(identity) + 1;
		if (idx >= tracks.Count()) idx = 0;
		SetIndex(identity, idx);
		return idx;
	}

	static int Prev(PlayerIdentity identity)
	{
		int pid = GetPlaylist(identity);
		array<string> tracks = UnesennyeMusicLibrary.GetTracks(pid);
		if (tracks.Count() == 0) return 0;
		int idx = GetIndex(identity) - 1;
		if (idx < 0) idx = tracks.Count() - 1;
		SetIndex(identity, idx);
		return idx;
	}

	static void ClearPlayer(PlayerIdentity identity)
	{
		string k = Key(identity);
		if (k == "") return;
		m_TrackIndex.Remove(k);
		m_PlaylistId.Remove(k);
	}
};
