
// Forwards from the CSX module and DODX module
public grenade_throw( index, greindex, wId )
{
	
	if ( !WC3_Check() )
	{
		return;
	}
	
	// If user isn't alive do nothing!
	if ( !is_user_alive( index ) )
	{
		return;
	}

	// User has gloves!  Do we need to give them another grenade?
	if ( ITEM_Has( index, ITEM_GLOVES ) > ITEM_NONE )
	{
		ITEM_Glove_Begin( index );
	}

	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( index, SKILL_CRITICALGRENADE );

	// Make sure the user has the skill and we actually have a grenade index
	if ( greindex && iSkillLevel > 0 )
	{
		
		// Then Critical Grenades are allowed
		if ( OR_CriticalGrenadeAllowed( index ) )
		{

			// Then draw it!
			if ( SHARED_IsGrenade( wId ) )
			{
				new iWidth = 3 * iSkillLevel;

				Create_TE_BEAMFOLLOW( greindex, g_iSprites[SPR_TRAIL], 20, iWidth, 255, 32, 32, 196 );
				emit_sound (index, CHAN_STATIC, g_szSounds [SOUND_HEORC], 1.0 , ATTN_NORM, 0 , PITCH_NORM);
			}
		}
	}
	return;
}

// HamSandwich implementation
public EVENT_TakeDamage( iVictim, iWeapon, iAttacker, Float:f_Damage, damagetype )
{

	/*static s_Classname[ 8 ];
	pev ( inflictor, pev_classname, s_Classname, charsmax ( s_Classname ) );
	*/

		static szWeaponClassName[32];
	pev ( iWeapon, pev_classname, szWeaponClassName, charsmax ( szWeaponClassName ) );

	new s_PlayerName[32], s_PlayerName2[32];

	get_user_name( iVictim, s_PlayerName, 31 );
	get_user_name( iAttacker, s_PlayerName2, 31 );
	
	if(SHARED_ValidPlayer(iAttacker) && is_user_alive( iVictim ))
	{
		static iSkillLevel;
		iSkillLevel = SM_GetSkillLevel( iVictim, PASS_BALANCE );
	if ( iSkillLevel > 0 )
	{   
		if ( random_float( 0.0, 1.0 ) <= p_balance[iSkillLevel] )
			{
				if(equali(szWeaponClassName,"grenade"))
				{
				ChatColor( iVictim,"!g* [!t %s!g ]!t Explosion!g Blocked !",g_MODclient);
				return HAM_SUPERCEDE;
				}
			}
	}
	
	if(equali(szWeaponClassName,"grenade") && ITEM_Has(iVictim, ITEM_GRENADE ) > ITEM_NONE )
				{
				ChatColor( iVictim,"!g* [!t %s!g ]!t Explosion!g Blocked !",g_MODclient);
				return HAM_SUPERCEDE;
				}
	
	
	}

	//server_print( "%s:%d attack's %s:%d for %0.0f damage with %s:%d", s_PlayerName2, iAttacker, s_PlayerName, iVictim, f_Damage, s_Classname, inflictor );

      
/*	client_print( iAttacker, print_chat, "Damage: %f0.0, Victim: %d, Inflictor: %d (%s)", iDamage, iVictim, inflictor, s_Classname );
	client_print( iVictim, print_chat, "Damage: %f0.0, iAttacker: %d, Inflictor: %d (%s)", iDamage, iAttacker, inflictor, s_Classname );


	server_print( "Attacker: %d, Damage: %f0.0, Victim: %d, Inflictor: %d (%s)", iAttacker, iDamage, iVictim, inflictor, s_Classname );
*/
	//return HAM_SUPERCEDE


	return HAM_IGNORED;
}

