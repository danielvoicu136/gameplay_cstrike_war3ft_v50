#define HEROIC_DAMAGE		15			// Amount of damage dealt with heroic presence
#define GIFT_RANGE 750    // Distance Between Gift Works 	



DR_SkillsDefensive( iVictim, iDamage )
{
	static iSkillLevel;
	
	// Resistant Skin
	iSkillLevel = SM_GetSkillLevel( iVictim, SKILL_SHADOW );
	if ( iSkillLevel > 0 )
	{
		new iBonusHealth = floatround( float( iDamage ) * p_shadow_resistence[iSkillLevel-1] );
		
		if ( p_data_b[iVictim][PB_ISCONNECTED] )
		{
			set_user_health( iVictim, get_user_health( iVictim ) + iBonusHealth );
		}
	}
	
}


DR_SkillsOffensive( iAttacker, iVictim, iHitPlace )
{

	static iSkillLevel;

	// Heroic Presence 
	iSkillLevel = SM_GetSkillLevel( iAttacker, SKILL_HEROIC );
	if ( iSkillLevel > 0 )
	{

		if ( random_float( 0.0, 1.0 ) <= p_heroic[iSkillLevel-1] )
		{

			SHARED_GlowShell(iVictim, 255, 0, 0, 1.5, 100);

			// Damage the user
			WC3_Damage( iVictim, iAttacker, HEROIC_DAMAGE, CSW_SHADOW, iHitPlace );
		}

		else if ( get_pcvar_num( CVAR_wc3_psychostats ) )
		{
			new WEAPON = CSW_SHADOW - CSW_WAR3_MIN;

			iStatsShots[iAttacker][WEAPON]++;
		}
	}
}



public DR_Abundence( id )
{
	if ( !task_exists( id + TASK_ABUNDENCE ) )
	{
		_DR_Abundence( id );
	}
}

// We don't need to ever actually "turn this off" since this task will take care of itself
public _DR_Abundence( id )
{
	
	if ( id >= TASK_ABUNDENCE	)
	{
		id -= TASK_ABUNDENCE;
	}
	
	// User is no longer connected :/
	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}
	
	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( id, SKILL_ABUNDENCE );
	
	// User doesn't have this skill, so lets return
	//  - Also return if this was called twice
	if ( iSkillLevel <= 0 )
	{
		return;
	}
	
	// Continue healing...
	if ( is_user_alive( id ) )
	{
		set_task( 10.0, "_DR_Abundence", TASK_ABUNDENCE + id );
	}
	
		
		// User is on the caster's team 
		
			if ( is_user_alive( id ) ) 
			{
				
				
				if ( cs_get_user_money( id ) + p_money[iSkillLevel-1] <= 16000 ) 
				{ 
					
					cs_set_user_money( id, cs_get_user_money( id ) + p_money[iSkillLevel-1]) ; 
					
				} 
								
				 
				
			} 
		return;
}
	
	
	
public DR_Ult_Gift( id )
{
	if ( !is_user_connected( id ) )
	{
		return;
	}


	new players[32], numberofplayers, targetid, targetorigin[3], origin[3];
	new iTeam = get_user_team( id );

	get_user_origin( id, origin );
	get_players( players, numberofplayers, "a" );
	
	// Loop through each player and check to see if one is close enough to be healed
	for ( new i = 0; i < numberofplayers; i++ )
	{
		targetid = players[i];
		
		// User is on the caster's team
		if ( is_user_connected( targetid ) && get_user_team( targetid ) == iTeam )
		{
			get_user_origin( targetid, targetorigin );
			
			// User is close enough
			if ( get_distance(origin, targetorigin) <= GIFT_RANGE )
			{
				if (ITEM_Has(id, ITEM_SCEPTER ) > ITEM_NONE)
				{
				if ( get_user_health( targetid ) + 90 <= get_user_maxhealth( targetid ) )
				{
					set_user_health( targetid, get_user_health( targetid ) + 90 );
					fm_cs_set_user_armor( targetid, get_user_armor( targetid ) + 100 , CS_ARMOR_VESTHELM );
					SHARED_GlowShell(targetid, 255, 255, 0, 1.5, 100);
					Create_ScreenFade(targetid,(1<<15),(1<<10),(1<<12), 255, 255, 0, 100);
					emit_sound( targetid, CHAN_STATIC, g_szSounds[SOUND_AR], 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
				else 
				{ 	set_user_health( targetid, get_user_maxhealth( targetid ) ) ; 
					fm_cs_set_user_armor( targetid, get_user_armor( targetid ) + 100 , CS_ARMOR_VESTHELM );
					SHARED_GlowShell(targetid, 255, 255, 0, 1.5, 100);
					Create_ScreenFade(targetid,(1<<15),(1<<10),(1<<12), 255, 255, 0, 100);
					emit_sound( targetid, CHAN_STATIC, g_szSounds[SOUND_AR], 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
				}
				else {
				if ( get_user_health( targetid ) + 45 <= get_user_maxhealth( targetid ) )
				{
					set_user_health( targetid, get_user_health( targetid ) + 45 );
					fm_cs_set_user_armor( targetid, get_user_armor( targetid ) + 50 , CS_ARMOR_VESTHELM );
					SHARED_GlowShell(targetid, 255, 255, 0, 1.5, 100);
					Create_ScreenFade(targetid,(1<<15),(1<<10),(1<<12), 255, 255, 0, 100);
					emit_sound( targetid, CHAN_STATIC, g_szSounds[SOUND_AR], 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
				else 
				{ 	set_user_health( targetid, get_user_maxhealth( targetid ) ) ; 
					fm_cs_set_user_armor( targetid, get_user_armor( targetid ) + 50 , CS_ARMOR_VESTHELM );
					SHARED_GlowShell(targetid, 255, 255, 0, 1.5, 100);
					Create_ScreenFade(targetid,(1<<15),(1<<10),(1<<12), 255, 255, 0, 100);
					emit_sound( targetid, CHAN_STATIC, g_szSounds[SOUND_AR], 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
				}
				
				
			}
		}
	}
	if ( SM_GetSkillLevel( id, ULTIMATE_GIFT ) == 1 )
		{ ULT_ResetCooldown( id, 45 ); }	
		else if ( SM_GetSkillLevel( id, ULTIMATE_GIFT ) == 2 )
		{ ULT_ResetCooldown( id, 35 ); }
		else if ( SM_GetSkillLevel( id, ULTIMATE_GIFT ) == 3 )
		{ ULT_ResetCooldown( id, 25 ); }
		else if ( SM_GetSkillLevel( id, ULTIMATE_GIFT ) == 4 )
		{ ULT_ResetCooldown( id, 15 ); }
	
	return;
}