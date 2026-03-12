
public MENU_War3Menu( id )
{
	static pos, szMenu[256], keys;
	keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<9);
	pos = 0;

	// Add the title
	pos += formatex( szMenu[pos], 255-pos, "%L^n^n", id, "MENU_WAR3MENU" );

	// Add the actual options to the menu
	pos += formatex( szMenu[pos], 255-pos, "\r1.\w %L^n", id, "SKILLS_MENU" );
	pos += formatex( szMenu[pos], 255-pos, "\r2.\w %L^n", id, "RACE_MENU" );
	pos += formatex( szMenu[pos], 255-pos, "\r3.\w %L^n", id, "ITEM_MENU" );
	pos += formatex( szMenu[pos], 255-pos, "\r4.\r %L^n", id, "GOLD_MENU_TITLE" );
	pos += formatex( szMenu[pos], 255-pos, "\r5.\y %L^n", id, "ADMIN_MENU_TITLE" );
	pos += formatex( szMenu[pos], 255-pos, "\r6.\y %L^n", id, "HELP" );
	pos += formatex( szMenu[pos], 255-pos, "\r7.\r %L^n", id, "VIP_TITLE" );
	pos += formatex( szMenu[pos], 255-pos, "^n\r0.\w %L", id, "WORD_EXIT" );

	// Display the menu
	show_menu( id, keys, szMenu, -1 );

	return;
}

public _MENU_War3Menu( id, key )
{

	if ( !WC3_Check() )
	{
		return PLUGIN_HANDLED;
	}

	switch ( key )
	{
		case 0:	menu_Skill_Options( id );
		case 1:	menu_Race_Options( id );
		case 2:	menu_Item_Options( id );
		case 3:	menu_Gold_Options( id );
		case 4:	menu_Admin_Options( id );
		case 5:	MOTD_War3help( id );
		case 6:	MOTD_Vip( id );
	}
	
	return PLUGIN_HANDLED;
}



public menu_Skill_Options( id )
{

	new pos = 0, i, menu_body[512], menuitems[3][32]
	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<8)|(1<<9)


	format(menuitems[0],31,"%L",id,"SELECT_SKILLS")
	format(menuitems[1],31,"%L",id,"SKILLS_INFORMATION")
	format(menuitems[2],31,"%L",id,"RESELECT_SKILLS")

	pos += format(menu_body[pos], 511-pos, "%L^n^n",id,"MENU_SKILLS_OPTIONS")
	for (i = 0; i<3; i++){
		pos += format(menu_body[pos], 511-pos, "\r%d.\w %s^n",i+1,menuitems[i])
	}
	pos += format(menu_body[pos], 511-pos, "^n^n\r9.\w %L",id,"BACK_STRING")
	pos += format(menu_body[pos], 511-pos, "^n\r0.\w %L",id,"WORD_EXIT")
	show_menu(id,keys,menu_body,-1)

	return PLUGIN_CONTINUE
}

public _menu_Skill_Options(id,key){
	
	if ( !WC3_Check() )
	{
		return PLUGIN_HANDLED;
	}

	switch (key){
		case 0:	MENU_SelectSkill( id );
		case 1:	MOTD_SkillsInfo( id );
		case 2:	CMD_Handle( id, "resetskills", true );
		case 8: MENU_War3Menu(id)
		default: return PLUGIN_HANDLED;
	}

	return PLUGIN_HANDLED;
}

public menu_Race_Options(id){

	new pos = 0, i, menu_body[512], menuitems[4][32]
	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<8)|(1<<9)

	format(menuitems[0],31,"%L",id,"CHANGE_RACE")
	format(menuitems[1],31,"%L",id,"SHOW_LEVEL")
	format(menuitems[2],31,"%L",id,"RESET_XP")
	format(menuitems[3],31,"%L",id,"SHOW_PLAYER_SKILLS")

	pos += format(menu_body[pos], 511-pos, "%L^n^n",id,"MENU_RACE_OPTIONS")
	for (i = 0; i<4; i++){
		pos += format(menu_body[pos], 511-pos, "\r%d.\w %s^n",i+1,menuitems[i])
	}
	pos += format(menu_body[pos], 511-pos, "^n^n\r9.\w %L",id,"BACK_STRING")
	pos += format(menu_body[pos], 511-pos, "^n\r0.\w %L",id,"WORD_EXIT")
	show_menu(id,keys,menu_body,-1)

	return PLUGIN_CONTINUE
}

public _menu_Race_Options(id,key){

	if ( !WC3_Check() )
	{
		return PLUGIN_HANDLED;
	}

	switch (key){
		case 0:	WC3_ChangeRaceStart( id );
		case 1:	WC3_ShowRaceInfo( id );
		case 2:	MENU_ResetXP( id );
		case 3:	MOTD_PlayerSkills( id, true );
		case 8: MENU_War3Menu(id)
		default: return PLUGIN_HANDLED;
	}

	return PLUGIN_HANDLED;
}