public client_damage( iAttacker, iVictim, iDamage, iWeapon, iHitPlace, TA )
{

	if ( !WC3_Check() )
	{
		return;
	}

	// If they damage themself we don't care now do we ?
	if ( iVictim == iAttacker )
	{
		return;
	}
	
	if (ITEM_Has(iAttacker, ITEM_DEATH ) > ITEM_NONE && arrDeathTouch[iAttacker])
	{
		new parm[5], vOrigin[3];
		get_user_origin(iVictim, vOrigin );

		parm[0] = iVictim;
		parm[1] = 6;
		parm[2] = vOrigin[0];
		parm[3] = vOrigin[1];
		parm[4] = vOrigin[2];

		emit_sound(iAttacker, CHAN_STATIC, g_szSounds[SOUND_DEATH_TOUCH], 1.0, ATTN_NORM, 0, PITCH_NORM );
		
		set_task(0.2, "fDrawDeathTouchExplode", TASK_DEATH_TOUCH + iVictim, parm, 5 );
				
		WC3_Kill( iVictim, iAttacker, iWeapon, 0 );	
		ITEM_RemoveID(iAttacker, ITEM_DEATH );

	}
	
	if (ITEM_Has(iVictim, ITEM_FROSTARMOR ) > ITEM_NONE)
	{
		WC3_Damage(iAttacker,iVictim,FROST_ARMOR_DAMAGE, iWeapon,0);
		SHARED_GlowShell(iVictim,0,139,139,0.2);
	}
	
	
	g_iDamageDealt[iAttacker][iVictim] += iDamage;

	// Bot should "auto" cast his/her ultimate on random
	if ( SHARED_ValidPlayer( iAttacker ) && is_user_bot( iAttacker ) && random_num( 0, 100 ) <= ( BOT_CAST_ULT_CHANCE * 100 ) )
	{
		// Check for an actual ultimate is done in this function, why do it twice?
		cmd_Ultimate( iAttacker );
	}
	

	// We need to make sure that we have a valid attacker and the user isn't hexed
	if ( SHARED_ValidPlayer( iAttacker ) && !p_data_b[iAttacker][PB_HEXED] )
	{

		// Run the offensive spells
		UD_SkillsOffensive( iAttacker, iDamage );
		HU_SkillsOffensive( iAttacker, iVictim );
		OR_SkillsOffensive( iAttacker, iVictim, iWeapon, iDamage, iHitPlace );
		NE_SkillsOffensive( iAttacker, iVictim, iWeapon, iDamage, iHitPlace );
		BM_SkillsOffensive( iAttacker, iVictim, iDamage );
		SH_SkillsOffensive( iAttacker, iVictim );
		WA_SkillsOffensive( iAttacker, iVictim, iHitPlace );
		CL_SkillsOffensive( iAttacker, iVictim, iHitPlace );
		DR_SkillsOffensive( iAttacker, iVictim, iHitPlace );
		WR_SkillsOffensive( iAttacker, iVictim );
		BE_SkillsOffensive( iAttacker, iVictim );
		TR_SkillsOffensive( iAttacker, iVictim );
		WK_SkillsOffensive( iAttacker, iVictim );
		PR_SkillsOffensive( iAttacker );
		DK_SkillsOffensive( iAttacker, iVictim, iDamage );
		DU_SkillsOffensive( iAttacker, iVictim, iHitPlace );
	}

	// Make sure we can run the defensive skills
	if ( SHARED_ValidPlayer( iAttacker ) && !p_data_b[iVictim][PB_HEXED] )
	{
			if (ITEM_Has(iVictim, ITEM_MIRROR ) > ITEM_NONE )
		{
			iDamage = iDamage - floatround(iDamage * 0.30);
			SHARED_GlowShell(iVictim,255,105,180,0.2);
		}
	
		//UD_SkillsDefensive( iAttacker, iVictim, iWeapon, iDamage, iHitPlace );
		//HU_SkillsDefensive( iAttacker, iVictim, iWeapon, iDamage, iHitPlace );
		//OR_SkillsDefensive( iAttacker, iVictim, iWeapon, iDamage, iHitPlace );
		NE_SkillsDefensive( iAttacker, iVictim, iDamage, iHitPlace );
		BM_SkillsDefensive( iAttacker, iVictim, iDamage );
		SH_SkillsDefensive( iAttacker, iVictim );
		//WA_SkillsDefensive( iAttacker, iVictim, iWeapon, iDamage, iHitPlace );
		CL_SkillsDefensive( iAttacker, iVictim, iDamage, iHitPlace );
		DR_SkillsDefensive( iVictim, iDamage );
		PR_SkillsDefensive( iVictim, iDamage );
		DK_SkillsDefensive( iAttacker, iVictim, iDamage, iHitPlace );
		
		
		
	}

	// Item abilities
	if ( SHARED_ValidPlayer( iAttacker ) )
	{
		ITEM_Offensive( iAttacker, iVictim, iWeapon, iDamage, iHitPlace );
	}

	return;
}

