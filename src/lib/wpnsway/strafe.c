#include <ACS_ZDoom.h>

#include <stdfix.h>
#include <stdlib.h>
#include <math.h>

#include "../xenutils/utils.h"

#include "strafe.h"

static fixed offset;

[[call("ScriptS"), script("Enter")]]
void compute_offset_strafe(void)
{
	for (;;) {
		struct Vec2	player_vel = {ACS_GetActorVelX(0), ACS_GetActorVelY(0)};
		fixed player_angle = angle_to_fixed(ACS_GetActorAngle(0));
		
		// fixed vel_strafe = rotate_point(player_vel, player_angle).x;
	}
}

fixed get_offset_strafe(void)
{
	return 0.0k;
}
