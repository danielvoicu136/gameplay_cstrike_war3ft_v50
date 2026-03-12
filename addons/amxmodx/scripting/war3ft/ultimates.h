// For Icon events
#define ICON_HIDE 0 
#define ICON_SHOW 1 
#define ICON_FLASH 2 



// http://doktor.haze.free.fr/counter-strike/sprites_screens/index.php


new g_UltimateIcons[16][32] = 
					{
						"dmg_rad",				// Undead
						"item_longjump",		// Human Alliance
						"dmg_shock",			// Orcish Horde
						"item_healthkit",		// Night Elf
						"dmg_heat",				// Blood Mage
						"suit_full",			// Shadow Hunter
						"cross",				// Warden
						"dmg_gas",				// Crypt Lord
						"cross",				// Draenei
						"item_battery",             // Worgen
						"dmg_drown",			// Blood Elf
						"dmg_bio",					// Troll
						"dmg_gas",                        // Warlock 
						"dmg_rad",						// Priest 
						"item_healthkit",				// Death Knight
						"train_forward1"					// Druid 
					};

new g_ULT_iLastIconShown[33];				// Stores what the last icon shown was for each user (race #)

