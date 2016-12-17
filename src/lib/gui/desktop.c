#include <ACS_ZDoom.h>

#include <stdio.h>

#include "desktop.h"
#include "window.h"

struct gui_Desktop {
	struct Window* window;
	int window_amount;
	
	int camera_tid;
	
	// output device
	
	/* int lineid; // line of the background
	char* image; */
	
	int near_z; // distance from camera to background/reference line
	
};