// All we want to check is if the user was killed by the bomb
public client_death( iAttacker, iVictim, iWeapon, hitplace, TK )
{
	// Counter-Strike and Condition Zero Checks
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
	
			static iSkillLevel;
		iSkillLevel = SM_GetSkillLevel( iAttacker, SKILL_SOUL );
	if ( iSkillLevel > 0 )
	{   
	new hpbonus, curenthp;
	hpbonus = p_soul[iSkillLevel-1] ;
	curenthp = get_user_health(iAttacker) ;
		if(is_user_alive(iAttacker))
				{
		if((curenthp + hpbonus) > get_user_maxhealth(iAttacker))
			{set_user_health(iAttacker , get_user_maxhealth(iAttacker));
			SHARED_GlowShell(iAttacker, 255, 0, 255, 1.5, 50);}
		else 
			{set_user_health(iAttacker , curenthp + hpbonus);
			SHARED_GlowShell(iAttacker, 255, 0, 255, 1.5, 50);}
			
			
			}
	}
	
	iSkillLevel = SM_GetSkillLevel( iAttacker, PASS_HEAVEN );
	if ( iSkillLevel > 0 )
	{  new XP_BONUS = random_num(50,300) ;
		if ( is_user_connected(iAttacker) )
		 {if ( random_float( 0.0, 1.0 ) <= p_heaven[iSkillLevel] )
			{
		   ChatColor( iAttacker,"!g* [!t %s!g ] Your Victim !tSoul is in Heaven!g +!t %d XP !g!",g_MODclient,XP_BONUS);
		   XP_Give( iAttacker, XP_BONUS );
		   
			}
			}			
			
	}
	
	
	
	iSkillLevel = SM_GetSkillLevel( iAttacker, SKILL_RAISE );
	if ( iSkillLevel > 0 && is_user_connected(iAttacker) && is_user_alive(iAttacker) )
	{ 
		if ( random_float( 0.0, 1.0 ) <= p_raise[iSkillLevel-1] )
		{
				new id;
				id = iAttacker;
				respawn_menu(id);
			
		}
		
	}
	
	
	
	
		
	
	
	
	}
	
	
		 		

	
	

		// Check out who the inflictor was
		new iInflictor = entity_get_edict( iVictim, EV_ENT_dmg_inflictor );

		// Check to see if the death was from the bomb
		if ( !SHARED_ValidPlayer( iInflictor ) && iWeapon != CSW_HEGRENADE && iInflictor )
		{
			
			if ( is_valid_ent ( iInflictor ) )
			{
				new szClassName[64];
				entity_get_string( iInflictor, EV_SZ_classname, szClassName, 63 );

				// Check the classname of our inflictor
				if ( equali( szClassName, "grenade" ) || equali( szClassName, "env_explosion" ) )
				{
					iWeapon = CSW_C4;
					iAttacker = 0;

					// Well if this isn't set, shouldn't it be?
					if ( !p_data_b[iVictim][PB_DIEDLASTROUND] )
					{
						on_Death( iVictim, iAttacker, iWeapon, 0 );
					}
					//client_print( iVictim, print_chat, "[DEBUG] You were just killed by the bomb (%s) Alive? %d", szClassName, is_user_alive( iVictim ) );
				}
			}
		}
	}
//}

public on_Death( iVictim, iAttacker, iWeaponID, iHeadshot )
{

	if ( !WC3_Check() )
	{
		return;
	}
	
	// Counter-Strike and Condition Zero Checks
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		// For some reason the damage passed by explosions is not actually correct (perhaps armor adjustments weren't done yet), so lets check
		if ( is_user_alive( iVictim ) && iWeaponID == CSW_C4 )
		{
			return;
		}

		// Check for NightVision
		p_data_b[iVictim][PB_NIGHTVISION]	= (cs_get_user_nvg( iVictim )) ? true : false;

		// Check if a user had a shield on death
		p_data_b[iVictim][PB_SHIELD]		= (cs_get_user_shield( iVictim )) ? true : false;

		// See if the user has a defuse kit
		p_data_b[iVictim][PB_DEFUSE]		= (cs_get_user_defuse( iVictim )) ? true : false;

		// Save the number of flash grenades the user has
		p_data[iVictim][P_FLASHCOUNT]		= cs_get_user_bpammo( iVictim, CSW_FLASHBANG );
		
		// Check to see if weapons were silenced on death
		new iWeaponUSPEnt = find_ent_by_owner( -1, "weapon_usp", iVictim );
		new iWeaponM4A1Ent = find_ent_by_owner( -1, "weapon_m4a1", iVictim );
		
		if ( is_valid_ent( iWeaponUSPEnt ) )
		{
			p_data_b[iVictim][PB_USP_SILENCED]	= cs_get_weapon_silen( iWeaponUSPEnt ) ? true : false;
		}

		if ( is_valid_ent( iWeaponM4A1Ent ) )
		{
			p_data_b[iVictim][PB_M4A1_SILENCED]	= cs_get_weapon_silen( iWeaponM4A1Ent ) ? true : false;
		}


		// Check to see if weapons were in burst mode on death
		new iWeaponGlock18Ent = find_ent_by_owner( -1, "weapon_glock18", iVictim );
		new iWeaponFamasEnt = find_ent_by_owner( -1, "weapon_famas", iVictim );

		if ( is_valid_ent( iWeaponGlock18Ent ) )
		{
			p_data_b[iVictim][PB_GLOCK_BURST]	= cs_get_weapon_burst( iWeaponGlock18Ent ) ? true : false;
		}

		if ( is_valid_ent( iWeaponFamasEnt ) )
		{
			p_data_b[iVictim][PB_FAMAS_BURST]	= cs_get_weapon_burst( iWeaponFamasEnt ) ? true : false;
		}
		/*
		if(g_iShopMenuItems[iVictim][ITEM_SLOT_ONE] !=-1 || g_iShopMenuItems[iVictim][ITEM_SLOT_TWO]!=-1 || g_iShopMenuItems[iVictim][ITEM_SLOT_THREE]!=-1) 
 		{ 
    		test_create(iVictim) 
 		}
		*/
		static iSkillLevel;
		iSkillLevel = SM_GetSkillLevel( iAttacker, SKILL_BERSERKING );
	if ( iSkillLevel > 0 )
	{   
	
		if(is_user_alive(iAttacker))
				{ if ( random_float( 0.0, 1.0 ) <= p_berserking[iSkillLevel-1] )
					{
						give_item(iAttacker, "weapon_hegrenade") 
						give_item(iAttacker, "weapon_flashbang")
						give_item(iAttacker, "weapon_smokegrenade")
						
					}
	
				}
	}
	}
	
	// Day of Defeat Checks
	else if ( g_MOD == GAME_DOD )
	{

		// Save the user's origin for reincarnation
		get_user_origin( iVictim, iReincarnation[iVictim] );
	}

	WC3_Death( iVictim, iAttacker, iWeaponID, iHeadshot );
	
	return;
}

