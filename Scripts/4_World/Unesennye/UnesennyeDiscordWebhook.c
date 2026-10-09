// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
// Do not remove this header. Unauthorized redistribution is prohibited.
// Safe Discord only — never passwords or credentials.

class UnesennyeDiscordCallback : RestCallback
{
	override void OnSuccess(string data, int dataSize) { UnesennyeLogger.Log("Discord OK"); }
	override void OnError(int errorCode) { UnesennyeLogger.Log("Discord error " + errorCode.ToString()); }
	override void OnTimeout() { UnesennyeLogger.Log("Discord timeout"); }
};

class UnesennyeDiscordWebhook
{
	protected static string m_WebhookUrl = "";
	protected static bool m_Loaded = false;

	static void LoadConfig()
	{
		if (m_Loaded) return;
		m_Loaded = true;
		m_WebhookUrl = "";
		if (!FileExist(UnesennyeConstants.PROFILE_DIR))
			MakeDirectory(UnesennyeConstants.PROFILE_DIR);

		string path = UnesennyeConstants.DISCORD_CFG_FILE;
		if (!FileExist(path))
		{
			FileHandle tmpl = OpenFile(path, FileMode.WRITE);
			if (tmpl != 0)
			{
				FPrintln(tmpl, "# Unesennye Discord Webhook — paste URL below. No passwords.");
				FPrintln(tmpl, "");
				CloseFile(tmpl);
			}
			return;
		}

		FileHandle file = OpenFile(path, FileMode.READ);
		if (file == 0) return;
		string line;
		while (FGets(file, line) >= 0)
		{
			line = line.Trim();
			if (line == "" || line.IndexOf("#") == 0) continue;
			if (line.IndexOf("https://") == 0 || line.IndexOf("http://") == 0)
			{
				m_WebhookUrl = line;
				break;
			}
		}
		CloseFile(file);
	}

	static bool IsEnabled()
	{
		LoadConfig();
		if (m_WebhookUrl == "") return false;
		if (UnesennyeConfig.Get() && !UnesennyeConfig.Get().DiscordEnabled) return false;
		return true;
	}

	static string EscapeJson(string s)
	{
		string outStr = s;
		outStr.Replace("\\", "\\\\");
		outStr.Replace("\"", "\\\"");
		outStr.Replace("\n", "\\n");
		outStr.Replace("\r", "");
		return outStr;
	}

	static void SendEmbed(string title, string description, int color, string fieldName, string fieldValue)
	{
		if (!IsEnabled()) return;

		string json = "{\"username\":\"Unesennye\",\"embeds\":[{";
		json = json + "\"title\":\"" + EscapeJson(title) + "\",";
		json = json + "\"description\":\"" + EscapeJson(description) + "\",";
		json = json + "\"color\":" + color.ToString() + ",";
		json = json + "\"fields\":[{\"name\":\"" + EscapeJson(fieldName) + "\",\"value\":\"" + EscapeJson(fieldValue) + "\",\"inline\":true}]";
		json = json + "}]}";

		RestApi api = GetRestApi();
		if (!api) api = CreateRestApi();
		if (!api) return;
		RestContext ctx = api.GetRestContext(m_WebhookUrl);
		if (!ctx) return;
		ctx.SetHeader("application/json");
		ctx.POST(new UnesennyeDiscordCallback(), "", json);
	}

	static void NotifyServerStart()
	{
		string hostname = GetGame().GetHostName();
		if (hostname == "") hostname = "DayZ Server";
		SendEmbed("Server Started", "Unesennye v" + UnesennyeConstants.MOD_VERSION, 5763719, "Server", hostname);
	}

	static void NotifyPlayerConnect(string name)
	{
		if (!UnesennyeConfig.Get().DiscordPlayerConnect) return;
		SendEmbed("Player Connected", name, 3066993, "Player", name);
	}

	static void NotifyPlayerDisconnect(string name)
	{
		if (!UnesennyeConfig.Get().DiscordPlayerDisconnect) return;
		SendEmbed("Player Disconnected", name, 15158332, "Player", name);
	}

	static void NotifySDInsert(string name, int playlistId)
	{
		if (!UnesennyeConfig.Get().DiscordSDInsert) return;
		SendEmbed("SD Card Inserted", name + " playlist " + playlistId.ToString(), 3447003, "Player", name);
	}
};
