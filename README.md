# UNESENNYE MUSIC SYSTEM v1.2.1 — Server Mod

**Author:** KRa Tos (Константин)  
**Version:** 1.2.1  
**Type:** Server-only mod  
**Required for:** `@unesennye` (client) and `@unesennye_music_db`

---

## Что нового в v1.2.1

- **SD-карта** (`Unesennye_SD_Card` / `Unesennye_SD_Card_Empty`)
- Слот `Unesennye_SDCard` добавлен на:
  - PersonalRadio (рации)
  - OffroadHatchback, Hatchback_02, CivilianSedan, Sedan_02, Truck_01_Base (автомобили)
- Серверная валидация вставки/извлечения SD-карты
- Привязка плейлиста к SD-карте через `varQuantity` (ID из `@unesennye_music_db`)
- Воспроизведение через рацию/магнитолу возможно **только** при вставленной SD-карте

---

## SD-карта — как это работает

1. Игрок находит или получает `Unesennye_SD_Card` (с quantity = ID плейлиста) или пустую `Unesennye_SD_Card_Empty`.
2. Вставляет карту в слот рации или автомобиля.
3. Клиент отправляет RPC `RADIO_INSERT_CARD` (300) с параметрами `(className, playlistId)`.
4. Сервер сохраняет состояние в `UnesennyeSDCardManager`.
5. При `RADIO_PLAY_TRACK` (302) сервер проверяет наличие карты и рассылает broadcast с `playlistId + track`.
6. Клиент по `playlistId` берёт файлы из `@unesennye_music_db`.

### Привязка к music_db

| quantity SD-карты | Что означает                          |
|-------------------|---------------------------------------|
| 0                 | Пустая карта                          |
| 1…99              | ID плейлиста / альбома в music_db     |

Рекомендуется в `@unesennye_music_db` иметь структуру:

```
sounds/
  sd_playlists/
    01/
      track_01.ogg
      track_02.ogg
    02/
      ...
```

---

## Установка (PBO)

1. Склонируйте репозиторий.
2. Переименуйте корень в `@unesennye_servermod` (если нужно).
3. Упакуйте в PBO (DayZ Tools / Mikero / Addon Builder).
4. Добавьте в параметры сервера:

```
-mod=@unesennye_servermod;@unesennye_music_db;@unesennye
```

5. В логе сервера должно появиться:

```
[Unesennye Server] Manager initialized | Version: 1.2.1 | Author: KRa Tos (Константин)
```

---

## Важные замечания по слотам

- Слоты `attachments[] += {"Unesennye_SDCard"}` добавлены на несколько классов машин и PersonalRadio.
- Для полного визуального слота и корректной работы на всех машинах рекомендуется продублировать определения слотов и предметов в **клиентском** моде `@unesennye`.
- Модель SD-карты сейчас использует placeholder (`battery.p3d`). Замените на свою модель в клиентском моде.

---

## RPC (дополнено)

| ID  | Назначение                    |
|-----|-------------------------------|
| 300 | RADIO_INSERT_CARD (SD)        |
| 301 | RADIO_EJECT_CARD (SD)         |
| 302 | RADIO_PLAY_TRACK (требует SD) |
| 303 | RADIO_STOP_TRACK              |
| 304 | RADIO_BROADCAST               |
| 305 | RADIO_BROADCAST_STOP          |

---

## Author

**KRa Tos (Константин)**  

All rights reserved. Unauthorized redistribution or removal of author credits is prohibited.

---

*Ready for DayZ Standalone 1.24+ | Pack to PBO and test on server*