// Hook for CS/CZ
public on_DeathMsg()
{

	if ( !WC3_Check() )
	{
		return;
	}

	new iAttacker	= read_data( 1 );
	new iVictim		= read_data( 2 );
	new iHeadshot	= read_data( 3 );
	
	
	
	
	
	   if ( iAttacker )
   {
      if ( iAttacker != iVictim )
      {
         g_frags[ iAttacker ]++;
		 
		 if((get_user_flags(iAttacker) & ADMIN_LEVEL_H))
		 {
			 if(g_frags[ iAttacker ] >= KILL_LIMIT_VIP)
			{
		if(get_user_credits(iAttacker) + KILL_BONUS_VIP <= get_pcvar_num( CVAR_wc3_max_gold_vip ))
					{
		set_user_credits(iAttacker, get_user_credits(iAttacker) + KILL_BONUS_VIP);
					}
		else { set_user_credits(iAttacker, get_pcvar_num( CVAR_wc3_max_gold_vip ) ) ;
			 }
		
		ChatColor( iAttacker,"!g* [!t %s!g ] You received!t %d Gold Bonus!g for!t %d Kills",g_MODclientVIP,KILL_BONUS_VIP,KILL_LIMIT_VIP);
		
		g_frags[ iAttacker ] = 0;
		
			}
		 }
		 else {
		 if(g_frags[ iAttacker ] >= KILL_LIMIT)
			{
		if(get_user_credits(iAttacker) + KILL_BONUS <= get_pcvar_num( CVAR_wc3_max_gold ))
					{
		set_user_credits(iAttacker, get_user_credits(iAttacker) + KILL_BONUS);
					}
		else { set_user_credits(iAttacker, get_pcvar_num( CVAR_wc3_max_gold ) ) ;
			 }
		
		ChatColor( iAttacker,"!g* [!t %s!g ] You received!t %d Gold Bonus!g for!t %d Kills",g_MODclient,KILL_BONUS,KILL_LIMIT);
		
		g_frags[ iAttacker ] = 0;
		
			}
			 }
			
			
			if(iHeadshot && is_user_alive(iAttacker) && ITEM_Has( iAttacker, ITEM_SKULL ) > ITEM_NONE)   
					{
									if ( get_user_health( iAttacker ) + 35 <= get_user_maxhealth( iAttacker ) )
													{
														set_user_health( iAttacker, get_user_health( iAttacker ) + 35 );
													}
									else {		set_user_health( iAttacker, get_user_maxhealth( iAttacker ) ) ; 
					
										 }
     
					}
			
      }

	 
	  
	  
   }
	
	
	new iWeaponID;
	get_user_attacker( iVictim, iWeaponID );

	on_Death( iVictim, iAttacker, iWeaponID, iHeadshot );
	
	return;
}

new g_iLastCurWeapon[33];

public on_CurWeapon( id )
{
	// read_data(1) = isActive?
	// read_data(2) = weapon index
	// read_data(3) = ammo

	if ( !WC3_Check() )
	{
		return;
	}

	new iCurWeapon = read_data( 2 );

	// Then a weapon strip was triggered - we don't want to save now do we?
	if ( iCurWeapon == 0 && read_data( 1 ) == 0 && read_data( 3 ) == 0 )
	{
		return;
	}
	
	if ( ITEM_Has( id, ITEM_INFINITY ) > ITEM_NONE )
	{
		static clip;
		clip = read_data(3);

		give_ammo(id , iCurWeapon , clip);
		
	}
	

	// Record the last time a shot was fired
	fLastShotFired[id] = halflife_time();
	
	// Save the user's weapons
	SHARED_SaveWeapons( id );

	// Set the fuse for the weapon in DOD
	if ( g_MOD == GAME_DOD )
	{

		// Critical Grenade
		if ( SM_GetSkillLevel( id, SKILL_CRITICALGRENADE ) > 0 && SHARED_HasGrenade( id ) )
		{
			dod_set_fuse( id, FUSE_SET, 2.0, FT_NEW );
		}
	}
	
	// We only need to run these functions if the user's weapon has changed since our last function call!
	if ( g_iLastCurWeapon[id] != iCurWeapon && SHARED_ValidPlayer( id ) )
	{
		// Check to see if we should set the player's invisibility
		SHARED_INVIS_Set( id );
		
		// Set the user's speed
		SHARED_SetSpeed( id );
	}

	g_iLastCurWeapon[id] = iCurWeapon;

	return;
}

