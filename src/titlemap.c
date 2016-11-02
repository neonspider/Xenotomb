#include <ACS_ZDoom.h>

#include <limits.h>
#include <stddef.h>
#include <stdfix.h>
#include <stdio.h>

#include "titlemap.h"

[[call("ScriptS"), script("Open")]]
void map01_open(void)
{
	reset_player();
	show_cutscene();
	
	ACS_Delay (300);
	
	print_msg();
}

void reset_player(void)
{
	ACS_ClearInventory();
}

[[call("ScriptS")]]
void print_msg(void)
{
	const int msg_amount = 7;
	
	const char* msg[msg_amount] = {
		"NETWORK CONNECTION TO $COMM/GUEST/SIGOURNEY ESTABLISHING...\n",
		"NETWORK CONNECTION TO $COMM/GUEST/SIGOURNEY ESTABLISHED.\n",
		"DOCKING CONNECTION TO $DA8/SIGOURNEY ESTABLISHING...\n",
		"DOCKING CONNECTION TO $DA8/SIGOURNEY ESTABLISHED.\n",
		"ENGAGING DOCKING PROCEDURE: STANDARD DOCKING PROTOCOLS...\n",
		"INCOMING GREETER FROM */GUEST SIGOURNEY...\n",
		"WELCOME TO THE SIGOURNEY, PLEASE WAIT FOR DIRECTIONS!\n"
	};
	
	for (int i = 0; i < msg_amount; ++i)
	{
		ACS_SetFont(s"SMALLFONT");
		
		ACS_BeginHudMessage();
		/*__n*/printf(msg[i]);
		ACS_MoreHudMessage();
		ACS_OptHudMessage(HUDMSG_TYPEON, 0, CR_DARKGREEN, 0.5, -0.75, 1.0);
		ACS_EndHudMessage(0.1, 2.5);
		
		ACS_Delay(300);
	}
}

[[call("ScriptS")]]
void show_cutscene(void)
{
	struct Hud_image advisory = {
		s"ADVISOR", 320, 240, 9, 5.0, 2.0, 1.0, 300
	};
	
	const int cutscene_amount = 17;
	
	struct Hud_image cutscene[] = {
		{s"CUT1A1", 640, 480, 9, 5.0, 2.0, 1.0, 300},
		{s"CUT1B1", 640, 480, 9, 0.0, 0.0, 0.0, 10},
		{s"CUT1B2", 640, 480, 9, 0.0, 0.0, 0.0, 10},
		{s"CUT1B3", 640, 480, 9, 0.0, 0.0, 0.0, 10},
		{s"CUT1B4", 640, 480, 9, 0.0, 0.0, 0.0, 10},
		{s"CUT1B5", 640, 480, 9, 0.0, 0.0, 0.0, 10},
		{s"CUT1B6", 640, 480, 9, 0.0, 0.0, 0.0, 12},
		{s"CUT1B7", 640, 480, 9, 0.0, 0.0, 0.0, 10},
		{s"CUT1B8", 640, 480, 9, 0.0, 0.0, 0.0, 10},
		{s"CUT1B9", 640, 480, 9, 0.0, 0.0, 0.0, 12},
		{s"CUT1B10",640, 480, 9, 0.0, 0.0, 0.0, 14},
		{s"CUT1B11",640, 480, 9, 0.0, 0.0, 0.0, 50},
		{s"CUT1B12",640, 480, 9, 2.0, 0.0, 1.0, 200},
		{s"CUT1C1", 640, 480, 9, 5.0, 2.0, 1.0, 300},
		{s"CUT1D1", 640, 480, 9, 5.0, 2.0, 1.0, 300},
		{s"CUT1E1", 640, 480, 9, 5.0, 2.0, 1.0, 300},
		{s"CUT1F1", 640, 480, 9, 0.0, 0.0, 0.0, 0}
	};
	
	display_image(advisory);
	ACS_Delay(advisory.delay);
	
	for(int i = 0; i < cutscene_amount; ++i)
	{
		display_image(cutscene[i]);
		ACS_Delay(cutscene[i].delay);
	}
	
}

void display_image(struct Hud_image image)
{
	ACS_SetFont(image.font);
	ACS_SetHudSize(image.width, image.height, FALSE);
	
	ACS_BeginHudMessage();
	ACS_PrintChar('A');
	ACS_MoreHudMessage();
	
	if(image.fadeout_time > 0.0) { // use HUDMSG_FADEOUT or HUDMSG_FADEINOUT
		if(image.fadein_time > 0.0) { // use HUDMSG_FADEINOUT
			ACS_OptHudMessage(HUDMSG_FADEINOUT, image.msg_id, CR_UNTRANSLATED, 0.5, 0.5, image.hold_time);
			ACS_EndHudMessage(image.fadein_time, image.fadeout_time);
		} else { // use HUDMSG_FADEOUT
			ACS_OptHudMessage(HUDMSG_FADEOUT, image.msg_id, CR_UNTRANSLATED, 0.5, 0.5, image.hold_time);
			ACS_EndHudMessage(0.0, image.fadeout_time);
		}
	} else { // use HUDMSG_PLAIN
		ACS_OptHudMessage(HUDMSG_PLAIN, image.msg_id, CR_UNTRANSLATED, 0.5, 0.5, image.hold_time);
		ACS_EndHudMessage();
	}
}