public menu_Item_Options(id){

	new pos = 0, i, menu_body[512], menuitems[8][32]
	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9)

	format(menuitems[0],31,"%L",id,"SHOPMENU1_OPTION")
	format(menuitems[1],31,"%L",id,"SHOPMENU2_OPTION")
	format(menuitems[2],31,"%L",id,"SHOPMENU3_OPTION")
	format(menuitems[3],31,"%L",id,"SHOPMENU4_OPTION")
	format(menuitems[4],31,"%L",id,"SHOW_SHOPMENU1_INFO")
	format(menuitems[5],31,"%L",id,"SHOW_SHOPMENU2_INFO")
	format(menuitems[6],31,"%L",id,"SHOW_SHOPMENU3_INFO")
	format(menuitems[7],31,"%L",id,"SHOW_SHOPMENU4_INFO")

	pos += format(menu_body[pos], 511-pos, "%L^n^n",id,"MENU_ITEM_OPTIONS")
	for (i = 0; i<8; i++){
		pos += format(menu_body[pos], 511-pos, "\r%d.\w %s^n",i+1,menuitems[i])
	}
	pos += format(menu_body[pos], 511-pos, "^n^n\r9.\w %L",id,"BACK_STRING")
	pos += format(menu_body[pos], 511-pos, "^n\r0.\w %L",id,"WORD_EXIT")
	show_menu(id,keys,menu_body,-1)

	return PLUGIN_CONTINUE
}

public _menu_Item_Options(id,key){

	if ( !WC3_Check() )
	{
		return PLUGIN_HANDLED;
	}

	switch (key){
		case 0:	MENU_Shopmenu( id, 0 );
		case 1:	MENU_Shopmenu( id, 9 );
		case 2:	{
		if(!(get_user_flags(id) & ADMIN_LEVEL_H) && get_pcvar_num(CVAR_wc3_shopmenu3_vip) == 1) 
{   
	   
			ChatColor( id,"!g* [!t %s!g ] This Item is only for!t VIP",g_MODclient);
			MOTD_Vip(id);
			return PLUGIN_HANDLED;
}
else {MENU_Shopmenu( id, 18 );}
}
		case 3:	
		{
		if(!(get_user_flags(id) & ADMIN_LEVEL_H) && get_pcvar_num(CVAR_wc3_shopmenu4_vip) == 1) 
{   
	   
			ChatColor( id,"!g* [!t %s!g ] This Item is only for!t VIP",g_MODclient);
			MOTD_Vip(id);
			return PLUGIN_HANDLED;
}
else {MENU_Shopmenu( id, 27 ); }
}
		case 4:	MOTD_ItemsInfo( id, 0 );
		case 5:	MOTD_ItemsInfo( id, 9 );
		case 6:	MOTD_ItemsInfo( id, 18 );
		case 7:	MOTD_ItemsInfo( id, 27 );
		case 8: MENU_War3Menu(id);
		default: return PLUGIN_HANDLED;
	}

	return PLUGIN_HANDLED;
}

public menu_Gold_Options( id ){
new pos = 0, i, menu_body[512], menuitems[2][32]
	new keys = (1<<0)|(1<<1)|(1<<8)|(1<<9)

	format(menuitems[0],31,"%L",id,"TRADE")
	//format(menuitems[1],31,"%L",id,"GOLD_SHOP")
	format(menuitems[1],31,"%L",id,"TRADE_INFO")
	//format(menuitems[3],31,"%L",id,"GOLD_SHOP_INFO")

	pos += format(menu_body[pos], 511-pos, "\r%L^n^n",id,"GOLD_MENU_OPTIONS")
	for (i = 0; i<2; i++){
		pos += format(menu_body[pos], 511-pos, "\r%d.\w %s^n",i+1,menuitems[i])
	}
	pos += format(menu_body[pos], 511-pos, "^n^n\r9.\w %L",id,"BACK_STRING")
	pos += format(menu_body[pos], 511-pos, "^n\r0.\w %L",id,"WORD_EXIT")
	show_menu(id,keys,menu_body,-1)

	return PLUGIN_CONTINUE
}

public _menu_Gold_Options(id,key){

	if ( !WC3_Check() )
	{
		return PLUGIN_HANDLED;
	}

	switch (key){
		case 0:	menu_Trade_Options( id );
		//case 1:	ChatColor(id,"!g* [!t WAR3FT!g ]!t GoldShopmenu!g is!t Disabled!g !");
		case 1:	MOTD_TRADEINFO( id );
		//case 3:	ChatColor(id,"!g* [!t WAR3FT!g ]!t GoldShopmenu!g is!t Disabled!g !");
		case 8: MENU_War3Menu(id)
		default: return PLUGIN_HANDLED;
	}

	return PLUGIN_HANDLED;
}


//===========================================================================

public menu_Trade_Options( id )
{
	static pos, szMenu[256], keys;
	keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<8)|(1<<9);
	pos = 0;

	// Add the title
	pos += formatex( szMenu[pos], 255-pos, "\r%L^n^n", id, "MENU_TRADE_OPTIONS" );

	// Add the actual options to the menu
	pos += formatex( szMenu[pos], 255-pos, "\r1.\w Money\r 8000 $\R1 G o ld^n");
	pos += formatex( szMenu[pos], 255-pos, "\r2.\w Money\r 16000 $\R2 G o ld^n");

	pos += formatex( szMenu[pos], 255-pos, "\r3.\w Experience\r 1500 XP\R1 G o ld^n");
	pos += formatex( szMenu[pos], 255-pos, "\r4.\w Experience\r 7500 XP\R5 G o ld^n");
	
	pos += formatex( szMenu[pos], 255-pos, "\r5.\w Gold\r 1 Gold\R8000 $^n");
	pos += formatex( szMenu[pos], 255-pos, "\r6.\w Gold\r 2 Gold\R16000 $^n");
	
	pos += formatex( szMenu[pos], 255-pos, "^n^n\r9.\w %L^n", id,"BACK_STRING" );
	pos += formatex( szMenu[pos], 255-pos, "\r0.\w %L", id, "WORD_EXIT" );

	// Display the menu
	show_menu( id, keys, szMenu, -1 );

	return;
}