public on_Drop( id )
{
	if ( !WC3_Check() )
	{
		return;
	}

	SHARED_SaveWeapons( id );

	return;
}

// HamSandwich implementation
public EVENT_Spawn( id )
{

	if ( !WC3_Check() )
	{
		return HAM_HANDLED;
	}

	// ResetHUD can be called when the user is not alive, lets ignore those calls
	if ( !is_user_alive( id ) )
	{
		return HAM_HANDLED;
	}

	// Store the player's team!
	g_iPlayerTeam[id] = get_user_team( id );

	// Prespawn call
	//   - Purpose is to have a spawn call that happens before everything else!
	WC3_PreSpawn( id );
	
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		
		// This is the first time the user has spawned this round
		if ( !p_data_b[id][PB_HAS_SPAWNED] )
		{	
			EVENT_PlayerInitialSpawn( id );

			p_data_b[id][PB_HAS_SPAWNED] = true;
		}
	}
	
	// Start a new session under the following conditions:
	//		- Day of Defeat - need a new session per spawn!
	//		- CSDM - rounds never end!!!
	if ( g_MOD == GAME_DOD || ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 ) )
	{
		WC3_NewSession( id );
	}

	// Should be called at the end of each spawn
	WC3_PostSpawn( id );

	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( id, SKILL_FORM );
	if ( iSkillLevel > 0 )
	{  
		if ( random_float( 0.0, 1.0 ) <= p_form[iSkillLevel-1] )		
		{
		SHARED_ChangeSkin( id, SKIN_SWITCH );

		ChatColor( id,"!g* [!t %s!g ] You have your enemys form ! Enjoy !", g_MODclient );
		
	   	}

	
	}
	

	return HAM_HANDLED;
}

// Function called EVERYTIME a user spawns!
public on_ResetHud( id )
{

	if ( !WC3_Check() )
	{
		return PLUGIN_CONTINUE;
	}

	// ResetHUD can be called when the user is not alive, lets ignore those calls
	if ( !is_user_alive( id ) )
	{
		return PLUGIN_CONTINUE;
	}

	// Store the player's team!
	g_iPlayerTeam[id] = get_user_team( id );

	// We're forcibly respawning the player - so lets just return
	if ( bIgnorePlayerSpawning[id] )
	{
		return PLUGIN_CONTINUE;
	}

	// Prespawn call
	//   - Purpose is to have a spawn call that happens before everything else!
	WC3_PreSpawn( id );

	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		
		// This is the first time the user has spawned this round
		if ( !p_data_b[id][PB_HAS_SPAWNED] )
		{	
			EVENT_PlayerInitialSpawn( id );

			p_data_b[id][PB_HAS_SPAWNED] = true;
		}
	}
	
	// Start a new session under the following conditions:
	//		- Day of Defeat - need a new session per spawn!
	//		- CSDM - rounds never end!!!
	if ( g_MOD == GAME_DOD || ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 ) )
	{
		WC3_NewSession( id );
	}

	// Should be called at the end of each spawn
	WC3_PostSpawn( id );

	return PLUGIN_CONTINUE;
}

// Function is called when the user is spawned at the START of each round - only WC3_PreSpawn is called first
//		TRIGGERED BY: ResetHUD
public EVENT_PlayerInitialSpawn( id )
{
	

	// Display the cheat message ONLY if they just joined!
	if ( p_data_b[id][PB_JUSTJOINED] && get_pcvar_num( CVAR_wc3_cheats ) )
	{
		ChatColor( id,"!g* [!t %s!g ] WC3 Cheats are enabled on this server ! Try typing!t /level10", g_MODclient );
		
		

		p_data_b[id][PB_JUSTJOINED]			= false;
	}

	// Display the new Chameleon skills for the round
	/*if ( p_data[id][P_RACE] == 9 && get_pcvar_num( CVAR_wc3_cham_random ) )
	{
		WC3_ShowRaceInfo( id );
	}
	*/

	WC3_NewSession( id );

	return;
}

