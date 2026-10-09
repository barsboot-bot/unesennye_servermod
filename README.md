# UNESENNYE MUSIC SYSTEM v1.2.3 — Server Mod

**Author:** KRa Tos (Константин)  
**Version:** 1.2.3

---

## Что нового в v1.2.3

- **Автогенерация meta для каждого файла**
  - Рядом с каждым `.ogg` / `.mp3` / `.wav` создаётся файл `имя_трека.meta`
  - Содержит: name, file, extension, index, playlist, size_bytes
- Плейлистный `meta.txt` по-прежнему создаётся для каждой папки

### Пример

```
Music/sd_playlists/01/
├── night_drive.ogg
├── night_drive.meta      ← авто
├── summer_hit.mp3
├── summer_hit.meta       ← авто
└── meta.txt              ← авто (список всех треков)
```

Запуск:
```
tools\generate_music_meta.bat
```

---

## Author

**KRa Tos (Константин)**
