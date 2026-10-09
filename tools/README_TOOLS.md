# Unesennye Tools

**Author:** KRa Tos (Константин)  
**Version:** 1.2.3

## generate_music_meta.bat

Автоматически создаёт meta-файлы двух уровней:

1. **Плейлист** — `meta.txt` в каждой папке
2. **Каждый трек** — отдельный `.meta` файл рядом с аудио

### Пример результата

```
Music/sd_playlists/01/
├── song_one.ogg
├── song_one.meta          ← автогенерация для файла
├── song_two.mp3
├── song_two.meta          ← автогенерация для файла
└── meta.txt               ← автогенерация для плейлиста
```

### Содержимое song_one.meta

```
name=song one
file=song_one.ogg
extension=.ogg
index=1
playlist=01
size_bytes=3456789
generated_by=Unesennye generate_music_meta.bat v1.2.3
author=KRa Tos (Константин)
```

### Содержимое meta.txt (плейлист)

```
name=01
id=01
tracks=song_one.ogg,song_two.mp3
count=2
generated_by=Unesennye generate_music_meta.bat v1.2.3
author=KRa Tos (Константин)
```

### Как использовать

1. Разложите музыку по папкам:
   - `Music/sd_playlists/01/` … `99/` — для SD-карт
   - `Music/Type/` — кассеты
   - `Music/CD/` — диски
2. Запустите `generate_music_meta.bat`
3. Все `.meta` и `meta.txt` появятся автоматически

Поддерживаемые форматы: `.ogg` · `.mp3` · `.wav`