public _menu_Trade_Options(id,key){

	if ( !WC3_Check() )
	{
		return PLUGIN_HANDLED;
	}

	switch (key){
		case 0:	Retrage(id);
		case 1:	Retrage_2(id);
		case 2:	RetrageXP_A(id);
		case 3: RetrageXP_B(id)
		case 4:	Depozit(id);
		case 5:	Depozit_2(id);
		case 8: menu_Gold_Options( id );
		default: return PLUGIN_HANDLED;
	}

	return PLUGIN_HANDLED;
}



//=================================================================================
public menu_Admin_Options(id){

    if ( id && !( get_user_flags( id ) & XP_GetAdminFlag() ) )
	{
			client_print(id,print_center,"%s %L",g_MODclient, id,"YOU_HAVE_NO_ACCESS")
			return PLUGIN_HANDLED
	}

	new pos = 0, i, menu_body[512], menuitems[3][32]
	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<8)|(1<<9)

	format(menuitems[0],31,"%L",id,"GIVE_IND_XP")
	format(menuitems[1],31,"%L",id,"GIVE_MULT_XP")
	format(menuitems[2],31,"%L",id,"SAVE_ALL_XP")

	pos += format(menu_body[pos], 511-pos, "%L^n^n",id,"MENU_ADMIN_MENU")
	for (i = 0; i<3; i++){
		pos += format(menu_body[pos], 511-pos, "\r%d.\w %s^n",i+1,menuitems[i])
	}
	pos += format(menu_body[pos], 511-pos, "^n^n\r9.\w %L",id,"BACK_STRING")
	pos += format(menu_body[pos], 511-pos, "^n\r0.\w %L",id,"WORD_EXIT")
	show_menu(id,keys,menu_body,-1)

	return PLUGIN_CONTINUE
}

public _menu_Admin_Options(id,key){

	if ( !WC3_Check() )
	{
		return PLUGIN_HANDLED;
	}

	switch (key){
		case 0:{
			g_menuOption[id] = 1
			g_menuSettings[id] = 50
			menu_PlayerXP_Options(id,g_menuPosition[id] = 0)
		}
		case 1:{
			g_menuOption[id] = 1
			g_menuSettings[id] = 50
			menu_TeamXP_Options(id)
		}
		case 2: DB_SaveAll( false );
		case 8: MENU_War3Menu(id)
	}

	return PLUGIN_HANDLED;
}

public menu_PlayerXP_Options(id,pos){

	if (pos < 0){
		menu_Admin_Options(id)
		return PLUGIN_CONTINUE
	}

	get_players(g_menuPlayers[id],g_menuPlayersNum[id])
	new menuBody[512]
	new b = 0
	new i
	new name[32], team[4], title[128], back[16], exitstring[16]
	new start = pos * 7
	if (start >= g_menuPlayersNum[id])
		start = pos = g_menuPosition[id] = 0
	format(title,127,"%L",id,"MENU_GIVE_PLAYERS_XP")
	new len = format(menuBody,511, "%s\R%d/%d^n\w^n",title,pos+1,(g_menuPlayersNum[id] / 7 + ((g_menuPlayersNum[id] % 7) ? 1 : 0 )))
	new end = start + 7
	new keys = (1<<9)|(1<<7)

	if (end > g_menuPlayersNum[id])
		end = g_menuPlayersNum[id]

	for(new a = start; a < end; ++a){
		i = g_menuPlayers[id][a]
		get_user_name(i,name,31)
		get_user_team(i,team,3)
		keys |= (1<<b)
		len += format(menuBody[len],511-len,"\r%d.\w %s^n\w",++b,name)
	}

	format(title,127,"%L",id,"GIVE")
	len += format(menuBody[len],511-len,"^n\r8.\w %s  %d XP^n",title,g_menuSettings[id])

	format(back,15,"%L",id,"BACK_STRING")

	if (end != g_menuPlayersNum[id]){
		format(menuBody[len],511-len,"^n\r9.\w %L...^n\r0.\w %s", id,"MORE_STRING", pos ? back : back)
		keys |= (1<<8)
	}
	else{
		format(exitstring,15,"%L",id,"WORD_EXIT")
		format(menuBody[len],511-len,"^n\r0.\w %s", pos ? back : exitstring)
	}


	show_menu(id,keys,menuBody,-1)
	return PLUGIN_CONTINUE

}

