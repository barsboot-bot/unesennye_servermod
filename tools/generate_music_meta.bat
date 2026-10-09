@echo off
chcp 65001 >nul
setlocal EnableDelayedExpansion

:: ============================================================
::  UNESENNYE MUSIC SYSTEM - Automatic Meta Generator
::  Author: KRa Tos (Константин)
::  Version: 1.2.3
:: ============================================================
::  1. Создаёт meta.txt для каждого плейлиста (папки)
::  2. Создаёт отдельный .meta файл для КАЖДОГО аудиофайла
::
::  Поддерживаемые форматы: .ogg .mp3 .wav
:: ============================================================

title Unesennye - Generate Music Meta (per-file + playlist)
echo.
echo  ========================================
echo   UNESENNYE MUSIC META GENERATOR v1.2.3
echo   Author: KRa Tos (Константин)
echo   Per-file + Playlist meta auto-generation
echo  ========================================
echo.

:: ---- Путь к корню музыки ----
set "MUSIC_ROOT=%~dp0Music"

if not exist "%MUSIC_ROOT%" (
    set "MUSIC_ROOT=%~dp0..\Music"
)

if not exist "%MUSIC_ROOT%" (
    echo [!] Папка Music не найдена.
    echo     Укажите полный путь к папке Music:
    set /p MUSIC_ROOT="Путь: "
)

if not exist "%MUSIC_ROOT%" (
    echo [ERROR] Папка не существует: %MUSIC_ROOT%
    pause
    exit /b 1
)

echo [+] Корень музыки: %MUSIC_ROOT%
echo.

set /a PLAYLIST_COUNT=0
set /a TRACK_COUNT=0
set /a FILE_META_COUNT=0

:: ---- Type ----
if exist "%MUSIC_ROOT%\Type" (
    echo [+] Сканирование Type\ ...
    for /d %%D in ("%MUSIC_ROOT%\Type\*") do call :ProcessPlaylist "%%D"
)

:: ---- CD ----
if exist "%MUSIC_ROOT%\CD" (
    echo [+] Сканирование CD\ ...
    for /d %%D in ("%MUSIC_ROOT%\CD\*") do call :ProcessPlaylist "%%D"
)

:: ---- sd_playlists ----
if exist "%MUSIC_ROOT%\sd_playlists" (
    echo [+] Сканирование sd_playlists\ ...
    for /d %%D in ("%MUSIC_ROOT%\sd_playlists\*") do call :ProcessPlaylist "%%D"
)

:: ---- Корень (если нет стандартных папок) ----
if not exist "%MUSIC_ROOT%\Type" if not exist "%MUSIC_ROOT%\CD" if not exist "%MUSIC_ROOT%\sd_playlists" (
    echo [+] Сканирование корневых папок ...
    for /d %%D in ("%MUSIC_ROOT%\*") do call :ProcessPlaylist "%%D"
)

echo.
echo  ========================================
echo   Готово!
echo   Плейлистов обработано     : !PLAYLIST_COUNT!
echo   Треков найдено            : !TRACK_COUNT!
echo   Индивидуальных .meta      : !FILE_META_COUNT!
echo  ========================================
echo.
echo  Для каждого .ogg/.mp3/.wav создан файл .meta
echo  Для каждой папки создан meta.txt
echo.
pause
exit /b 0

:: ============================================================
:ProcessPlaylist
set "FOLDER=%~1"
set "FOLDER_NAME=%~nx1"

if /i "%FOLDER_NAME%"=="_пример_кассеты" exit /b 0
if /i "%FOLDER_NAME%"=="_пример_диск" exit /b 0
if /i "%FOLDER_NAME%"==".git" exit /b 0
if /i "%FOLDER_NAME%"=="tools" exit /b 0

set "META_FILE=%FOLDER%\meta.txt"
set "TRACKS="
set /a LOCAL_TRACKS=0
set /a INDEX=0

for %%F in ("%FOLDER%\*.ogg" "%FOLDER%\*.mp3" "%FOLDER%\*.wav") do (
    if exist "%%F" (
        set /a INDEX+=1
        set /a LOCAL_TRACKS+=1
        set /a TRACK_COUNT+=1

        set "FNAME=%%~nxF"
        set "FNAME_NO_EXT=%%~nF"
        set "FEXT=%%~xF"
        set "FSIZE=%%~zF"

        set "TRACKS=!TRACKS!!FNAME!,"

        :: ---- Индивидуальный .meta для каждого файла ----
        set "FILE_META=%FOLDER%\!FNAME_NO_EXT!.meta"

        :: Красивое имя трека (замена _ и - на пробелы)
        set "TRACK_DISPLAY=!FNAME_NO_EXT!"
        set "TRACK_DISPLAY=!TRACK_DISPLAY:_= !"
        set "TRACK_DISPLAY=!TRACK_DISPLAY:-= !"

        (
            echo name=!TRACK_DISPLAY!
            echo file=!FNAME!
            echo extension=!FEXT!
            echo index=!INDEX!
            echo playlist=%FOLDER_NAME%
            echo size_bytes=!FSIZE!
            echo generated_by=Unesennye generate_music_meta.bat v1.2.3
            echo author=KRa Tos (Константин)
        ) > "!FILE_META!"

        set /a FILE_META_COUNT+=1
    )
)

if !LOCAL_TRACKS! equ 0 (
    echo     [-] %FOLDER_NAME% — нет аудиофайлов, пропуск
    exit /b 0
)

if defined TRACKS set "TRACKS=!TRACKS:~0,-1!"

set "DISPLAY_NAME=%FOLDER_NAME%"
set "DISPLAY_NAME=!DISPLAY_NAME:_= !"

:: ---- meta.txt плейлиста ----
(
    echo name=!DISPLAY_NAME!
    echo id=%FOLDER_NAME%
    echo tracks=!TRACKS!
    echo count=!LOCAL_TRACKS!
    echo generated_by=Unesennye generate_music_meta.bat v1.2.3
    echo author=KRa Tos (Константин)
) > "%META_FILE%"

set /a PLAYLIST_COUNT+=1
echo     [+] %FOLDER_NAME% — !LOCAL_TRACKS! трек(ов) + !LOCAL_TRACKS! .meta → meta.txt
exit /b 0
