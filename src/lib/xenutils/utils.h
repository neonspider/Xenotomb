#ifndef UTILS_H
#define UTILS_H

#include <stdfix.h>
#include <math.h>
#include <stdbool.h>

// all angles are in FIXED POINT - 1.0 units per full turn

#define M_PI  3.141592653589793238462643383279502884
#define M_PIf 3.141592653589793238462643383279502884F
#define M_PIl 3.141592653589793238462643383279502884L

#define M_PI_2  1.570796326794896619231321691639751442
#define M_PI_2f 1.570796326794896619231321691639751442F
#define M_PI_2l 1.570796326794896619231321691639751442L

#ifdef XENO_DEBUG
#define debug_msg(fmt, ...) do { \
		printf("%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
	} while (false)
#else
#define debug_msg(fmt, ...) do {} while (false)
#endif // XENO_DEBUG

struct Vec2 {
	fixed x;
	fixed y;
};

[[extern("ACS")]]
struct Vec2 rotate_point(struct Vec2, fixed angle);

// opposite of lerp
// "unlerps" number to return result between 0 and 1
// returns -1 for error
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

[[extern("ACS")]]
fixed angle_to_radians(fixed angle);

[[extern("ACS")]]
fixed pitch_to_radians(fixed pitch);

[[extern("ACS")]]
fixed angle_to_fixed(fixed angle);

[[extern("ACS")]]
fixed pitch_to_fixed(fixed pitch);

#endif	// UTILS_H