// Function is called ONCE at the start of a new round BEFORE user's spawn
public EVENT_NewRound()
{
	if ( !WC3_Check() )
	{
		return;
	}

		fRemoveAllItems();
	// Reset the global ultimate delay
	g_iUltimateDelay = get_pcvar_num( CVAR_wc3_ult_delay );

	// User's have not spawned yet, so lets do some pre-spawn things
	new players[32], numplayers, i;
	get_players( players, numplayers );
	for ( i = 0; i < numplayers; i++ )
	{
		WC3_BeforeSpawn( players[i] );
	}
	
	// Reset which spawn points are reserved....
	_SHARED_SpawnReset();

	// If someone restarted the game, then lets reset war3
	if ( g_GameRestarting )
	{
		WC3_ResetGame();
	}
	
	// Randomize Chameleon if we need to
	//CHAM_Randomize();

	// We need to determine when the buytime is up
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		if ( get_pcvar_num( CVAR_wc3_buy_time ) )
		{
			// Remove our buytime task if it exists (from a previous round)
			( task_exists( TASK_BUYTIME ) ) ? remove_task( TASK_BUYTIME ) : 0;

			g_buyTime = true;

			set_task( get_cvar_float("mp_buytime") * 60.0, "_CS_BuyTimeOver", TASK_BUYTIME );
		}

		g_freezeTime	= true;
	}

	g_EndRound = false;
new del_items = 0
 do
 { 
   del_items = find_ent_by_class(del_items,"test_item") 
   if(del_items > 0) 
    remove_entity(del_items) 
 } 
 while(del_items)
}

