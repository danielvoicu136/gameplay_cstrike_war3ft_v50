#define etherealdamage 10.0
#define WORDS_RANGE 750
#define etherealknockback 3.0

new g_PR_LightGiven[33];


PR_SkillsOffensive( iAttacker )
{

	static iSkillLevel;

	// Spiritual Energy
	iSkillLevel = SM_GetSkillLevel( iAttacker, SKILL_ENERGY );
	if ( iSkillLevel > 0 )
	{

		if ( random_float( 0.0, 1.0 ) <= p_energy[iSkillLevel-1] )
		{
			new id = iAttacker;
			Ethereal_Fire(id);
			
		}

		
	}
}


PR_SkillsDefensive( iVictim, iDamage )
{
	static iSkillLevel;
	
	// Power Words 
	iSkillLevel = SM_GetSkillLevel( iVictim, SKILL_WORDS );
	if ( iSkillLevel > 0 )
	{
		new iBonusHealth = floatround( float( iDamage ) * p_words[iSkillLevel-1] );
		
		
		new players[32], numberofplayers, targetid, targetorigin[3], origin[3];
	new iTeam = get_user_team( iVictim );

	get_user_origin( iVictim, origin );
	get_players( players, numberofplayers, "a" );
	
	// Loop through each player and check to see if one is close enough to be healed
	for ( new i = 0; i < numberofplayers; i++ )
	{
		targetid = players[i];
		
		// User is on the caster's team
		if ( p_data_b[targetid][PB_ISCONNECTED] && get_user_team( targetid ) == iTeam )
		{
			get_user_origin( targetid, targetorigin );
			
			// User is close enough
			if ( get_distance(origin, targetorigin) < WORDS_RANGE )
			{
				get_user_origin( targetid, origin )
				if ( is_user_alive ( targetid ) && is_user_connected ( targetid ))
				{
				// User needs health
				if ( get_user_health( targetid ) + iBonusHealth <= get_user_maxhealth( targetid ) )
				{
					set_user_health( targetid, get_user_health( targetid ) + iBonusHealth );
					//ChatColor( targetid,"!g* [!t %s!g ] You received a !thealth bonus %d!g thanks to a!t Priest!g !",g_MODclient,iBonusHealth);
				}
				else { set_user_health( targetid, get_user_maxhealth( targetid ) ) ;
				//ChatColor( targetid,"!g* [!t %s!g ] Your !tlife is full!g again thanks to a!t Priest!g !",g_MODclient);
				}
				
				//SHARED_GlowShell(targetid, 137, 137, 137, 1.5, 100);
				}
						
			}
		}
	}	
		
	}
	
}

PR_LightWard( id )
{
	static iSkillLevel;

	iSkillLevel = SM_GetSkillLevel( id, SKILL_LIGHT );

	// User should have some!
	if ( iSkillLevel > 0 )
	{

		// Then we can give the user a serpent ward!
		while ( g_PR_LightGiven[id] < p_light[iSkillLevel-1] )
		{
			// Increase the available serpent wards
			p_data[id][P_LIGHTCOUNT]++;

			// Increase the total we have given the user!
			g_PR_LightGiven[id]++;

			//client_print( id, print_chat, "[DEBUG] Total wards increased to %d (total given so far: %d)", p_data[id][P_SERPENTCOUNT], g_SH_SerpentGiven[id] );
		}
	}
	
	// User should not have any!
	else
	{
		// Remove all available serpents!
		p_data[id][P_LIGHTCOUNT] = 0;

		// We don't need to remove any of the wards b/c the task knows to check the skill level
	}
}

public PR_PlaceLightWard( id )
{

	// User is hexed, can't use any skills
	if ( p_data_b[id][PB_HEXED] )
	{
		WC3_StatusText( id, 0, "%L", id, "HEX_NO_ABILITY" );
	}

	// User is alive we can place a ward!
	else if ( is_user_alive( id ) && SM_GetSkillLevel( id, SKILL_LIGHT ) > 0 && p_data[id][P_LIGHTCOUNT] > 0 )
	{

		
			new parm[5], origin[3]

			get_user_origin( id, origin );
			parm[0] = origin[0];
			parm[1] = origin[1];
			parm[2] = origin[2];
			parm[3] = id;
			parm[4] = get_user_team( id );

			_PR_DrawLightWard( parm );
			p_data[id][P_LIGHTCOUNT]--;

			WC3_StatusText( id, 0, "%L", id, "LIGHT_WARD", p_data[id][P_LIGHTCOUNT] );
		
	}
}


