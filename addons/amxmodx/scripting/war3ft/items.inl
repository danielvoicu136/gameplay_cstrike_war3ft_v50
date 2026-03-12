/*
*	Item Functions
*/

// Item Setup Functions
ITEM_Init()
{
	ITEM_COST[ITEM_ANKH]	    = 2000;			// Ankh of Reincarnation
	ITEM_COST[ITEM_BOOTS]       = 3000;			// Boots of Speed
	ITEM_COST[ITEM_CLAWS]	    = 1500;			// Claws of Attack
	ITEM_COST[ITEM_CLOAK]	    = 1500;			// Cloak of Shadows
	ITEM_COST[ITEM_MASK]	    = 3000;			// Mask of Death
	ITEM_COST[ITEM_NECKLACE]	= 1000;			// Necklace of Immunity
	ITEM_COST[ITEM_FROST]	    = 2500;			// Orb of Frost
	ITEM_COST[ITEM_HEALTH]	    = 1500;			// Periapt of Health
	ITEM_COST[ITEM_TOME]	    = 7000;			// Tome of Experience
	ITEM_COST[ITEM_SCROLL]	    = 10000;			// Scroll of Respawning
	ITEM_COST[ITEM_PROTECTANT]	= 1500;			// Mole Protectant
	ITEM_COST[ITEM_HELM]	    = 3500;			// Helm of Excellence
	ITEM_COST[ITEM_AMULET]	    = 2000;			// Amulet of the Cat
	ITEM_COST[ITEM_SOCK]	    = 1500;			// Sock of the Feather
	ITEM_COST[ITEM_GLOVES]	    = 2500;			// Flaming Gloves of Warmth
	ITEM_COST[ITEM_RING]	    = 500;			// Ring of Regeneration + 1
	ITEM_COST[ITEM_CHAMELEON]	= 5000;			// Chameleon
	ITEM_COST[ITEM_MOLE]	    = 16000;		        // Mole
	
	ITEM_COST[ITEM_FROSTARMOR]	    = 3500;			// Frost Armor
	ITEM_COST[ITEM_GRENADE]       = 2500;			// Grenade Protection 
	ITEM_COST[ITEM_MIRROR]	    = 3500;			// Mirror Shield 
	ITEM_COST[ITEM_ACCELERATOR]	    = 2000;			// Ultimate Accelerator
	ITEM_COST[ITEM_DEATH]	    = 16000;			// Death Touch
	ITEM_COST[ITEM_POTION]	= 6000;			// Healing Potion 
	ITEM_COST[ITEM_SCEPTER]	    = 4500;			// Scepter 
	ITEM_COST[ITEM_SCANNER]	    = 2500;			// Scanner 
	ITEM_COST[ITEM_STEEL]	    = 2500;			// Steel Skin
	
	ITEM_COST[ITEM_ASSASIN]	    = 3500;			// Assasin Aura
	ITEM_COST[ITEM_SNAKE]       = 1500;			// Snake Eater 
	ITEM_COST[ITEM_PORTAL]	    = 1500;			// Town Portal 
	ITEM_COST[ITEM_OMNISCIENCE]	    = 2000;			// Omniscience
	ITEM_COST[ITEM_INFINITY]	    = 4500;			// Infinity
	ITEM_COST[ITEM_FLAME]	= 7000;			// Flame Thrower
	ITEM_COST[ITEM_SKULL]	    = 3500;			// Skull Colector 
	ITEM_COST[ITEM_BOOK]	    = 10000;			// Death Book
	ITEM_COST[ITEM_SPIKES]	    = 3000;			// Spikes Skin 
	

	// Item costs are a little different for DOD
	if ( g_MOD == GAME_DOD )
	{
		ITEM_COST[ITEM_SCROLL]	= 800;
	}

	// Items are chargeable
	g_iFlag[ITEM_NECKLACE]	|= ITEM_CHARGEABLE;
	g_iFlag[ITEM_HELM]		|= ITEM_CHARGEABLE;
	g_iFlag[ITEM_RING]		|= ITEM_CHARGEABLE;
	g_iFlag[ITEM_DEATH]		|= ITEM_CHARGEABLE;

	// Items should be used when bought
	g_iFlag[ITEM_TOME]		|= ITEM_USEONBUY;
	g_iFlag[ITEM_ACCELERATOR]		|= ITEM_USEONBUY;
	g_iFlag[ITEM_POTION]		|= ITEM_USEONBUY;
	g_iFlag[ITEM_STEEL]		|= ITEM_USEONBUY;
	g_iFlag[ITEM_PORTAL]		|= ITEM_USEONBUY;
	g_iFlag[ITEM_BOOK]		|= ITEM_USEONBUY;
	
	
	

	// Items CAN be bought when dead
	g_iFlag[ITEM_ANKH]		|= ITEM_BUYWHENDEAD;
	g_iFlag[ITEM_SCROLL]	|= ITEM_BUYWHENDEAD;
	g_iFlag[ITEM_MOLE]		|= ITEM_BUYWHENDEAD;
	g_iFlag[ITEM_TOME]		|= ITEM_BUYWHENDEAD;

	// Items are used when the next round starts...
	g_iFlag[ITEM_ANKH]		|= ITEM_NEXTROUNDUSE;
	g_iFlag[ITEM_MOLE]		|= ITEM_NEXTROUNDUSE;
}

// We created this to allow for different prices of items at different levels
ITEM_Cost( id, iItem )
{
	// How much should ratio increase per level?
	new Float:fInc = ( 1.0 - ITEM_COST_RATIO ) / float( MAX_LEVELS );

	// Cost * ratio (ITEM_COST_RATIO to 1.0 dependent on level)
	new Float:fRatio = (float( p_data[id][P_LEVEL] ) * fInc) + ITEM_COST_RATIO;

	return ( p_data[id][P_RACE] != RACE_NONE ) ? floatround( float( ITEM_COST[iItem] ) * fRatio ) : ITEM_COST[iItem];
}


