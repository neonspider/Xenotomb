#include <ACS_ZDoom.h>

#include <stdfix.h>
#include <stdlib.h>
#include <math.h>

#include "../xenutils/utils.h"
#include "wpnsway.h"

fixed gun_offset_x = 0.0k;
fixed gun_offset_y = 32.0k;

[[call("ScriptS"), script("Enter")]]
void main(void)
{
	for(;;) {
		// horizontal movement
		fixed velx = ACS_GetActorVelX(0);
		fixed vely = ACS_GetActorVelY(0);
		fixed velz = ACS_GetActorVelZ(0);
		
		fixed angle = angle_to_radians(ACS_GetActorAngle(0));
		fixed pitch = pitch_to_radians(ACS_GetActorPitch(0));
		
		// vertical movement
		
		// freelook
		
		ACS_Delay(1);
	}
}

[[call("ScriptS"), extern("ACS")]]
fixed get_gun_offset_x (void)
{
	return gun_offset_x;
}

[[call("ScriptS"), extern("ACS")]]
fixed get_gun_offset_y (void)
{
	return gun_offset_y;
}

fixed target_velocity(fixed d, fixed v, fixed a)
{
	a = copysign(a, d);
	return copysign(sqrt(v * (v - a) / 2 + a * d), d);
}

fixed update_velocity(fixed d, fixed v, fixed a)
{
	fixed x = target_velocity(d, v, a);
	
	if (v < x) {
		v = clamp(v + abs(a), v, x);
	} else if (v > x) {
		v = clamp(v - abs(a), v, x);
	} else { // v == x
		v = clamp(v - a, v, x);
	}
	
	return v;
}
