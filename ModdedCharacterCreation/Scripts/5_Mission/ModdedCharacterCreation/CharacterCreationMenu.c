modded class CharacterCreationMenu extends UIScriptedMenu
{
	protected ref OptionSelectorMultistateCharacterMenu		m_BagSelector;

	override Widget Init()
	{
		#ifdef PLATFORM_CONSOLE
			layoutRoot = GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/character_creation/xbox/character_creation.layout" );
			m_CharacterSaved 				= false;
			m_ConsoleSave 					= layoutRoot.FindAnyWidget( "save_console" );
		#else
			layoutRoot = GetGame().GetWorkspace().CreateWidgets( "ModdedCharacterCreation/GUI/Layouts/character_creation.layout" );
		#endif
		
		m_CharacterRotationFrame			= layoutRoot.FindAnyWidget( "character_rotation_frame" );
		m_Apply								= layoutRoot.FindAnyWidget( "apply" );
		m_Save 								= layoutRoot.FindAnyWidget( "save" );
		m_RandomizeCharacter				= layoutRoot.FindAnyWidget( "randomize_character" );
		m_BackButton						= layoutRoot.FindAnyWidget( "back" );
		m_Version							= TextWidget.Cast( layoutRoot.FindAnyWidget( "version" ) );
		m_DetailsRoot 						= layoutRoot.FindAnyWidget( "menu_details_tooltip" );
		m_DetailsLabel						= TextWidget.Cast( m_DetailsRoot.FindAnyWidget( "menu_details_label" ) );
		m_DetailsText						= RichTextWidget.Cast( m_DetailsRoot.FindAnyWidget( "menu_details_tooltip_content" ) );
		m_CharacterHeaderText 				= TextWidget.Cast(layoutRoot.FindAnyWidget( "char_header_text" ));
		m_PlayedCharacterInfo 				= layoutRoot.FindAnyWidget( "played_char_info" );
		
		string version;
		GetGame().GetVersion( version );
		#ifdef PLATFORM_CONSOLE
			version = "#main_menu_version" + " " + version + " (" + g_Game.GetDatabaseID() + ")";
		#else
			version = "#main_menu_version" + " " + version;
		#endif
		m_Version.SetText( version );
		
		if( m_Scene && m_Scene.GetIntroCharacter() )
		{
			m_OriginalCharacterID = m_Scene.GetIntroCharacter().GetCharacterID();
			/*#ifdef PLATFORM_CONSOLE
				//m_Scene.GetIntroCharacter().SetToDefaultCharacter();
				m_Scene.GetIntroCharacter().LoadCharacterData( m_Scene.GetIntroCharacter().GetCharacterObj().GetPosition(), m_Scene.GetIntroCharacter().GetCharacterObj().GetDirection(), true );
			#endif;*/
		}
		
		m_NameSelector		= new OptionSelectorEditbox( layoutRoot.FindAnyWidget( "character_name_setting_option" ), m_Scene.GetIntroCharacter().GetCharacterName(), null, false );
		m_GenderSelector	= new OptionSelectorMultistateCharacterMenu( layoutRoot.FindAnyWidget( "character_gender_setting_option" ), 0, null, false, m_Scene.GetIntroCharacter().GetCharGenderList() );
		if ( m_Scene.GetIntroCharacter().IsCharacterFemale() )
		{
			m_GenderSelector.SetValue( "Female" );
			m_SkinSelector	= new OptionSelectorMultistateCharacterMenu( layoutRoot.FindAnyWidget( "character_head_setting_option" ), 0, null, false, m_Scene.GetIntroCharacter().GetCharList( ECharGender.Female ) );
		}
		else
		{
			m_GenderSelector.SetValue( "Male" );
			m_SkinSelector	= new OptionSelectorMultistateCharacterMenu( layoutRoot.FindAnyWidget( "character_head_setting_option" ), 0, null, false, m_Scene.GetIntroCharacter().GetCharList( ECharGender.Male ) );
		}
		
		m_TopSelector		= new OptionSelectorMultistateCharacterMenu( layoutRoot.FindAnyWidget( "character_top_setting_option" ), 0, null, false, DefaultCharacterCreationMethods.GetConfigAttachmentTypes(InventorySlots.BODY) );
		m_BottomSelector	= new OptionSelectorMultistateCharacterMenu( layoutRoot.FindAnyWidget( "character_bottom_setting_option" ), 0, null, false, DefaultCharacterCreationMethods.GetConfigAttachmentTypes(InventorySlots.LEGS) );
		m_ShoesSelector		= new OptionSelectorMultistateCharacterMenu( layoutRoot.FindAnyWidget( "character_shoes_setting_option" ), 0, null, false, DefaultCharacterCreationMethods.GetConfigAttachmentTypes(InventorySlots.FEET) );
		m_BagSelector		= new OptionSelectorMultistateCharacterMenu( layoutRoot.FindAnyWidget( "character_bag_setting_option" ), 0, null, false, DefaultCharacterCreationMethods.GetConfigAttachmentTypes(InventorySlots.BACK) );

		PlayerBase scene_char = GetPlayerObj();
		if( scene_char )
		{
			Object obj = scene_char.GetInventory().FindAttachment(InventorySlots.BODY);
			if( obj )
				m_TopSelector.SetValue( obj.GetType(), false );
			
			obj = scene_char.GetInventory().FindAttachment(InventorySlots.LEGS);
			if( obj )
				m_BottomSelector.SetValue( obj.GetType(), false );
			
			obj = scene_char.GetInventory().FindAttachment(InventorySlots.FEET);
			if( obj )
				m_ShoesSelector.SetValue( obj.GetType(), false );

			obj = scene_char.GetInventory().FindAttachment(InventorySlots.BACK);
			if( obj )
				m_BagSelector.SetValue( obj.GetType(), false );

			m_SkinSelector.SetValue( scene_char.GetType() );
		}
		
		m_GenderSelector.m_OptionChanged.Insert( GenderChanged );
		m_SkinSelector.m_OptionChanged.Insert( SkinChanged );
		m_TopSelector.m_OptionChanged.Insert( TopChanged );
		m_BottomSelector.m_OptionChanged.Insert( BottomChanged );
		m_ShoesSelector.m_OptionChanged.Insert( ShoesChanged );
		m_BagSelector.m_OptionChanged.Insert( BagChanged );
		
		#ifdef PLATFORM_PS4
			string confirm = "cross";
			string back = "circle";
			if( GetGame().GetInput().GetEnterButton() == GamepadButton.A )
			{
				confirm = "cross";
				back = "circle";
			}
			else
			{
				confirm = "circle";
				back = "cross";
			}
		
			ImageWidget toolbar_a = layoutRoot.FindAnyWidget( "SelectIcon" );
			ImageWidget toolbar_b = layoutRoot.FindAnyWidget( "BackIcon" );
			ImageWidget toolbar_b2 = layoutRoot.FindAnyWidget( "BackIcon0" );
			ImageWidget toolbar_x = layoutRoot.FindAnyWidget( "RandomizeIcon" );
			ImageWidget toolbar_x2 = layoutRoot.FindAnyWidget( "RandomizeIcon0" );
			ImageWidget toolbar_y = layoutRoot.FindAnyWidget( "save_consoleIcon" );
			ImageWidget toolbar_y2 = layoutRoot.FindAnyWidget( "save_consoleIcon0" );
			toolbar_a.LoadImageFile( 0, "set:playstation_buttons image:" + confirm );
			toolbar_b.LoadImageFile( 0, "set:playstation_buttons image:" + back );
			toolbar_b2.LoadImageFile( 0, "set:playstation_buttons image:" + back );
			toolbar_x.LoadImageFile( 0, "set:playstation_buttons image:square" );
			toolbar_x2.LoadImageFile( 0, "set:playstation_buttons image:square" );
			toolbar_y.LoadImageFile( 0, "set:playstation_buttons image:triangle" );
			toolbar_y2.LoadImageFile( 0, "set:playstation_buttons image:triangle" );
		#endif
		
		Refresh();
		SetCharacter();
		CheckNewOptions();
		return layoutRoot;
	}

	override void ~CharacterCreationMenu()
	{
		m_BagSelector.m_OptionChanged.Remove( BagChanged );
	}

	override void RandomizeCharacter()
	{
	
		m_BagSelector.SetValue(GetGame().GetMenuDefaultCharacterData().GetAttachmentMap().Get(InventorySlots.BACK),false);

		super.RandomizeCharacter();

	}
	
	void BagChanged()
	{
		GetGame().GetMenuDefaultCharacterData().SetDefaultAttachment(InventorySlots.BACK,m_BagSelector.GetStringValue());
		GetGame().GetMenuDefaultCharacterData().EquipDefaultCharacter(m_Scene.GetIntroCharacter().GetCharacterObj());
		SetCharacterSaved(false);
	}
}