public ITEM_CanBuy( id, iItem )
{
	// User doesn't have the money
	if ( SHARED_GetUserMoney( id ) < ITEM_Cost( id, iItem ) )
	{
		client_print( id, print_center, "%L", id, "INSUFFICIENT_FUNDS" );

		return false;
	}
	
	// User already owns the item and it's not a chargeable item!
	else if ( ITEM_Has( id, iItem ) > ITEM_NONE && !ITEM_CheckFlag( iItem, ITEM_CHARGEABLE ) )
	{
		client_print( id, print_center, "%L", id, "ALREADY_OWN_THAT_ITEM" );

		return false;
	}
	
	// Make sure these items can be bought if the user is dead
	else if ( !is_user_alive( id ) && !ITEM_CheckFlag( iItem, ITEM_BUYWHENDEAD ) ) 
	{
		client_print( id, print_center, "%L", id, "NOT_PURCHASE_WHEN_DEAD" );

		return false;
	}
	
	// User has necklace + blink, they don't need a necklace
	else if ( iItem == ITEM_NECKLACE && p_data_b[id][PB_WARDENBLINK] )
	{
		client_print( id, print_center, "You are already immune to ultimates through one of your skills!" );

		return false;
	}

	// User doesn't need an ankh if they're going to reincarnate
	else if ( iItem == ITEM_ANKH && SM_GetSkillLevel( id, SKILL_REINCARNATION ) == 7 && !p_data[id][P_CHANGERACE] )
	{
		client_print( id, print_center, "You will already reincarnate your weapons through one of your skills!" );

		return false;
	}
	
	// User has purchased the maximum allowed rings
	else if ( g_iTotalRings[id] >= 5 && iItem == ITEM_RING )
	{
		client_print( id, print_center, "%L", id, "NOT_PURCHASE_MORE_THAN_FIVE_RINGS" );

		return false;
	}

	// User has purchased gloves when they're disabled on this map
	else if ( iItem == ITEM_GLOVES && g_bGlovesDisabled )
	{
		ChatColor( id,"!g*[!t %s!g ] Gloves are disabled on this map !",g_MODclient );

		return false;
	}

	// User is already going to reincarnate weapons because they bought an ankh earlier (probably lost it when died)
	else if ( ( iItem == ITEM_ANKH && g_bPlayerBoughtAnkh[id] ) || ( iItem == ITEM_MOLE && g_bPlayerBoughtMole[id] ) )
	{
		client_print( id, print_center, "%L", id, "ALREADY_OWN_THAT_ITEM" );

		return false;
	}

	return true;
}

public ITEM_Buy( id, iItem )
{

	
	// If the user can buy this item...
	if ( ITEM_CanBuy( id, iItem ) )
	{

		// User's items are full
		if ( ITEM_GetSlot( id ) == ITEM_SLOT_FULL && !ITEM_CheckFlag( iItem, ITEM_USEONBUY ) )
		{

			// We only care about items being full if this item isn't a use on buy
			if ( !ITEM_CheckFlag( iItem, ITEM_USEONBUY ) )
			{

				new bool:bShowReplaceMenu = false;

				// One time use...
				if ( !ITEM_CheckFlag( iItem, ITEM_CHARGEABLE ) )
				{
					//client_print( id, print_chat, "[DEBUG] Item is not chargeable" );

					bShowReplaceMenu = true;
				}

				// We also need to replace it if the item is chargeable but they don't own that item
				if ( ITEM_Has( id, iItem ) == ITEM_NONE && ITEM_CheckFlag( iItem, ITEM_CHARGEABLE ) )
				{
					//client_print( id, print_chat, "[DEBUG] Doesn't have item and new item is chargeable" );

					bShowReplaceMenu = true;
				}

				if ( bShowReplaceMenu )
				{
					g_iFutureItem[id] = iItem;

					MENU_ReplaceItem( id );

					return;
				}
			}
		}
	
		// We're clear!

		// Remove user's money
		new iNewMoney = SHARED_GetUserMoney( id ) - ITEM_Cost( id, iItem );
		SHARED_SetUserMoney( id, iNewMoney );

		ITEM_GiveItem( id, iItem );
	}

	return;
}

// Item Buy Functions
bool:ITEM_MenuCanBuyCheck( id )
{
	// Duh how can they buy if they're dead!
	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return false;
	}

	new isPlayerAlive		= is_user_alive( id );

	if ( !get_pcvar_num( CVAR_wc3_buy_dead ) && !isPlayerAlive )
	{
		client_print( id, print_center, "%L", id, "NOT_BUY_ITEMS_WHEN_DEAD" );
		
		return false;
	}
	
	else if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		new isPlayerInBuyZone	= cs_get_user_buyzone( id )
		
		if ( get_pcvar_num( CVAR_wc3_buy_time ) && !g_buyTime )
		{
			client_print( id, print_center, "%L", id, "SECONDS_HAVE_PASSED_CANT_BUY", ( get_cvar_float( "mp_buytime" ) * 60.0 ) );

			return false;
		}
		
		else if ( get_pcvar_num( CVAR_wc3_buy_zone ) && !isPlayerInBuyZone && isPlayerAlive )
		{
			client_print( id, print_center, "%L", id, "MUST_BE_IN_BUYZONE" );
			
			return false;
		}
	}
	
	return true;
}

// Item Preset Function
ITEM_GiveItem( id, iItem )
{

	// This item we should use instantly
	if ( ITEM_CheckFlag( iItem, ITEM_USEONBUY ) )
	{
		if ( iItem == ITEM_TOME )
		{
			ITEM_Tome( id );

			return;
		}
		
		if ( iItem == ITEM_ACCELERATOR )
		{
			ITEM_Accelerator( id );

			return;
		}
		
		if ( iItem == ITEM_POTION )
		{
			ITEM_Potion( id );

			return;
		}
		if ( iItem == ITEM_STEEL )
		{
			ITEM_Steel( id );

			return;
		}
		if ( iItem == ITEM_PORTAL )
		{
			ITEM_Portal( id );

			return;
		}
		if ( iItem == ITEM_BOOK )
		{
			ITEM_Book( id );

			return;
		}
	}

	// They are just adding some charges
	else
	{
		// Actually set our item variable
		if ( is_user_alive( id ) )
		{
			ITEM_Equip( id, iItem );
		}

		// Display message to the user regarding the item they just purchased
		ITEM_DisplayMessage( id, iItem );

		// Give bonuses
		ITEM_GiveBonuses( id, iItem );

		// Play purchase sound
		emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_PICKUPITEM], 1.0, ATTN_NORM, 0, PITCH_NORM );
	}

	WC3_ShowBar( id );

	return;
}

