#define SKULLBOLT_HOLD_TIME 1.0
#define SKULL_ARROW_SPEED 1000
#define DEATH_SHADOW_DMG 45
#define SKULL_ARROW_TIME 10




DK_SkillsDefensive( iAttacker, iVictim, iDamage, iHitPlace )
{
	static iSkillLevel;


	iSkillLevel = SM_GetSkillLevel( iVictim, SKILL_PACT );
	if ( iSkillLevel > 0 && is_user_alive( iAttacker ) )
	{
		static iAdditionalDamage;
		iAdditionalDamage = floatround( float( iDamage ) * p_pact[iSkillLevel-1] );
		
		// Damage the user
		WC3_Damage( iAttacker, iVictim, iAdditionalDamage, CSW_THORNS, iHitPlace );

		// Make the user glow!
		SHARED_Glow( iAttacker, ( 3 * iAdditionalDamage ), 0, 0, 0 );
		
		// Create a screen fade
		Create_ScreenFade( iAttacker, (1<<10), (1<<10), (1<<12), 255, 0, 0, iAdditionalDamage )
	}
	
		
	
}



DK_SkillsOffensive( iAttacker, iVictim, iDamage)
{
	if ( !p_data_b[iAttacker][PB_ISCONNECTED] )
	{
		return;
	}

	static iSkillLevel;
	
	iSkillLevel = SM_GetSkillLevel( iAttacker, SKILL_POSESION )
	if( iSkillLevel > 0 )
	{
	    if ( random_float( 0.0, 1.0 ) <= p_posesion[iSkillLevel-1] && !SHARED_IsPlayerSlowed( iVictim ) )
		{
		new id ;
		id = iAttacker ;
	    skull_arrow(id);
        }
	
	}
	
	
	iSkillLevel = SM_GetSkillLevel( iAttacker, PASS_CONVERSION );
	if ( iSkillLevel > 0 && p_data_b[iAttacker][PB_ISCONNECTED])
	{
		static iHealth, iMaxHealth, iBonusHealth;

		iHealth		= get_user_health( iAttacker );
		iMaxHealth	= get_user_maxhealth( iAttacker );
		iBonusHealth = floatround( float( iDamage ) * p_conversion[iSkillLevel] );
		
		// Give the user health!
		if ( iHealth < iMaxHealth )
		{

			// Then give the user his maximum health
			if ( iHealth + iBonusHealth > iMaxHealth )
			{
				set_user_health( iAttacker, iMaxHealth );
			}

			// Otherwise just give iMaxHealth
			else
			{
				set_user_health( iAttacker, iHealth + iBonusHealth );
			}
		}
		
		// Make the attacker glow
		SHARED_Glow( iAttacker, 0, ( 3 * iBonusHealth ), 0, 0 );
		
		// Give the attacker a nice screen fade
		Create_ScreenFade( iAttacker, (1<<10), (1<<10), (1<<12), 0, 255, 0, iBonusHealth );
	}
}






public DK_ULT_DEATH_SHADOW( iCaster, iTarget )
{
	emit_sound( iCaster, CHAN_STATIC, g_szSounds[SOUND_IMMOLATE], 0.5, ATTN_NORM, 0, PITCH_NORM );

	
	new parm[5], vOrigin[3];
		get_user_origin(iTarget, vOrigin );

		parm[0] = iTarget;
		parm[1] = 6;
		parm[2] = vOrigin[0];
		parm[3] = vOrigin[1];
		parm[4] = vOrigin[2];

		emit_sound(iCaster, CHAN_STATIC, g_szSounds[SOUND_DEATH_TOUCH], 1.0, ATTN_NORM, 0, PITCH_NORM );
		
		set_task(0.2, "fDrawDeathTouchExplode", TASK_DEATH_TOUCH + iTarget, parm, 5 );
	
	

	Create_ScreenShake( iTarget, (10<<12), (2<<12), (5<<12) );

		if (ITEM_Has(iCaster, ITEM_SCEPTER ) > ITEM_NONE)
		{WC3_Damage( iTarget, iCaster, 2*DEATH_SHADOW_DMG, CSW_IMMOLATE, -1 );}
		else {WC3_Damage( iTarget, iCaster, DEATH_SHADOW_DMG, CSW_IMMOLATE, -1 );}

	Create_ScreenFade( iTarget, (1<<10), (1<<10), (1<<12), 137, 137, 137, 250 )


	
	
	return PLUGIN_HANDLED;
}





