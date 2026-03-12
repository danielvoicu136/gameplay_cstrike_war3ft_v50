//=====================================================================================================================================================
// Credite Aragon . Love .dat saving :X 
//==================================================================

new PlayerCredits[33];
new File[128], SymbolsName;


//------| Change Name |------//
public ChangeName(id, buffer) {
	if(!is_user_connected(id))
		return FMRES_IGNORED;
	
	static Name[32], Val[32];
	get_user_name(id, Name, sizeof Name - 1);
	engfunc(EngFunc_InfoKeyValue, buffer, "name", Val, sizeof Val - 1);
	
	if(equal(Val, Name))
		return FMRES_IGNORED;
	
	set_task(0.2, "client_connect", id);
	return FMRES_SUPERCEDE;
}

public set_user_credits(id, credits) {
	PlayerCredits[id] = credits;
	
	SaveCredits(id)
}
public get_user_credits(id) {
	return PlayerCredits[id]
}

//==============================================================================================================
public Depozit(id) {

if((get_user_flags(id) & ADMIN_LEVEL_H))
			 {
					if(cs_get_user_money(id) >= 8000) {
						if(get_user_credits(id)<get_pcvar_num( CVAR_wc3_max_gold_vip ))
							{
								ChatColor(id, "!g* [!t WAR3FT!g ] You changed!t 8000 $!g in!t 1 Gold ");
								set_user_credits(id, get_user_credits(id) + 1);
								cs_set_user_money(id, cs_get_user_money(id) - 8000);
							}
														}
						else {
								ChatColor(id, "!g* [!t WAR3FT!g ] You need!t 8000 $!g to buy!t 1 Gold");	
							 }
			 
			 }

else {	
		if(cs_get_user_money(id) >= 8000) {
					if(get_user_credits(id)<get_pcvar_num( CVAR_wc3_max_gold ))
					{
						ChatColor(id, "!g* [!t WAR3FT!g ] You changed!t 8000 $!g in!t 1 Gold ");
						set_user_credits(id, get_user_credits(id) + 1);
						cs_set_user_money(id, cs_get_user_money(id) - 8000);
					}
											}
		else {
		ChatColor(id, "!g* [!t WAR3FT!g ] You need!t 8000 $!g to buy!t 1 Gold");	
			}
	
	}
	
	
	return PLUGIN_HANDLED;
}


public Depozit_2(id) {

if((get_user_flags(id) & ADMIN_LEVEL_H))
			 {
					if(cs_get_user_money(id) >= 16000) {
						if(get_user_credits(id) + 2 <= get_pcvar_num( CVAR_wc3_max_gold_vip ))
							{
								ChatColor(id, "!g* [!t WAR3FT!g ] You changed!t 16000 $!g in!t 2 Gold ");
								set_user_credits(id, get_user_credits(id) + 2);
								cs_set_user_money(id, cs_get_user_money(id) - 16000);
							}
														}
						else {
								ChatColor(id, "!g* [!t WAR3FT!g ] You need!t 16000 $!g to buy!t 2 Gold");	
							 }
			 
			 }

else {	
		if(cs_get_user_money(id) >= 16000) {
					if(get_user_credits(id) + 2 <= get_pcvar_num( CVAR_wc3_max_gold ))
					{
						ChatColor(id, "!g* [!t WAR3FT!g ] You changed!t 16000 $!g in!t 2 Gold ");
						set_user_credits(id, get_user_credits(id) + 2);
						cs_set_user_money(id, cs_get_user_money(id) - 16000);
					}
											}
		else {
		ChatColor(id, "!g* [!t WAR3FT!g ] You need!t 16000 $!g to buy!t 2 Gold");	
			}
	
	}
	
	
	return PLUGIN_HANDLED;
}



//====================================================




