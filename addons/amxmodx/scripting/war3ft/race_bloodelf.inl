#define ARCANE_TORENT_RANGE 750

#define SLEEP_RANGE 350



BE_SkillsOffensive( iAttacker, iVictim )
{

	static iSkillLevel;
	
	// 
	iSkillLevel = SM_GetSkillLevel( iAttacker, SKILL_TORENT );
	if ( iSkillLevel > 0 )
	{
		
		if ( random_float( 0.0, 1.0 ) <= p_torent[iSkillLevel-1] )
		{
			
	new players[32], numberofplayers;
	get_players( players, numberofplayers, "a" );
	new i, iTargetID, vTargetOrigin[3], iDistance, vOrigin[3], vPosition[3],vPosition2[3];
	new iTeam = get_user_team( iVictim );
	get_user_origin( iVictim, vOrigin );
	
	vPosition[0] = vOrigin[0];
	vPosition[1] = vOrigin[1];
	vPosition[2] = vOrigin[2] + 50;
	
	Create_TE_BEAMCYLINDER( vOrigin, vOrigin, vPosition, g_iSprites[SPR_SHOCKWAVE], 0, 0, 6, 30, 0, 0, 0, 255, 255, 0 );
	
	// Check all players and see if they should be damaged
			for ( i = 0; i < numberofplayers; i++ )
			{
	iTargetID = players[i];
	
	// Get origin of target
	get_user_origin( iTargetID, vTargetOrigin );
	
	// Get distance in b/t target and caster
	iDistance = get_distance( vOrigin, vTargetOrigin );
	
					if ( iDistance < ARCANE_TORENT_RANGE && iTeam == get_user_team( iTargetID ))
						{

	vPosition2[0] = vTargetOrigin[0];
	vPosition2[1] = vTargetOrigin[1];
	vPosition2[2] = vTargetOrigin[2] + 50;
	
	Create_TE_BEAMCYLINDER( vTargetOrigin, vTargetOrigin, vPosition2, g_iSprites[SPR_SHOCKWAVE], 0, 0, 6, 30, 0, 0, 0, 255, 255, 0 );
		
		// Damage them!!!!
		WC3_Damage( iTargetID, iAttacker, 10, CSW_SUICIDE, -1 );
		
		// Lets shake up their screen a bit
		Create_ScreenShake( iTargetID, (1<<14), (1<<13), (1<<14) );
						}
				
			
			}
		}

	}
	

	iSkillLevel = SM_GetSkillLevel( iVictim, SKILL_BLOODEYES );
	if ( iSkillLevel > 0 )
	{
		if ( random_float( 0.0, 1.0 ) <= p_bloodeyes[iSkillLevel-1] )		
		{
			
		//Create_ScreenFade( iAttacker, 2, (1<<10), (1<<12), 255, 0, 0, 255 ); 
		Create_ScreenFade(iAttacker,(1<<15),(1<<10),(1<<12), 255, 0, 0, 200);
		
		}
	}
	
	
}





public BF_PlaceSleep( id )
{
   if ( is_user_alive( id ) )
   {
			new parm[5];
			new origin[3];
			get_user_origin( id, origin );
			parm[0] = origin[0];
			parm[1] = origin[1];
			parm[2] = origin[2];
			parm[3] = id;
			parm[4] = get_user_team( id );
			
			SLEEP_ON = true;
			
	
			
			emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_SLEEP], 1.0, ATTN_NORM, 0, PITCH_NORM );

			_BF_DrawSleep( parm );
			
			if ( SM_GetSkillLevel( id, ULTIMATE_SLEEP ) == 1 )
		{ ULT_ResetCooldown( id, 45 ); }	
		else if ( SM_GetSkillLevel( id, ULTIMATE_SLEEP ) == 2 )
		{ ULT_ResetCooldown( id, 35 ); }
		else if ( SM_GetSkillLevel( id, ULTIMATE_SLEEP ) == 3 )
		{ ULT_ResetCooldown( id, 25 ); }
		else if ( SM_GetSkillLevel( id, ULTIMATE_SLEEP ) == 4 )
		{ ULT_ResetCooldown( id, 15 ); }
		
		set_task( 10.0, "BF_Ult_Remove", TASK_BLDELF + id );  
	}
	return;

}

public _BF_DrawSleep( parm[5] )
{

	if ( !WC3_Check() )
	{
		return;
	}

	if ( !SLEEP_ON )
	{
		return;
	}
	new id = parm[3];

	// User is no longer connected, stop drawing wards
	if( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}

	// User is no longer alive, don't draw wards
	if ( !is_user_alive( id ) )
	{		
		return;
	}


	new origin[3];
	origin[0]=parm[0]
	origin[1]=parm[1]
	origin[2]=parm[2]
	
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
		write_byte(TE_BEAMCYLINDER);
		write_coord(origin[0]); // x
		write_coord(origin[1]); // y
		write_coord(origin[2]); // z
		write_coord(origin[0]); // x axis
		write_coord(origin[1]); // y axis
		write_coord(origin[2] + SLEEP_RANGE); // z axis
		write_short(g_iSprites[SPR_TRAIL]); // sprite
		write_byte(0); // start frame
		write_byte(1); // framerate
		write_byte(6); // life
		write_byte(8); // width
		write_byte(1); // noise
		write_byte(0); // red
		write_byte(255); // green
		write_byte(0); // blue
		write_byte(192); // brightness
		write_byte(0); // speed
		message_end();
		
	
	


	// Now lets check and see if any players are near that need to be damaged
	new players[32], numberofplayers;
	new targetid, targetorigin[3];

	get_players( players, numberofplayers, "a" );
	
	for ( new i = 0; i < numberofplayers; i++ )
	{
		targetid = players[i];

		if ( parm[4] != get_user_team( targetid ) )
		{
			get_user_origin( targetid, targetorigin );

			if ( get_distance( origin, targetorigin ) < SLEEP_RANGE && SLEEP_ON )
			{

				if ( !ULT_CanUserBlockUlt( targetid ) )
					{
					if (ITEM_Has(id, ITEM_SCEPTER ) > ITEM_NONE)
					{
				WC3_Damage( targetid, id, 2*10, CSW_SERPENTWARD, -1 );
					}
					else { WC3_Damage( targetid, id, 10, CSW_SERPENTWARD, -1 ); }

				Create_ScreenFade( id, (1<<10), (1<<10), (1<<12), 0, 255, 0, 70 );
				Create_ScreenFade( targetid, (1<<10), (1<<10), (1<<12), 0, 255, 0, 130 );
				emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_SLEEP], 1.0, ATTN_NORM, 0, PITCH_NORM );
				emit_sound( targetid, CHAN_STATIC, g_szSounds[SOUND_SLEEP], 1.0, ATTN_NORM, 0, PITCH_NORM );
					}
				
			}
		}
	}

	set_task( 0.5, "_BF_DrawSleep", TASK_SLEEP + id, parm, 5 );

	return;
}
   
   

public BF_Ult_Remove( id )
{
	if ( id >= TASK_BLDELF )
	{
		id -= TASK_BLDELF;
	}

	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}

	SLEEP_ON = false;

	return;
}