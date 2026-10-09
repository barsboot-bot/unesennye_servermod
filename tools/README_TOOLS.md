# Unesennye Tools

**Author:** KRa Tos (Константин)  
**Version:** 1.2.2

## generate_music_meta.bat

Автоматически создаёт / обновляет файлы `meta.txt` для всех музыкальных плейлистов.

### Как использовать

1. Создайте структуру папок (рядом с bat или укажите путь):

```
Music/
├── Type/                    ← кассеты / обычные плейлисты
│   ├── Rock_80s/
│   │   ├── track01.ogg
│   │   ├── track02.ogg
│   │   └── meta.txt         ← создаётся автоматически
│   └── Pop_Hits/
│       └── ...
├── CD/                      ← диски
│   └── Classic/
│       └── ...
└── sd_playlists/            ← плейлисты для SD-карт (ID = имя папки)
    ├── 01/
    │   ├── track_01.ogg
    │   └── meta.txt
    └── 02/
        └── ...
```

2. Запустите `generate_music_meta.bat`.
3. Скрипт обойдёт все подпапки и создаст `meta.txt` вида:

```
name=Rock 80s
tracks=track01.ogg,track02.ogg,track03.ogg
count=3
generated_by=Unesennye generate_music_meta.bat
author=KRa Tos (Константин)
```

### Автоматическая регистрация

- Имя папки становится ID плейлиста (для SD-карт используйте числовые имена: `01`, `02` …).
- `varQuantity` на предмете `Unesennye_SD_Card` = числовой ID папки.
- Клиентский / серверный код читает `meta.txt` и автоматически подхватывает список треков без ручного прописывания в config.cpp.

### Поддерживаемые форматы

`.ogg` · `.mp3` · `.wav`
