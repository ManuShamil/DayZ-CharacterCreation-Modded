class CfgPatches
{
    class ModdedCharacterCreation
    {
        requiredAddons[]=
        {
        };
    };
};

class CfgMods
{
    class GridSpawnSystem
    {
        name = "ModdedCharacterCreation";
        type = "mod";

        class defs
        {
            class missionScriptModule
            {
                value = "";
                files[] = {"ModdedCharacterCreation\Scripts\5_Mission"};
            };
        };
    };
};