// ***************************************************************************
// Author: B. Josh Becker
// Description: This page contains defines as well as the variables used
// in this plugin
// ***************************************************************************

#define TASK_ITEMS			0		// Showing items in the HUD
#define TASK_SPAWN			32		// Respawning from revive
#define TASK_IMPALE			64		// Crypt Lord's Impale
#define TASK_BANISH			96		// Used to set the user's origin back to normal
#define TASK_SPAWNREMOVEGOD	128		// Gives the user godmode for a brief period after they respawn
#define TASK_EXPLOSION		160		// From Suicide Bomber
#define TASK_BEAMCYLINDER	192		// From Suicide Bomber
#define	TASK_GETINPUT		224		// Calls getuserinput function
#define TASK_COOLDOWN		256		// Ultimate Cooldown function
#define TASK_TRANSPORT		288		// Transport function for ITEM_MOLE
#define TASK_MOLE			320		// Used for mole + fan of knives
#define	TASK_WAVE			352		// Healing Wave
#define	TASK_REINCARNATION	384		// Weapon Reincarnation
#define	TASK_GLOW			416		// Calls glow_change
#define	TASK_REMOVEBUYZONE	448		// This will remove a buyzone
#define	TASK_HEX			480		// Jumper task (goomba)
#define	TASK_RESETSPEED		512		// Reset maxspeed (bash)
#define	TASK_ITEM_GLOVES	544		// Nade timer (gloves)
#define	TASK_UNHOLYSPEED	576		// Unholyspeed timer
#define	TASK_RESETGOD		608		// Reset god mode
#define	TASK_BLINKCHECK		640		// Check to see if the player teleported into an invalid location
#define	TASK_BLINKSTUCK		672		// Checks to see if a user is stuck after blinking
#define	TASK_BIGBADATTACKER	704		// _SH_ResetBigBadAttacker
#define	TASK_TELEPORT		736		// For teleporting someone w00t
//#define	TASK_TELEPORT		768		// Teleports the player
//#define	TASK_TELEFADEIN		800		// Calls telefadein function
//#define	TASK_UNSTICK		832		// "Unsticks" a stuck teleported player
#define	TASK_SEARCHTARGET	864		// Used by some ultimates
//#define TASK_WALKER			896		// Walker process
#define	TASK_ENTANGLEWAIT	928		// Used for entangling roots
#define	TASK_LIGHTNING		960		// Used for chain lightning
//#define	TASK_LIGHTSEARCH	992		// Used for chain lightning
#define	TASK_LIGHTNINGNEXT	1024	// Used for chain lightning
#define TASK_SPAWNPLAYER	1056	// Used to spawn a player (final spawn call)
#define TASK_GIVEITEMS		1088	// Used to give a player his items after spawning
#define	TASK_ITEM_RING	1120	// Used with rings of regeneration
#define	TASK_SILENCEBURST	1152
//#define	TASK_ONFIRE			1184	// Used with flamethrower
//#define	TASK_HEALNOW		1226	// Used with Healing Waves
#define	TASK_HEALNEXT		1258	// Used with Healing Waves
#define	TASK_LIGHT			1290	// Used with serpant wards
#define	TASK_SHIELD			1322	// Used to check for shield
#define	TASK_FUNNELS		1354	// Used with Swarming Locusts
#define	TASK_HETHROWEVENT	1386	// Used for nade trails
#define	TASK_MONEYLOOP		1428	// Used for displaying the money for DOD
#define TASK_TEMPENTITY		1460
#define TASK_ANKHGIVEITEMS	1492
#define TASK_HELM			1524
#define	TASK_REINCCHECK		1556
#define TASK_SAVE			1588	// Used for saving XP
//#define TASK_UDELAY			1620	// Ultimate Delay Function
//#define TASK_BURN           1652
#define TASK_BURNING		1684	// Used for Blood Mage Ultimate
#define TASK_FINDTARGET		1706	// Used for finding a target
#define TASK_ULTPING		1738	// Used to play the "ping" sound every second


#define TASK_BUYTIME		2000	// Checks for buytime
#define	TASK_CHECKVOTES		2002	// Used for checking the votes
#define	TASK_FTCONTROLLER	2003	// Used for automatic start/stop
#define	TASK_CHECKWAR3		2004
#define	TASK_EXECUTECONFIG	2005
#define	TASK_AFTERCONFIG	2006
#define	TASK_SETSQL			2007
//#define	TASK_SETLANGUAGE	2008
#define	TASK_SETVARIABLES	2009
#define	TASK_CLONETHINK		2010
//#define	TASK_CHECKMAP		2011
#define TASK_BOIDTHINK		2012
#define TASK_TARGETBOMBED	2013
//#define TASK_BOMBTIMER		2014
//#define TASK_WAR3CHECK		2015	// Checks the value of sv_warcraft3 every 5 seconds (better than checking it on every function call)
#define TASK_SIPHON			2016
#define TASK_ENDULTIMATE	2017
//#define TASK_BEFORE_ROUND_START		2018
#define TASK_MOLEFIX		3000
#define TASK_RESETSPAWNS	3001
#define TASK_UDELAY			3002		// Ultimate delay function

