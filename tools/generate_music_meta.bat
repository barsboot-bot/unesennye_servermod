@echo off
chcp 65001 >nul
setlocal EnableDelayedExpansion

:: ============================================================
::  UNESENNYE MUSIC SYSTEM - Automatic Meta Generator
::  Author: KRa Tos (Константин)
::  Version: 1.2.2
:: ============================================================
::  Сканирует папки с музыкой и создаёт / обновляет meta.txt
::  для каждого плейлиста. Поддерживает .ogg, .mp3, .wav.
::
::  Использование:
::    1. Положите этот bat рядом с папкой Music (или укажите путь)
::    2. Запустите generate_music_meta.bat
::    3. Скрипт обойдёт Type/ и CD/ (или sd_playlists/) и
::       создаст meta.txt с названием и списком треков.
:: ============================================================

title Unesennye - Generate Music Meta
echo.
echo  ========================================
echo   UNESENNYE MUSIC META GENERATOR v1.2.2
echo   Author: KRa Tos (Константин)
echo  ========================================
echo.

:: ---- Путь к корню музыки ----
:: По умолчанию ищем папку Music рядом с bat-файлом
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

:: ---- Обработка Type (кассеты / обычные плейлисты) ----
if exist "%MUSIC_ROOT%\Type" (
    echo [+] Сканирование Type\ ...
    for /d %%D in ("%MUSIC_ROOT%\Type\*") do (
        call :ProcessPlaylist "%%D"
    )
)

:: ---- Обработка CD (диски) ----
if exist "%MUSIC_ROOT%\CD" (
    echo [+] Сканирование CD\ ...
    for /d %%D in ("%MUSIC_ROOT%\CD\*") do (
        call :ProcessPlaylist "%%D"
    )
)

:: ---- Обработка sd_playlists (SD-карты) ----
if exist "%MUSIC_ROOT%\sd_playlists" (
    echo [+] Сканирование sd_playlists\ ...
    for /d %%D in ("%MUSIC_ROOT%\sd_playlists\*") do (
        call :ProcessPlaylist "%%D"
    )
)

:: ---- Обработка корневых папок (если нет Type/CD) ----
if not exist "%MUSIC_ROOT%\Type" if not exist "%MUSIC_ROOT%\CD" if not exist "%MUSIC_ROOT%\sd_playlists" (
    echo [+] Сканирование корневых папок ...
    for /d %%D in ("%MUSIC_ROOT%\*") do (
        call :ProcessPlaylist "%%D"
    )
)

echo.
echo  ========================================
echo   Готово!
echo   Плейлистов обработано : !PLAYLIST_COUNT!
echo   Треков найдено        : !TRACK_COUNT!
echo  ========================================
echo.
echo  meta.txt созданы/обновлены.
echo  Теперь можно упаковывать @unesennye_music_db или
echo  использовать внешнюю папку Music на сервере.
echo.
pause
exit /b 0

:: ============================================================
::  Функция обработки одной папки-плейлиста
:: ============================================================
:ProcessPlaylist
set "FOLDER=%~1"
set "FOLDER_NAME=%~nx1"

:: Пропускаем служебные папки
if /i "%FOLDER_NAME%"=="_пример_кассеты" exit /b 0
if /i "%FOLDER_NAME%"=="_пример_диск" exit /b 0
if /i "%FOLDER_NAME%"==".git" exit /b 0

set "META_FILE=%FOLDER%\meta.txt"
set "TRACKS="
set /a LOCAL_TRACKS=0

:: Собираем список треков (.ogg, .mp3, .wav)
for %%F in ("%FOLDER%\*.ogg" "%FOLDER%\*.mp3" "%FOLDER%\*.wav") do (
    if exist "%%F" (
        set "TRACKS=!TRACKS!%%~nxF,"
        set /a LOCAL_TRACKS+=1
        set /a TRACK_COUNT+=1
    )
)

if !LOCAL_TRACKS! equ 0 (
    echo     [-] %FOLDER_NAME% — нет аудиофайлов, пропуск
    exit /b 0
)

:: Убираем последнюю запятую
if defined TRACKS (
    set "TRACKS=!TRACKS:~0,-1!"
)

:: Формируем отображаемое имя (заменяем _ на пробелы)
set "DISPLAY_NAME=%FOLDER_NAME%"
set "DISPLAY_NAME=!DISPLAY_NAME:_= !"

:: Пишем meta.txt
(
    echo name=!DISPLAY_NAME!
    echo tracks=!TRACKS!
    echo count=!LOCAL_TRACKS!
    echo generated_by=Unesennye generate_music_meta.bat
    echo author=KRa Tos (Константин)
) > "%META_FILE%"

set /a PLAYLIST_COUNT+=1
echo     [+] %FOLDER_NAME% — !LOCAL_TRACKS! трек(ов) → meta.txt
exit /b 0
