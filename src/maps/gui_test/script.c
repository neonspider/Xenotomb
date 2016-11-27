#include <ACS_ZDoom.h>

#include <limits.h>
#include <stddef.h>
#include <stdfix.h>
#include <stdio.h>

#define FIRST_DOOR	16
#define SECOND_DOOR	17

[[call("ScriptS"), script("Open")]]
void main(void)
{
	ACS_SetCameraToTexture(7, s"GUI3DTEX", 90)
}

[[call("ScriptS")]]
void gui_activate(void)

[[call("ScriptS")]]
void open_airlock(void)
{
	ACS_Door_Open(FIRST_DOOR, 32, 0);
}

[[call("ScriptS")]]
void finish_airlock(void)
{
	ACS_Door_Close(FIRST_DOOR, 64, 0);
	ACS_Delay(35 * 2);
	ACS_Door_Open(SECOND_DOOR, 16, 0);
}