#define TASK_ABUNDENCE		4001		// Abundence fuction
#define TASK_RUN		4002		// Wild Run fuction
#define TASK_INVRESET		4003		// Functie la Sleep
#define TASK_SLEEP		4004
#define TASK_STEALTH		4005
#define TASK_TRREG			4006
#define TASK_BLDELF			4007

#define TASK_DRAIN			4008
#define TASK_MAGIC			4009
#define TASK_SEAL			4010
#define TASK_LIGHTWARD			4011
#define TASK_NATURA			4012
#define TASK_TESPRAY			4013
#define TASK_ONFIRE			4014



#define	TASK_DEATH_TOUCH	97855		// Death Touch





//----------------------------------------------------------------------------------------------

// From ../multiplayer source/dlls/player.cpp
#define ARMOR_RATIO	 0.7	// Armor Takes 30% of the damage (was .2 in the SDK)
#define ARMOR_BONUS  0.5	// Each Point of Armor is work 1/x points of health

#define TE_BEAMPOINTS		0
#define TE_EXPLOSION		3
#define	TE_TAREXPLOSION		4
#define TE_SMOKE			5
#define TE_BEAMENTS			8
#define	TE_LAVASPLASH		10
#define	TE_TELEPORT			11
#define TE_IMPLOSION		14
#define TE_SPRITETRAIL		15
#define TE_SPRITE			17
#define TE_BEAMCYLINDER		21
#define TE_BEAMFOLLOW		22
#define TE_STREAK_SPLASH	25
#define TE_ELIGHT			28
#define TE_LARGEFUNNEL		100
#define TE_FIZZ				105		// create alpha sprites inside of entity, float upwards
#define TE_BUBBLES			113		// create alpha sprites inside of box, float upwards
#define TE_SPRAY			120
#define TE_PLAYERATTACHMENT 124

#define	EF_BRIGHTFIELD		1

#define TE_EXPLFLAG_NONE	0

#define MAX_NAME_LENGTH 32
#define MAX_VAR_LENGTH 64 
#define RACE_SKILL_LENGTH 64
#define RACE_SKILL_LENGTH_F 63
#define RACE_NAME_LENGTH 64
#define RACE_NAME_LENGTH_F 63
#define ITEM_NAME_LENGTH 64
#define ITEM_NAME_LENGTH_F 63
#define SHORT_RACE_NAME_LENGTH 16
#define SHORT_RACE_NAME_LENGTH_F 15
#define SHORT_ITEM_NAME_LENGTH 32
#define SHORT_ITEM_NAME_LENGTH_F 31

#define TELEPORT_RADIUS			50
#define LIGHTNING_RANGE			500
#define ORB_DAMAGE				10			// Damage done by Orb of Annihilation

// CS AmmoX Types
#define AMMOX_338MAGNUM			1     // AWP
#define AMMOX_762NATO			2     // AK47, SCOUT, G3SG1
#define AMMOX_556NATOBOX		3     // MG
#define AMMOX_556NATO			4     // SG552, GALI, FAMAS, M4A1, AUG, SG550
#define AMMOX_BUCKSHOT			5     // M3, XM1014
#define AMMOX_45ACP				6     // MAC10, UMP45, USP
#define AMMOX_57MM				7     // P90, FIVESEVEN
#define AMMOX_50AE				8     // DEAGLE
#define AMMOX_357SIG			9     // P228
#define AMMOX_9MM				10     // MP5NAVY, TMP, GLOCK18, ELITE
#define AMMOX_FLASHBANG			11     // Flashbang
#define AMMOX_HEGRENADE			12     // HE Grenade
#define AMMOX_SMOKEGRENADE		13     // Smoke Grenade


#define HITGROUP_GENERIC		0 // none
#define HITGROUP_HEAD			1 // 1 << 1 = 2
#define HITGROUP_CHEST			2 // 1 << 2 = 4
#define HITGROUP_STOMACH		3 // 8
#define HITGROUP_LEFTARM		4 // 16
#define HITGROUP_RIGHTARM		5 // 32
#define HITGROUP_LEFTLEG		6 // 64
#define HITGROUP_RIGHTLEG		7 // 128

/*	 Weapon IDs	 */
#define CSW_WORLDSPAWN			0 

#if !defined CSW_GALIL
	#define CSW_GALIL			14
#endif
#if !defined CSW_FAMAS
	#define CSW_FAMAS			15
#endif

#define CSW_WAR3_MIN			51

#define	CSW_LIGHTNING			51
#define	CSW_SUICIDE				52
#define	CSW_IMMOLATE			53
#define	CSW_LOCUSTS				54
#define	CSW_SERPENTWARD			55
#define CSW_SHADOW				56
#define	CSW_THORNS				57
#define	CSW_CARAPACE			58
#define CSW_CARRION				59
#define CSW_ORB					60
#define CSW_CONCOCTION			61
#define CSW_BANISH				62

#define CSW_WAR3_MAX			62

// Should be equal to (CSW_WAR3_MIN - CSW_WAR3_MAX) + 1
#define MAX_CSW_S				12

// Race numbers
#define RACE_NONE				0
#define RACE_UNDEAD				1
#define RACE_HUMAN				2
#define RACE_ORC				3
#define RACE_ELF				4
#define RACE_BLOOD				5
#define RACE_SHADOW				6
#define RACE_WARDEN				7
#define RACE_CRYPT				8
#define RACE_DRAENEI				9
#define RACE_WORGEN				10
#define RACE_BLOODELF				11
#define RACE_TROLL				12
#define RACE_WARLOCK				13
#define RACE_PRIEST				14
#define RACE_DEATH				15
#define RACE_DRUID				16



