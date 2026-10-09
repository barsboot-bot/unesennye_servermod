# UNESENNYE SERVER v1.3.0

**Автор:** KRa Tos (Константин)

Серверный мод системы музыки Unesennye. Обязателен для работы клиентского мода (handshake).

## Что нового в 1.3.0

- `$profile:Unesennye/config.json` — Discord, радиус вещания, whitelist плейлистов
- Файловый лог `$profile:Unesennye/server.log`
- Discord: старт сервера, вход/выход игроков, вставка SD (без паролей)
- Проверка SD-карты в слоте на сервере
- Очередь альбома next/prev
- Вещание только в радиусе
- Опциональный whitelist плейлистов
- Скрипты в подпапках `Unesennye/`

## Пример config.json

```json
{
  "DiscordEnabled": true,
  "DiscordPlayerConnect": true,
  "DiscordPlayerDisconnect": true,
  "DiscordSDInsert": true,
  "BroadcastRadius": 80.0,
  "PlaylistWhitelistEnabled": false,
  "PlaylistWhitelist": [1, 2],
  "FileLogEnabled": true
}
```

## Discord webhook

1. Создайте webhook в канале Discord.
2. Пропишите URL в файле:

```
<профиль_сервера>/Unesennye/discord_webhook.txt
```

3. Перезапустите сервер.

**Пароли сервера и администратора не отправляются.**

## Запуск

```
-mod=@unesennye_servermod;@unesennye_music_db;@unesennye
```

**Автор:** KRa Tos (Константин)