public _PR_DrawLightWard( parm[5] )
{

	if ( !WC3_Check() )
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
		p_data[id][P_LIGHTCOUNT]++;
		return;
	}

	// User doesn't have this skill anymore! Remove the ward!
	if ( SM_GetSkillLevel( id, SKILL_LIGHT ) <= 0 )
	{
		return;
	}

	

	new origin[3], start[3], end[3], red, blue, green
	origin[0]=parm[0]
	origin[1]=parm[1]
	origin[2]=parm[2]
	
	// Set up the top of the ward
	start[0] = origin[0]
	start[1] = origin[1]
	start[2] = origin[2] + 600

	// Set up the bottom of the ward
	end[0] = origin[0]
	end[1] = origin[1]
	end[2] = origin[2] - 600

	// Set up colors based on what game/team
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		if ( parm[4] == TS )
		{
			red		= 255;
			blue	= 0;
			green	= 255;
		}
		else
		{
			red		= 255;
			blue	= 0;
			green	= 255;
		}
	}
	
	else if ( g_MOD == GAME_DOD )
	{
		if ( parm[4] == AXIS )
		{
			red		= 255;
			blue	= 0;
			green	= 0;
		}
		else
		{
			red		= 20;
			blue	= 225;
			green	= 160;
		}
	}

	// Draw the serpent ward
	Create_TE_BEAMPOINTS( start, end, g_iSprites[SPR_LIGHTNING], 1, 5, 2, 500, 20, red, green, blue, 100, 100 );

	// Now lets check and see if any players are near that need to be damaged
	new players[32], numberofplayers;
	new targetid, targetorigin[3];

	get_players( players, numberofplayers, "a" );
	
	for ( new i = 0; i < numberofplayers; i++ )
	{
		targetid = players[i];

		if ( parm[4] == get_user_team( targetid ) )
		{
			get_user_origin( targetid, targetorigin );

			if ( get_distance( origin, targetorigin ) < 85 )
			{

				// Damage the user
				if ( is_user_alive( targetid ) && is_user_connected ( targetid ) )
				if( get_user_health( targetid ) + 1 <= get_user_maxhealth( targetid ) )
				{set_user_health( targetid, get_user_health( targetid ) + 1);
				}
				

				// Make the sound when they're attacked
				client_cmd( targetid, "speak ambience/thunder_clap.wav" );

				// Create screen fade on the owners screen
				//Create_ScreenFade( id, (1<<10), (1<<10), (1<<12), red, green, blue, 70 );
				Create_ScreenFade( targetid, (1<<10), (1<<10), (1<<12), red, green, blue, 130 );
			}
		}
	}

	set_task( 0.5, "_PR_DrawLightWard", TASK_LIGHTWARD + id, parm, 5 );

	return;
}





public DL_ULT_MIND( iCaster, iTarget )
{	

	
	new echipa , echipa2;
	echipa2 = get_user_team( iCaster );
	echipa = get_user_team( iTarget );
	new players[32], numberofplayers;
	new targetid;
	new numarjucatori = 0;
	new numarjucatori2 = 0;
	

	get_players( players, numberofplayers, "a" );
	
	for ( new i = 0; i < numberofplayers; i++ )
	{
		targetid = players[i];

		if ( (echipa == get_user_team( targetid )) && is_user_alive( targetid ) )
		{
			numarjucatori = numarjucatori + 1;		
		}
		if ( (echipa2 == get_user_team( targetid )) && is_user_alive( targetid ) )
		{
			numarjucatori2 = numarjucatori2 + 1;		
		}
	}
		if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		if ( echipa == CTS )
		{
			if ( numarjucatori >= 2 && numarjucatori2 <= numarjucatori)
			{cs_set_user_team(iTarget, TEAM_T) ; 
			ChatColor( iTarget,"!g* [!t %s!g ] You are now in !tyour enemy team!g !",g_MODclient);
			}
			
		}
		else if ( echipa == TS )
		{	if ( numarjucatori >= 2 && numarjucatori2 <= numarjucatori)
			{cs_set_user_team(iTarget, TEAM_CT) ;
			ChatColor( iTarget,"!g* [!t %s!g ] You are now in !tyour enemy team!g !",g_MODclient);
			}
		}
	}
	

	Create_ScreenShake( iTarget, (10<<12), (2<<12), (5<<12) );
	Create_ScreenFade( iTarget, (1<<15), (1<<10), (1<<12), 75, 0, 130, 200 );
	SHARED_GlowShell( iTarget, 75, 0, 130, 3.0, 250);
	emit_sound( iTarget, CHAN_STATIC, g_szSounds[SOUND_BLASTO], 1.0, ATTN_NORM, 0, PITCH_NORM );
	emit_sound( iCaster, CHAN_STATIC, g_szSounds[SOUND_BLASTO], 1.0, ATTN_NORM, 0, PITCH_NORM );
	
	

	
	return PLUGIN_HANDLED;
}



