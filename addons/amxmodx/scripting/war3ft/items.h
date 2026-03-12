/*
*	Item Defines
*/

// Item Values
#define DOD_BOOT_SPEED 45.0

// Item Charge Defines
#define NECKLACE_CHARGES	3
#define HELM_CHARGES		1
#define NECKLACE_CHARGES_VIP  6 
#define HELM_CHARGES_VIP    2
#define CHARGE_DISPOSE      1
#define RING_INCREMENT      1

// Item Variable Defines
#define MAX_SHOPMENU_ITEMS  36
#define MAX_PLAYER_ITEMS    3
#define MAX_PAGE_ITEMS      9
#define ITEM_SLOT_ONE       0
#define ITEM_SLOT_TWO       1
#define ITEM_SLOT_THREE       2
#define ITEM_SLOT_FULL      3

#define ITEM_NONE          -1
#define ITEM_ANKH		    0
#define ITEM_BOOTS		    1
#define ITEM_CLAWS		    2
#define ITEM_CLOAK		    3
#define ITEM_MASK		    4
#define ITEM_NECKLACE	    5
#define ITEM_FROST		    6
#define ITEM_HEALTH		    7
#define ITEM_TOME		    8
#define ITEM_SCROLL		    9
#define ITEM_PROTECTANT     10
#define ITEM_HELM		    11
#define ITEM_AMULET		    12
#define ITEM_SOCK		    13
#define ITEM_GLOVES		    14
#define ITEM_RING		    15
#define ITEM_CHAMELEON	    16
#define ITEM_MOLE		    17

#define ITEM_FROSTARMOR		    18
#define ITEM_GRENADE		    19
#define ITEM_MIRROR		    	20
#define ITEM_ACCELERATOR		21
#define ITEM_DEATH			    22
#define ITEM_POTION			    23
#define ITEM_SCEPTER		    24
#define ITEM_SCANNER		    25
#define ITEM_STEEL			    26

#define ITEM_ASSASIN		    27
#define ITEM_SNAKE		    	28
#define ITEM_PORTAL		    	29
#define ITEM_OMNISCIENCE		30
#define ITEM_INFINITY		    31
#define ITEM_FLAME			    32
#define ITEM_SKULL			    33
#define ITEM_BOOK			    34
#define ITEM_SPIKES			    35






#define MAX_ITEMS_PAGE		9

// Item Variables
new g_iShopMenuItems[33][MAX_PLAYER_ITEMS];			// Holds the player's current items
new g_iFutureItem[33];                              // Holds the item that the player wants to buy 

new g_iTotalRings[33];								// Holds the number of rings the player has
new g_iNecklaceCharges[33];							// Holds the number of charges left in the player's necklace
new g_iHelmCharges[33];								// Holds the number of charges left in the player's helm

new bool:g_bPlayerBoughtAnkh[33];					// Set to true when a user buys an ankh
new bool:g_bPlayerBoughtMole[33];					// Set to true when a user buys a mole

new g_iGloveTimer[33];								// Keeps track of how much time is left to give a user a grenade

new arrDeathTouch[33];

new ITEM_COST[MAX_SHOPMENU_ITEMS];                  // Holds the price of an item

#define ITEM_CHARGEABLE		1
#define ITEM_USEONBUY		2
#define ITEM_BUYWHENDEAD	4
#define ITEM_NEXTROUNDUSE	8

new g_iFlag[MAX_SHOPMENU_ITEMS] = {0};			// Stores information about items

#define ITEM_COST_RATIO		0.7


new bool:bIsUserESP[33];

#define	TASK_ESP	97854

#define	FREQUENCY_ESP 2.0
#define	RADIUS_ESP 700