// team ids 
#define UNASSIGNED 0 
#define TS 1 
#define CTS 2 
#define AUTO_TEAM 5 

// New team ID defines
#define TEAM_T		1
#define TEAM_CT		2

// To determine what game is running
#define GAME_CSTRIKE		1
#define GAME_CZERO			2
#define GAME_DOD			3

// Used with PB_SKINSWITCHED
#define SKIN_RESET					0
#define SKIN_SWITCH					1

#define KEY_1						0
#define KEY_2						1
#define KEY_3						2
#define KEY_4						3
#define KEY_5						4
#define KEY_6						5
#define KEY_7						6
#define KEY_8						7
#define KEY_9						8
#define KEY_0						9

#define XPOS						0
#define YPOS						1
#define ZPOS						2

#define DISPLAYLEVEL_NONE			0
#define DISPLAYLEVEL_SHOWRACE		1
#define DISPLAYLEVEL_SHOWGAINED		2
//#define DISPLAYLEVEL_SHOWBOTH		3
#define	DISPLAYLEVEL_SHOWRACECHAT	4

#define MAX_RACES					16

#define MAX_LEVELS					25

// ***************************************************************************
// The following section contains defines for the player_data array, it pretty much
// stores everything.  
//		P_ is within player_data
//		PB_ is within player_data_bool array
// ***************************************************************************
	// ***************************
	//		Start of info for player_data
	// ***************************

	#define P_RACE                  0		// Race
	//#define P_SKILL1                1		// Skill 1 level
	//#define P_SKILL2                2		// Skill 2 level
	//#define P_SKILL3                3		// Skill 4 level
	//#define P_ULTIMATE              4		// Ultimate level
	#define P_LEVEL					5		// Player Level
	#define P_XP                    6		// Current XP

	// Miscellaneous options
	#define P_SPECMODE				7		// Used to determine if the player is spectating or not
	#define P_SHOWRACEMENU			8		// Should we show the race menu when the player respawns?
	#define P_SHOWICONS				9		// Show player icons/levels for this player?
	#define P_CHANGERACE			10		// Holds the value of what race to change to when the following round starts

	// Used for weapon Reincarnation
	#define P_FLASHCOUNT			11		// Number of flash grenades bought that round
	#define	P_HECOUNT				12		// Number of HE's bought that round
	#define P_SMOKECOUNT			13		// Number of smoke grenades bought that round
	#define P_ARMORONDEATH			14		// Amount of armor the player had when he/she died
	#define P_LASTARMOR				15		// This will contain the previous value of P_ARMORONDEATH

	// Used by various ultimates/abilities
	#define P_TELEMENU				16		// Used by teleport
	#define P_TEAM					17		// Stores the player's team ID
	//#define P_SHADOWCOUNT			18		// Number of shadow strikes the player has left
	#define P_SERPENTCOUNT			19		// Number of serpent wards the player has left
	#define P_RINGS					20
	#define P_ULTIMATEDELAY			21
	#define P_RESPAWNBY				22		// Stores how the user is going to respawn

	// Used for DOD
	#define P_MONEY					23		// Amount of money the player has
	#define P_LIGHTCOUNT			24		// Number of serpent wards the player has left
	#define P_LAST					25
	// ***************************
	//		End of info for player_data
	// ***************************


	// ***************************
	//		Start of info for player_data_bool
	// ***************************

	// Miscellaneous
	#define PB_SKINSWITCHED			0		// Set if the user's skin has been changed
	#define PB_RESETSKILLS			1		// Does the player want to reset their skills in the next round?
	#define PB_CHANGINGTEAM			2		// Is the user currently changing his/her team?
	#define PB_DIEDLASTROUND		3		// Did the user died during the previous round?

	// Used for weapon Reincarnation
	#define PB_DEFUSE				4		// Player had a defuse kit when he/she died?
	#define PB_SHIELD				5		// Player had a shield when he/she died?
	#define PB_NIGHTVISION			6		// Player had nightvision when he/she died?
	#define PB_USP_SILENCED			28		// USP silenced on death?
	#define PB_M4A1_SILENCED		29		// M4A1 silenced on death?
	#define PB_GLOCK_BURST			30		// Glock in burst mode on death?
	#define PB_FAMAS_BURST			31		// Famas in burst mode on death?


	// Used by various ultimates/abilities
	#define PB_GIVEITEMS			7		// Tells weapon controller function to give the player his items after respawning
	#define PB_NADEJUSTRECEIVED		8		// Used with flaming gloves... (removable?)
	#define PB_MOLE					9		// Is the player a mole?
	#define PB_PHOENIX				10		// Will this player have phoenix?
	#define PB_WARDENBLINK			11		// Does this player have blink enabled?
	#define PB_SUICIDEATTEMPT		12		// Has this player made a suicide attempt for undead's ultimate?
	#define PB_ISBURNING			13		// Is the player burning from the immolate ultimate?
	#define PB_STUNNED				14
	#define PB_SLOWED				15
	#define PB_ISSEARCHING			16
	#define PB_LIGHTNINGHIT			17
	#define PB_INVIS				18
	#define PB_HEXED				19		// Is the player hexed? (All abilities are disabled)
	#define PB_JUSTJOINED			20
	#define PB_ISCONNECTED			21
	#define PB_GODMODE				22

	#define PB_HAS_SPAWNED			23		// Has the player previously spawned this round?
	#define PB_CAN_RENDER			24

	#define PB_NO_DAMAGE			25
	#define PB_BIGBAD_ATTACKER		26		// This user is allowed to attack a user running big bad voodoo!

	#define PB_ISPLANTING			27		// Set to true if the user is planting the bomb