public Ethereal_Fire(id) {
	static Victim, iBody, iEndOrigin[3], iBeamOrigin[3];
	get_user_origin(id, iBeamOrigin, 3) ;
	get_user_origin(id, iEndOrigin, 3);
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(TE_BEAMENTPOINT);
	write_short(id | 0x1000);
	write_coord(iBeamOrigin[0]);	// Start X
	write_coord(iBeamOrigin[1]);	// Start Y
	write_coord(iBeamOrigin[2]);	// Start Z
	write_short(g_iSprites[SPR_ETH_TRAIL]);	// Sprite
	write_byte(1);      		// Start frame				
	write_byte(2);     		// Frame rate					
	write_byte(2);			// Life
	write_byte(25);   		// Line width				
	write_byte(0);    		// Noise
	write_byte(0); 			// Red
	write_byte(255);		// Green
	write_byte(0);			// Blue
	write_byte(150);     		// Brightness					
	write_byte(25);      		// Scroll speed					
	message_end();
	
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
	write_byte(3);
	write_coord(iEndOrigin[0]);
	write_coord(iEndOrigin[1]);
	write_coord(iEndOrigin[2]);
	write_short(g_iSprites[SPR_ETH_EXP]);
	write_byte(10);
	write_byte(15);
	write_byte(4);
	message_end();
	
	get_user_aiming(id, Victim, iBody);
	
	new iEnt = create_entity("info_target");
	
	static Float:flOrigin[3];
	IVecFVec(iEndOrigin, flOrigin);
	entity_set_origin(iEnt, flOrigin);
	remove_entity(iEnt);
	if(is_user_connected(Victim)) {
		new Float:aimOrigin2[3];
		aimOrigin2[0] = float(iEndOrigin[0]);
		aimOrigin2[1] = float(iEndOrigin[1]);
		aimOrigin2[2] = float(iEndOrigin[2]);
		
		//make_blood(aimOrigin2, etherealdamage, Victim);
		//make_knockback(Victim, aimOrigin2, etherealknockback*etherealdamag);
		if(pev(Victim, pev_health) > etherealdamage && is_user_alive(Victim) && get_user_team(Victim) != get_user_team(id)) {
			set_pev(Victim, pev_health, pev(Victim, pev_health) - etherealdamage);
			
			message_begin(MSG_ONE_UNRELIABLE, get_user_msgid("Damage"), _, Victim);
			write_byte(0);
			write_byte(0);
			write_long(DMG_NERVEGAS);
			write_coord(0) ;
			write_coord(0);
			write_coord(0);
			message_end();
			
			Create_ScreenFade( Victim, (1<<10), (1<<10), (1<<12), 0, 255, 0, 100 );
			SHARED_GlowShell(Victim, 0, 255, 0, 1.0, 50);
		}
		else if(pev(Victim, pev_health) <= etherealdamage && is_user_alive(Victim) && get_user_team(Victim) != get_user_team(id)) {
			death_message(id, Victim, 1, "Energy");
		}
	}
	else if(is_valid_ent(Victim) && get_user_team(id) != pev(Victim, pev_team)){
		set_pev(Victim, pev_health, pev(Victim, pev_health) - etherealdamage);
		emit_sound(id, CHAN_STATIC, g_szSounds[SOUND_ETH], 1.0, ATTN_NORM, 0, PITCH_NORM );
	}
	
}

stock death_message(Killer, Victim, ScoreBoard, const Weapon[]) {
	// Block death msg
	set_msg_block(get_user_msgid("DeathMsg"), BLOCK_SET);
	ExecuteHamB(Ham_Killed, Victim, Killer, 2);
	set_msg_block(get_user_msgid("DeathMsg"), BLOCK_NOT);
	
	// Death
	make_deathmsg(Killer, Victim, 0, Weapon);
	cs_set_user_money(Killer, cs_get_user_money(Killer) + 300);
	
	// Update score board
	if(ScoreBoard) {
		message_begin(MSG_BROADCAST, get_user_msgid("ScoreInfo"));
		write_byte(Killer); // id
		write_short(pev(Killer, pev_frags)); // frags
		write_short(cs_get_user_deaths(Killer)); // deaths
		write_short(0); // class?
		write_short(get_user_team(Killer)); // team
		message_end();
		
		message_begin(MSG_BROADCAST, get_user_msgid("ScoreInfo"));
		write_byte(Victim); // id
		write_short(pev(Victim, pev_frags)); // frags
		write_short(cs_get_user_deaths(Victim)); // deaths
		write_short(0); // class?
		write_short(get_user_team(Victim)); // team
		message_end();
	}
}