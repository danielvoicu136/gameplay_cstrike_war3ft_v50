#define DRAIN_RANGE 750
#define MAGIC_RANGE 750
#define WK_SEAL_LENGTH 3.0


// Life Drain  
public WK_DrainLife( id )
{
	if ( task_exists( id + TASK_DRAIN ) == 0 )
	{
		_WK_DrainLife( id );
	}
}

// We don't need to ever actually "turn this off" since this task will take care of itself
public _WK_DrainLife( id )
{
	if ( id >= TASK_DRAIN )
	{
		id -= TASK_DRAIN;
	}

	// User is no longer connected
	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}
	
	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( id, SKILL_DRAIN );

	// User doesn't have this skill, so lets return
	//  - Also return if this was called twice
	if ( iSkillLevel <= 0 )
		return;

	// Continue healing...
	if ( is_user_alive( id ) )
	{
		set_task( p_drain[iSkillLevel-1], "_WK_DrainLife", TASK_DRAIN + id );
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
		if ( p_data_b[targetid][PB_ISCONNECTED] && get_user_team( targetid ) != iTeam )
		{
			if ( is_user_alive( targetid ) )
			{
				get_user_origin( targetid, targetorigin );
			
				// User is close enough
				if ( get_distance(origin, targetorigin) < DRAIN_RANGE )
				{
					get_user_origin( targetid, origin )
			
					// User needs health
			if( get_user_health( targetid ) - 2 > 1 )	
		{set_user_health( targetid, get_user_health( targetid ) - 2 );}
			
					
				}
			}
		}
	}

	return;
}

// Magic Essence 
public WK_Magic( id )
{
	if ( !task_exists( id + TASK_MAGIC ) )
	{
		_WK_Magic( id );
	}
}

// We don't need to ever actually "turn this off" since this task will take care of itself
public _WK_Magic( id )
{
	
	if ( id >= TASK_MAGIC )
	{
		id -= TASK_MAGIC;
	}

	// User is no longer connected :
	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}
	
	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( id, SKILL_MAGIC );

	// User doesn't have this skill, so lets return
	//  - Also return if this was called twice
	if ( iSkillLevel <= 0 )
	{
		return;
	}

	// Continue healing...
	if ( is_user_alive( id ) )
	{
		set_task( p_magic[iSkillLevel-1], "_WK_Magic", TASK_MAGIC + id );
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
		if ( p_data_b[targetid][PB_ISCONNECTED] && get_user_team( targetid ) != iTeam )
		{
			get_user_origin( targetid, targetorigin );
			
			// User is close enough
			if ( get_distance(origin, targetorigin) < MAGIC_RANGE )
			{
		message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
		write_byte(TE_BEAMCYLINDER);
		write_coord(targetorigin[0]); // x
		write_coord(targetorigin[1]); // y
		write_coord(targetorigin[2] - 35); // z
		write_coord(targetorigin[0]); // x axis
		write_coord(targetorigin[1]); // y axis
		write_coord(targetorigin[2] + 250); // z axis
		write_short(g_iSprites[SPR_TRAIL]); // sprite
		write_byte(0); // start frame
		write_byte(1); // framerate
		write_byte(6); // life
		write_byte(8); // width
		write_byte(1); // noise
		write_byte(100); // red
		write_byte(100); // green
		write_byte(255); // blue
		write_byte(192); // brightness
		write_byte(0); // speed
		message_end();
		
			}
		}
	}

	return;
}


WK_SkillsOffensive( iAttacker, iVictim )
{

	static iSkillLevel;

	iSkillLevel = SM_GetSkillLevel( iAttacker, PASS_SEAL );

	if ( iSkillLevel > 0 )
	{
		if ( random_float( 0.0, 1.0 ) <= p_seal[iSkillLevel] )
		{
						
			// We need to identify the victim as slowed + hexed			
			//p_data_b[iVictim][PB_FROSTED] = true
			p_data_b[iVictim][PB_SLOWED] = true;
				
			// Slow the user's speed
			SHARED_SetSpeed( iVictim );

			// Set the user's gravity
			SHARED_SetGravity( iVictim );

			// Set the user's rendering
			SHARED_INVIS_Set( iVictim );

			// Create the "remove hex" task
			set_task( WK_SEAL_LENGTH ,"_WK_RemoveSeal", TASK_SEAL + iVictim );

			// Make the user glow!
			SHARED_Glow( iVictim, 137, 137, 137, 250 );

			// Lets create a screen fade
			Create_ScreenFade( iVictim, (1<<15), (1<<10), (1<<12), 137, 137, 137, 250 )
		
		}
	}
		
}


public _WK_RemoveSeal( id )
{
	id -= TASK_SEAL;

	if( !p_data_b[id][PB_ISCONNECTED] )
	{
		return PLUGIN_HANDLED;
	}
	
	p_data_b[id][PB_CAN_RENDER] = true;
	//p_data_b[id][PB_FROSTED]		= false;
	
	if ( is_user_alive( id ) )
	{
		// Reset the user's speed
		SHARED_ResetMaxSpeed( id );

		// Reset the user's gravity
		SHARED_SetGravity( id );

		// Reset the user's rendering
		SHARED_INVIS_Set( id );

	}

	return PLUGIN_HANDLED;
}