ITEM_DisplayMessage( id, iItem )
{
	// Display a message regarding the item they just purchased
	switch ( iItem )
	{
		case ITEM_ANKH:
		{
			(g_MOD == GAME_DOD)								? client_print( id, print_chat,"%s %L", g_MODclient, id, "DOD_INFO_SHOPMENU_1" ) : 0;
			(g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO)	? ChatColor( id,"!g* [!t %s!g ] You will reincarnate all of your weapons next round ", g_MODclient) : 0;
		}

		case ITEM_BOOTS:
		{
			if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
			{
				ChatColor( id,"!g* [!t %s!g ] You will now run!t %0.0f%% !gfaster with each weapon", g_MODclient,( ( get_pcvar_float( CVAR_wc3_boots ) ) * 100.00 ) );
			}

			else if ( g_MOD == GAME_DOD )
			{
				client_print( id, print_chat,"%s %L", g_MODclient, id, "DOD_INFO_SHOPMENU_2" );
			}
		}

		case ITEM_CLAWS:
		{
			ChatColor( id,"!g* [!t %s!g ] Each attack will now do an additional!t %d !gdamage", g_MODclient, get_pcvar_num( CVAR_wc3_claw ) );
		}

		case ITEM_CLOAK:
		{
			new Float:fInvis = 100.0 * ( float( get_pcvar_num( CVAR_wc3_cloak ) ) / 255.0 );
			
			ChatColor(id,"!g* [!t %s!g ] You are now!t %0.0f%% !g less visible",g_MODclient,fInvis);
		}

		case ITEM_MASK:
		{
			new Float:fMask = ( 100.0 * get_pcvar_float( CVAR_wc3_mask ) );
			ChatColor(id,"!g* [!t %s!g ] You will now gain!t %0.0f%% !gof the damage done to enemies back as!t health", g_MODclient, fMask );
		}

		case ITEM_NECKLACE:
		{	if((get_user_flags(id) & ADMIN_LEVEL_H)) 
			{ ChatColor( id,"!g* [!t %s!g ] You have been given!t %d !gcharges, each charge will block an enemy ultimate", g_MODclientVIP,NECKLACE_CHARGES_VIP ); }
			else ChatColor( id,"!g* [!t %s!g ] You have been given!t %d !gcharges, each charge will block an enemy ultimate", g_MODclient,NECKLACE_CHARGES );
		}

		case ITEM_FROST:
		{
			new Float:fFrost = 100.0 * ( get_pcvar_float( CVAR_wc3_frost ) / 260.0 );
			ChatColor(id,"!g* [!t %s!g ] You will now slow enemies by!t %0.0f%% !gwith each successful hit", g_MODclient, fFrost );
		}

		case ITEM_HEALTH:
		{
			ChatColor(id,"!g* [!t %s!g ] You will be given an additional!t %d health", g_MODclient, get_pcvar_num( CVAR_wc3_health ) );
		}

		case ITEM_SCROLL:
		{
			if ( is_user_alive( id ) )
			{
				ChatColor( id,"!g* [!t %s!g ] If the round has not ended, you will respawn after you die", g_MODclient );
			}

			else
			{
				ChatColor( id,"!g* [!t %s!g ] You will now be respawned", g_MODclient );
			}
		}

		case ITEM_PROTECTANT:
		{
			ChatColor( id,"!g* [!t %s!g ] You will now be partially immune to moles", g_MODclient );
		}

		case ITEM_HELM:
		{	if((get_user_flags(id) & ADMIN_LEVEL_H)) 
			{ChatColor( id,"!g* [!t %s!g ] You have been given!t %d !gcharges, each charge will block a headshot", g_MODclientVIP, HELM_CHARGES_VIP );}
			else ChatColor( id,"!g* [!t %s!g ] You have been given!t %d !gcharges, each charge will block a headshot", g_MODclient, HELM_CHARGES );
		}

		case ITEM_AMULET:
		{
			ChatColor( id,"!g* [!t %s!g ] You will now be silent while walking and running", g_MODclient );
		}

		case ITEM_SOCK:
		{
			ChatColor( id,"!g* [!t %s!g ] You will now be able to jump higher", g_MODclient );
		}

		case ITEM_GLOVES:
		{
			ChatColor( id,"!g* [!t %s!g ] You will now be given a grenade once every!t %d!g seconds", g_MODclient, get_pcvar_num( CVAR_wc3_glove_timer ) );
		}

		case ITEM_RING:
		{
			ChatColor( id,"!g* [!t %s!g ] You will now regenerate!t 1 HP!g every!t 2 seconds !g(you may purchase up to 5 rings)", g_MODclient );
		}

		case ITEM_CHAMELEON:
		{
			ChatColor( id,"!g* [!t %s!g ] You now look like the enemy", g_MODclient );
		}

		case ITEM_MOLE:
		{
			ChatColor( id,"!g* [!t %s!g ] You will be disguised as your enemy and appear at the enemy's spawn next round", g_MODclient );
		}
		
			case ITEM_FROSTARMOR:
		{
			ChatColor( id,"!g* [!t %s!g ] You will damage your attacker with!t 3 HP!g and!t 2 AR!g every time he hit you", g_MODclient );
		}
		
			case ITEM_GRENADE:
		{
			ChatColor( id,"!g* [!t %s!g ] You will be immune to!t explosion grenades", g_MODclient );
		}
			case ITEM_MIRROR:
		{
			ChatColor( id,"!g* [!t %s!g ] You will reflect a part of the damage done to you", g_MODclient );
		}
			case ITEM_ACCELERATOR:
		{
			ChatColor( id,"!g* [!t %s!g ] You will be able to use your!t ultimate immediately", g_MODclient );
		}
			case ITEM_DEATH:
		{
			ChatColor( id,"!g* [!t %s!g ] You will kill with!t one shot ", g_MODclient );
		}
		/*
		case ITEM_POTION:
		{
			ChatColor( id,"!g* [!t %s!g ] Your health will be!t full", g_MODclient );
		}
		*/
		case ITEM_SCEPTER:
		{
			ChatColor( id,"!g* [!t %s!g ] Your ultimate will be!t 2 times!g more!t efficient", g_MODclient );
		}
		
			case ITEM_SCANNER:
		{
			ChatColor( id,"!g* [!t %s!g ] You will be able to see all!t invisible enemys", g_MODclient );
		}
		
/*		case ITEM_STEEL:
		{
			ChatColor( id,"!g* [!t %s!g ] You will gain a!t armor bonus", g_MODclient );
		}
		*/
		
				case ITEM_ASSASIN:
		{
			ChatColor( id,"!g* [!t %s!g ] You will gain!t + 50 $!g on each successful hit", g_MODclient );
		}
		
			case ITEM_SNAKE:
		{
			ChatColor( id,"!g* [!t %s!g ] You will be immune to!t serpent wards", g_MODclient );
		}
		/*
			case ITEM_PORTAL:
		{
			ChatColor( id,"!g* [!t %s!g ] You will be teleport back in base", g_MODclient );
		}
		*/
			case ITEM_OMNISCIENCE:
		{
			ChatColor( id,"!g* [!t %s!g ] You will be able to see how much!t damage!g you done", g_MODclient );
		}
			case ITEM_INFINITY:
		{
			ChatColor( id,"!g* [!t %s!g ] You will have!t infinite!g bullets", g_MODclient );
		}
		
		case ITEM_FLAME:
		{
			ChatColor( id,"!g* [!t %s!g ] You will!t burn!g all nearby enemys", g_MODclient );
		}
		
		case ITEM_SKULL:
		{
			ChatColor( id,"!g* [!t %s!g ] You will gain!t + 35 HP!g on each headshot kill and magic kill", g_MODclient );
		}
		
		/*
			case ITEM_BOOK:
		{
			ChatColor( id,"!g* [!t %s!g ] You will be able to revive a dead teammate", g_MODclient );
		}
		*/
		
		case ITEM_SPIKES:
		{
			ChatColor( id,"!g* [!t %s!g ] You will be able to!t walk!g on walls", g_MODclient );
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
}

// Give the user bonuses for their items (except charges)
ITEM_GiveAllBonuses( id )
{

	// Loop through all item slots
	for ( new i = ITEM_SLOT_ONE; i <= ITEM_SLOT_THREE; i++ )
	{
		
		// Do we have a valid item here?
		if ( g_iShopMenuItems[id][i] != ITEM_NONE )
		{

			// Don't want to give the user more charges for free do we?
			//  And we don't want to give the bonuses if this is a next round use item (i.e. if we do then mole for infinity - that doesn't seem nice)
			if ( !ITEM_CheckFlag( g_iShopMenuItems[id][i], ITEM_CHARGEABLE ) && !ITEM_CheckFlag( g_iShopMenuItems[id][i], ITEM_NEXTROUNDUSE ) )
			{
				ITEM_GiveBonuses( id, g_iShopMenuItems[id][i] );
			}
		}
	}
}

// Give our players their bonus!
ITEM_GiveBonuses( id, iItem )
{
	
	// Display a message regarding the item they just purchased
	switch ( iItem )
	{
		case ITEM_ANKH:
		{
			g_bPlayerBoughtAnkh[id] = true;
		}

		case ITEM_BOOTS:
		{
			SHARED_SetSpeed( id );
		}

		case ITEM_CLOAK:
		{
			SHARED_INVIS_Set( id );
		}

		case ITEM_NECKLACE:
		{
			
			if((get_user_flags(id) & ADMIN_LEVEL_H)) 
    g_iNecklaceCharges[id] += NECKLACE_CHARGES_VIP; 
 else
    g_iNecklaceCharges[id] += NECKLACE_CHARGES;
		}

		case ITEM_HEALTH:
		{
			new iHealth = get_pcvar_num( CVAR_wc3_health );
			iHealth += get_user_health( id );
			set_user_health( id, iHealth );
		}

		case ITEM_SCROLL:
		{
			if ( !is_user_alive( id ) )
			{
				ITEM_Scroll( id );
			}
		}

		case ITEM_HELM:
		{
			if((get_user_flags(id) & ADMIN_LEVEL_H)) 
    g_iHelmCharges[id] += HELM_CHARGES_VIP; 
 else
    g_iHelmCharges[id] += HELM_CHARGES;
		}

		case ITEM_SOCK:
		{
			SHARED_SetGravity( id );
		}

		case ITEM_GLOVES:
		{
			ITEM_Gloves( id );
		}

		case ITEM_RING:
		{
			g_iTotalRings[id] += RING_INCREMENT;

			if ( !task_exists( TASK_ITEM_RING + id ) )
			{
				_ITEM_Ring( id );
			}
		}

		case ITEM_CHAMELEON:
		{
			SHARED_ChangeSkin( id, SKIN_SWITCH );
		}

		case ITEM_MOLE:
		{
			g_bPlayerBoughtMole[id] = true;
		}
		case ITEM_DEATH:
		{
			arrDeathTouch[id] = true;
			
		}
		case ITEM_SCANNER:
		{
			fEnableItemESP(id);
		}
	}
}

// Item Equip Function
ITEM_Equip( id, iItem )
{
	new iItemSlot = ITEM_GetSlot( id );

	// Items are not full
	if ( iItemSlot != ITEM_SLOT_FULL )
	{

		new iOldItem = g_iShopMenuItems[id][iItemSlot];

		if ( iItem == iOldItem || ITEM_Has( id, iItem ) > ITEM_NONE )
		{
			// Might hit this if we added charges - we want to update the user's HUD
			WC3_ShowBar( id );

			return;
		}

		// Remove the user's old item if necessary
		else if ( g_iShopMenuItems[id][iItemSlot] > ITEM_NONE )
		{
			ITEM_Remove( id, iItemSlot );
		}
			
		// Set their new item
		g_iShopMenuItems[id][iItemSlot] = iItem;
	}

	WC3_ShowBar( id );

	return;
}

// Item Remove Functions
ITEM_RemoveID( id, iItem )
{
	new iItemSlot = ITEM_Has( id, iItem );

	if ( iItemSlot > ITEM_NONE )
	{
		ITEM_Remove( id, iItemSlot );
	}

	return;
}

ITEM_Remove( id, iItemSlot, bResetAnkhMole = true )
{
	new iItem = g_iShopMenuItems[id][iItemSlot];

	g_iShopMenuItems[id][iItemSlot] = ITEM_NONE;

	switch( iItem )
	{
		case ITEM_ANKH:
		{
			if ( bResetAnkhMole )
			{
				g_bPlayerBoughtAnkh[id] = false;
			}
		}

		case ITEM_BOOTS:
		{
			SHARED_SetSpeed( id );
		}

		case ITEM_CLOAK:
		{
			SHARED_INVIS_Set( id );
		}

		case ITEM_NECKLACE:
		{
			g_iNecklaceCharges[id] = 0;
		}

		case ITEM_HEALTH:
		{
			new iNewHealth = get_user_health( id ) - get_pcvar_num( CVAR_wc3_health );
			
			// Lets not kill the user, give them 1 health
			iNewHealth = ( ( iNewHealth <= 0 ) ? 1 : iNewHealth );

			set_user_health( id, iNewHealth );
		}

		case ITEM_HELM:
		{
			g_iHelmCharges[id] = 0;
		}
		
		case ITEM_SOCK:
		{
			SHARED_SetGravity( id );
		}

		case ITEM_GLOVES:
		{
			if ( task_exists( TASK_ITEM_GLOVES + id ) )
			{
				remove_task( TASK_ITEM_GLOVES + id );
			}
		}

		case ITEM_RING:
		{
			if ( task_exists( TASK_ITEM_RING + id ) )
			{
				remove_task( TASK_ITEM_RING + id );
			}
			
			// Set the number of rings to 0
			g_iTotalRings[id] = 0;
		}

		case ITEM_CHAMELEON:
		{
			SHARED_ChangeSkin( id, SKIN_RESET );
		}

		case ITEM_MOLE:
		{
			if ( bResetAnkhMole )
			{
				g_bPlayerBoughtMole[id] = false;
			}
		}
		case ITEM_DEATH:
		{
			arrDeathTouch[id] = false;
			
		}
		case ITEM_SCANNER:
		{
			fDisableItemESP(id);
		}
	}

	WC3_ShowBar( id );

	return;
}

ITEM_RemoveCharge( id, iItem )
{
	if ( ITEM_Has( id, iItem ) > ITEM_NONE )
	{
		switch ( iItem )
		{
			case ITEM_NECKLACE:
			{
				g_iNecklaceCharges[id] -= CHARGE_DISPOSE;
				
				if ( g_iNecklaceCharges[id] <= 0 )
				{
					ITEM_RemoveID( id, iItem );
				}
			}

			case ITEM_HELM:
			{
				g_iHelmCharges[id] -= CHARGE_DISPOSE;
				
				if ( g_iHelmCharges[id] <= 0 )
				{
					ITEM_RemoveID( id, iItem );
				}
			}

			case ITEM_RING:
			{
				g_iTotalRings[id] -= CHARGE_DISPOSE;
				
				if ( g_iTotalRings[id] <= 0 )
				{
					ITEM_RemoveID( id, iItem );
				}
			}
		}
	}

	WC3_ShowBar( id );
	return;
}

// Item Get Functions 
 ITEM_GetSlot( id ) 
 { 
 if ( g_iShopMenuItems[id][ITEM_SLOT_ONE] > ITEM_NONE && g_iShopMenuItems[id][ITEM_SLOT_TWO] > ITEM_NONE&& 
 g_iShopMenuItems[id][ITEM_SLOT_THREE] > ITEM_NONE ) 
 return ITEM_SLOT_FULL; 
 
 else if ( g_iShopMenuItems[id][ITEM_SLOT_ONE] > ITEM_NONE && g_iShopMenuItems[id][ITEM_SLOT_TWO] > ITEM_NONE) 
 return ITEM_SLOT_THREE; 
 
 else if ( g_iShopMenuItems[id][ITEM_SLOT_ONE] > ITEM_NONE) 
 return ITEM_SLOT_TWO; 
 
 return ITEM_SLOT_ONE; 
 } 
 
 ITEM_Has( id, iItem ) 
 { 
 if ( g_iShopMenuItems[id][ITEM_SLOT_ONE] == iItem ) 
 return ITEM_SLOT_ONE; 
 
 else if ( g_iShopMenuItems[id][ITEM_SLOT_TWO] == iItem ) 
 return ITEM_SLOT_TWO; 
 
 else if ( g_iShopMenuItems[id][ITEM_SLOT_THREE] == iItem ) 
 return ITEM_SLOT_THREE; 
 
 return ITEM_NONE; 
 } 
 
 // Item Death Function 
 ITEM_UserDied( id ) 
 { 
 // The user just died, remove all items 
 if ( g_iShopMenuItems[id][ITEM_SLOT_ONE] > ITEM_NONE ) 
 { 
 ITEM_Remove( id, ITEM_SLOT_ONE ); 
 } 
 
 if ( g_iShopMenuItems[id][ITEM_SLOT_TWO] > ITEM_NONE ) 
 { 
 ITEM_Remove( id, ITEM_SLOT_TWO ); 
 } 
 
 if ( g_iShopMenuItems[id][ITEM_SLOT_THREE] > ITEM_NONE ) 
 { 
 ITEM_Remove( id, ITEM_SLOT_THREE ); 
 } 
 }

// Item Specific Functions

ITEM_Offensive( iAttacker, iVictim, iWeapon, iDamage, iHitPlace )
{

	// Claws of Attack
	if ( ITEM_Has( iAttacker, ITEM_CLAWS ) > ITEM_NONE )
	{	
		WC3_Damage( iVictim, iAttacker, get_pcvar_num( CVAR_wc3_claw ), iWeapon, iHitPlace );
		
		SHARED_Glow( iAttacker, (2 * get_pcvar_num( CVAR_wc3_claw ) ), 0, 0, 0 );

		Create_ScreenFade( iVictim, (1<<10), (1<<10), (1<<12), 255, 0, 0, g_GlowLevel[iVictim][0] );
	}

	// Mask of Death
	if ( ITEM_Has( iAttacker, ITEM_MASK ) > ITEM_NONE && p_data_b[iAttacker][PB_ISCONNECTED])
	{
		new iHealth = get_user_health( iAttacker );
		new iBonusHealth = floatround( float( iDamage ) * get_pcvar_float( CVAR_wc3_mask ) );
		
		new iVampiricBonus = p_data_b[iAttacker][PB_HEXED] ? 0 : SM_GetSkillLevel( iAttacker, SKILL_VAMPIRICAURA );

		// Then the user already gets a bonus, lets lower the total amount the user is going to get
		if ( iVampiricBonus > 0 )
		{
			iBonusHealth /= iVampiricBonus;
		}
		
		// User needs to be set to max health
		if ( iHealth + iBonusHealth > get_user_maxhealth( iAttacker ) )
		{
			set_user_health( iAttacker, get_user_maxhealth( iAttacker ) );
		}
		
		// Give them bonus
		else
		{
			set_user_health( iAttacker, iHealth + iBonusHealth );
		}

		SHARED_Glow( iAttacker, 0, iBonusHealth, 0, 0 );

		Create_ScreenFade( iAttacker, (1<<10), (1<<10), (1<<12), 0, 255, 0, g_GlowLevel[iAttacker][1] );
	}

	if ( ITEM_Has( iAttacker, ITEM_ASSASIN ) > ITEM_NONE )
	{new iMoney = 50;
		
		
		// Give the money to the attacker
		SHARED_SetUserMoney( iAttacker, SHARED_GetUserMoney( iAttacker ) + iMoney, 1 );

	}
	
	if ( ITEM_Has( iAttacker, ITEM_FLAME ) > ITEM_NONE )
	{new id ;
	id = iAttacker ;
	fire_strike(id) ;
    }
	
	// Orb of Frost
	if ( ITEM_Has( iAttacker, ITEM_FROST ) > ITEM_NONE )
	{
		// Only slow them if they aren't slowed/stunned already
		if ( !SHARED_IsPlayerSlowed( iVictim ) )
		{

			p_data_b[iVictim][PB_SLOWED]	= true;

			SHARED_SetSpeed( iVictim );

			set_task( 1.0, "SHARED_ResetMaxSpeed", TASK_RESETSPEED + iVictim );

			SHARED_Glow( iAttacker, 0, 0, 0, 100 );

			Create_ScreenFade( iVictim, (1<<10), (1<<10), (1<<12), 255, 255, 255, g_GlowLevel[iVictim][3] );
		}
	}
}

ITEM_Tome( id )
{
	new iXp = get_pcvar_num( CVAR_wc3_tome ) + XP_GivenByLevel( p_data[id][P_LEVEL] );
		
	if ( g_MOD == GAME_DOD )
	{
		iXp *= 2;
	}

	new iBonusXP = XP_Give( id, iXp );

	if ( iBonusXP != 0 )
	{
		ChatColor( id,"!g* [!t %s!g ] You just gained!t %d !gexperience from purchasing a!t tome", g_MODclient, iBonusXP );
	}

	emit_sound( id, CHAN_STATIC, "warcraft3/Tomes.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );

	return;
}

ITEM_Accelerator( id )
{
	if ( SM_GetSkillLevel( id, ULTIMATE_CHAINLIGHTNING ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_SUICIDE ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_BLINK ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_ENTANGLE ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_IMMOLATE ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_BIGBADVOODOO ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_VENGEANCE ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_LOCUSTSWARM ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_GIFT ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_CLAWS ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_SLEEP ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_STEALTH ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_ILUSION ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_MIND ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_SHADOW) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	else if ( SM_GetSkillLevel( id, ULTIMATE_NATURA ) > 0 )
	{ ULT_ResetCooldown( id, 1 ); }
	
	emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_PSYCHO], 1.0, ATTN_NORM, 0, PITCH_NORM );
	
	return;
}

ITEM_Potion( id )
{
if (!is_user_alive(id)) 
		return;

	
	new iHealthMax = get_user_maxhealth( id );

	if ( get_user_health(id) + 35 <= iHealthMax )
	{
	set_user_health( id, get_user_health( id ) + 35 );
	ChatColor( id,"!g* [!t %s!g ] You gained a health potion!t +35 Health", g_MODclient );
	EffectRestoreHealth(id);
	emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_HP], 1.0, ATTN_NORM, 0, PITCH_NORM );
	}
	else {
	set_user_health( id , iHealthMax ) ; 
	ChatColor( id,"!g* [!t %s!g ] You gained a health potion!t +35 Health", g_MODclient );
	EffectRestoreHealth(id);
	emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_HP], 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
	

	return;
}

