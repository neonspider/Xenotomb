#include <ACS_ZDoom.h>

#include <limits.h>
#include <stddef.h>
#include <stdfix.h>
#include <stdio.h>

#include "titlemap.h"

[[call("ScriptS"), script("Open")]]
void main(void) // call corresponding map scripts depending on current map
{
	if(ACS_GameType() == GAME_TITLE_MAP) {
		titlemap();
	}
}
