#include <ACS_ZDoom.h>

#include <stdfix.h>
#include <stdlib.h>
#include <math.h>

#include "../xenutils/utils.h"
#include "wpnsway.h"

fixed gun_offset_x = 0.0;
fixed gun_offset_y = 32.0;

[[call("ScriptS"), script("Enter")]]
void main(void)
{
	fixed move_offset_y = 0.0;
	fixed move_offset_z = 0.0;
	
	fixed view_offset_x = 0.0;
	fixed view_offset_y = 0.0;
	
	for(;;) {
		// ...
		
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
