#include <ACS_ZDoom.h>

#include <limits.h>
#include <stddef.h>
#include <stdfix.h>
#include <stdio.h>

#define FIRST_DOOR	16
#define SECOND_DOOR	17

#define RANGE	32.0

int shooter_tid;
int cursor_tid;

[[call("ScriptS"), script("Enter")]]
void main(void)
{
	ACS_SetCameraToTexture(7, s"GUI3DTEX", 90); // init screen
	
	if(!ACS_ActivatorTID())
		ACS_Thing_ChangeTID(0, ACS_UniqueTID(1, 0));
	int player_tid = ACS_ActivatorTID(); // give player unique tid
	
	shooter_tid = ACS_UniqueTID(1, 0);
	cursor_tid = ACS_UniqueTID(1, 0); // give initial values so Thing_Remove doesn't do anything dangerous
	
	for(;;)
	{
		ACS_Thing_Remove(shooter_tid);
		ACS_Thing_Remove(cursor_tid); // get rid of existing actors
		
		shooter_tid = ACS_UniqueTID(1, 0);
		ACS_SpawnSpot(s"MapSpot", player_tid, shooter_tid); // spawn hitscan shooter at player position
		
		cursor_tid = ACS_UniqueTID(1, 0);
		ACS_LineAttack(shooter_tid, ACS_GetActorAngle(player_tid), ACS_GetActorPitch(player_tid), 0, s"Cursor", s"", RANGE, FHF_NORANDOMPUFFZ | FHF_NOIMPACTDECAL, cursor_tid);
		
		ACS_Delay(1);
	}
}

[[call("ScriptS")]]
void gui_activate(void)
{
	if(ACS_ActivatorTID() != shooter_tid)
		return; // make sure only activated by shooter
	
	// do stuff with cursor_tid
	
}

[[call("ScriptS")]]
void open_airlock(void)
{
	ACS_Door_Open(FIRST_DOOR, 32, 0);
}

[[call("ScriptS")]]
void finish_airlock(void)
{
	ACS_Door_Close(FIRST_DOOR, 64, 0);
	ACS_Delay(35 * 2);
	ACS_Door_Open(SECOND_DOOR, 16, 0);
}
