class CfgPatches
{
    class ModdedCharacterCreation
    {
        requiredAddons[]=
        {
            "DZ_Data"
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

class cfgCharacterCreation
{
	format = "Survivor%1_%2";
	gender[] = {"Female","Male"};
	personalityMale[] = {"Mirek","Boris","Cyril","Denis","Elias","Francis","Guo","Hassan","Indar","Jose","Kaito","Lewis","Manua","Niki","Oliver","Peter","Quinn","Rolf","Seth","Taiki"};
	personalityFemale[] = {"Eva","Frida","Gabi","Helga","Irena","Judy","Keiko","Linda","Maria","Naomi"};
	shoulder[] = {};
	melee[] = {};
	headgear[] = {};
	mask[] = {};
	eyewear[] = {};
	gloves[] = {};
	armband[] = {};
	top[] = {"TShirt_Beige","TShirt_Black","TShirt_Blue","TShirt_Green","TShirt_OrangeWhiteStripes","TShirt_Red","TShirt_RedBlackStripes","TShirt_White","TShirt_Grey"};
	vests[] = {};
	backpacks[] = {"CoyoteBag_Green","TortillaBag"};
	hips[] = {};
	bottom[] = {"CanvasPantsMidi_Beige","CanvasPantsMidi_Blue","CanvasPantsMidi_Grey","CanvasPantsMidi_Red","CanvasPantsMidi_Violet"};
	shoe[] = {"AthleticShoes_Black","AthleticShoes_Blue","AthleticShoes_Brown","AthleticShoes_Green","AthleticShoes_Grey"};
};