//	#define PB_CHAM_CONFIGURED		28		// Has chameleon been configured?

	#define PB_LAST					32
	// ***************************
	//		End of info for player_data_bool
	// ***************************
// ***************************************************************************
//	End player array information
// ***************************************************************************


// What is the user going to respawn by?
#define RESPAWN_ITEM			1
#define RESPAWN_PHOENIX			2
#define RESPAWN_VENGEANCE		3

// Enemies who have immunity w/in this radius will cause blink to fail 
#define IMMUNITY_RADIUS		500

#define SPAWN_DELAY			0.2

// ***************************************************************************
//  Start of variables
// ***************************************************************************

// Use this everywhere instead of declaring it in each function (compiles faster)
new szTmpMsg[2048];

// This keeps track of which races were given "free" XP - we don't want to save this XP to the database
new bool:g_bGivenLevel10[33][MAX_RACES+1];	// Stores if we gave them level 10

new g_GlowLevel[33][4];

// Used for Chameleon
//new g_ChamSkills[5];

new p_data[33][P_LAST]					// Contains player data
new bool:p_data_b[33][PB_LAST]			// Contains player data of type boolean

// Used for advanced statistics
new iStatsHead[33][MAX_CSW_S]
new iStatsChest[33][MAX_CSW_S]
new iStatsStomach[33][MAX_CSW_S]
new iStatsLeftArm[33][MAX_CSW_S]
new iStatsRightArm[33][MAX_CSW_S]
new iStatsLeftLeg[33][MAX_CSW_S]
new iStatsRightLeg[33][MAX_CSW_S]
new iStatsKills[33][MAX_CSW_S]
new iStatsDeaths[33][MAX_CSW_S]
new iStatsHS[33][MAX_CSW_S]
new iStatsTKS[33][MAX_CSW_S]
new iStatsShots[33][MAX_CSW_S]
new iStatsHits[33][MAX_CSW_S]
new iStatsDamage[33][MAX_CSW_S]

new MAXPLAYERS

// Used by admin menu
new g_menuPosition[33]
new g_menuPlayers[33][32]
new g_menuPlayersNum[33]
new g_menuOption[33]
new g_menuSettings[33]

new gmsgStatusText
new gmsgBarTime

// Used with SHARED_SetUserSpeed
new bool:g_bPlayerZoomed[33];

new szSpawnEnt[2][32];

/*  START - CSTRIKE VARIABLES */
new bool:g_freezeTime	= false;
new bool:g_buyTime

// Counter-Strike/Condition Zero Skins
new SKIN_CT[5][]		= { "sas"		, "gsg9"	, "urban"		, "gign"	, "spetsnaz" };
new SKIN_T[5][]			= { "arctic"	, "leet"	, "guerilla"	, "terror"	, "militia" };
	
// Day of Defeat Player skins
new SKIN_AXIS[2][]		= { "axis-inf"	, "axis-para" };
new SKIN_ALLIES[2][]	= { "us-inf"	, "us-para" };
new SKIN_BRIT[1][]		= { "brit-inf" };

new CsArmorType:g_ArmorType[33];

/*  END - CSTRIKE VARIABLES */

/*  START - DOD VARIABLES */
new gmsgHudText

new iReincarnation[33][3];
/*  END - DOD VARIABLES */

// Used to keep track of how much dmg one player does to another
new g_iDamageDealt[33][33];

// Used with helm
new Float:fLastShotFired[33];

// Used to determine if the ultimatedelay is valid
new g_iUltimateDelay;

// Captured Messages
new gmsgDeathMsg
new gmsgScreenFade
new gmsgScreenShake
new gmsgScoreInfo
new gmsgStatusIcon

new bool:g_GameRestarting = false;

new bool:bIgnoreArmorSet[33];

new g_MODclient[20] = "WAR3FT";
new g_MODclientVIP[20] = "WAR3FT VIP";

new bool:warcraft3 = true
new bool:g_EndRound

// Used to make sure a spawn point isn't used for another player
#define TOTAL_SPAWNS	64
new g_iSpawnReserved[TOTAL_SPAWNS];
new g_iSpawnInc = 0;

new g_PlayerWeapons[33][32];			// Stores player weapons after they have been purchased
new g_PlayerLastWeapons[33][32];		// Stores player weapons after they have been purchased

new g_MOD = 0;

// thanks twistedeuphoria - from objective proximity warning
#define MAX_OBJECTIVES			11
#define OBJENT_VIP_ESCAPE		0
#define OBJENT_HOSTAGE			1
#define OBJENT_BOMBSITE			2
#define OBJENT_HOSTAGE_ESCAPE	3