public Retrage(id) {

	if(PlayerCredits[id]>=1) {
		ChatColor(id, "!g* [!t WAR3FT!g ] You changed!t 1 Gold!g in!t 8000 $");
		set_user_credits(id, get_user_credits(id) - 1);
		cs_set_user_money(id, cs_get_user_money(id) + 8000);
	}
	else {
		ChatColor(id, "!g* [!t WAR3FT!g ] You need!t 1 Gold!g to buy!t 8000 $");	
	}
	return PLUGIN_HANDLED;
}

public Retrage_2(id) {

	if(PlayerCredits[id]>=2) {
		ChatColor(id, "!g* [!t WAR3FT!g ] You changed!t 2 Gold!g in!t 16000 $");
		set_user_credits(id, get_user_credits(id) - 2);
		cs_set_user_money(id, cs_get_user_money(id) + 16000);
	}
	else {
		ChatColor(id, "!g* [!t WAR3FT!g ] You need!t 2 Gold!g to buy!t 16000 $");	
	}
	return PLUGIN_HANDLED;
}




public GiveCredits(id) {
	new Arg1[32], Arg2[6];
	
	read_argv(1, Arg1, 31);
	read_argv(2, Arg2, 5);
	
	new Target = cmd_target(id, Arg1, 8);
	new Ammount = str_to_num(Arg2);
	
	if(Target == id) {
		ChatColor(id, "!g* [!t WAR3FT!g ] You can't give gold to!t yourself");
	}
	else if(!Target) {
		ChatColor(id, "!g* [!t WAR3FT!g ] This player dosen't exist");
	}
	
	else if(Ammount <= 0) {
		ChatColor(id, "!g* [!t WAR3FT!g ] This Gold number is invalid");
	}
	else if(Ammount > get_user_credits(id)){
		ChatColor(id, "!g* [!t WAR3FT!g ] You can't give more Gold than you have");
	}
	else {		
		new TargetName[32], Name[32];
		get_user_name(Target, TargetName, 31);
		get_user_name(id, Name, 31);
		
		set_user_credits(id, get_user_credits(id) -  Ammount)
		//ColorChat(id, "!x03I-ai dat lui!x04 %s!x03 suma de!x04 %d$", TargetName, Ammount);
		ChatColor(id, "!g* [!t WAR3FT!g ] You gave!t %d Gold!g to!t %s", Ammount, TargetName);
		
		set_user_credits(Target, get_user_credits(Target) + Ammount)
		//ColorChat(Target, "!x03Ai primit de la !x04%s!x03 suma de!x04 %d$", Name, Ammount);
		ChatColor(Target, "!g* [!t WAR3FT!g ] You received!t %d Gold !gfrom!t %s", Ammount, Name);
	}
}


public Show_Credits(id) {
	ChatColor(id, "!g* [!t WAR3FT!g ] You have!t %d Gold", PlayerCredits[id]);
	return PLUGIN_HANDLED;
}


