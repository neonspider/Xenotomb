#include <stdfix.h>

#ifndef UTILS_H
#define UTILS_H

[[extern("ACS")]]
int debug_msg(const char*, ...);

// opposite of lerp
[[extern("ACS")]]
accum unlerp(accum x, accum min, accum max);

// like UniqueTid, but guaranteed not to return
// the same tid twice in a row, so it can be called
// multiple times
[[extern("ACS")]]
int safe_tid(void);

#endif	// UTILS_H
