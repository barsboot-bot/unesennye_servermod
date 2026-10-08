# UNESENNYE MUSIC SYSTEM v1.2.0 — Server Mod

**Author:** KRa Tos (Константин)  
**Version:** 1.2.0  
**Type:** Server-only mod  
**Required for:** `@unesennye` (client) and `@unesennye_music_db`

---

## Description

This is the **server-side** component of the Unesennye Music System.  
It provides:

- Handshake Protocol (protection against unauthorized client usage)
- Full RPC handling (IDs 100–406)
- Player authorization tracking
- Validation of radio / walkie / album actions
- Broadcast synchronization

**Without this mod installed on the server, the client mod will force-disconnect players after 4 seconds.**

---

## Installation (for PBO packing & testing)

1. Download / clone this repository.
2. Rename the root folder to `@unesennye_servermod` (if needed).
3. Pack with your preferred tool (Addon Builder, Mikero's Tools, DayZ Tools, etc.) into a `.pbo`.
4. Place the resulting `@unesennye_servermod` folder into your server's mods directory.
5. Add to server launch parameters:

```
-mod=@unesennye_servermod;@unesennye_music_db;@unesennye
```

6. Restart the server and check the script log for:

```
[Unesennye Server] Manager initialized | Version: 1.2.0 | Author: KRa Tos (Константин)
[Unesennye Server] MissionServer.OnInit | Author: KRa Tos (Константин) | v1.2.0
```

---

## Handshake Protocol

| Parameter          | Value   |
|--------------------|---------|
| Request RPC        | 100     |
| Response RPC       | 200     |
| Timeout            | 4000 ms |
| Check interval     | 500 ms  |
| Disconnect message | `Error: Required server mod 'unesennye_servermod' is missing.` |

---

## RPC Ranges

| Range   | System                          |
|---------|---------------------------------|
| 100–104 | Car Radio (v1.0.0) requests     |
| 200–204 | Car Radio responses / broadcast |
| 300–305 | Walkie-talkie (v1.1.0)          |
| 400–406 | Albums (v1.2.0)                 |

---

## File Structure (ready for packing)

```
@unesennye_servermod/
├── mod.cpp
├── config.cpp
├── README.md
└── Scripts/
    ├── 3_Game/
    │   └── UnesennyeConstants.c
    ├── 4_World/
    │   ├── UnesennyeAuth.c
    │   ├── UnesennyeRPCHandler.c
    │   └── UnesennyeServerManager.c
    └── 5_Mission/
        └── MissionServer.c
```

---

## Author & License

**Author:** KRa Tos (Константин)  

All rights reserved.  
Unauthorized redistribution, repacking or removal of author credits is prohibited.

---

*Ready for DayZ Standalone 1.24+ | Pack to PBO and test on server*