ITEM_Steel( id )
{
	if (!is_user_alive(id)) 
		return;

	new iArmor = 200 ;
	ChatColor( id,"!g* [!t %s!g ] You will gain a bonus!t armor", g_MODclient );	
	
	EffectRestoreArmor(id);

	fm_cs_set_user_armor(id, get_user_armor(id) + iArmor , CS_ARMOR_VESTHELM ); 
	emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_AR], 1.0, ATTN_NORM, 0, PITCH_NORM );
	
	return;

	
}

ITEM_Portal( id )
{

ChatColor( id,"!g* [!t %s!g ] You will be teleport back in base", g_MODclient);

// Lets find a free spawn and obey immunity rules
		new ent = SHARED_FindFreeSpawn( id, true );
		
		// No spawn found
		if ( ent < 0 )
		{
				WC3_StatusText( id, 0, "%L", id, "NO_FREE_SPAWN_FOUND" );
			
		}

		// Spawn found!
		else
		{
		new vOrigin[3], vNewOrigin[3], Float:fSpawnOrigin[3];
			// Get the user's origin
			get_user_origin( id, vOrigin );
			
		new j, count = 90
		
		for(j=0;j<5;j++){
			Create_TE_IMPLOSION(vOrigin, 300, count, 30)
			vOrigin[2] -= 15
			count-=15
		}

			// Get the origin of the spawn
			entity_get_vector( ent, EV_VEC_origin, fSpawnOrigin );
			
			// Convert float vector to int vector
			FVecIVec( fSpawnOrigin, vNewOrigin );
			
			// Move the user
			set_user_origin( id, vNewOrigin );

			// Play teleport animation at old location
			//Create_TE_TELEPORT( vOrigin );
emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_VENGEANCE], 1.0, ATTN_NORM, 0, PITCH_NORM );
			}