public Give_Credits(id, level, cid) {
	if(!cmd_access(id, level, cid, 2)) {
		return PLUGIN_HANDLED;
	}
	new arg[23], gplayers[32], num, i, players, name[32];
	get_user_name(id, name, 31);
	read_argv(1, arg, 23);
	new give_credits[5];
	read_argv(2, give_credits, charsmax(give_credits));
	new Credits = str_to_num(give_credits);
	if(equali(arg, "@T")) {
		get_players(gplayers, num, "e", "TERRORIST");
		for(i = 0; i < num; i++) {
			players = gplayers[i];
			if(!is_user_connected(players))
				continue;
				if((get_user_flags(players) & ADMIN_LEVEL_H))
						{
								if(get_user_credits(players) + Credits <= get_pcvar_num( CVAR_wc3_max_gold_vip ))
									{
										set_user_credits(players, get_user_credits(players) + Credits);
									}
									else { 
											set_user_credits(players, get_pcvar_num( CVAR_wc3_max_gold_vip ));
										 }
						}
			 else {
			 if(get_user_credits(players) + Credits <= get_pcvar_num( CVAR_wc3_max_gold ))
									{
										set_user_credits(players, get_user_credits(players) + Credits);
									}
									else { 
											set_user_credits(players, get_pcvar_num( CVAR_wc3_max_gold ));
										 }
				  }
		}
		switch(get_cvar_num("amx_show_activity")) {
			case 1: ChatColor(0, "!g*!t ADMIN!g give!t %i Gold!g to all!t Terrorist", Credits);
			case 2: ChatColor(0, "!g*!t %s!g give!t %i Gold!g to all!t Terrorist", name, Credits);
			}
	}
	else if(equali(arg, "@CT")) {
		get_players(gplayers, num, "e", "CT");
		for(i = 0; i < num; i++) {
			players = gplayers[i];
			if(!is_user_connected(players))
				continue;
			if((get_user_flags(players) & ADMIN_LEVEL_H))
						{
								if(get_user_credits(players) + Credits <= get_pcvar_num( CVAR_wc3_max_gold_vip ))
									{
										set_user_credits(players, get_user_credits(players) + Credits);
									}
									else { 
											set_user_credits(players, get_pcvar_num( CVAR_wc3_max_gold_vip ));
										 }
						}
			 else {
			 if(get_user_credits(players) + Credits <= get_pcvar_num( CVAR_wc3_max_gold ))
									{
										set_user_credits(players, get_user_credits(players) + Credits);
									}
									else { 
											set_user_credits(players, get_pcvar_num( CVAR_wc3_max_gold ));
										 }
				  }
		}
		switch(get_cvar_num("amx_show_activity")) {
			case 1: ChatColor(0, "!g*!t ADMIN!g give!t %i Gold!g to all!t Counter-Terrorist", Credits);
			case 2: ChatColor(0, "!g*!t %s!g give!t %i Gold!g to all!t Counter-Terrorist", name, Credits);
			}
	}
	if(equali(arg, "@All")) {
		get_players(gplayers, num, "a");
		for(i = 0; i < num; i++) {
			players = gplayers[i];
			if(!is_user_connected(players))
				continue;
			if((get_user_flags(players) & ADMIN_LEVEL_H))
						{
								if(get_user_credits(players) + Credits <= get_pcvar_num( CVAR_wc3_max_gold_vip ))
									{
										set_user_credits(players, get_user_credits(players) + Credits);
									}
									else { 
											set_user_credits(players, get_pcvar_num( CVAR_wc3_max_gold_vip ));
										 }
						}
			 else {
			 if(get_user_credits(players) + Credits <= get_pcvar_num( CVAR_wc3_max_gold ))
									{
										set_user_credits(players, get_user_credits(players) + Credits);
									}
									else { 
											set_user_credits(players, get_pcvar_num( CVAR_wc3_max_gold ));
										 }
				  }
		}
		switch(get_cvar_num("amx_show_activity")) {
			case 1: ChatColor(0, "!g*!t ADMIN!g give!t %i Gold!g to all!t Players", Credits);
			case 2: ChatColor(0, "!g*!t %s!g give!t %i Gold!g to all!t Players", name, Credits);
			}
	}
	new player = cmd_target(id, arg, 11);
	if(!player) {
		return PLUGIN_HANDLED;
	}
	if((get_user_flags(players) & ADMIN_LEVEL_H))
						{
								if(get_user_credits(players) + Credits <= get_pcvar_num( CVAR_wc3_max_gold_vip ))
									{
										set_user_credits(players, get_user_credits(players) + Credits);
									}
									else { 
											set_user_credits(players, get_pcvar_num( CVAR_wc3_max_gold_vip ));
										 }
						}
			 else {
			 if(get_user_credits(players) + Credits <= get_pcvar_num( CVAR_wc3_max_gold ))
									{
										set_user_credits(players, get_user_credits(players) + Credits);
									}
									else { 
											set_user_credits(players, get_pcvar_num( CVAR_wc3_max_gold ));
										 }
				  }
	switch(get_cvar_num("amx_show_activity")) {
		case 1: ChatColor(player, "!g*!t ADMIN!g gave you !t %i Gold", Credits);
		case 2: ChatColor(player, "!g*!t %s!g gave you!t %i Gold", name, Credits);
		}
	return PLUGIN_HANDLED;
}