// Called when a user looks somewhere
public TRIGGER_TraceLine( Float:v1[3], Float:v2[3], noMonsters, pentToSkip )
{
	if ( !WC3_Check() )
	{
		return FMRES_IGNORED;
	}

	new iAttacker = pentToSkip;
	new iVictim = get_tr(TR_pHit);
	new iHitZone = (1 << get_tr(TR_iHitgroup));
	
	// Make sure we have a valid victim
	if ( SHARED_ValidPlayer( iVictim ) && p_data_b[iVictim][PB_ISCONNECTED] )
	{
		// We need to have a valid player!
		if ( SHARED_ValidPlayer( iAttacker ) )
		{
			// This is a check for ultimates that need to "search" for a target
			if ( p_data_b[iAttacker][PB_ISSEARCHING] )
			{

				// Now lets make sure the person he's looking at is in view and isn't on the same team
				if ( get_user_team( iAttacker ) != get_user_team( iVictim ) ) //&& UTIL_EntInView( iAttacker, iVictim ) )
				{
					
					// Check to see if the user should block this ultimate!
					if ( !g_EndRound && ULT_CanUserBlockUlt( iVictim ) )
					{
						ULT_RemoveCharge( iVictim, 0 );
						ULT_Blocked( iAttacker );
					}

					// Then the user's ult should work!
					else
					{
						// Well we do have a target so lets execute the user's ultimate!!
						if ( SM_GetSkillLevel( iAttacker, ULTIMATE_CHAINLIGHTNING ) > 0 )
						{
							OR_ULT_ChainLightning( iAttacker, iVictim, iHitZone );
						}
						else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_ENTANGLE ) > 0 )
						{
							NE_ULT_Entangle( iAttacker, iVictim );
						}
						else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_IMMOLATE ) > 0 )
						{
							BM_ULT_Immolate( iAttacker, iVictim );
						}
						else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_CLAWS ) > 0 )
						{
							WR_ULT_Claws( iAttacker, iVictim );
						}
						else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_MIND ) > 0 )
						{
							DL_ULT_MIND( iAttacker, iVictim );
						}
						else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_SHADOW ) > 0 )
						{
							DK_ULT_DEATH_SHADOW( iAttacker, iVictim );
						}
						
					}

					// No longer searching since we found a target
					p_data_b[iAttacker][PB_ISSEARCHING]	= false;

					// Set up the user's ultimate delay
					//ULT_ResetCooldown( iAttacker, get_pcvar_num( CVAR_wc3_ult_cooldown ) );

					if ( SM_GetSkillLevel( iAttacker, ULTIMATE_CHAINLIGHTNING ) == 1 )
					{ ULT_ResetCooldown( iAttacker, 45 ); }	
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_CHAINLIGHTNING ) == 2 )
					{ ULT_ResetCooldown( iAttacker, 35 ); }
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_CHAINLIGHTNING ) == 3 )
					{ ULT_ResetCooldown( iAttacker, 25 ); }
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_CHAINLIGHTNING ) == 4 )
					{ ULT_ResetCooldown( iAttacker, 15 ); }

			
					if ( SM_GetSkillLevel( iAttacker, ULTIMATE_ENTANGLE ) == 1 )
					{ ULT_ResetCooldown( iAttacker, 45 ); }	
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_ENTANGLE ) == 2 )
					{ ULT_ResetCooldown( iAttacker, 35 ); }
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_ENTANGLE ) == 3 )
					{ ULT_ResetCooldown( iAttacker, 25 ); }
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_ENTANGLE ) == 4 )
					{ ULT_ResetCooldown( iAttacker, 15 ); }

					
					if ( SM_GetSkillLevel( iAttacker, ULTIMATE_IMMOLATE ) == 1 )
					{ ULT_ResetCooldown( iAttacker, 45 ); }	
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_IMMOLATE ) == 2 )
					{ ULT_ResetCooldown( iAttacker, 35 ); }
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_IMMOLATE ) == 3 )
					{ ULT_ResetCooldown( iAttacker, 25 ); }
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_IMMOLATE ) == 4 )
					{ ULT_ResetCooldown( iAttacker, 15 ); }
					
					if ( SM_GetSkillLevel( iAttacker, ULTIMATE_CLAWS ) == 1 )
					{ ULT_ResetCooldown( iAttacker, 45 ); }	
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_CLAWS ) == 2 )
					{ ULT_ResetCooldown( iAttacker, 35 ); }
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_CLAWS ) == 3 )
					{ ULT_ResetCooldown( iAttacker, 25 ); }
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_CLAWS ) == 4 )
					{ ULT_ResetCooldown( iAttacker, 15 ); }
					
					if ( SM_GetSkillLevel( iAttacker, ULTIMATE_MIND ) == 1 )
					{ ULT_ResetCooldown( iAttacker, 45 ); }	
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_MIND ) == 2 )
					{ ULT_ResetCooldown( iAttacker, 35 ); }
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_MIND ) == 3 )
					{ ULT_ResetCooldown( iAttacker, 25 ); }
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_MIND ) == 4 )
					{ ULT_ResetCooldown( iAttacker, 15 ); }
					
					
					if ( SM_GetSkillLevel( iAttacker, ULTIMATE_SHADOW ) == 1 )
					{ ULT_ResetCooldown( iAttacker, 45 ); }	
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_SHADOW ) == 2 )
					{ ULT_ResetCooldown( iAttacker, 35 ); }
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_SHADOW ) == 3 )
					{ ULT_ResetCooldown( iAttacker, 25 ); }
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_SHADOW ) == 4 )
					{ ULT_ResetCooldown( iAttacker, 15 ); }
					
					
				}
			}

			// This is a nice check for Helm of Excellence
			if ( ITEM_Has( iVictim, ITEM_HELM ) > ITEM_NONE )
			{
				// Friendly fire is off! - This means same team shouldn't remove a charge!
				if ( !get_pcvar_num( CVAR_mp_friendlyfire ) )
				{
					if ( g_iPlayerTeam[iAttacker] == g_iPlayerTeam[iVictim] )
					{
						return FMRES_IGNORED;
					}
				}

				// If its a headshot then we want to block it
				if ( iHitZone & (1 << 1) )
				{
					set_tr( TR_flFraction, 1.0 );
					
					// Make sure we have a valid attacker!
					if ( SHARED_ValidPlayer( iAttacker ) )
					{
						// Do the check to see if we should flash the screen orange
						new Float:fTime = halflife_time();
						new Float:fDifference = fTime - fLastShotFired[iAttacker];

						if ( fDifference < 0.1 && fDifference > 0.0 )
						{
							Create_ScreenFade( iVictim, (1<<10), (1<<10), (1<<12), 0, 0, 255, 150 );

							// Lets remove a charge from the helm!
							ITEM_RemoveCharge( iVictim, ITEM_HELM );
						}
					}
					
					return FMRES_SUPERCEDE;
				}
			}
			
			static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( iVictim, SKILL_AFFINITY );
	if ( iSkillLevel > 0 )
	{  if ( iHitZone & (1 << 1) && random_float( 0.0, 1.0 ) <= p_affinity[iSkillLevel-1] )
				{
					set_tr( TR_flFraction, 1.0 );
					
					// Make sure we have a valid attacker!
					if ( SHARED_ValidPlayer( iAttacker ) )
					{
						// Do the check to see if we should flash the screen orange
						new Float:fTime = halflife_time();
						new Float:fDifference = fTime - fLastShotFired[iAttacker];

						if ( fDifference < 0.1 && fDifference > 0.0 )
						{
							Create_ScreenFade( iVictim, (1<<10), (1<<10), (1<<12), 0, 0, 255, 150 );
							emit_sound( iVictim, CHAN_STATIC, g_szSounds[SOUND_AFFINITY], 1.0, ATTN_NORM, 0, PITCH_NORM );
							ChatColor( iVictim,"!g* [!t %s!g ]!t HeadShot!g Blocked !", g_MODclient );
						}
					}
					
					return FMRES_SUPERCEDE;
				}
	}
	
		

			// Check to see if this user has night elf's evasion
			if ( SM_GetSkillLevel( iVictim, SKILL_EVASION ) > 0 )
			{
				// Do the check to see if we should "evade" this shot
				new Float:fTime = halflife_time();
				new Float:fDifference = fTime - fLastShotFired[iAttacker];

				if ( SHARED_ValidPlayer( iAttacker ) && fDifference < 0.1 && fDifference > 0.0 )
				{

					// Friendly fire is off! - This means we shouldn't evade since no damage will be done!
					if ( !get_pcvar_num( CVAR_mp_friendlyfire ) )
					{
						if ( g_iPlayerTeam[iAttacker] == g_iPlayerTeam[iVictim] )
						{
							return FMRES_IGNORED;
						}
					}
					
					// Then we should evade this shot!
					if ( NE_Evasion( iVictim, iHitZone ) )
					{
						set_tr( TR_flFraction, 1.0 );
						
						WC3_StatusText( iVictim, TXT_SKILL, "You have evaded a shot!" );

						return FMRES_SUPERCEDE;
					}
				}
			}
			
			// Mole protectant
			if ( p_data_b[iAttacker][PB_MOLE] && ITEM_Has( iVictim, ITEM_PROTECTANT ) > ITEM_NONE )
			{	
				new Float:fTime = halflife_time();

				if ( fTime - fLastShotFired[iAttacker] < 0.1  )
				{
					
					ChatColor( iVictim,"!g* [!t %s!g ] A shot by a mole was deflected", g_MODclient);

					set_tr( TR_flFraction, 1.0 );

					return FMRES_SUPERCEDE;
				}
			}

			// Check for Big Bad Voodoo's ultimate!
			if ( p_data_b[iVictim][PB_GODMODE] )
			{
				
				new bool:bBlockDamage = true;

				// Do we allow this person to be attacked by this player?
				if ( p_data_b[iAttacker][PB_BIGBAD_ATTACKER] )
				{
					bBlockDamage = false;
				}

				// Check to see if immunity is available for the attacker
				else if ( ULT_CanUserBlockUlt( iAttacker ) )
				{
					// Remove charge and display message to attacker
					ULT_RemoveCharge( iAttacker, 1 );

					// Display message about user's ultimate being blocked!
					ULT_Blocked( iVictim );

					// This user can attack someone with big bad voodoo!
					p_data_b[iAttacker][PB_BIGBAD_ATTACKER] = true;

					// Reset the attacker dmg
					//set_task( get_pcvar_float( CVAR_wc3_ult_cooldown ), "_SH_ResetBigBadAttacker", TASK_BIGBADATTACKER + iAttacker );

					if ( SM_GetSkillLevel( iAttacker, ULTIMATE_BIGBADVOODOO ) == 1 )
					{ set_task( 45.0, "_SH_ResetBigBadAttacker", TASK_BIGBADATTACKER + iAttacker );}	
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_BIGBADVOODOO ) == 2 )
					{ set_task( 35.0, "_SH_ResetBigBadAttacker", TASK_BIGBADATTACKER + iAttacker );}
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_BIGBADVOODOO ) == 3 )
					{ set_task( 25.0, "_SH_ResetBigBadAttacker", TASK_BIGBADATTACKER + iAttacker );}
					else if ( SM_GetSkillLevel( iAttacker, ULTIMATE_BIGBADVOODOO ) == 4 )
					{ set_task( 15.0, "_SH_ResetBigBadAttacker", TASK_BIGBADATTACKER + iAttacker );}
				}

				// Block the damage!
				if ( bBlockDamage )
				{
					set_tr( TR_flFraction, 1.0 );

					return FMRES_SUPERCEDE;
				}
			}
		}
	}
	
	return FMRES_IGNORED;
}