return;

}

ITEM_Book( id )
{
ChatColor( id,"!g* [!t %s!g ] You will be able to revive a dead teammate", g_MODclient );
respawn_menu_new(id);

return;
}





ITEM_Gloves( id )
{
	if ( !WC3_Check() )
	{
		return;
	}

	if ( !SHARED_HasGrenade( id ) )
	{
		g_iGloveTimer[id] = 0;

		_ITEM_Glove_Give( id );
	}

	return;
}

ITEM_Glove_Begin( id )
{
	// Then lets start a timer to give them a grenade!
	g_iGloveTimer[id] = get_pcvar_num( CVAR_wc3_glove_timer );

	//WC3_StatusText( id, TXT_TIMER, "%d second(s) until your next grenade", g_iGloveTimer[id] );
					new szMessageTimer[256];
					format(szMessageTimer, charsmax(szMessageTimer),
						"%d second(s) until your next grenade", g_iGloveTimer[id] );
	 set_dhudmessage( 0, 100, 0, 0.05, 0.65, 0, 0.02, 0.7, 0.01, 0.1); 
 	 show_dhudmessage(id,"%s", szMessageTimer);

	g_iGloveTimer[id]--;

	set_task( 1.0, "_ITEM_Glove_Give", TASK_ITEM_GLOVES + id );
}

