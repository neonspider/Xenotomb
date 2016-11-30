#include <ACS_ZDoom.h>

#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include "utils.h"

[[extern("ACS")]]
int debug_msg(char* msg, ...)
{
	int result = 0;
	
	#ifdef XENOTOMB_DEBUG
	
    va_list args;
    va_start(args, msg);
    result = vprintf(msg, args);
    va_end(args);
	
	#endif // XENOTOMB_DEBUG
	
    return result;
	
}

[[extern("ACS")]]
accum unlerp(accum x, accum min, accum max)
{
	assert(min < max);
	return (x - min) / (max - min);
}

[[extern("ACS")]]
int safe_tid(void)
{
	static int last_tid = 0;
	
	debug_msg("safe_tid before: last_tid = %i\n", last_tid);
	last_tid = ACS_UniqueTID(++last_tid, 0);
	debug_msg("safe_tid after:  last_tid = %i\n", last_tid);
	
	if(last_tid == 0) { // can't find a free tid
		debug_msg("safe_tid: can't find free tid\n");
		last_tid = ACS_UniqueTID(1, 0); // so start again at 1
		debug_msg("safe_tid try again: last_tid = %i\n", last_tid);
		
		assert(last_tid != 0); // if last_tid is 0, no free tids on map
	}
	
	debug_msg("safe_tid returning: %i\n", last_tid);
	
	return last_tid;
}