new g_iObjectiveEnt[MAX_OBJECTIVES];
new g_iObjectiveEntType[MAX_OBJECTIVES];
new Float:g_fObjectiveOrigin[MAX_OBJECTIVES][3]
new g_iTotalObjectiveEnts = 0;

new bool:g_bLevitation[33];

new bool:g_bOrcNadesDisabled = false;
new bool:g_bGlovesDisabled = false;

// ***************************
// Skill Information
// ***************************

#define SKILL_1						1
#define SKILL_2						2
#define SKILL_3						3
#define SKILL_ULTIMATE				4
#define SKILL_PASSIVE				5

#define MAX_PLAYER_SKILLS			6
#define MIN_ULT_LEVEL               6

// SKILL DEFINES
#define SKILL_NONE				-1

#define SKILL_VAMPIRICAURA		0
#define SKILL_UNHOLYAURA		1
#define SKILL_LEVITATION		2
#define ULTIMATE_SUICIDE		3

#define SKILL_INVISIBILITY		4
#define SKILL_DEVOTION			5
#define SKILL_BASH				6
#define ULTIMATE_BLINK			7

#define SKILL_CRITICALSTRIKE	8
#define SKILL_CRITICALGRENADE	9
#define SKILL_REINCARNATION		10
#define ULTIMATE_CHAINLIGHTNING	11

#define SKILL_EVASION			12
#define SKILL_THORNS			13
#define SKILL_TRUESHOT			14
#define ULTIMATE_ENTANGLE		15

#define SKILL_PHOENIX			16
#define SKILL_BANISH			17
#define SKILL_SIPHONMANA		18
#define ULTIMATE_IMMOLATE		19
#define PASS_RESISTANTSKIN		20

#define SKILL_HEALINGWAVE		21
#define SKILL_HEX				22
#define SKILL_SERPENTWARD		23
#define ULTIMATE_BIGBADVOODOO	24
#define PASS_UNSTABLECONCOCTION	25

#define SKILL_FANOFKNIVES		26
#define SKILL_BLINK				27
#define SKILL_SHADOWSTRIKE		28
#define ULTIMATE_VENGEANCE		29
#define PASS_HARDENEDSKIN		30

#define SKILL_IMPALE			31
#define SKILL_SPIKEDCARAPACE	32
#define SKILL_CARRIONBEETLES	33
#define ULTIMATE_LOCUSTSWARM	34
#define PASS_ORB				35

#define SKILL_SHADOW			36
#define SKILL_HEROIC			37
#define SKILL_ABUNDENCE			38
#define ULTIMATE_GIFT			39

#define SKILL_RUN			40
#define SKILL_ABERRATION			41
#define SKILL_FORM			42
#define ULTIMATE_CLAWS			43

#define SKILL_TORENT			44
#define SKILL_AFFINITY			45
#define SKILL_BLOODEYES			46
#define ULTIMATE_SLEEP			47

#define SKILL_BERSERKING			48
#define SKILL_REGENERATION			49
#define SKILL_SHUFFLE			50
#define ULTIMATE_STEALTH			51


#define SKILL_SOUL			52
#define SKILL_MAGIC	53
#define SKILL_DRAIN	54
#define ULTIMATE_ILUSION	55
#define PASS_SEAL				56

#define SKILL_ENERGY			57
#define SKILL_WORDS	58
#define SKILL_LIGHT	59
#define ULTIMATE_MIND	60
#define PASS_HEAVEN 61

#define SKILL_RAISE			62
#define SKILL_PACT	63
#define SKILL_POSESION	64
#define ULTIMATE_SHADOW	65
#define PASS_CONVERSION 66


#define SKILL_WATER			67
#define SKILL_TYPHOON	68
#define SKILL_FIRE	69
#define ULTIMATE_NATURA	70
#define PASS_BALANCE 71



#define MAX_SKILLS				72
#define MAX_RACE_SKILLS         3
#define MAX_SKILL_LEVEL			7
#define MAX_ULTIMATE_LEVEL		4

// Used with g_SkillType
#define SKILL_TYPE_TRAINABLE	1
#define SKILL_TYPE_PASSIVE		2
#define SKILL_TYPE_ULTIMATE		3

// Used with g_SkillOrder
#define SKILL_POS_NONE			-1
#define SKILL_POS_1				0
#define SKILL_POS_2				1
#define SKILL_POS_3				2
#define SKILL_POS_4				3

new g_SkillOwner[MAX_SKILLS	];	// For each skill, says who the owning race is
new g_SkillType[MAX_SKILLS	];	// For each skill, says what type of skill it is (trainable/ultimate/passive)
new g_SkillOrder[MAX_SKILLS	];	// For each skill, lists what order it should appear in /level and /selectskill (and how it should save)

// Used to store what level each skill is for the players
new g_PlayerSkillLevel[33][MAX_SKILLS];			// Stores what level each skill is
new bool:g_bPlayerSkills[33][MAX_SKILLS];		// Stores what skills the player has available (set on race selection)

