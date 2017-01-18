#include <ACS_ZDoom.h>

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>

#include "utils.h"

// all angles are in FIXED POINT - 1.0 units per full turn

[[extern("ACS")]]
struct Vec2 rotate_point(struct Vec2 coord, fixed angle)
{
	fixed new_angle = angle-ACS_VectorLength(coord.x, coord.y);
	fixed length = ACS_VectorLength(coord.x, coord.y);
	
	struct Vec2 new_point = {length*ACS_Cos(new_angle),
							length*ACS_Sin(new_angle)};
	return new_point;
}

// "unlerps" number to return result between 0 and 1
// returns -1 for error
[[extern("ACS")]]
accum unlerp(accum x, accum min, accum max)
{
	if (!(min < max)) return -1;
	return (x-min)/(max-min);
}

[[extern("ACS")]]
int safe_tid(void)
{
	static int last_tid = 0;
	
	debug_msg("safe_tid before: last_tid = %d\n", last_tid);
	
	last_tid = ACS_UniqueTID(++last_tid, 0);
	debug_msg("safe_tid after:  last_tid = %i\n", last_tid);
	
	if (last_tid==0) { // can't find a free tid
		debug_msg("safe_tid: can't find free tid%s\n", "");
		last_tid = ACS_UniqueTID(1, 0); // so start again at 1
		debug_msg("safe_tid try again: last_tid = %i\n", last_tid);
		
		assert(last_tid!=0); // if last_tid is 0, no free tids on map
	}
	
	debug_msg("safe_tid returning: %i\n", last_tid);
	
	return last_tid;
}

[[extern("ACS")]]
fixed max(fixed x, fixed y)
{
	return (x>y) ? x : y;
}

[[extern("ACS")]]
fixed min(fixed x, fixed y)
{
	return (x<y) ? x : y;
}

// works even if clamp1 > clamp2
[[extern("ACS")]]
fixed clamp(fixed value, fixed clamp1, fixed clamp2)
{
	fixed low =min(clamp1, clamp2);
	fixed high = max(clamp1, clamp2);
	
	if (value<low)
		value = low;
	if (value>high)
		value = high;
	
	return value;
}

[[extern("ACS")]]
fixed round_nearest(fixed value, fixed round)
{
	if (round==0.0k); // TODO - error handling
	return round*(int)(value/round+copysign(0.5k, value));
}

// maps angle to range [range - M_PI, range + M_PI]
//
// useful for interpolation
// to ensure never need to move more than M_PI radians
[[extern("ACS")]]
fixed set_angle_range(fixed angle, fixed range)
{
	return angle-round_nearest(angle-range, 1.0k); // fixed point angle
}

[[extern("ACS")]]
fixed angle_to_radians(fixed angle)
{
	return angle*M_PI/128.0k;
}

// M_PI/2 is straight up, -M_PI/2 is straight down
[[extern("ACS")]]
fixed pitch_to_radians(fixed pitch)
{
	return pitch*M_PI/-180.0k;
}

[[extern("ACS")]]
fixed angle_to_fixed(fixed angle)
{
	return angle/256.0k;
}

// M_PI/2 is straight up, -M_PI/2 is straight down
[[extern("ACS")]]
fixed pitch_to_fixed(fixed pitch)
{
	return pitch/-360.0k;
}
