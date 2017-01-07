#ifndef UTILS_H
#define UTILS_H

#include <stdfix.h>
#include <math.h>

#define PI acos(-1.0)

struct Point {
	fixed x;
	fixed y;
};

[[extern("ACS")]]
struct Point rotate_point(struct Point, fixed angle);

[[extern("ACS")]]
fixed get_angle(struct Point);

[[extern("ACS")]]
fixed get_length(struct Point);

[[extern("ACS")]]
int debug_msg(const char*, ...);

// opposite of lerp
[[extern("ACS")]]
fixed unlerp(fixed x, fixed min, fixed max);

// like UniqueTid, but guaranteed not to return
// the same tid twice in a row, so it can be called
// multiple times
[[extern("ACS")]]
int safe_tid(void);

[[extern("ACS")]]
fixed min(fixed, fixed);

[[extern("ACS")]]
fixed max(fixed, fixed);

// works even if clamp1 > clamp2
[[extern("ACS")]]
fixed clamp(fixed value, fixed clamp1, fixed clamp2);

[[extern("ACS")]]
fixed round_nearest(fixed value, fixed round);

[[extern("ACS")]]
fixed set_angle_range(fixed angle, fixed range);

#endif	// UTILS_H