// Constants for Abilities
new const Float:p_vampiric[MAX_SKILL_LEVEL] =			{0.10,0.15,0.20,0.25,0.30,0.40,0.45}		// Vampiric Aura			(skill 1)
new Float:p_unholy[MAX_SKILL_LEVEL] =					{260.0,270.0,280.0,290.0,300.0,310.0,320.0}		// Unholy Aura				(skill 2)
new Float:p_unholy_dod[MAX_SKILL_LEVEL] =				{10.2,33.3,45.3,66.6,70.3,90.3,100.0}		// Unholy Aura				(skill 2)
new const Float:p_levitation[MAX_SKILL_LEVEL] =		{0.8,0.75,0.7,0.6,0.5,0.4,0.3}			// Levitation				(skill 3)

new const p_invisibility[MAX_SKILL_LEVEL] =			{200,190,170,150,140,130,120}			// Invisibility				(skill 1)
new const p_devotion =					7						// Devotion Aura			(skill 2)
new const Float:p_bash[MAX_SKILL_LEVEL] =				{0.05,0.10,0.15,0.20,0.25,0.30,0.35}		// Bash						(skill 3)

new const Float:p_critical[MAX_SKILL_LEVEL] =			{0.15,0.25,0.45,0.50,0.60,0.75,0.85}		// Critical Strike			(skill 1)
new const Float:p_grenade[MAX_SKILL_LEVEL] =			{2.0,3.0,4.0,5.0,6.0,7.0}			// Critical Grenade			(skill 2)
new const Float:p_ankh[MAX_SKILL_LEVEL] =				{0.150,0.333,0.450,0.666,0.800,0.900,1.0}		// Equipment reincarnation	(skill 3)

new const Float:p_evasion[MAX_SKILL_LEVEL] =			{0.5,0.1,0.15,0.20,0.25,0.30,0.35}		// Evasion					(skill 1)
new const Float:p_thorns[MAX_SKILL_LEVEL] =			{0.05,0.1,0.15,0.17,0.20,0.23,0.25}			// Thorns Aura				(skill 2)
new const Float:p_trueshot[MAX_SKILL_LEVEL] =			{0.05,0.1,0.15,0.2,0.25,0.27,0.30}			// Trueshot Aura			(skill 3)

new const Float:p_trueshot_weak[MAX_SKILL_LEVEL] =			{0.02,0.04,0.06,0.08,0.10,0.12,0.15}			// Trueshot Aura			(skill 3)


new const Float:p_phoenix[MAX_SKILL_LEVEL] =			{0.155,0.333,0.450,0.666,0.800,0.900,1.0}		// Phoenix					(skill 1)
new const p_phoenix_dod[MAX_SKILL_LEVEL] =			{100,300,400,600,700,800,900}			// Phoenix - DOD			(skill 1)
new const Float:p_banish[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}		// Banish					(skill 2)
new const Float:p_mana[MAX_SKILL_LEVEL] =				{0.02,0.04,0.08,0.10,0.12,0.14,0.16}		// Siphon Mana				(skill 3)
new const Float:p_resistant[MAX_LEVELS+1] =		{0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,0.20,0.21,0.22,0.23,0.24,0.25,0.26}	// Resistant Skin		(Skill 4)

new const Float:p_heal[MAX_SKILL_LEVEL] =				{7.0,6.0,5.0,4.0,3.0,2.0,1.0}			// Healing Wave				(skill 1)
new const Float:p_hex[MAX_SKILL_LEVEL] =				{0.05,0.10,0.15,0.20,0.23,0.25,0.30}		// Hex						(skill 2)
new const p_serpent[MAX_SKILL_LEVEL] =				{1,2,3,4,5,6,7}					// Serpent Ward				(skill 3)
new const Float:p_concoction[MAX_LEVELS+1] =		{0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,0.20,0.21,0.22,0.23,0.24,0.25,0.26}	// Unstable Concoction	(Skill 4)

new const Float:p_fan[MAX_SKILL_LEVEL] =				{0.05,0.10,0.15,0.20,0.23,0.25,0.30}		// Fan of Knives			(skill 1)
new const Float:p_blink[MAX_SKILL_LEVEL] =			{0.150,0.333,0.450,0.666,0.800,0.900,1.0}		// Blink					(skill 2)
new const Float:p_shadow[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}		// Shadow Strike			(skill 3)
new const Float:p_harden[MAX_LEVELS+1] =			{0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,0.40,0.42,0.44,0.46,0.48,0.50,0.52}	// Hardened Skin		(Skill 4)

