#define WATER_DAMAGE 10
#define FIRE_RANGE 350
#define DU_NATURA_DURATION 2




DU_SkillsOffensive( iAttacker, iVictim, iHitPlace )
{

	static iSkillLevel;

	
	iSkillLevel = SM_GetSkillLevel( iAttacker, SKILL_WATER );
	if ( iSkillLevel > 0 )
	{

		if ( random_float( 0.0, 1.0 ) <= p_water[iSkillLevel-1] )
		{

			new vVictimOrigin[3], vAttackerOrigin[3]
			get_user_origin( iVictim, vVictimOrigin );
			get_user_origin( iAttacker, vAttackerOrigin );
			
			// Create the shadow strike effect
			Create_TE_SPRITETRAIL( vAttackerOrigin, vVictimOrigin, g_iSprites[SPR_WATER], 50, 15, 2, 2, 6 );
			
			// Emit the shadow strike sound
			emit_sound( iVictim, CHAN_STATIC, g_szSounds[SOUND_WATER], 1.0, ATTN_NORM, 0, PITCH_NORM );

			// Damage the user
			WC3_Damage( iVictim, iAttacker, WATER_DAMAGE, CSW_SHADOW, iHitPlace );
		}

		else if ( get_pcvar_num( CVAR_wc3_psychostats ) )
		{
			new WEAPON = CSW_SHADOW - CSW_WAR3_MIN;

			iStatsShots[iAttacker][WEAPON]++;
		}
	}
	
	
		iSkillLevel = SM_GetSkillLevel( iAttacker, SKILL_TYPHOON );
	if ( iSkillLevel > 0 )
	{

		if ( random_float( 0.0, 1.0 ) <= p_typhoon[iSkillLevel-1] )
		{

			// Play the impale sound
			emit_sound( iVictim, CHAN_STATIC, g_szSounds[SOUND_IMPALE], 1.0, ATTN_NORM, 0, PITCH_NORM );
			
			new Float:vVelocity[3];
			entity_get_vector( iVictim, EV_VEC_velocity, vVelocity );

			vVelocity[0] = random_float( 100.0, 400.0 );
			vVelocity[1] = random_float( 100.0, 400.0 );
			vVelocity[2] = random_float( 400.0, 700.0 );

			entity_set_vector( iVictim, EV_VEC_velocity, vVelocity );
		}
	}
	
	
	iSkillLevel = SM_GetSkillLevel( iAttacker, SKILL_FIRE );
	if ( iSkillLevel > 0 )
	{
		
		if ( random_float( 0.0, 1.0 ) <= p_fire[iSkillLevel-1] )
		{
			
	new players[32], numberofplayers;
	get_players( players, numberofplayers, "a" );
	new i, iTargetID, vTargetOrigin[3], iDistance, vOrigin[3];
	new iTeam = get_user_team( iVictim );
	get_user_origin( iVictim, vOrigin );
	
	
	
		message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
		write_byte(TE_BEAMCYLINDER);
		write_coord(vOrigin[0]); // x
		write_coord(vOrigin[1]); // y
		write_coord(vOrigin[2] - 20); // z
		write_coord(vOrigin[0]); // x axis
		write_coord(vOrigin[1]); // y axis
		write_coord(vOrigin[2] + FIRE_RANGE); // z axis
		write_short(g_iSprites[SPR_TRAIL]); // sprite
		write_byte(0); // start frame
		write_byte(1); // framerate
		write_byte(6); // life
		write_byte(8); // width
		write_byte(1); // noise
		write_byte(255); // red
		write_byte(0); // green
		write_byte(0); // blue
		write_byte(192); // brightness
		write_byte(0); // speed
		message_end();
		
	
	/*
	vPosition[0] = vOrigin[0];
	vPosition[1] = vOrigin[1];
	vPosition[2] = vOrigin[2];
	
	Create_TE_BEAMCYLINDER( vOrigin, vOrigin, vPosition, g_iSprites[SPR_SHOCKWAVE], 0, 0, 6, 80, 0, 255, 0, 0, 255, 0 );
	*/
	
	// Check all players and see if they should be damaged
			for ( i = 0; i < numberofplayers; i++ )
			{
	iTargetID = players[i];
	
	// Get origin of target
	get_user_origin( iTargetID, vTargetOrigin );
	
	// Get distance in b/t target and caster
	iDistance = get_distance( vOrigin, vTargetOrigin );
	
					if ( iDistance < FIRE_RANGE && iTeam == get_user_team( iTargetID ) && iVictim != iTargetID)
						{

		
		// Damage them!!!!
		WC3_Damage( iTargetID, iAttacker, 10, CSW_SUICIDE, -1 );
		
		// Lets shake up their screen a bit
		Create_ScreenShake( iTargetID, (1<<14), (1<<13), (1<<14) );
						}
				
			
			}
		}

	}

	
}



public DU_ULT_Natura( id )
{
	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}

	if ( SM_GetSkillLevel( id, ULTIMATE_NATURA ) == 1 )
		{ ULT_ResetCooldown( id, 45 ); }	
		else if ( SM_GetSkillLevel( id, ULTIMATE_NATURA ) == 2 )
		{ ULT_ResetCooldown( id, 35 ); }
		else if ( SM_GetSkillLevel( id, ULTIMATE_NATURA ) == 3 )
		{ ULT_ResetCooldown( id, 25 ); }
		else if ( SM_GetSkillLevel( id, ULTIMATE_NATURA ) == 4 )
		{ ULT_ResetCooldown( id, 15 ); }

	ULT_Icon( id, ICON_FLASH );
	
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{		if (ITEM_Has(id, ITEM_SCEPTER ) > ITEM_NONE)
		  {Create_BarTime( id, 2*DU_NATURA_DURATION, 0 );}
		  else {Create_BarTime( id, DU_NATURA_DURATION, 0 );}
	}
		
	emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_VOODOO], 1.0, ATTN_NORM, 0, PITCH_NORM );
		
	//set_entity_visibility(id, 0);
	set_user_noclip(id,1);
	if (ITEM_Has(id, ITEM_SCEPTER ) > ITEM_NONE)
	{set_task( float( 2*DU_NATURA_DURATION ), "DU_Ult_Remove", TASK_NATURA + id ); }
	else {set_task( float( DU_NATURA_DURATION ), "DU_Ult_Remove", TASK_NATURA + id ); }

	return;
}

public DU_Ult_Remove( id )
{
	if ( id >= TASK_NATURA )
	{
		id -= TASK_NATURA;
	}

	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}

	//set_entity_visibility(id, 1);
	set_user_noclip(id,0);

	ULT_Icon( id, ICON_HIDE );

	return;
}