public ULT_make_decoy(id)
{
//client_print(id, print_chat, "Making decoy")
//ChatColor( ptd,"!g* [!t %s!g ] Your !tIlusion!g Has Been Created !",g_MODclient);

if ( SM_GetSkillLevel( id, ULTIMATE_ILUSION ) == 1 )
		{ ULT_ResetCooldown( id, 45 ); }	
		else if ( SM_GetSkillLevel( id, ULTIMATE_ILUSION ) == 2 )
		{ ULT_ResetCooldown( id, 35 ); }
		else if ( SM_GetSkillLevel( id, ULTIMATE_ILUSION ) == 3 )
		{ ULT_ResetCooldown( id, 25 ); }
		else if ( SM_GetSkillLevel( id, ULTIMATE_ILUSION ) == 4 )
		{ ULT_ResetCooldown( id, 15 ); }


//Making Decoy start -- Copied from UWC3 Mod
new arg[64]
new Float:arg2[3]
new vec[3]
new aimvec[3]
new Float:b_orig[3]

get_user_origin(id, vec)
get_user_origin(id, aimvec, 2)

//Fix for people spawning decoys on other players to trap them
new sClass[32], target, body

get_user_aiming(id, target, body)

if ((0 < target <= MAX_PLAYERS))
{
entity_get_string(target, EV_SZ_classname, sClass, 32)
if (equal(sClass, "player")){
ChatColor( id,"!g* [!t %s!g ] Your ultimate has been Blocked !",g_MODclient);
return PLUGIN_HANDLED
}
}

b_orig[0] = float(aimvec[0])
b_orig[1] = float(aimvec[1])
b_orig[2] = float(aimvec[2] + 35)

entity_get_string(id, EV_SZ_classname, arg, 63)

new decoyEnt = create_entity("info_target")
entity_set_string(decoyEnt, EV_SZ_classname, "decoy_entity")

entity_set_origin(decoyEnt, b_orig)

entity_set_byte(decoyEnt, EV_BYTE_controller1, 127)

entity_get_vector(id,EV_VEC_absmin,arg2)
entity_set_vector(decoyEnt, EV_VEC_absmin, arg2)
entity_get_vector(id,EV_VEC_absmax,arg2)
entity_set_vector(decoyEnt, EV_VEC_absmax, arg2)
entity_get_vector(id,EV_VEC_mins,arg2)
entity_set_vector(decoyEnt, EV_VEC_mins, arg2)
entity_get_vector(id,EV_VEC_maxs,arg2)
entity_set_vector(decoyEnt, EV_VEC_maxs, arg2)
entity_get_vector(id, EV_VEC_size,arg2)
entity_set_vector(decoyEnt, EV_VEC_size, arg2)


new model[32]
new pmodel[128]

get_user_info(id,"model",model,31)
format(pmodel, 127, "models/player/%s/%s.mdl", model, model)

entity_set_model(decoyEnt, pmodel)

entity_set_float(decoyEnt, EV_FL_health,99999200.0)
entity_set_float(decoyEnt, EV_FL_takedamage, 1.0)
entity_set_float(decoyEnt, EV_FL_dmg_take, 1.0)

entity_set_int(decoyEnt, EV_INT_movetype, 13)
entity_set_int(decoyEnt, EV_INT_solid, 2)
entity_set_int(decoyEnt, EV_INT_spawnflags, 0)
entity_set_int(decoyEnt, EV_INT_sequence, 1)

//Give it a weapon
new weapmodel[256]
entity_get_string(id, EV_SZ_weaponmodel, weapmodel, 255)

new entWeapon = create_entity("info_target")

entity_set_string(entWeapon, EV_SZ_classname, "npc_weapon")

entity_set_int(entWeapon, EV_INT_movetype, MOVETYPE_FOLLOW)
entity_set_int(entWeapon, EV_INT_solid, SOLID_NOT)
entity_set_edict(entWeapon, EV_ENT_aiment, decoyEnt)
entity_set_model(entWeapon, weapmodel)
//------------------


decoy[id] = decoyEnt
decoy_frame[id]=0.0
decoy_seq[id]=0
decoyused[id] = true

//Used to get rid of decoy after ammount of time
new cargs[3]
cargs[0] = id
cargs[1] = decoyEnt
cargs[2] = entWeapon
set_task(10.0, "cleanup_decoy", 866, cargs, 3)

return PLUGIN_CONTINUE
}




public cleanup_decoy(args[])
{

new id = args[0]
new ent = args[1]
new weap = args[2]

//Remove gun entity
remove_entity(weap)

new Float:orig[3]

entity_get_vector(ent, EV_VEC_origin, orig)
message_begin(MSG_BROADCAST,SVC_TEMPENTITY)
write_byte(11)
write_coord(floatround(orig[0]))
write_coord(floatround(orig[1]))
write_coord(floatround(orig[2]))
message_end()

decoy[id] = 0

remove_entity(ent)
//client_print(id, print_chat, "Your decoy has expired")
ChatColor( id,"!g* [!t %s!g ] Your !tIlusion!g Has Vanished !",g_MODclient);
}