public _ITEM_Glove_Give( id )
{
	if ( !WC3_Check() )
	{
		return;
	}

	if ( id >= TASK_ITEM_GLOVES )
	{
		id -= TASK_ITEM_GLOVES;
	}

	if ( !p_data_b[id][PB_ISCONNECTED] || !is_user_alive( id ) )
	{
		return;
	}

	// Only need to save once! - this is b/c I'm not sure when the loss of a grenade is updated - and I wanted SHARED_HasGrenade to work @ all times!
	if ( g_iGloveTimer[id] == get_pcvar_num( CVAR_wc3_glove_timer ) - 1 )
	{
		SHARED_SaveWeapons( id );
	}

	// If somehow they already got a grenade - stop this!
	/*new bool:bHasGrenade = false;
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		if ( cs_get_user_bpammo( id, CSW_HEGRENADE ) > 0 )
		{
			bHasGrenade = true;
		}
	}

	// Lets not check in DOD b/c I *believe* you can have 2 grenades with a certain class
	else if ( g_MOD == GAME_DOD )
	{
		if ( dod_get_user_ammo( id, DODW_HANDGRENADE ) > 0 || dod_get_user_ammo( id, DODW_STICKGRENADE ) > 0 )
		{
			bHasGrenade = true;
		}
	}*/

	// Lets do CS/CZ only
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		// Already have a grenade!!
		if ( SHARED_HasGrenade( id ) )
		{
			g_iGloveTimer[id] = 0;

			return;
		}
	}


	if ( g_iGloveTimer[id] > 0 )
	{
		//WC3_StatusText( id, TXT_TIMER, "%d second(s) until your next grenade", g_iGloveTimer[id] );
		new szMessageTimer[256];
					format(szMessageTimer, charsmax(szMessageTimer),
						"%d second(s) until your next grenade", g_iGloveTimer[id] );
	 set_dhudmessage( 0, 100, 0, 0.05, 0.65, 0, 0.02, 0.7, 0.01, 0.1); 
 	 show_dhudmessage(id,"%s", szMessageTimer);

		g_iGloveTimer[id]--;

		set_task( 1.0, "_ITEM_Glove_Give", TASK_ITEM_GLOVES + id );

		return;
	}

	// Counter-Strike or Condition Zero grenade
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		give_item( id, "weapon_hegrenade" );
	}

	// Day of Defeat
	else if ( g_MOD == GAME_DOD )
	{
		if ( get_user_team( id ) == ALLIES )
		{
			give_item( id, "weapon_handgrenade" );
		}
		else
		{
			give_item( id, "weapon_stickgrenade" );
		}
	}

	// Display a message to the user
	//WC3_StatusText( id, TXT_TIMER, "%L", id, "ENJOY_A_GRENADE" )
	new szMessageTimer[256];
					format(szMessageTimer, charsmax(szMessageTimer),
						"%L",LANG_PLAYER, "ENJOY_A_GRENADE");
	 set_dhudmessage( 0, 100, 0, 0.05, 0.65, 0, 0.02, 0.7, 0.01, 0.1); 
 	 show_dhudmessage(id,"%s", szMessageTimer);
	

	return;
}		

ITEM_BuyRings( id )
{

	new iItemSlot = ITEM_GetSlot( id );

	// Items are full
	if ( iItemSlot == ITEM_SLOT_FULL && ITEM_Has( id, ITEM_RING ) == ITEM_NONE )
	{
		g_iFutureItem[id] = -3;

		MENU_ReplaceItem( id );

		return;
	}

	new iMoney;
	new iAdditionalRings = 0;
	
	while ( g_iTotalRings[id] + iAdditionalRings < 5 )
	{
		iMoney = SHARED_GetUserMoney( id );

		if ( iMoney < ITEM_Cost( id, ITEM_RING ) )
		{
			break;
		}

		iAdditionalRings++;
		
		new iNewMoney = iMoney - ITEM_Cost( id, ITEM_RING );
		SHARED_SetUserMoney( id, iNewMoney, 1 );
	}

	// Then we need to give them some rings!
	if ( iAdditionalRings > 0 )
	{

		// Subtract 1 b/c ITEM_GiveItem will add one
		g_iTotalRings[id] += ( ( iAdditionalRings * RING_INCREMENT ) - ( RING_INCREMENT ) );

		ITEM_GiveItem( id, ITEM_RING );
	}

	return;
}

