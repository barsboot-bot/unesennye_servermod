# UNESENNYE SERVER v1.3.0

**Author:** KRa Tos (Константин)

## New in 1.3.0
- `$profile:Unesennye/config.json` (Discord flags, radius, whitelist)
- File log `$profile:Unesennye/server.log`
- Discord: start, connect, disconnect, SD insert (no passwords)
- SD slot validation on server
- Album next/prev queue
- Broadcast only within radius
- Playlist whitelist option
- Scripts under `Unesennye/` subfolders

## Config example
```json
{
  "DiscordEnabled": true,
  "BroadcastRadius": 80.0,
  "PlaylistWhitelistEnabled": false,
  "PlaylistWhitelist": [1, 2],
  "FileLogEnabled": true
}
```