public check_duck()
{
for(new i = 1; i <= MAX_PLAYERS; ++i) {
if (is_user_alive(i)) {
if (decoy[i]) {
//client_print(i, print_chat, "MIH2")
if (get_user_button(i)&IN_DUCK) {
if (!pIsDucking[i]) {
//client_print(i, print_chat, "You are now ducking")
pIsDucking[i]=true
DoOnce[i]=true
}
}else{
if (pIsDucking[i]) {
//client_print(i, print_chat, "Stopped ducking")
pIsDucking[i]=false
DoOnce[i]=true
}
}
}

}
}
return PLUGIN_CONTINUE
}


public server_frame()
{
new id
new Float:vel[3]
new Float:speed
new Float:new_frame = get_gametime()
new Float:newAngle[3]
new Float:orig[3]
new Float:framerate = 30.0;
new Float:MinBox[3]
new Float:MaxBox[3]


if ( (new_frame - last_frame) < ( 1.0 / framerate) )
return PLUGIN_CONTINUE

last_frame = new_frame

for( id=0; id<MAX_PLAYERS; id++) {
if ( !decoy[id] || !is_user_connected(id) ) continue

//new Float:health = entity_get_float(decoy[id],EV_FL_health)
//client_print(id, print_chat, "decoy health: %f", health)

if (pIsDucking[id]) {
MinBox[0] = 0.0
MinBox[1] = 0.0
MinBox[2] = -20.0 //change to -40 for standing models
MaxBox[0] = 0.0
MaxBox[1] = 0.0
MaxBox[2] = 0.0
}else{
MinBox[0] = 0.0
MinBox[1] = 0.0
MinBox[2] = -40.0 //change to -20 for crouching models
MaxBox[0] = 0.0
MaxBox[1] = 0.0
MaxBox[2] = 0.0
}

entity_set_vector(decoy[id],EV_VEC_mins, MinBox)

new Float:vRetVector[3]
entity_get_vector(id, EV_VEC_v_angle, vRetVector)
vRetVector[0]=float(0)
entity_set_vector(decoy[id], EV_VEC_angles, vRetVector)

entity_get_vector(decoy[id], EV_VEC_velocity, vel)
//client_print(id,print_chat,"Beyonder velocity <%f %f %f> ", vel[0], vel[1], vel[2])
if( vel[0] != 0.0 && vel[1] != 0.0) {
vel[2] = 0.0
vector_to_angle(vel, newAngle);
//entity_set_vector(decoy[id], EV_VEC_angles, newAngle)
}

vel[2] = 0.0
speed = vector_length(vel)
//client_print(id,print_center,"Beyonder speed = %f ",speed)
if (speed <= 5 && pIsDucking[id]){
if (DoOnce[id]) {
entity_get_vector(decoy[id],EV_VEC_origin,orig)
orig[2]=orig[2] - 20
entity_set_vector(decoy[id],EV_VEC_origin,orig)
DoOnce[id]=false
}

decoy_seq[id] = 2
entity_set_int(decoy[id], EV_INT_sequence, 2)

MinBox[0] = -20.0
MinBox[1] = -20.0
MinBox[2] = -20.0
MaxBox[0] = 20.0
MaxBox[1] = 20.0
MaxBox[2] = 40.0

entity_set_vector(decoy[id],EV_VEC_mins, MinBox)
entity_set_vector(decoy[id],EV_VEC_maxs, MaxBox)

new Float:tmpVec[3]
tmpVec[0] = 40.0; tmpVec[1] = 40.0; tmpVec[2] = 80.0
entity_set_vector(decoy[id],EV_VEC_size,tmpVec)
}else if (speed <= 5 && !pIsDucking[id]){
if (DoOnce[id]) {
entity_get_vector(decoy[id],EV_VEC_origin,orig)
orig[2]=orig[2] + 20
entity_set_vector(decoy[id],EV_VEC_origin,orig)
DoOnce[id]=false
}

decoy_seq[id] = 1
entity_set_int(decoy[id], EV_INT_sequence, 1)

MinBox[0] = -20.0
MinBox[1] = -20.0
MinBox[2] = -40.0
MaxBox[0] = 20.0
MaxBox[1] = 20.0
MaxBox[2] = 40.0

entity_set_vector(decoy[id],EV_VEC_mins, MinBox)
entity_set_vector(decoy[id],EV_VEC_maxs, MaxBox)

new Float:tmpVec[3]
tmpVec[0] = 40.0; tmpVec[1] = 40.0; tmpVec[2] = 80.0
entity_set_vector(decoy[id],EV_VEC_size,tmpVec)
}

decoy_fstep[id] = 5.0
decoy_frame[id] += decoy_fstep[id]

if( decoy_frame[id] >= 254.0 ) decoy_frame[id] = 0.0
entity_set_float(decoy[id], EV_FL_frame, decoy_frame[id])

}

return PLUGIN_CONTINUE

}