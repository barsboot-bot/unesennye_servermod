// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.2.0
// Do not remove this header. Unauthorized redistribution is prohibited.

class CfgPatches
{
	class unesennye_servermod
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data", "DZ_Scripts"};
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
		version = "1.2.0";
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