public Reset_Credits(id, level, cid) {
	if(!cmd_access(id, level, cid, 2)) {
		return PLUGIN_HANDLED;
	}
	new arg[23], gplayers[32], num, i, players, name[32];
	get_user_name(id, name, 31);
	read_argv(1, arg, 23);
	if(equali(arg, "@T")) {
		get_players(gplayers, num, "e", "TERRORIST");
		for(i = 0; i < num; i++) {
			players = gplayers[i];
			if(!is_user_connected(players))
				continue;
			set_user_credits(players, 0);
		}
		switch(get_cvar_num("amx_show_activity")) {
			case 1: ChatColor(0, "!g*!t ADMIN!g reset!t Gold!g to all!t Terrorist");
			case 2: ChatColor(0, "!g*!t %s!g reset!t Gold!g to all!t Terrorist", name);
			}
	}
	
	else if(equali(arg, "@CT")) {
		get_players(gplayers, num, "e", "CT");
		for(i = 0; i < num; i++) {
			players = gplayers[i];
			if(!is_user_connected(players))
				continue;
			set_user_credits(players, 0);
		}
		switch(get_cvar_num("amx_show_activity")) {
			case 1: ChatColor(0, "!g*!t ADMIN!g reset!t Gold!g to all!t Counter-Terrorist");
			case 2: ChatColor(0, "!g*!t %s!g reset!t Gold!g to all!t Counter-Terrorist", name);
			}
	}
	if(equali(arg, "@All")) {
		get_players(gplayers, num, "a");
		for(i = 0; i < num; i++) {
			players = gplayers[i];
			if(!is_user_connected(players))
				continue;
			set_user_credits(players, 0);
		}
		switch(get_cvar_num("amx_show_activity")) {
			case 1: ChatColor(0, "!g*!t ADMIN!g reset!t Gold!g to all!t Players");
			case 2: ChatColor(0, "!g*!t %s!g reset!t Gold!g to all!t Players", name);
			}
	}
	new player = cmd_target(id, arg, 11);
	if(!player) {
		return PLUGIN_HANDLED;
	}
	set_user_credits(player, 0);
	switch(get_cvar_num("amx_show_activity")) {
		case 1: ChatColor(player, "!g* !tADMIN!g reset your!t Gold");
			case 2: ChatColor(player, "!g*!t %s!g reset your!t Gold", name);
		}
	return PLUGIN_HANDLED;
}

//------| Save Credits |------//
public SaveCredits(id) {
	new Name[32];
	get_user_name(id, Name, 31);

	static Data[1024]
	formatex(Data, sizeof(Data) - 1, "^"%i^"", PlayerCredits[id])
	
	new Save[512]
	format(Save, 511, "^"%s^" %s", Name, Data)
	
	new Line[128], Linie, IsPlayer = false, Arg1[32]
	
	new FileOpen = fopen(File, "rt")
	while(!feof(FileOpen)) {
		fgets(FileOpen, Line, 127)
		trim(Line)

		parse(Line, Arg1, 31)
		
		if (equali(Arg1, Name)) {
			write_file(File, Save, Linie)
			IsPlayer = true
			break
		}
		
		Linie++
	}
	fclose(FileOpen)
	if (!IsPlayer) {
		write_file(File, Save, -1)
	}
}