//========================================================================================================================



// Skull Arrow 
new skull_arrowtimer[33];

public skull_arrow(id)
{
	//makes sure that the number of entities created does not exceed the maximum amount
    //of entities allowed
    if(entity_count() == get_global_int(GL_maxEntities)){
	client_print(id, print_chat, "[WAR3FT] Cannot create more entities")
	return
    } 

    //Makes an array of origin in the (x,y,z) coordinate system.
    new origin[3]

    //Makes an array of velocity, specifically in the (x,y,z) coordinate system 
    new velocity[3] 

    new Float:fOrigin[3], Float:fVelocity[3]
    get_user_origin(id, origin, 1)
    new Float: minBound[3] = {-50.0, -50.0, 0.0}  //sets the minimum bound of entity
    new Float: maxBound[3] = {50.0, 50.0, 0.0}    //sets the maximum bound of entity
    IVecFVec(origin, fOrigin)

    //This will make it so that the disk appears in front of the user
    new Float:viewing_angles[3]
    new distance_from_user = 70
    entity_get_vector(id, EV_VEC_angles, viewing_angles)
    fOrigin[0] += floatcos(viewing_angles[1], degrees) * distance_from_user
    fOrigin[1] += floatsin(viewing_angles[1], degrees) * distance_from_user
    fOrigin[2] += floatsin(-viewing_angles[0], degrees) * distance_from_user

    new NewEnt = create_entity("info_target")  //Makes an object 
    entity_set_string(NewEnt, EV_SZ_classname, "skull_arrow") //sets the classname of the entity

    engfunc(EngFunc_SetModel, NewEnt, "models/warcraft3/bskull_template1.mdl")

    //This will set the origin of the entity 
    entity_set_origin(NewEnt, fOrigin) 

    //This will set the movetype of the entity 
    entity_set_int(NewEnt,EV_INT_movetype, MOVETYPE_NOCLIP) 


    //This makes the entity touchable
    entity_set_int(NewEnt, EV_INT_solid, SOLID_TRIGGER)
	entity_set_float(NewEnt,EV_FL_scale,0.5)
	entity_set_int( NewEnt, EV_INT_renderfx, kRenderFxNone );
	entity_set_int( NewEnt, EV_INT_rendermode, kRenderTransAdd );
	entity_set_float( NewEnt, EV_FL_renderamt, 255.0 );

    //This will set the velocity of the entity 
    velocity_by_aim(id, SKULL_ARROW_SPEED, fVelocity) 
    FVecIVec(fVelocity, velocity) //converts a floating vector to an integer vector

    //Sets the size of the entity
    entity_set_size(NewEnt, minBound, maxBound)

    //Sets who the owner of the entity is
    entity_set_edict(NewEnt, EV_ENT_owner, id)

    //This will set the entity in motion 
    entity_set_vector(NewEnt, EV_VEC_velocity, fVelocity) 

    new lifetime = SKULL_ARROW_TIME
	
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY)
    write_byte(22)       //TE_BEAMFOLLOW
    write_short(NewEnt)  //The entity to attach the sprite to
    write_short(g_iSprites[SPR_TRAIL])  //sprite's model
    write_byte(lifetime)   //life in 0.1 seconds
    write_byte(10)   //width of sprite
    write_byte(0)  //red
    write_byte(255)    //green
    write_byte(0)  //blue
    write_byte(255)  //brightness
    message_end()

    return
}
	

public touch_skull_arrow(pToucher, pTouched)  //This is triggered when two entites touch
{ 
    new aimvec[3], Float:fAimvec[3]  //This is the position where the disk collides 
    entity_get_vector(pTouched, EV_VEC_origin, fAimvec) 
    FVecIVec(fAimvec, aimvec) 
    new self_immune = SKULL_ARROW_TIME - 2 //Gives split-second immunity

    if(pTouched == entity_get_edict(pToucher, EV_ENT_owner) && skull_arrowtimer[pTouched] > self_immune)
	return PLUGIN_HANDLED
    //Checks to see if entity is a player or an inanimate object. 
    if(is_user_connected(pTouched))
	{
	skullarrow_effects(pToucher, pTouched, aimvec)
	return PLUGIN_CONTINUE
    }

    skullarrow_effects(pToucher, 0, aimvec)

    return PLUGIN_CONTINUE 
} 
 