public _ITEM_Ring( id )
{
	if ( !WC3_Check() )
	{
		return;
	}

	if ( id >= TASK_ITEM_RING )
	{
		id -= TASK_ITEM_RING;
	}

	if ( !p_data_b[id][PB_ISCONNECTED] || ITEM_Has( id, ITEM_RING ) == ITEM_NONE )
	{
		return;
	}

	new iBonusHealth = g_iTotalRings[id];

	while ( iBonusHealth > 0 )
	{
		new iHealth =  get_user_health( id ) + 1;

		if ( iHealth <= get_user_maxhealth( id ) )
		{
			set_user_health( id, iHealth );
		}

		iBonusHealth--;
	}

	set_task( 2.0, "_ITEM_Ring", TASK_ITEM_RING + id );

	return;
}

ITEM_Scroll( id )
{
	// Make sure the user isn't about to respawn when we do these checks
	if ( !p_data[id][P_RESPAWNBY] )
	{
		p_data[id][P_RESPAWNBY] = RESPAWN_ITEM;

		set_task( SPAWN_DELAY, "_SHARED_Spawn", TASK_SPAWN + id );
	}
}

ITEM_CheckFlag( iItemID, iFlag )
{
	if ( g_iFlag[iItemID] & iFlag )
	{
		return true;
	}

	return false;	
}

// Format the item for WC3_ShowBar
ITEM_Format( id, iItem, szItemString[], iLen )
{
	new szItemName[32];
	LANG_GetItemName( iItem, id, szItemName, 31, true );

	// Special options
	if ( iItem == ITEM_NECKLACE )
	{
		formatex( szItemString, iLen, "%s[%d]", szItemName, g_iNecklaceCharges[id] );
	}

	else if ( iItem == ITEM_HELM )
	{
		formatex( szItemString, iLen, "%s[%d]", szItemName, g_iHelmCharges[id] );
	}

	else if ( iItem == ITEM_RING )
	{
		formatex( szItemString, iLen, "%s[%d]", szItemName, g_iTotalRings[id] );
	}
	
	// All other cases
	else
	{
		copy( szItemString, iLen, szItemName );
	}
}

ITEM_HasItem( id, iItem )
{
	if ( g_iShopMenuItems[id][ITEM_SLOT_ONE] == iItem )
		return iItem;

	else if ( g_iShopMenuItems[id][ITEM_SLOT_TWO] == iItem )
		return iItem;

	else if ( g_iShopMenuItems[id][ITEM_SLOT_THREE] == iItem )
		return iItem;

	return ITEM_NONE;
}


EffectRestoreHealth(id)
{
	if (!is_user_alive(id)) 
		return;
	
	static Float:origin[3];
	pev(id,pev_origin,origin);
    
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY); 
	write_byte(TE_EXPLOSION); // TE_EXPLOSION
	write_coord(floatround(origin[0])); // origin x
	write_coord(floatround(origin[1])); // origin y
	write_coord(floatround(origin[2])); // origin z
	write_short(g_iSprites[SPR_HEAL]); // sprites
	write_byte(15); // scale in 0.1's
	write_byte(12); // framerate
	write_byte(14); // flags 
	message_end(); // message end
	
	message_begin(MSG_ONE_UNRELIABLE, gmsgScreenFade,_, id);
	write_short(1<<10);
	write_short(1<<10);
	write_short(0x0000);
	write_byte(0);//r
	write_byte(255);  //g
	write_byte(0);  //b
	write_byte(75);
	message_end();
}

EffectRestoreArmor(id)
{
	if (!is_user_alive(id)) 
		return;
	
	static Float:origin[3];
	pev(id,pev_origin,origin);
    
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY); 
	write_byte(TE_EXPLOSION); // TE_EXPLOSION
	write_coord(floatround(origin[0])); // origin x
	write_coord(floatround(origin[1])); // origin y
	write_coord(floatround(origin[2])); // origin z
	write_short(g_iSprites[SPR_STEEL]); // sprites
	write_byte(15); // scale in 0.1's
	write_byte(12); // framerate
	write_byte(14); // flags 
	message_end(); // message end
	
	message_begin(MSG_ONE_UNRELIABLE, gmsgScreenFade,_, id);
	write_short(1<<10);
	write_short(1<<10);
	write_short(0x0000);
	write_byte(238);//r
	write_byte(232);  //g
	write_byte(170);  //b
	write_byte(75);
	message_end();

}





public fEnableItemESP(id)
{
	if(task_exists(id + TASK_ESP))
		remove_task(id + TASK_ESP);

	bIsUserESP[id] = true;
	set_task(FREQUENCY_ESP, "fESPLoop", id + TASK_ESP, _, _, "b");
	
}

public fDisableItemESP(id)
{
	bIsUserESP[id] = false;

	if(task_exists(id + TASK_ESP))
		remove_task(id + TASK_ESP);
}

public fESPLoop(id)
{	
	if (id >= TASK_ESP )
			id -= TASK_ESP;

	if(!is_user_connected(id) || !is_user_alive(id) || !bIsUserESP[id]) 
	{
		if(task_exists(id + TASK_ESP))
			remove_task(id + TASK_ESP);

		return PLUGIN_CONTINUE;
	}
	
	new arrPlayers[32], iNum;
	get_players(arrPlayers, iNum, "a");
	
	for(new i = 0; i < iNum; ++i)
	{
		new iLoopIdPlayer = arrPlayers[i];
		new iTeamCurrentUser = get_user_team(id);
		new iTeamLoopUser = get_user_team(iLoopIdPlayer);

		if(iTeamCurrentUser == iTeamLoopUser || id == iLoopIdPlayer) 
			continue;

		//if(!p_data[iLoopIdPlayer][P_RACE] || p_data[iLoopIdPlayer][P_RACE] != RACE_HUMAN || ITEM_Has(iLoopIdPlayer, ITEM_CLOAK ) <= ITEM_NONE)
			//continue;
		if( p_data[iLoopIdPlayer][P_RACE] == RACE_HUMAN || ITEM_Has(iLoopIdPlayer, ITEM_CLOAK ) > ITEM_NONE)
		{new iOrigin[3];
		get_user_origin(iLoopIdPlayer, iOrigin, 0);
			
		message_begin(MSG_ONE, SVC_TEMPENTITY, iOrigin, id);
		write_byte(21);
		write_coord(iOrigin[0]);
		write_coord(iOrigin[1]);
		write_coord(iOrigin[2] - 20);
		write_coord(iOrigin[0]);
		write_coord(iOrigin[1]);
		write_coord(iOrigin[2] + RADIUS_ESP);
		write_short(g_iSprites[SPR_TRAIL]);
		write_byte(0);
		write_byte(1);
		write_byte(6); 
		write_byte(8);
		write_byte(1);
		write_byte(100);
		write_byte(100);
		write_byte(255);
		write_byte(192);
		write_byte(0);
		message_end();
		}
	}

	return PLUGIN_CONTINUE;
}



