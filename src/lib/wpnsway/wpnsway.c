#include <ACS_ZDoom.h>

#include <stdfix.h>
#include <stdlib.h>
#include <math.h>

#include "../xenutils/utils.h"
#include "wpnsway.h"

#include "strafe.h"
#include "vert.h"
#include "look.h"

#define CLAMP_LEFT		-32.0k
#define CLAMP_RIGHT		32.0k
#define CLAMP_UP		0.0k
#define CLAMP_DOWN		64.0k

// macro because who wants to see all that everytime
#define USERCVAR(x) ACS_GetUserCVar(ACS_PlayerNumber(), x)

[[call("ScriptS"), extern("ACS")]]
fixed get_gun_offset_x (void)
{
	struct Vec2 look_offset = get_offset_look();
	
	return clamp(USERCVAR(s"wpnsway_strafeamt") * get_offset_strafe()
					+ USERCVAR(s"wpnsway_lookamtx") * look_offset.x,
					CLAMP_LEFT, CLAMP_RIGHT);
}

[[call("ScriptS"), extern("ACS")]]
fixed get_gun_offset_y (void)
{
	struct Vec2 look_offset = get_offset_look();
	
	return clamp(USERCVAR(s"wpnsway_vertamt") * ACS_Cos(pitch_to_fixed(ACS_GetActorPitch(0))) * get_offset_vert()
					+ USERCVAR(s"wpnsway_lookamty") * look_offset.y
					+ USERCVAR(s"wpnsway_pitchamt") * pitch_to_fixed(ACS_GetActorPitch(0)),
					CLAMP_LEFT, CLAMP_RIGHT);
}

fixed target_velocity(fixed d, fixed v, fixed a)
{
	a = copysign(a, d);
	return copysign(sqrt(v*(v-a)/2 + a*d), d);
}

fixed update_velocity(fixed v, fixed x, fixed a)
{
	if (v<x) {
		v = clamp(v+abs(a), v, x);
	}
	else if (v>x) {
		v = clamp(v-abs(a), v, x);
	}
	else { // v==x
		v = clamp(v-a, v, x);
	}
	
	return v;
}
