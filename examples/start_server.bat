@echo off
REM Unesennye DayZ Server — Author: KRa Tos (Константин)
REM Клиентские моды: -mod=
REM Серверный мод:   -serverMod=

set SERVER_EXE=DayZServer_x64.exe
set CONFIG=serverDZ.cfg
set PORT=2302
set PROFILES=ServerProfile
set MODS=@unesennye;@unesennye_music_db
set SERVERMODS=@unesennye_servermod

%SERVER_EXE% -config=%CONFIG% -port=%PORT% -profiles=%PROFILES% -dologs -adminlog -netlog -freezecheck -mod=%MODS% -serverMod=%SERVERMODS%
pause
