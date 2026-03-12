#define CLAWS_DAMAGE 45


WR_SkillsOffensive( iAttacker, iVictim )
{

	static iSkillLevel;
	
	iSkillLevel = SM_GetSkillLevel( iVictim, SKILL_ABERRATION )
	if( iSkillLevel > 0 )
	{
	    if ( random_float( 0.0, 1.0 ) <= p_aberration[iSkillLevel-1] )
		{	if ( p_data_b[iVictim][PB_ISCONNECTED] && is_user_alive( iVictim ) )
			{
			if ( get_user_health( iVictim ) + 10 <= get_user_maxhealth( iVictim ) )
						{
						set_user_health( iVictim, get_user_health( iVictim ) + 10 );
						Create_ScreenFade( iVictim, (1<<10), (1<<10), (1<<12), 121, 28, 248, 100 );
						SHARED_GlowShell(iVictim, 121, 28, 248, 1.5, 100);
						}
			else { set_user_health( iVictim, get_user_maxhealth( iVictim ) ) ; 
					Create_ScreenFade( iVictim, (1<<10), (1<<10), (1<<12), 121, 28, 248, 100 );
					SHARED_GlowShell(iVictim, 121, 28, 248, 1.5, 100);
								}
							Create_ScreenFade( iAttacker, (1<<10), (1<<10), (1<<12), 121, 28, 248, 50 );
			}
		}
	}
	
}


public WR_ULT_Claws( iCaster, iTarget )
{
	


	
		if (ITEM_Has(iCaster, ITEM_SCEPTER ) > ITEM_NONE)
		{
	WC3_Damage( iTarget, iCaster, 2*CLAWS_DAMAGE, CSW_IMMOLATE, -1 );
	}
	else { WC3_Damage( iTarget, iCaster, CLAWS_DAMAGE, CSW_IMMOLATE, -1 ); }

	
	Create_ScreenFade( iTarget,(1<<15),(1<<10),(1<<12), 255, 0, 0, 200);
	SHARED_GlowShell(iTarget, 255, 0, 0, 1.5, 100);
	emit_sound( iTarget, CHAN_STATIC, g_szSounds[SOUND_WORGEN], 1.0, ATTN_NORM, 0, PITCH_NORM );
	emit_sound( iCaster, CHAN_STATIC, g_szSounds[SOUND_WORGEN], 1.0, ATTN_NORM, 0, PITCH_NORM );
	//Create_ScreenShake( iTarget, (10<<12), (2<<12), (5<<12) );
	
	new vOldLocation[3];
	get_user_origin( iTarget, vOldLocation );
	Create_TE_SPRITE( vOldLocation, g_iSprites[SPR_WORGEN], 15 , 200 );
	
	return PLUGIN_HANDLED;
}
