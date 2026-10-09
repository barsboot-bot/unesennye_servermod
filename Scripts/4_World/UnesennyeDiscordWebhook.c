// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.5
// Do not remove this header. Unauthorized redistribution is prohibited.
//
// Safe Discord notifications only:
//   - server hostname
//   - mod version
//   - start time
// NEVER send passwords, admin credentials, or other secrets.

class UnesennyeDiscordCallback : RestCallback
{
	override void OnSuccess(string data, int dataSize)
	{
		Print("[Unesennye Server] Discord webhook: message sent OK");
	}

	override void OnError(int errorCode)
	{
		Print("[Unesennye Server] Discord webhook error code: " + errorCode.ToString());
	}

	override void OnTimeout()
	{
		Print("[Unesennye Server] Discord webhook timeout");
	}
};

class UnesennyeDiscordWebhook
{
	protected static string m_WebhookUrl = "";
	protected static bool m_Loaded = false;

	static void LoadConfig()
	{
		if (m_Loaded)
			return;

		m_Loaded = true;
		m_WebhookUrl = "";

		// Ensure profile folder exists
		if (!FileExist(UnesennyeConstants.DISCORD_CFG_DIR))
		{
			MakeDirectory(UnesennyeConstants.DISCORD_CFG_DIR);
		}

		string path = UnesennyeConstants.DISCORD_CFG_FILE;

		if (!FileExist(path))
		{
			// Create empty template so admin knows where to put the URL
			FileHandle tmpl = OpenFile(path, FileMode.WRITE);
			if (tmpl != 0)
			{
				FPrintln(tmpl, "# Unesennye Discord Webhook");
				FPrintln(tmpl, "# Paste your Discord webhook URL on the next line (no quotes).");
				FPrintln(tmpl, "# Example: https://discord.com/api/webhooks/ID/TOKEN");
				FPrintln(tmpl, "# Leave empty to disable. NEVER put passwords in this file.");
				FPrintln(tmpl, "");
				CloseFile(tmpl);
				Print("[Unesennye Server] Created Discord config template: " + path);
			}
			return;
		}

		FileHandle file = OpenFile(path, FileMode.READ);
		if (file == 0)
		{
			Print("[Unesennye Server] Cannot read Discord config: " + path);
			return;
		}

		string line;
		while (FGets(file, line) >= 0)
		{
			line = line.Trim();
			if (line == "")
				continue;
			if (line.IndexOf("#") == 0)
				continue;

			// First non-comment line = webhook URL
			if (line.IndexOf("https://") == 0 || line.IndexOf("http://") == 0)
			{
				m_WebhookUrl = line;
				break;
			}
		}
		CloseFile(file);

		if (m_WebhookUrl != "")
			Print("[Unesennye Server] Discord webhook loaded (URL hidden in log)");
		else
			Print("[Unesennye Server] Discord webhook disabled (empty config)");
	}

	static bool IsEnabled()
	{
		LoadConfig();
		return m_WebhookUrl != "";
	}

	static string EscapeJson(string s)
	{
		if (s == "")
			return "";

		string outStr = s;
		outStr.Replace("\\", "\\\\");
		outStr.Replace("\"", "\\\"");
		outStr.Replace("\n", "\\n");
		outStr.Replace("\r", "");
		outStr.Replace("\t", " ");
		return outStr;
	}

	static void NotifyServerStart()
	{
		if (!IsEnabled())
			return;

		string hostname = GetGame().GetHostName();
		if (hostname == "")
			hostname = "DayZ Server";

		// Safe payload only — no passwords, no admin credentials
		string title = "Unesennye Server Started";
		string desc = "Server is online.";
		int color = 5763719; // green

		string json = "{";
		json = json + "\"username\":\"Unesennye\",";
		json = json + "\"embeds\":[{";
		json = json + "\"title\":\"" + EscapeJson(title) + "\",";
		json = json + "\"description\":\"" + EscapeJson(desc) + "\",";
		json = json + "\"color\":" + color.ToString() + ",";
		json = json + "\"fields\":[";
		json = json + "{\"name\":\"Server\",\"value\":\"" + EscapeJson(hostname) + "\",\"inline\":true},";
		json = json + "{\"name\":\"Mod\",\"value\":\"Unesennye v" + EscapeJson(UnesennyeConstants.MOD_VERSION) + "\",\"inline\":true},";
		json = json + "{\"name\":\"Author\",\"value\":\"" + EscapeJson(UnesennyeConstants.AUTHOR) + "\",\"inline\":true}";
		json = json + "],";
		json = json + "\"footer\":{\"text\":\"Unesennye Music System — no credentials are sent\"}";
		json = json + "}]}";

		RestApi api = GetRestApi();
		if (!api)
			api = CreateRestApi();

		if (!api)
		{
			Print("[Unesennye Server] Discord: RestApi unavailable");
			return;
		}

		RestContext ctx = api.GetRestContext(m_WebhookUrl);
		if (!ctx)
		{
			Print("[Unesennye Server] Discord: RestContext failed");
			return;
		}

		ctx.SetHeader("application/json");
		ctx.POST(new UnesennyeDiscordCallback(), "", json);
		Print("[Unesennye Server] Discord webhook: start notification queued");
	}
};