new const Float:p_impale[MAX_SKILL_LEVEL] =			{0.04,0.06,0.08,0.10,0.12,0.14,0.16}		    // Impale					(skill 1)
new const Float:p_spiked[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// Spiked Carapace			(skill 2)
new const Float:p_carrion[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}		// Carrion Beetle			(skill 3)
new const Float:p_orb[MAX_LEVELS+1] =				{0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,0.20,0.21,0.22,0.23,0.24,0.25,0.26}	// Orb of Annihilation	(Skill 4)

new const Float:p_shadow_resistence[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// Shadow Resistence		(skill 1)
new const Float:p_heroic[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// Heroic Presence	(skill 2)
new const p_money[MAX_SKILL_LEVEL] =			{30,50,70,100,150,200,300}			// Abundence Money			(skill 3)

new Float:p_run[MAX_SKILL_LEVEL] =					{265.0,270.0,275.0,280.0,285.0,290.0,300.0}		// Wild Run				(skill 1)
new const Float:p_aberration[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// Aberration	(skill 2)
new const Float:p_form[MAX_SKILL_LEVEL] =			{0.5,0.1,0.15,0.20,0.25,0.30,0.35}		// Two Forms					(skill 3)


new const Float:p_torent[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// Torent	(skill 1)
new const Float:p_affinity[MAX_SKILL_LEVEL] =			{0.10,0.20,0.30,0.40,0.50,0.60,0.70}			// Affinity	(skill 2)
new const Float:p_bloodeyes[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// Blood Eyes	(skill 3)

new const p_regeneration[MAX_SKILL_LEVEL] =			{5,10,15,20,25,30,35}			// Regeneration 			(skill 1)
new const Float:p_berserking[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// berserking	(skill 2)
new const Float:p_shuffle[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// shuffle	(skill 3)

new const p_soul[MAX_SKILL_LEVEL] =			{10,15,20,25,30,40,50}			// Soul Shards 			(skill 1)
new const Float:p_magic[MAX_SKILL_LEVEL] =				{7.0,6.0,5.0,4.0,3.0,2.0,1.0}			// Magic				(skill 2)
new const Float:p_drain[MAX_SKILL_LEVEL] =				{7.0,6.0,5.0,4.0,3.0,2.0,1.0}			// Drain Life				(skill 3)
new const Float:p_seal[MAX_LEVELS+1] =		{0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,0.20,0.21,0.22,0.23,0.24,0.25,0.26}	// Seal	(Skill 4)


new const Float:p_energy[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// Energy		(skill 1)
new const Float:p_words[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// Power Words		(skill 2)
new const p_light[MAX_SKILL_LEVEL] =				{1,2,3,4,5,6,7}					// Light Ward				(skill 3)

new const Float:p_heaven[MAX_LEVELS+1] =		{0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,0.20,0.21,0.22,0.23,0.24,0.25,0.26}	// heaven(Skill 4)

new const Float:p_raise[MAX_SKILL_LEVEL] =			{0.02,0.04,0.06,0.08,0.10,0.12,0.15}			// Death Pact				(skill 1)
new const Float:p_pact[MAX_SKILL_LEVEL] =			{0.05,0.1,0.15,0.17,0.20,0.23,0.25}			// Death Pact				(skill 2)
new const Float:p_posesion[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// Souls Posesion				(skill 3)
new const Float:p_conversion[MAX_LEVELS+1] =		{0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,0.20,0.21,0.22,0.23,0.24,0.25,0.26}	// heaven(Skill 4)

new const Float:p_water[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// Wicked Water				(skill 1)
new const Float:p_typhoon[MAX_SKILL_LEVEL] =			{0.02,0.04,0.06,0.08,0.10,0.12,0.15}			// Typhoon				(skill 2)
new const Float:p_fire[MAX_SKILL_LEVEL] =			{0.05,0.10,0.15,0.20,0.23,0.25,0.30}			// Fire Ring			(skill 3)

new const Float:p_balance[MAX_LEVELS+1] =		{0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,0.20,0.21,0.22,0.23,0.24,0.25,0.26}	// balance(Skill 4)


new MOTD_header[] = "<html><head><LINK REL=^"StyleSheet^" HREF=^"wc3.css^" TYPE=^"text/css^"></head><body>";


// SOUNDS
#define MAX_SOUNDS	45

new g_szSounds[MAX_SOUNDS][64];

#define SOUND_VENGEANCE			0
#define SOUND_SUICIDE			1
#define SOUND_BANISH			2
#define SOUND_LOCUSTSWARM		3
#define SOUND_SHADOWSTRIKE		4
#define SOUND_CARRION			5
#define SOUND_IMPALE			6
#define SOUND_VOODOO			7
#define SOUND_FLAMESTRIKE		8
#define SOUND_ENTANGLING		9
#define SOUND_LIGHTNING			10
#define SOUND_TELEPORT			11
#define SOUND_BLINK				12
#define SOUND_ANNIHILATION		13
#define SOUND_CONCOCTION_CAST	14
#define SOUND_CONCOCTION_HIT	15
#define SOUND_HEX				16
#define SOUND_IMMOLATE			17
#define SOUND_IMMOLATE_BURNING	18
#define SOUND_LEVELUP			19
#define SOUND_PICKUPITEM		20
#define SOUND_TOME				21
#define SOUND_ULTIMATESCAN		22
#define SOUND_ULTIMATEREADY		23
#define SOUND_REINCARNATION		24
#define SOUND_ANTEND			25
#define SOUND_ERROR				26
#define SOUND_DISPELL			27
#define SOUND_SPELLSHIELD		28
#define SOUND_HEORC		29
#define SOUND_XP		30
#define SOUND_HP		31
#define SOUND_MONEY		32
#define SOUND_AR		33
#define SOUND_PSYCHO		34
#define SOUND_DEKLOWAZ		35
#define SOUND_BLASTO		36
#define SOUND_WORGEN		37
#define SOUND_AFFINITY		38
#define SOUND_SLEEP		39
#define SOUND_DRAINLIFE		40
#define SOUND_ETH		41
#define SOUND_GOLD		42
#define SOUND_DEATH_TOUCH 43
#define SOUND_WATER 44

// SPRITES
#define MAX_SPRITES	25

new g_szSprites[MAX_SPRITES][64];
//new g_szRaceSprites[MAX_RACES + 1][64];
//new g_szLevelSprites[MAX_LEVELS + 1][64];

//new g_iRaceSprites[MAX_RACES + 1];
//new g_iLevelSprites[MAX_LEVELS + 1];
new g_iSprites[MAX_SPRITES] = {0};

//new bool:g_bExtraSpritesEnabled = false

#define SPR_BANISH			0
#define SPR_SHADOWSTRIKE	1
#define SPR_SNOW			2
#define SPR_FIRE			3
#define SPR_BURNING			4
#define SPR_BEETLE			5
#define SPR_FIREBALL		6
#define SPR_BEAM			7
#define SPR_TRAIL			8
#define SPR_SHOCKWAVE		9
#define SPR_LIGHTNING		10
#define SPR_FLARE			11
#define SPR_WAVE			12
#define SPR_SMOKE			13
#define SPR_IMMOLATE		14
#define SPR_TELEPORT			15
#define SPR_TELEPORT_GIB		16
#define SPR_WORGEN		17
#define SPR_SLEEP		18
#define SPR_ETH_TRAIL		19
#define SPR_ETH_EXP		20
#define SPR_DEATH_TOUCH 21
#define SPR_WATER 22
#define SPR_HEAL 23
#define SPR_STEEL 24

	

// HUD Channels
#define HUD_SPEC_INFO			1	// Info displayed in bottom corner of player being spectated
#define HUD_SHOWSTATUS			4	// Information shown on enemies/teammates when looking at them
#define HUD_DOD_MONEY			4	// Money Displayed at top center of screen in DOD
#define HUD_RACE_INFO			2	// /level command
#define HUD_ULTIMATE			1	// Ultimate messages (i.e. you have _ seconds remaining)
#define HUD_SKILL				3	// i.e. "you have evaded a shot"
#define HUD_XP					3	// Used to show the user their xp/items when dead
#define HUD_AUTO				-1	// Automatically choose one!
#define HUD_TIMER				1	// Timer

#define FADE_OUT                0x0000          // Fade out from max alpha
#define FADE_IN                 0x0001          // Fade in to max alpha
#define FADE_MODULATE_OUT       0x0002          // Modulate, fade out from max alpha
#define FADE_MODULATE_IN        0x0003      // Modulate, fade in to max alpha
#define FADE_ONLYONE_OUT        0x0004      // Start at max Alpha, no fade out
#define FADE_ONLYONE_IN         0x0005      // Fade in to max Alpha, no fade out
#define FADE_MODONE_OUT         0x0006      // Modulate, Start at max Alpha, no fade
#define FADE_MODONE_IN          0x0007      // Modulate, Fade in to max Alpha, no fade out

#define HUDMESSAGE_FX_FADEIN    0           // hudmessage effect types
#define HUDMESSAGE_FX_FLICKER   1
#define HUDMESSAGE_FX_WRITEOUT  2

// Used for spectating info
#define SPEC_HOLDTIME		10.0
new g_iSpectatingID[33];
new Float:g_fLastSpecDisplay[33];

// Lets keep track of what team the player is on!
new g_iPlayerTeam[33];

#define BOT_CAST_ULT_CHANCE		0.10

new bool:g_bCZBotRegisterHam



// New Defines 

#define OFFSET_FLASH_AMMO 387
#define OFFSET_HE_AMMO 388
#define OFFSET_SMOKE_AMMO 389
#define OFFSET_ARMORTYPE 112 
#define EXTRAOFFSET 5

#define    TASK_GLOW_SHELL    6547    // Calls glow_change

/*
new dropitem1[33] ;
new dropitem2[33] ;
new dropitem3[33] ;
new g_models[][] = {"models/warcraft3/newkorobka.mdl", "models/warcraft3/arxphpx.mdl"}
*/

new bool:SLEEP_ON = false;


#define MAX_PLAYERS    33


//---------------------------------------------------------------------------------------

new decoy[MAX_PLAYERS] = 0 // Decoys stored for each player
new Float:decoy_frame[MAX_PLAYERS] = 0.0 // Used in server_frame()
new Float:decoy_fstep[MAX_PLAYERS] = 0.0 // Frame step time
new Float:last_frame = 0.0 // Last server_frame saved
new decoy_seq[MAX_PLAYERS] = 0 // Current sequence for each decoy
new bool:DoOnce[MAX_PLAYERS] = false // Used for handling crouch mode
new bool:decoyused[MAX_PLAYERS] = false // Has decoy been used this round
new bool:pIsDucking[MAX_PLAYERS] = false // Is player crouching or not

//----------------------------------------------------------------------------


// Kill for bonus 

new g_frags[ 33 ];

#define KILL_LIMIT 25
#define KILL_BONUS 5

#define KILL_LIMIT_VIP 15
#define KILL_BONUS_VIP 5

 
#define FROST_ARMOR_DAMAGE 5

// Bullet Damage

new const Float:g_flCoords[][] = 
{
    {0.50, 0.40},
    {0.56, 0.44},
    {0.60, 0.50},
    {0.56, 0.56},
    {0.50, 0.60},
    {0.44, 0.56},
    {0.40, 0.50},
    {0.44, 0.44}
}

new g_iPlayerPos[MAX_PLAYERS];

new Float:WallOrigin[33][3];