public skullarrow_effects(pToucher, pTouched, aimvec[3]) //effects for when disk touch
{
	new Float:fVelocity[3]
	new velocity[3]
	entity_get_vector(pToucher, EV_VEC_velocity, fVelocity)
	FVecIVec(fVelocity, velocity)

	new killer = entity_get_edict(pToucher, EV_ENT_owner)

	if(is_user_alive(pTouched))
	{

		new victim = pTouched
		
		if(cs_get_user_team(victim) != cs_get_user_team(killer))
		{
		
	        p_data_b[victim][PB_STUNNED] = true;
			SHARED_SetSpeed( victim );	
			set_task( SKULLBOLT_HOLD_TIME, "SHARED_ResetMaxSpeed", TASK_RESETSPEED + victim );
			// Make the user glow!
			SHARED_GlowShell(victim, 0, 255, 0, 1.0, 30); 
					
		if(find_ent_by_owner(-1,"skull_arrow",killer)!=0)
		remove_entity(find_ent_by_owner(-1,"skull_arrow",killer))					
		}
		
	}

}	


// Draw the death touch
public fDrawDeathTouchExplode( parm[5] )
{

	new vOrigin[3], vPosition[3];
	vOrigin[0] = parm[2];
	vOrigin[1] = parm[3];
	vOrigin[2] = parm[4];

	vPosition[0] = vOrigin[0] + random_num( -100, 100 );
	vPosition[1] = vOrigin[1] + random_num( -100, 100 );
	vPosition[2] = vOrigin[2] + random_num( -50, 50 );

	Create_TE_EXPLOSION(  vOrigin, vPosition, g_iSprites[SPR_DEATH_TOUCH], (random_num(0,20) + 20), 12, 4 );
	Create_TE_Smoke( vOrigin, vPosition, g_iSprites[SPR_SMOKE], 60, 10 );
		
}


//=================================================================================


public respawn_menu(id) {
    //if (g_F_counter[id] < 1) {
        new title_msg[100];
        formatex(title_msg, charsmax(title_msg), "\rRaise Deads Menu")
        new menu = menu_create(title_msg, "menu_res")
        new players[32], pnum, tempid;
        new szName[32], szTempid[10];
        get_players(players, pnum);

        for (new i; i < pnum; i++) {
            tempid = players[i]

			/*
            if (is_user_alive(tempid)) {
                WC3_StatusText(id, 0, "All Team is Alive !");
            }
			*/

            if (!is_user_alive(tempid) && is_user_alive(id)) {
                get_user_name(tempid, szName, 31)
                num_to_str(tempid, szTempid, 9)
                if (get_user_team(id) == get_user_team(tempid)) {
                    menu_additem(menu, szName, szTempid, 0)
                   
                }
            }
        }

        menu_display(id, menu, 0)

    //}

    return PLUGIN_HANDLED

}

public menu_res(idUser, menu, item) {
    if (item == MENU_EXIT) {
        menu_destroy(menu)
        return PLUGIN_HANDLED
    }

    new data[6], iName[64], playername[33], playername2[33]
    new access, callback
    menu_item_getinfo(menu, item, access, data, 5, iName, 63, callback)

    new tempid = str_to_num(data)
    cs_get_user_team(tempid)

    get_user_name(idUser, playername, 32)
    get_user_name(tempid, playername2, 32)

    
            ExecuteHam(Ham_CS_RoundRespawn, tempid);

	 ChatColor( idUser,"!g* [!t %s!g ] You Resurrect!t %s",g_MODclient,playername2);
	 ChatColor( tempid,"!g* [!t %s!g ] You was Resurrected by !t %s",g_MODclient,playername);
    

    menu_destroy(menu)
    return PLUGIN_HANDLED
}
