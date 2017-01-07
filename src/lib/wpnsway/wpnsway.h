#ifndef WPNSWAY_H
#define WPNSWAY_H

#include <ACS_ZDoom.h>

#include <stdfix.h>

[[call("ScriptS"), script("Enter")]]
void main(void);

[[call("ScriptS"), extern("ACS")]]
fixed get_gun_offset_x (void);

[[call("ScriptS"), extern("ACS")]]
fixed get_gun_offset_y (void);

fixed target_velocity(fixed d, fixed v, fixed a);

fixed update_velocity(fixed d, fixed v, fixed a);

#endif	// WPNSWAY_H