public _menu_PlayerXP_Options(id,key){

	if ( !WC3_Check() )
	{
		return PLUGIN_HANDLED;
	}

	switch(key){
		case 7:{
			++g_menuOption[id]
			if (g_menuOption[id]>6){
				g_menuOption[id]=1
			}
			switch(g_menuOption[id]){
				case 1: g_menuSettings[id] = 50
				case 2: g_menuSettings[id] = 100
				case 3: g_menuSettings[id] = 500
				case 4: g_menuSettings[id] = 1000
				case 5: g_menuSettings[id] = 5000
				case 6: g_menuSettings[id] = 10000
			}
			menu_PlayerXP_Options(id,g_menuPosition[id])
		}
		case 8: menu_PlayerXP_Options(id,++g_menuPosition[id])
		case 9: return PLUGIN_HANDLED;
		default:{
			new player = g_menuPlayers[id][g_menuPosition[id] * 7 + key]
			ChatColor(player,"!g* [!t %s!g ] The admin just awarded you!t %d !gexperience",g_MODclient,g_menuSettings[id])
			p_data[player][P_XP] += g_menuSettings[id]

			XP_Check( player );

			menu_PlayerXP_Options(id,g_menuPosition[id])
		}
	}

	return PLUGIN_HANDLED;
}

public menu_TeamXP_Options(id){

	new pos = 0, i, menu_body[512], menuitems[3][32], give[16]
	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<7)|(1<<8)|(1<<9)

	format(menuitems[0],31,"%L",id,"TERRORISTS")
	format(menuitems[1],31,"%L",id,"CT")
	format(menuitems[2],31,"%L",id,"EVERYONE")

	pos += format(menu_body[pos], 511-pos, "%L^n^n",id,"MENU_TEAM_XP")
	for (i = 0; i<3; i++){
		pos += format(menu_body[pos], 511-pos, "\r%d.\w %s^n",i+1,menuitems[i])
	}
	format(give,15,"%L",id,"GIVE")
	pos += format(menu_body[pos], 511-pos,"^n\r8.\w %s  %d XP^n",give,g_menuSettings[id])
	pos += format(menu_body[pos], 511-pos, "^n^n\r9.\w %L",id,"BACK_STRING")
	pos += format(menu_body[pos], 511-pos, "^n\r0.\w %L",id,"WORD_EXIT")
	show_menu(id,keys,menu_body,-1)

	return PLUGIN_CONTINUE
}

public _menu_TeamXP_Options(id,key){

	if ( !WC3_Check() )
	{
		return PLUGIN_HANDLED;
	}

	switch(key){
		case 0:
		{
			ADMIN_GiveXP( id, "@T", g_menuSettings[id] );
			menu_TeamXP_Options(id)
		}
		case 1:{
			ADMIN_GiveXP( id, "@CT", g_menuSettings[id] );
			menu_TeamXP_Options(id)
		}
		case 2:{
			ADMIN_GiveXP( id, "@ALL", g_menuSettings[id] );
			menu_TeamXP_Options(id)
		}
		case 7:{
			++g_menuOption[id]
			if (g_menuOption[id]>6){
				g_menuOption[id]=1
			}
			switch(g_menuOption[id]){
				case 1: g_menuSettings[id] = 50
				case 2: g_menuSettings[id] = 100
				case 3: g_menuSettings[id] = 500
				case 4: g_menuSettings[id] = 1000
				case 5: g_menuSettings[id] = 5000
				case 6: g_menuSettings[id] = 10000
			}
			menu_TeamXP_Options(id)
		}
		case 8: menu_Admin_Options(id)
	}

	return PLUGIN_HANDLED;
}

public MENU_ResetXP(id)
{

	static szMenu[128];
	new keys = (1<<0)|(1<<1)|(1<<9);
	
	formatex( szMenu, 127, "%L^n^n\r1.\w Yes^n\r2.\w No", id, "MENU_RESET_XP" );

	show_menu( id, keys, szMenu, -1 );

	return;
}

public _MENU_ResetXP( id, key )
{
	
	if ( !WC3_Check() )
	{
		return PLUGIN_HANDLED;
	}

	// User selected yes
	if ( key == 0 )
	{
		XP_Reset( id );
	}
	
	return PLUGIN_HANDLED;
}

