# UNESENNYE MUSIC SYSTEM v1.2.5 — Server Mod

**Author:** KRa Tos (Константин)  
**Version:** 1.2.5

## Discord webhook (safe)

On server start the mod can post to Discord:

- server hostname
- mod version
- author

**Passwords and admin credentials are never sent.**

### Setup

1. Create a Discord webhook in your channel settings.
2. On the game server, open (or let the mod create):

```
<server_profile>/Unesennye/discord_webhook.txt
```

3. Put **only** the webhook URL on a non-comment line:

```
https://discord.com/api/webhooks/ID/TOKEN
```

4. Restart the server.

If the file is empty or missing a URL, Discord notifications stay disabled.

## Launch

```
-mod=@unesennye_servermod;@unesennye_music_db;@unesennye
```

**Author:** KRa Tos (Константин)
