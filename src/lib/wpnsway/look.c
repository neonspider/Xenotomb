#include <ACS_ZDoom.h>

#include <stdfix.h>
#include <stdlib.h>
#include <math.h>

#include "../xenutils/utils.h"

#include "look.h"

static struct Vec2 offset;

[[call("ScriptS"), script("Enter")]]
void compute_offset_look(void)
{
	for (;;) {
		
	}
}

struct Vec2 get_offset_look(void)
{
	return (struct Vec2){0.0k, 0.0k};
}