// Function will display the changerace menu
public MENU_ChangeRace( id, iRaceXP[MAX_RACES],iRaceLVL[MAX_RACES], pos )
{
	if(pos < 0) {
		g_menuPosition[id] = 0
		return
	}
	new i, szRaceName[MAX_RACES+1][64], szXP[256], szLVL[1024];
	
	// Get our race names
	for ( i = 0; i < get_pcvar_num( CVAR_wc3_races ); i++ )
	{
		lang_GetRaceName( i + 1, id, szRaceName[i], 63 );
	}
	
	static start
	start = pos * 8
	
	static maxitem
	maxitem = get_pcvar_num( CVAR_wc3_races )
	
	if(start >= maxitem)
		start = pos = g_menuPosition[id]
	
	static racemenu[65536], len
	len = formatex(racemenu, 65535, "\r%L", id, "MENU_SELECT_RACE" );
	
	static end
	end = start + 8
	
	if(end > maxitem)
		end = maxitem
	
	static keys
	keys = MENU_KEY_0
	
	static a, b
	b = 0
	
	if ( get_pcvar_num( CVAR_wc3_save_xp ) )
	{
		//len += formatex(racemenu[len], 65535 - len, "\r\R%L                     \R%L^n^n", id, "MENU_WORD_EXPERIENCE", id, "MENU_WORD_LEVEL" );
		len += formatex(racemenu[len], 65535 - len, "\r\R%L^n^n", id, "MENU_WORD_EXPERIENCE");
		
	}
	else
	{
		len += formatex(racemenu[len], 65535 - len, "^n^n" );
	}
	
	for(a = start; a < end; ++a) {
		num_to_str( iRaceXP[a], szXP, 255 );
		formatex(szLVL, charsmax(szLVL), "%d",iRaceLVL[a]); 
		
		// Add the "Select a Hero" message if necessary
		if ( a == 4 )
		{
			len += formatex(racemenu[len], 65535 - len, "\r%L", id, "SELECT_HERO" );
		}
		if ( a == 12 )
		{
			len += formatex(racemenu[len], 65535 - len, "\r%L", id, "SELECT_HERO" );
		}
		
		// User's current race
		if ( a == p_data[id][P_RACE] - 1 )
		{
			keys |= (1<<b)
			len += formatex(racemenu[len], 65535 - len, "\d%d. %s   (Level %s) \d\R%s^n", ++b, szRaceName[a], ( (get_pcvar_num( CVAR_wc3_save_xp )) ? szLVL : " " ), ( (get_pcvar_num( CVAR_wc3_save_xp )) ? szXP : " " ) );
		}
		
		// Race the user wants to change to
		else if ( a == p_data[id][P_CHANGERACE] - 1 )
		{
			keys |= (1<<b)
			len += formatex(racemenu[len], 65535 - len, "\r%d.\r %s   (Level %s) \r\R%s^n", ++b, szRaceName[a], ( (get_pcvar_num( CVAR_wc3_save_xp )) ? szLVL : " " ), ( (get_pcvar_num( CVAR_wc3_save_xp )) ? szXP : " " ) );
		}
		
		// All other cases
		else
		{
			new bool:bAllowRace = true;
			
			// Check to see if the user can choose this race (are there too many of this race?)
			if ( bAllowRace )
			{
				keys |= (1<<b)
				len += formatex(racemenu[len], 65535 - len, "\r%d.\w %s   (\rLevel %s\w)  \r\R%s^n", ++b, szRaceName[a], ( (get_pcvar_num( CVAR_wc3_save_xp )) ? szLVL : " " ), ( (get_pcvar_num( CVAR_wc3_save_xp )) ? szXP : " " ) );
			}
			
			// If not, display the race, but don't give them a key to press
			else
			{
				len += formatex(racemenu[len], 65535 - len, "\d%d. %s   (Level %s)  \d\R%s^n", ++b, szRaceName[a], ( (get_pcvar_num( CVAR_wc3_save_xp )) ? szLVL : " " ), ( (get_pcvar_num( CVAR_wc3_save_xp )) ? szXP : " " ) );
			}
		}
	}
	
	if(end != maxitem) {
		formatex(racemenu[len], 65535 - len, "^n\r9.\w Next Page^n\r0.\w %s", pos ? "Previous Page" : "Exit")
		keys |= MENU_KEY_9
	}
	else	
		formatex(racemenu[len], 65535 - len, "^n\r0.\w %s", pos ? "Previous Page" : "Exit")
		
	
	show_menu(id, keys, racemenu, -1, "ChangeRace")
	
	return
}

