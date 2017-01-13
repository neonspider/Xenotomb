#include <ACS_ZDoom.h>

#include <stdfix.h>
#include <stdio.h>
#include <stdbool.h>

#include "../../lib/xenutils/utils.h"

enum {first_door = 16};
enum {second_door = 17};

enum {range	= 8192<<8};

enum {screen_topleft = 2, screen_bottomleft = 3, screen_bottomright = 4};

enum {camera_tid = 7};

enum {zoffset_hack = -8}; // hack to stop puff spawning 8 units higher than it should

int player_tid;
int shooter_tid;
int cursor_tid;

[[call("ScriptS"), script("Enter")]]
void main(void)
{
	ACS_SetCameraToTexture(camera_tid, s"GUI3DTEX", 90); // init screen
	
	if (!ACS_ActivatorTID())
		ACS_Thing_ChangeTID(0, ACS_UniqueTID(1, 0));
	player_tid = ACS_ActivatorTID(); // give player unique tid
	
	shooter_tid = safe_tid();
	debug_msg("shooter_tid: %i\n", shooter_tid);
	
	cursor_tid = safe_tid();
	debug_msg("cursor_tid:  %i\n", cursor_tid);
	
	for (;;) {
		ACS_Thing_Remove(shooter_tid);
		ACS_Thing_Remove(cursor_tid); // get rid of existing actors
		
		ACS_SpawnForced(s"GuiShooter", ACS_GetActorX(player_tid), ACS_GetActorY(player_tid),
			ACS_GetActorZ(player_tid)+ACS_GetActorViewHeight(player_tid)+zoffset_hack,
				shooter_tid); // spawn hitscan shooter at player position
		
		ACS_LineAttack(shooter_tid, ACS_GetActorAngle(player_tid), ACS_GetActorPitch(player_tid),
			0, s"GuiCursor", s"None", range, FHF_NORANDOMPUFFZ|FHF_NOIMPACTDECAL, cursor_tid);
		
		ACS_Delay(1);
	}
}

[[call("ScriptS"), extern("ACS")]]
void gui_activate(void)
{
	if (ACS_ActivatorTID()!=shooter_tid)
		return;
	
	
}

[[call("ScriptS")]]
void open_airlock(void)
{
	ACS_Door_Open(first_door, 32, 0);
}

[[call("ScriptS")]]
void finish_airlock(void)
{
	ACS_Door_Close(first_door, 64, 0);
	ACS_Delay(35*2);
	ACS_Door_Open(second_door, 16, 0);
}