//======================================================================================================

public fire_strike(id)
{ 
   emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_FLAMESTRIKE], 0.5, ATTN_NORM, 0, PITCH_NORM );

   new vec[3] 
   new aimvec[3] 
   new velocityvec[3] 
   new length
   new speed = 10 
   get_user_origin(id,vec) 
   get_user_origin(id,aimvec,2) 
   new dist = get_distance(vec,aimvec) 

	/*
   if (p_data[id][P_FLAMECOUNT]==1){
      new parm[2]
      parm[0]=id
   }
   */
  
   new speed1 = 160 
   new speed2 = 350 
   new radius = 105 

   if(dist < 50){ 
      radius = 0 
      speed = 5 
   } 
   else if(dist < 150){ 
      speed1 = speed2 = 1 
      speed = 5 
      radius = 50 
   } 
   else if(dist < 200){ 
      speed1 = speed2 = 1 
      speed = 5 
      radius = 90 
   } 
   else if(dist < 250){ 
      speed1 = speed2 = 90 
      speed = 6 
      radius = 90 
   } 
   else if(dist < 300){ 
      speed1 = speed2 = 140 
      speed = 7 
   } 
   else if(dist < 350){ 
      speed1 = speed2 = 190 
      speed = 7 
   } 
   else if(dist < 400){ 
      speed1 = 150 
      speed2 = 240 
      speed = 8 
   } 
   else if(dist < 450){ 
      speed1 = 150 
      speed2 = 290 
      speed = 8 
   } 
   else if(dist < 500){ 
      speed1 = 180 
      speed2 = 340 
      speed = 9 
   } 

   velocityvec[0]=aimvec[0]-vec[0] 
   velocityvec[1]=aimvec[1]-vec[1] 
   velocityvec[2]=aimvec[2]-vec[2] 
   length=sqroot(velocityvec[0]*velocityvec[0]+velocityvec[1]*velocityvec[1]+velocityvec[2]*velocityvec[2]) 
   velocityvec[0]=velocityvec[0]*speed/length 
   velocityvec[1]=velocityvec[1]*speed/length 
   velocityvec[2]=velocityvec[2]*speed/length 

   new args[8] 
   args[0] = vec[0] 
   args[1] = vec[1] 
   args[2] = vec[2] 
   args[3] = velocityvec[0] 
   args[4] = velocityvec[1] 
   args[5] = velocityvec[2] 
	
   set_task(0.1,"te_spray",TASK_TESPRAY+id,args,8,"a",2) 
   check_burnzone(id,vec,aimvec,speed1,speed2,radius) 

} 

public te_spray(args[])
{
	new position[3], direction[3]
	position[0] = args[0]
	position[1] = args[1]
	position[2] = args[2]
	direction[0] = args[3]
	direction[1] = args[4]
	direction[2] = args[5]

	Create_TE_SPRAY(position, direction, g_iSprites[SPR_FIRE], 8, 70, 100, 5)

	return PLUGIN_CONTINUE 
} 

check_burnzone(id,vec[],aimvec[],speed1,speed2,radius)
{
	new maxplayers = get_maxplayers()
	new bodypart, victim 
	
	get_user_aiming(id,victim,bodypart,550) 

	if( victim > 0 && victim <= maxplayers ){
		if( get_user_team(victim)!=get_user_team(id) )
			burn_victim(victim,id,bodypart)
	}
    
	new burnvec1[3],burnvec2[3],length1 

	burnvec1[0]=aimvec[0]-vec[0] 
	burnvec1[1]=aimvec[1]-vec[1] 
	burnvec1[2]=aimvec[2]-vec[2] 

	length1=sqroot(burnvec1[0]*burnvec1[0]+burnvec1[1]*burnvec1[1]+burnvec1[2]*burnvec1[2]) 
	burnvec2[0]=burnvec1[0]*speed2/length1 
	burnvec2[1]=burnvec1[1]*speed2/length1 
	burnvec2[2]=burnvec1[2]*speed2/length1 
	burnvec1[0]=burnvec1[0]*speed1/length1 
	burnvec1[1]=burnvec1[1]*speed1/length1 
	burnvec1[2]=burnvec1[2]*speed1/length1 
	burnvec1[0] += vec[0] 
	burnvec1[1] += vec[1] 
	burnvec1[2] += vec[2] 
	burnvec2[0] += vec[0] 
	burnvec2[1] += vec[1] 
	burnvec2[2] += vec[2] 

	new origin[3], players[32], numberofplayers
	get_players(players, numberofplayers)

	for (new i=0; i < numberofplayers; i++){
		victim = players[i]
		if( is_user_alive(victim) && get_user_team(victim)!=get_user_team(id) ){ 
			get_user_origin(victim,origin) 
			if(get_distance(origin, burnvec1) < radius) 
				burn_victim(victim,id,bodypart) 
			else if(get_distance(origin, burnvec2) < radius) 
				burn_victim(victim,id,bodypart) 
		} 
	} 
	return PLUGIN_CONTINUE       
} 

burn_victim(victim,attacker,bodypart)
{
	if(p_data_b[victim][PB_ISBURNING]) 
		return PLUGIN_CONTINUE 

	p_data_b[victim][PB_ISBURNING] = true

	new hp,args[3] 
	hp = get_user_health(victim) 

	args[0] = victim 
	args[1] = attacker  
	args[2] = bodypart
	set_task(0.3,"on_fire",TASK_ONFIRE,args,3,"a",hp / 10) 

	return PLUGIN_CONTINUE 
} 

public on_fire(args[])
{
	new victim = args[0]
	new attacker = args[1] 
	new bodypart = args[2]

	if (!bodypart)
		bodypart = random_num(1,8)

	if(!p_data_b[victim][PB_ISCONNECTED])
		return PLUGIN_CONTINUE


	if(!p_data_b[victim][PB_ISBURNING]) 
		return PLUGIN_CONTINUE 

	new rx,ry,rz, origin[3], position[3]

	rx = random_num(-30,30) 
	ry = random_num(-30,30) 
	rz = random_num(-30,30) 

	get_user_origin(victim,origin) 

	position[0] = origin[0] + rx
	position[1] = origin[1] + ry
	position[2] = origin[2] + 10 + rz

	Create_TE_SPRITE(position, g_iSprites[SPR_BURNING], 30, 200)

	position[0] = origin[0]+(rx*2)
	position[1] = origin[1]+(ry*2)
	position[2] = origin[2]+100+(rz*2)

	Create_TE_Smoke(position, position, g_iSprites[SPR_SMOKE], 60, 15)

	WC3_Damage( victim, attacker, 10, CSW_IMMOLATE, bodypart)

	return PLUGIN_CONTINUE 
}


public respawn_menu_new(id) {
    //if (g_F_counter[id] < 1) {
        new title_msg[100];
        formatex(title_msg, charsmax(title_msg), "\rDeath's Book Menu")
        new menu = menu_create(title_msg, "menu_res_new")
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

public menu_res_new(idUser, menu, item) {
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