public _MENU_ChangeRace(id, key) {	
	switch(key) {
		case 8: {
			// Make sure the user is on a team!
			if ( SHARED_IsOnTeam( id ) )
			{
				g_menuPosition[id]++
				// Get the XP if we're saving XP
				if ( get_pcvar_num( CVAR_wc3_save_xp ) )
				{
					
					// This function will also display the changerace menu
					DB_GetAllXP( id );
				}
				
				// We're not saving XP, so lets just change the user's race
				else
				{
					WC3_ChangeRaceStart( id );
				}
			}
			
			else
			{
				client_print( id, print_center, "Please join a team before selecting a race!" );
			}
		}
		case 9: {
			// Make sure the user is on a team!
			if ( SHARED_IsOnTeam( id ) )
			{
				g_menuPosition[id]--
				// Get the XP if we're saving XP
				if ( get_pcvar_num( CVAR_wc3_save_xp ) )
				{
					
					// This function will also display the changerace menu
					DB_GetAllXP( id );
				}
				
				// We're not saving XP, so lets just change the user's race
				else
				{
					WC3_ChangeRaceStart( id );
				}
			}
			
			else
			{
				client_print( id, print_center, "Please join a team before selecting a race!" );
			}
		}

		default: {
			if ( !WC3_Check() )
			{
				return PLUGIN_HANDLED;
			}
			
			// User pressed 0 (cancel)
			if ( get_pcvar_num( CVAR_wc3_races ) < 9 && key - 1 == get_pcvar_num( CVAR_wc3_races ) )
			{
				return PLUGIN_HANDLED;
			}
			
			// Save the current race data before we change
			DB_SaveXP( id, false );
			
			new iRace
			iRace = g_menuPosition[id] * 8 + key + 1;
			
			//=============================================================
			
			 if(iRace == 9 ) 
		{ 
			
			if(!(get_user_flags(id) & ADMIN_LEVEL_H) && get_pcvar_num(CVAR_wc3_draenei_vip) == 1) 
			{   
	   
			ChatColor( id,"!g* [!t %s!g ] This Race is only for!t VIP",g_MODclient);
			MOTD_Vip(id);
			return PLUGIN_HANDLED; 
			
			}
		}
		
		 if(iRace == 10 ) 
		{ 
			
			if(!(get_user_flags(id) & ADMIN_LEVEL_H) && get_pcvar_num(CVAR_wc3_worgen_vip) == 1) 
			{   
	   
			ChatColor( id,"!g* [!t %s!g ] This Race is only for!t VIP",g_MODclient);
			MOTD_Vip(id);
			return PLUGIN_HANDLED; 
			
			}
		}
		 if(iRace == 11 ) 
		{ 
			
			if(!(get_user_flags(id) & ADMIN_LEVEL_H) && get_pcvar_num(CVAR_wc3_bloodelf_vip) == 1) 
			{   
	   
			ChatColor( id,"!g* [!t %s!g ] This Race is only for!t VIP",g_MODclient);
			MOTD_Vip(id);
			return PLUGIN_HANDLED; 
			
			}
		}
		
		 if(iRace == 12 ) 
		{ 
			
			if(!(get_user_flags(id) & ADMIN_LEVEL_H) && get_pcvar_num(CVAR_wc3_troll_vip) == 1) 
			{   
	   
			ChatColor( id,"!g* [!t %s!g ] This Race is only for!t VIP",g_MODclient);
			MOTD_Vip(id);
			return PLUGIN_HANDLED; 
			
			}
		}
		 if(iRace == 13 ) 
		{ 
			
			if(!(get_user_flags(id) & ADMIN_LEVEL_H) && get_pcvar_num(CVAR_wc3_warlock_vip) == 1) 
			{   
	   
			ChatColor( id,"!g* [!t %s!g ] This Race is only for!t VIP",g_MODclient);
			MOTD_Vip(id);
			return PLUGIN_HANDLED; 
			
			}
		}
	
		 if(iRace == 14 ) 
		{ 
			
			if(!(get_user_flags(id) & ADMIN_LEVEL_H) && get_pcvar_num(CVAR_wc3_priest_vip) == 1) 
			{   
	   
			ChatColor( id,"!g* [!t %s!g ] This Race is only for!t VIP",g_MODclient);
			MOTD_Vip(id);
			return PLUGIN_HANDLED; 
			
			}
		}
		
		 if(iRace == 15 ) 
		{ 
			
			if(!(get_user_flags(id) & ADMIN_LEVEL_H) && get_pcvar_num(CVAR_wc3_death_vip) == 1) 
			{   
	   
			ChatColor( id,"!g* [!t %s!g ] This Race is only for!t VIP",g_MODclient);
			MOTD_Vip(id);
			return PLUGIN_HANDLED; 
			
			}
		}

		 if(iRace == 16 ) 
		{ 
			
			if(!(get_user_flags(id) & ADMIN_LEVEL_H) && get_pcvar_num(CVAR_wc3_druid_vip) == 1) 
			{   
	   
			ChatColor( id,"!g* [!t %s!g ] This Race is only for!t VIP",g_MODclient);
			MOTD_Vip(id);
			return PLUGIN_HANDLED; 
			
			}
		}
 
 
 /*
 if(!(get_user_flags(id) & ADMIN_LEVEL_H) && get_pcvar_num(CVAR_wc3_shopmenu3_vip) == 1) 
{   
	   
			ChatColor( id,"!g* [!t %s!g ] This Item is only for!t VIP",g_MODclient);
			MOTD_Vip(id);
			return PLUGIN_HANDLED;
}
		
*/			
 
 
 
			//=====================================================================
 
			// User currently has a race
			if ( p_data[id][P_RACE] != 0 )
			{
				
				// Change the user's race at the start of next round
				if ( iRace != p_data[id][P_RACE] )
				{
					
					// Special message for csdm
					if ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 )
					{
						client_print( id, print_center, "Your race will be changed when you respawn" );
					}	
					else
					{
						client_print( id, print_center, "%L", id, "CENTER_CHANGED_NEXT" );
					}
					
					p_data[id][P_CHANGERACE] = iRace;
				}
				
				// Do nothing
				else
				{
					p_data[id][P_CHANGERACE] = 0;
				}
			}
			
			// User doesn't have a race so give it to him!!!
			else
			{
				WC3_SetRace( id, iRace );
			}
			return PLUGIN_HANDLED;
		}
	}
	return PLUGIN_HANDLED
}

public MENU_ReplaceItem( id )
{

	new szMenu[512] = "", pos = 0;
	new iKeys = (1<<9)|(1<<0)|(1<<1)|(1<<2);

	// Add the menu header
	pos += format( szMenu[pos], 511-pos, "%L^n^n", id, "MENU_REPLACE_ITEM" );

	new szItemName[64], szItemName2[64], szItemName3[64];
	LANG_GetItemName( g_iShopMenuItems[id][ITEM_SLOT_ONE], id, szItemName, 63 );
	LANG_GetItemName( g_iShopMenuItems[id][ITEM_SLOT_TWO], id, szItemName2, 63 );
	LANG_GetItemName( g_iShopMenuItems[id][ITEM_SLOT_THREE], id, szItemName3, 63 );

	// Add the items
	pos += format( szMenu[pos], 511-pos, "\r1.\w %s^n", szItemName );
	pos += format( szMenu[pos], 511-pos, "\r2.\w %s^n", szItemName2 );
	pos += format( szMenu[pos], 511-pos, "\r3.\w %s^n", szItemName3 );


	// Add the exit option
	pos += format( szMenu[pos], 511-pos, "^n\r0.\w %L", id, "WORD_EXIT" );

	// Show the menu
	show_menu( id, iKeys, szMenu, -1 );

	return;
}