public Event_Damage( iVictim )
{
    if(read_data(4) || read_data(5) || read_data(6)) 
    {
        new id = get_user_attacker(iVictim)
        if( (1 <= id <= get_maxplayers()) && is_user_connected(id) && ITEM_Has( id, ITEM_OMNISCIENCE ) > ITEM_NONE )
        {
            new iPos = ++g_iPlayerPos[id]
            if( iPos == sizeof(g_flCoords) )
            {
                iPos = g_iPlayerPos[id] = 0
            }
			 set_dhudmessage(0, 40, 80, Float:g_flCoords[iPos][0], Float:g_flCoords[iPos][1], 2, 0.0, 2.0, 0.02, 0.02)
            show_dhudmessage(id, "%d", read_data(2))
        }
    }
}  




public HAM_Player_PreThink(id) {
	if(is_user_alive(id) && ITEM_Has( id, ITEM_SPIKES ) > ITEM_NONE) {
		static Float:Origin[3];
		pev(id, pev_origin, Origin);
		
		static Button ;
		Button = pev(id, pev_button)
		
		if(Button & IN_USE && get_distance_f(Origin, WallOrigin[id]) <= 15.0) {
			new Float:Velocity[3];
			if(Button & IN_FORWARD) {
				velocity_by_aim(id, 120, Velocity);
				fm_set_user_velocity(id, Velocity);
			}
			else if(Button & IN_BACK) {
				velocity_by_aim(id, -120, Velocity);
				fm_set_user_velocity(id, Velocity);
			}
			else {
				velocity_by_aim(id, 0, Velocity);
				fm_set_user_velocity(id, Velocity);
			}
		}	
	}
}

public Touch_Climb(Ent,id)
{
    //If player is touching a wall then we find it's origin

    pev(id,pev_origin,WallOrigin[id]);
        
    return PLUGIN_HANDLED;
}  

stock fm_set_user_velocity(entity, const Float:vector[3]) {
    set_pev(entity, pev_velocity, vector);

    return 1;
}