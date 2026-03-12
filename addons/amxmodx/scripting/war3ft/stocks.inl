stock get_user_maxhealth( id )
{

	new maxHealth = 100

	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( id, SKILL_DEVOTION );

	// Human Devotion Skill
	if ( iSkillLevel > 0 )
	{
		maxHealth += iSkillLevel * p_devotion;
	}


	// Player has a health bonus from the Periapt of Health

	if ( ITEM_Has( id, ITEM_HEALTH ) > ITEM_NONE )
		maxHealth += get_pcvar_num( CVAR_wc3_health );

	return maxHealth
}

// Function checks to see if the weapon is a pistol
stock SHARED_IsSecondaryWeapon( iWeaponID )
{
	// Check for Counter-Strike or Condition Zero
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		if ( iWeaponID == CSW_ELITE || iWeaponID == CSW_FIVESEVEN || iWeaponID == CSW_USP || iWeaponID == CSW_GLOCK18 || iWeaponID == CSW_DEAGLE || iWeaponID == CSW_P90 )
		{
			return true;
		}
	}
	
	// Check for Day of Defeat
	else if ( g_MOD == GAME_DOD )
	{

	}


	return false;
}

stock fm_cs_get_user_armor(client, &CsArmorType:armortype) 
 { 
     armortype = CsArmorType:get_pdata_int(client, OFFSET_ARMORTYPE, EXTRAOFFSET); 
      
     static Float:armorvalue; 
     pev(client, pev_armorvalue, armorvalue); 
     return floatround(armorvalue); 
 } 
    
 stock fm_cs_set_user_armor(client, armorvalue, CsArmorType:armortype) 
 { 
     set_pdata_int(client, OFFSET_ARMORTYPE, _:armortype, EXTRAOFFSET); 
      
     set_pev(client, pev_armorvalue, float(armorvalue)); 
      
     if( armortype != CS_ARMOR_NONE ) 
     { 
         static ArmorType; 
         if( ArmorType || (ArmorType = get_user_msgid("ArmorType")) ) 
         { 
                 emessage_begin(MSG_ONE_UNRELIABLE, ArmorType, _, client); 
                 ewrite_byte((armortype == CS_ARMOR_VESTHELM) ? 1 : 0); 
                 emessage_end(); 
         } 
     } 
 }

 
 public give_ammo(id , wpnid , clip)
{
	if(!is_user_alive(id))
		return;

	if(	wpnid==CSW_C4		||
		wpnid==CSW_KNIFE	||
		wpnid==CSW_HEGRENADE	||
		wpnid==CSW_SMOKEGRENADE	||
		wpnid==CSW_FLASHBANG	) 
			return;

	if(!clip)
	{
		static weapname[33];
		get_weaponname(wpnid , weapname , 32);

		static wpn
		wpn = -1;
		while((wpn = find_ent_by_class(wpn , weapname)) != 0)
		{
			if(id == entity_get_edict(wpn , EV_ENT_owner))
			{
				cs_set_weapon_ammo(wpn , maxclip(wpnid))
				break;
			}
		}
	}
}


stock maxclip(wpnid) 
{
	static ca;
	ca = 0;

	switch (wpnid) 
	{
		case CSW_P228 : ca = 13;
		case CSW_SCOUT : ca = 10;
		case CSW_HEGRENADE : ca = 0;
		case CSW_XM1014 : ca = 7;
		case CSW_C4 : ca = 0;
		case CSW_MAC10 : ca = 30;
		case CSW_AUG : ca = 30;
		case CSW_SMOKEGRENADE : ca = 0;
		case CSW_ELITE : ca = 15;
		case CSW_FIVESEVEN : ca = 20;
		case CSW_UMP45 : ca = 25;
		case CSW_SG550 : ca = 30;
		case CSW_GALI : ca = 35;
		case CSW_FAMAS : ca = 25;
		case CSW_USP : ca = 12;
		case CSW_GLOCK18 : ca = 20;
		case CSW_AWP : ca = 10;
		case CSW_MP5NAVY : ca = 30;
		case CSW_M249 : ca = 100;
		case CSW_M3 : ca = 8;
		case CSW_M4A1 : ca = 30;
		case CSW_TMP : ca = 30;
		case CSW_G3SG1 : ca = 20;
		case CSW_FLASHBANG : ca = 0;
		case CSW_DEAGLE	: ca = 7;
		case CSW_SG552 : ca = 30;
		case CSW_AK47 : ca = 30;
		case CSW_P90 : ca = 50;
	}
	return ca;
}