public _menu_ReplaceItem( id, iKey ) 
 { 
 if ( !WC3_Check() || iKey == 9 ) 
 { 
 return PLUGIN_HANDLED; 
 } 
 
 // Remove item from item slot one 
 if ( iKey == 0 ) 
 { 
 ITEM_Remove( id, ITEM_SLOT_ONE ) 
 } 
 
 // Remove item from itemslot two 
 else if ( iKey == 1 ) 
 { 
 ITEM_Remove( id, ITEM_SLOT_TWO ) 
 } 
 else if ( iKey == 2 ) 
 { 
 ITEM_Remove( id, ITEM_SLOT_THREE ); 
 } 
 
 // Then the user typed "rings" 
 if ( g_iFutureItem[id] == -3 ) 
 { 
 ITEM_BuyRings( id ); 
 } 
 else
 { 
 ITEM_Buy( id, g_iFutureItem[id] ); 
 } 
 
 return PLUGIN_HANDLED; 
 }

public MENU_Shopmenu( id, iStart )
{

	if ( !ITEM_MenuCanBuyCheck( id ) )
	{
		return;
	}

	// Shopmenu2 can't display if we don't have the correct number of races!
	if ( iStart == MAX_PAGE_ITEMS && get_pcvar_num( CVAR_wc3_races ) <= 4 )
	{
		return;
	}

	new szMenu[512], szItemName[64], pos = 0, i, iItemID;
	new iKeys = (1<<9);

	// Add the header
	if ( iStart == 0 )
	{
		pos += format( szMenu[pos], 511-pos, "%L", id, "MENU_BUY_ITEM" );
	}

	// "Shopmenu 2"
	else if ( iStart == MAX_PAGE_ITEMS )
	{
		pos += format( szMenu[pos], 511-pos, "%L", id, "MENU_BUY_ITEM2" );
	}
	
	// "Shopmenu 3"
	else if ( iStart == 18 )
	{
		pos += format( szMenu[pos], 511-pos, "%L", id, "MENU_BUY_ITEM3" );
	}
	
	else if ( iStart == 27 )
	{
		pos += format( szMenu[pos], 511-pos, "%L", id, "MENU_BUY_ITEM4" );
	}

	// Lets add the items to the menu!  
   for ( i = 0; i < MAX_PAGE_ITEMS; i++ )  
   {  
    iItemID = iStart + i;  
    
    LANG_GetItemName( iItemID, id, szItemName,charsmax(szItemName));  
    
    new iMoney = SHARED_GetUserMoney( id );  
        
    new iItemCost = ITEM_Cost( id, iItemID );  
        
    if( iMoney < iItemCost )  
    {  
    pos += format( szMenu[pos], charsmax(szMenu)-pos, "\d%d. %s\d\R%d^n", i + 1, szItemName, ITEM_Cost( id, iItemID ) );  
    }  
    else
    {  
    pos += format( szMenu[pos], charsmax(szMenu)-pos, "\r%d.\w %s\r\R%d^n", i + 1, szItemName, ITEM_Cost( id, iItemID ) );  
    }  
        
    iKeys |= (1<<i);  
        
    
   }
	pos += format( szMenu[pos], 511-pos, "^n\r0.\w %L", id, "WORD_EXIT" );

	show_menu( id, iKeys, szMenu, -1 );
}

public _MENU_Shopmenu1( id, iKey )
{
	if ( !WC3_Check() || iKey == 9 )
	{
		return PLUGIN_HANDLED;
	}

	ITEM_Buy( id, iKey );

	return PLUGIN_HANDLED;
}

public _MENU_Shopmenu2( id, iKey )
{
	if ( !WC3_Check() || iKey == 9 )
	{
		return PLUGIN_HANDLED;
	}

	iKey += MAX_PAGE_ITEMS;
	
	ITEM_Buy( id, iKey );

	return PLUGIN_HANDLED;
}



public _MENU_Shopmenu3( id, iKey )
{
	if ( !WC3_Check() || iKey == 9 )
		return PLUGIN_HANDLED;

	iKey += 18;

	ITEM_Buy( id, iKey );

	return PLUGIN_HANDLED;
}

public _MENU_Shopmenu4( id, iKey )
{
	if ( !WC3_Check() || iKey == 9 )
		return PLUGIN_HANDLED;

	iKey += 27;

	ITEM_Buy( id, iKey );

	return PLUGIN_HANDLED;
}


