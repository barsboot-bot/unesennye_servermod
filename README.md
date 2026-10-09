# UNESENNYE MUSIC SYSTEM v1.2.2 — Server Mod

**Author:** KRa Tos (Константин)  
**Version:** 1.2.2  
**Type:** Server-only mod

---

## Что нового в v1.2.2

- **generate_music_meta.bat** — автоматическая генерация `meta.txt` для всех плейлистов
- Поддержка автоматической регистрации треков без ручного прописывания в config
- `UnesennyeMusicLibrary` — серверный реестр плейлистов по ID
- SD-карты продолжают работать через `varQuantity` = ID папки плейлиста

---

## Быстрый старт: автоматическая музыка

### 1. Подготовьте папку Music

```
Music/
├── sd_playlists/          ← для SD-карт (имя папки = ID)
│   ├── 01/
│   │   ├── song1.ogg
│   │   └── song2.ogg
│   └── 02/
│       └── ...
├── Type/                  ← кассеты / обычные плейлисты
│   └── Rock_80s/
│       └── ...
└── CD/
    └── Classic/
        └── ...
```

### 2. Запустите генератор meta

```
tools\generate_music_meta.bat
```

Скрипт создаст в каждой папке файл `meta.txt`:

```
name=Rock 80s
tracks=song1.ogg,song2.ogg
count=2
generated_by=Unesennye generate_music_meta.bat
author=KRa Tos (Константин)
```

### 3. Привязка к SD-карте

- Положите `Unesennye_SD_Card` с `varQuantity = 1` → будет играть плейлист из папки `01`
- `varQuantity = 2` → папка `02` и т.д.

Клиент при воспроизведении получает `playlistId` + имя трека и берёт файл из `@unesennye_music_db` или внешней папки Music.

---

## Установка

1. Упакуйте мод в PBO.
2. Добавьте в параметры сервера:

```
-mod=@unesennye_servermod;@unesennye_music_db;@unesennye
```

3. (Опционально) Положите папку `Music` в профиль сервера и запускайте `generate_music_meta.bat` при добавлении новых треков.

---

## Author

**KRa Tos (Константин)**  

All rights reserved.
