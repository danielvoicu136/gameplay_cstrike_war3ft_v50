#define TR_STEALTH_DURATION 2

public TR_Regeneration( id )
{
	if ( !task_exists( id + TASK_TRREG ) )
	{
		_TR_Regeneration( id );
	}
}

// We don't need to ever actually "turn this off" since this task will take care of itself
public _TR_Regeneration( id )
{
	
	if ( id >= TASK_TRREG	)
	{
		id -= TASK_TRREG;
	}
	
	// User is no longer connected :/
	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}
	
	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( id, SKILL_REGENERATION );
	
	// User doesn't have this skill, so lets return
	//  - Also return if this was called twice
	if ( iSkillLevel <= 0 )
	{
		return;
	}
	
	// Continue healing...
	if ( is_user_alive( id ) )
	{
		set_task( 10.0, "_TR_Regeneration", TASK_TRREG + id );
	}
	
		
		// User is on the caster's team 
		
			if ( is_user_alive( id ) ) 
			{
				
				
				if ( get_user_health( id ) + p_regeneration[iSkillLevel-1] <= get_user_maxhealth( id ) ) 
				{ 
					set_user_health( id, get_user_health( id ) + p_regeneration[iSkillLevel-1] ); 
					
				} 
				else { set_user_health( id, get_user_maxhealth( id ) ) ; }
				
				 
				
			} 
		return;
}
	
TR_SkillsOffensive( iAttacker, iVictim )
{
	
	static iSkillLevel;

	iSkillLevel = SM_GetSkillLevel( iAttacker, SKILL_SHUFFLE );
	if ( iSkillLevel > 0 )
	{
		if ( random_float( 0.0, 1.0 ) <= p_shuffle[iSkillLevel-1] )		
		{
		Create_ScreenShake( iVictim , (255<<14), (10<<14), (255<< 14) );	
		emit_sound( iVictim, CHAN_STATIC, g_szSounds[SOUND_HEX], 1.0, ATTN_NORM, 0, PITCH_NORM );
		
		}
	}

}
	
	
	
public TR_Ult_StealthAura( id )
{
	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}

	if ( SM_GetSkillLevel( id, ULTIMATE_STEALTH ) == 1 )
		{ ULT_ResetCooldown( id, 45 ); }	
		else if ( SM_GetSkillLevel( id, ULTIMATE_STEALTH ) == 2 )
		{ ULT_ResetCooldown( id, 35 ); }
		else if ( SM_GetSkillLevel( id, ULTIMATE_STEALTH ) == 3 )
		{ ULT_ResetCooldown( id, 25 ); }
		else if ( SM_GetSkillLevel( id, ULTIMATE_STEALTH ) == 4 )
		{ ULT_ResetCooldown( id, 15 ); }

	ULT_Icon( id, ICON_FLASH );
	
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{	if (ITEM_Has(id, ITEM_SCEPTER ) > ITEM_NONE)
		{Create_BarTime( id,2 * TR_STEALTH_DURATION, 0 );}
		else {Create_BarTime( id, TR_STEALTH_DURATION, 0 );}
	}
		
	emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_VOODOO], 1.0, ATTN_NORM, 0, PITCH_NORM );
		
	set_entity_visibility(id, 0);
	if (ITEM_Has(id, ITEM_SCEPTER ) > ITEM_NONE)
	{set_task( float( 2*TR_STEALTH_DURATION ), "TR_Ult_Remove", TASK_STEALTH + id ); }
	else {set_task( float( TR_STEALTH_DURATION ), "TR_Ult_Remove", TASK_STEALTH + id ); }

	return;
}

public TR_Ult_Remove( id )
{
	if ( id >= TASK_STEALTH )
	{
		id -= TASK_STEALTH;
	}

	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}

	set_entity_visibility(id, 1);

	ULT_Icon( id, ICON_HIDE );

	return;
}