// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.1
// Do not remove this header. Unauthorized redistribution is prohibited.

class CfgPatches
{
	class unesennye_servermod
	{
		units[] = {"Unesennye_SD_Card", "Unesennye_SD_Card_Empty"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Gear_Tools", "DZ_Vehicles_Wheeled"};
	};
};

class CfgMods
{
	class unesennye_servermod
	{
		dir = "unesennye_servermod";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "Unesennye Music System - Server";
		credits = "KRa Tos (Константин)";
		author = "KRa Tos (Константин)";
		authorID = "";
		version = "1.2.1";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game", "World", "Mission"};

		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"unesennye_servermod/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"unesennye_servermod/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"unesennye_servermod/Scripts/5_Mission"};
			};
		};
	};
};

// ==================== INVENTORY SLOTS ====================
class CfgSlots
{
	class Slot_Unesennye_SDCard
	{
		name = "Unesennye_SDCard";
		displayName = "SD Card";
		ghostIcon = "set:dayz_inventory image:battery1";
	};
};

// ==================== SD CARD ITEM ====================
class CfgVehicles
{
	class Inventory_Base;

	// Пустая SD-карта (можно записать треки из music_db)
	class Unesennye_SD_Card_Empty : Inventory_Base
	{
		scope = 2;
		displayName = "$STR_Unesennye_SD_Card_Empty";
		descriptionShort = "Пустая SD-карта. Можно записать на неё музыкальные файлы из базы Unesennye Music DB.";
		model = "\dz\gear\tools\battery.p3d"; // placeholder — замените на свою модель
		weight = 15;
		itemSize[] = {1, 1};
		absorption = 0;
		inventorySlot[] = {"Unesennye_SDCard"};
		varQuantityInit = 0;
		varQuantityMin = 0;
		varQuantityMax = 0;
		stackedUnit = "";
		quantityBar = 0;
		hiddenSelections[] = {};
		hiddenSelectionsTextures[] = {};
	};

	// SD-карта с записанным плейлистом (привязка к трекам из @unesennye_music_db)
	class Unesennye_SD_Card : Unesennye_SD_Card_Empty
	{
		scope = 2;
		displayName = "$STR_Unesennye_SD_Card";
		descriptionShort = "SD-карта с записанной музыкой. Вставьте в рацию или автомобильную магнитолу.";
		// varQuantity используется как ID плейлиста / индекс в music_db (0 = пусто)
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 99;
	};

	// ---------- Пример добавления слота SD-карты на рации (Transmitter) ----------
	class Transmitter_Base;
	class PersonalRadio : Transmitter_Base
	{
		attachments[] += {"Unesennye_SDCard"};
	};

	// ---------- Пример добавления слота на автомобильную магнитолу / машины ----------
	// Для полноценной поддержки рекомендуется создать отдельный item "CarRadio"
	// с attachment slot, либо модить конкретные классы машин в клиентском моде.
	class CarScript;
	class OffroadHatchback : CarScript
	{
		attachments[] += {"Unesennye_SDCard"};
	};
	class Hatchback_02 : CarScript
	{
		attachments[] += {"Unesennye_SDCard"};
	};
	class CivilianSedan : CarScript
	{
		attachments[] += {"Unesennye_SDCard"};
	};
	class Sedan_02 : CarScript
	{
		attachments[] += {"Unesennye_SDCard"};
	};
	class Truck_01_Base : CarScript
	{
		attachments[] += {"Unesennye_SDCard"};
	};
};