//------| Loading Credits |------//
public LoadCredits(id) {
	new Name[32];
	get_user_name(id, Name, 31);
	
	new Line[128], IsPlayer = false, Arg1[32], Arg2[32];
	
	new FileOpen = fopen(File, "rt")
	while(!feof(FileOpen)) {
		fgets(FileOpen, Line, 127)
		trim(Line)
		
		parse(Line, Arg1, 31, Arg2, 31)
		
		if (equali(Arg1, Name)) {
			PlayerCredits[id] = str_to_num(Arg2)
			IsPlayer = true
			break
		}
	}
	fclose(FileOpen)
	
	if (!IsPlayer) {
		PlayerCredits[id] = 1
	}
}





public DepozitXP_A(id) {

new XP_TEMP = p_data[id][P_XP] - 1500;

if( XP_TEMP >= 0)
{		
		if((get_user_flags(id) & ADMIN_LEVEL_H))
			 {
		if(get_user_credits(id)<get_pcvar_num( CVAR_wc3_max_gold_vip ))
		{p_data[id][P_XP]-=1500;
		ChatColor(id, "!g* [!t WAR3FT!g ] You changed!t 1500 Experience!g in!t 1 Gold ");
		set_user_credits(id, get_user_credits(id) + 1);
		}
		}
		else {
		
		if(get_user_credits(id)<get_pcvar_num( CVAR_wc3_max_gold ))
		{p_data[id][P_XP]-=1500;
		ChatColor(id, "!g* [!t WAR3FT!g ] You changed!t 1500 Experience!g in!t 1 Gold ");
		set_user_credits(id, get_user_credits(id) + 1);
		}
		
		
		}
		
		
		
		
		XP_Check( id );
		
}
else {
		ChatColor(id, "!g* [!t WAR3FT!g ] You need!t 1500 Experience!g to buy!t 1 Gold");	
	}
	return PLUGIN_HANDLED;
}

public RetrageXP_A(id) {
	if(get_user_credits(id)>=1) {
		ChatColor(id, "!g* [!t WAR3FT!g ] You changed!t 1 Gold!g in!t 1500 Experience");
		set_user_credits(id, get_user_credits(id) - 1);
		p_data[id][P_XP]+=1500;
		XP_Check( id );
		
	}
	else {
		ChatColor(id, "!g* [!t WAR3FT!g ] You need!t 1 Gold!g to buy!t 1500 Experience");	
	}
	return PLUGIN_HANDLED;
	
}



public DepozitXP_B(id) {

new XP_TEMP = p_data[id][P_XP] - 7500;

if( XP_TEMP >= 0)
{		
			if((get_user_flags(id) & ADMIN_LEVEL_H))
			 {
		if(get_user_credits(id)<get_pcvar_num( CVAR_wc3_max_gold_vip ))
		{p_data[id][P_XP]-=7500;
		ChatColor(id, "!g* [!t WAR3FT!g ] You changed!t 7500 Experience!g in!t 5 Gold ");
		set_user_credits(id, get_user_credits(id) + 5);
		}
			}
			else {
			if(get_user_credits(id)<get_pcvar_num( CVAR_wc3_max_gold ))
		{p_data[id][P_XP]-=7500;
		ChatColor(id, "!g* [!t WAR3FT!g ] You changed!t 7500 Experience!g in!t 5 Gold ");
		set_user_credits(id, get_user_credits(id) + 5);
		}
			
			}
		
		
		
		XP_Check( id );
		
}
else {
		ChatColor(id, "!g* [!t WAR3FT!g ] You need!t 7500 Experience!g to buy!t 5 Gold");	
	}
	return PLUGIN_HANDLED;
}

public RetrageXP_B(id) {
	if(get_user_credits(id)>=5) {
		ChatColor(id, "!g* [!t WAR3FT!g ] You changed!t 5 Gold!g in!t 7500 Experience");
		set_user_credits(id, get_user_credits(id) - 5);
		p_data[id][P_XP]+=7500;
		XP_Check( id );
		
	}
	else {
		ChatColor(id, "!g* [!t WAR3FT!g ] You need!t 5 Gold!g to buy!t 7500 Experience");	
	}
	return PLUGIN_HANDLED;
	
}




