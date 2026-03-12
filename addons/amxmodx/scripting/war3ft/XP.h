/*
*	XP Header File
*/

// Objective Modifiers
#define DEFUSING_BOMB		10			// XP awarded when the user starts to defuse the bomb
#define DEFUSED_BOMB		20			// XP awarded when the user defuses the bomb
#define PLANTING_BOMB		10			// XP awarded when the user starts planting the bomb
#define PLANT_BOMB			20			// XP awarded when the user plants the bomb
#define SPAWN_BOMB			10			// XP awarded when the user spawns with the bomb
#define BOMB_PICKUP			10			// XP awarded when the user picks up the bomb
#define TOUCH_HOSTAGE		10			// XP awarded when the user touches a hostage
#define RESCUE_HOSTAGE		20			// XP awarded when the user rescues the hostage
#define KILL_HOSTAGE		10			// XP lost when killing a hostage
#define SPAWN_VIP			10			// XP awarded for spawning as the VIP
#define ESCAPE_VIP			20			// XP awarded for escaping as the VIP
#define OBJ_RADIUS			1500			// Nearby radius to award XP for helping complete objectives

// Kill modifiers
#define KILL_HEADSHOT		10			// XP awarded for getting a headshot
#define KILL_HOSTAGE_SAVER	10			// XP awarded for killing the hostage saver
#define	KILL_DEFUSER		10			// XP awarded for killing the defuser
#define KILL_PLANTER		10			// XP awarded for killing the planter
#define KILL_BOMB_CARRIER	10			// XP awarded for killing the bomb carrier
#define KILL_VIP			20			// XP awarded for killing the VIP
#define KILL_RADIUS			1500			// Nearby radius to award XP

#define WIN_ROUND			50			// XP awarded for winning the round


// Holds information about the player
enum
{
	PLR_BOMB_DEFUSER = 1,
	PLR_BOMB_PLANTER,
	PLR_HOSTAGE_RESCUER,
	PLR_VIP,
	PLR_BOMB_CARRIER,
};

new g_iPlayerRole[33];
new bool:bHasBegunPlantingOrDefusing[33];

// Holds the XP Multipliers per weapon
new Float:fWpnXPMultiplier[CSW_WAR3_MAX+1] =		{1.0};

// Amount of XP needed to gain a level
new iXPLevelShortTerm[MAX_LEVELS+1]				= {0,
50,
100,
200,
400,
800,
1600,
3200,
6400,
12800,
25600,
51200,
102400,
204800,
409600,
819200,
1638400,
3276800,
6553600,
13107200,
26214400,
52428800,
104857600,
209715200,
419430400,
838860800};

/*new iXPLevelSaved[MAX_LEVELS+1]					= {0,
50,
100,
200,
400,
800,
1600,
3200,
6400,
12800,
25600,
51200,
102400,
204800,
409600,
819200,
1638400,
3276800,
6553600,
13107200,
26214400,
52428800,
104857600,
209715200,
419430400,
838860800};
*/
new iXPLevelSaved[MAX_LEVELS+1]					= {0,
150,
300,
450,
675,
1015,
1355,
1695,
2545,
3820,
5730,
8595,
12895,
19345,
29020,
43530,
65295,
97945,
146920,
220380,
330570,
495855,
743785,
1115680,
1673520,
2510280};





// Amount of XP awarded when killing a user of this level
new iXPGivenShortTerm[MAX_LEVELS+1]				= {5,
10,
15,
20,
25,
30,
35,
40,
45,
50,
55,
60,
65,
70,
75,
80,
85,
90,
95,
100,
105,
110,
115,
120,
125,
130};
new iXPGivenSaved[MAX_LEVELS+1]					= {5,
10,
15,
20,
25,
30,
35,
40,
45,
50,
55,
60,
65,
70,
75,
80,
85,
90,
95,
100,
105,
110,
115,
120,
125,
130};