public MENU_SelectSkill( id )
{

	// User has no race, how can we select skills?!?
	if ( p_data[id][P_RACE] == 0 )
	{
		//set_hudmessage(200, 100, 0, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 2)
		WC3_StatusText( id, TXT_TOP_CENTER, "%L", id, "SELECT_RACE_BEFORE_SKILLS" );

		return;
	}

	// They don't choose skills when it's random
	/*else if ( p_data[id][P_RACE] == RACE_CHAMELEON && get_pcvar_num( CVAR_wc3_cham_random ) )
	{
		//WC3_StatusText( id, TXT_TOP_CENTER, "%s", "Chameleons can't select skills!" );
		CHAM_ConfigureSkills( id );

		return;
	}
	*/

	// Lets make sure the user has some available skill points
	new iSkillsUsed = SM_TotalSkillPointsUsed( id );
	if ( iSkillsUsed >= p_data[id][P_LEVEL] )
	{

		//set_hudmessage(200, 100, 0, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 2)
		WC3_StatusText( id, TXT_TOP_CENTER, "%L", id, "ALREADY_SELECTED_SKILL_POINTS" );

		return;
	}

	// Bots don't need a menu now do they??
	if ( is_user_bot( id ) )
	{
		// No race has been selected yet!!
		if ( !SM_SkillAvailable( id ) )
		{
			return;
		}
		
		// Keep giving the bot a random ID until we are full!
		while ( iSkillsUsed < p_data[id][P_LEVEL] )
		{
			SM_GiveRandomSkillPoint( id );

			iSkillsUsed = SM_TotalSkillPointsUsed( id );
		}

		return;
	}

	// OK set up a menu!!!

	new szMsg[512], pos = 0, szSkillName[64];
	new iSkillCounter = 0, iSkillID = 0, iKeys = (1<<9), iSkillLevel;

	// Add the menu header
	pos += formatex( szMsg[pos], 512-pos, "%L", id, "MENU_SELECT_SKILL" );

	iSkillID = SM_GetSkillByPos( id, iSkillCounter );

	while ( iSkillID != -1 )
	{
		iSkillLevel = SM_GetSkillLevel( id, iSkillID, 4 );

		LANG_GetSkillName( iSkillID , id, szSkillName, 63, 1 );
		
		// Add the trainable skills to the menu
		if ( SM_GetSkillType( iSkillID ) == SKILL_TYPE_TRAINABLE )
		{

			// Only add it to the menu if they don't have level 3 already!
			if ( iSkillLevel < MAX_SKILL_LEVEL )
			{

				// User isn't high enough of a level to select this skill yet
				if ( p_data[id][P_LEVEL] <= 2 * iSkillLevel )
				{
					//pos += formatex( szMsg[pos], 512-pos, "\d" );
					pos += formatex( szMsg[pos], 512-pos, "^n\d%d.\d %s (\d%L %d\d)\d", iSkillCounter+1, szSkillName, id, "WORD_LEVEL", iSkillLevel + 1 );
				}

				// Then the user can choose it!
				else
				{
					iKeys |= (1<<iSkillCounter);
					pos += formatex( szMsg[pos], 512-pos, "^n\r%d.\w %s (\r%L %d\w)\w", iSkillCounter+1, szSkillName, id, "WORD_LEVEL", iSkillLevel + 1 );
				}

				
			}
		}
		
		// Add the ultimate to the menu
		else if ( SM_GetSkillType( iSkillID ) == SKILL_TYPE_ULTIMATE )
		{

			if ( iSkillLevel < MAX_ULTIMATE_LEVEL )
			{
				// User can't choose ultimate yet :/
				if ( p_data[id][P_LEVEL] <= 5 + 5 * iSkillLevel )
				{
					//pos += formatex( szMsg[pos], 512-pos, "\d" );
					pos += formatex( szMsg[pos], 512-pos, "^n\d%d.\d %L:\d %s\d (\d%L %d\d)\d", iSkillCounter+1, id, "WORD_ULTIMATE", szSkillName, id, "WORD_LEVEL", iSkillLevel + 1 );
				}

				// Then the user is level 6 or above and can select their ultimate!
				else
				{
					iKeys |= (1<<iSkillCounter);
					pos += formatex( szMsg[pos], 512-pos, "^n\r%d.\w %L:\r %s\w (\r%L %d\w)\w", iSkillCounter+1, id, "WORD_ULTIMATE", szSkillName, id, "WORD_LEVEL", iSkillLevel + 1 );
				}

				
			}
		}

		iSkillCounter++;
		iSkillID = SM_GetSkillByPos( id, iSkillCounter );
	}

	// Add the cancel button to the menu
	pos += formatex( szMsg[pos], 512-pos, "^n^n\r0.\w %L", id, "WORD_CANCEL" );

	// Show the menu!
	show_menu( id, iKeys, szMsg, -1 );

	return;
}

public _MENU_SelectSkill( id, iKey )
{

	if ( !WC3_Check() || iKey == 9 )
	{
		return PLUGIN_HANDLED;
	}

	// Determine which key was just selected
	new iSkillID = SM_GetSkillByPos( id, iKey );

	// Set up the skill!
	SM_SetSkill( id, iSkillID );
	
	new iSkillsUsed = SM_TotalSkillPointsUsed( id );
	
	// Then they have another skill to select!!
	if ( iSkillsUsed < p_data[id][P_LEVEL] )
	{
		MENU_SelectSkill( id );
	}

	// No more, lets show them their latest level/XP
	else
	{
		WC3_ShowBar( id );
	}

	return PLUGIN_HANDLED;
}
/* AMXX-Studio Notes - DO NOT MODIFY BELOW HERE
*{\\ rtf1\\ ansi\\ deff0{\\ fonttbl{\\ f0\\ fnil Tahoma;}}\n\\ viewkind4\\ uc1\\ pard\\ lang1033\\ f0\\ fs16 \n\\ par }
*/
