#include <ACS_ZDoom.h>

#include <stdfix.h>
#include <stdlib.h>
#include <math.h>

#include "../xenutils/utils.h"
#include "wpnsway.h"

enum {strafe_accel = 8.0k, vert_accel = 8.0k,
		look_straight_accel = 8.0k, look_side_accel = 8.0k};
		
enum {strafe_amount = 0.1k, vert_amount = 0.1k,
		look_amountx = 0.1k, look_amounty = 0.1k};
		
enum {offset_clamp_left = -32.0k, offset_clamp_right = 32.0k,
		offset_clamp_up = 0.0k, offset_clamp_down = 64.0k};

struct Vec2 gun_offset = {0.0k, 32.0k};

[[call("ScriptS"), script("Enter")]]
void main(void)
{
	fixed player_dist_strafe = 0.0k;
	fixed weapon_dist_strafe = 0.0k;
	
	fixed weapon_vel_strafe = 0.0k;
	
	
	fixed player_dist_vert; // TODO
	fixed weapon_dist_vert;
	fixed weapon_vel_vert;
	fixed player_dist_look_straight;
	fixed weapon_dist_look_straight;
	fixed weapon_vel_look_straight;
	fixed player_dist_look_side;
	fixed weapon_dist_look_side;
	fixed weapon_vel_look_side;
	
	// calculate x value
	fixed target_vel_strafe = target_velocity(player_dist_strafe - weapon_dist_strafe, weapon_vel_strafe, strafe_accel);
	fixed target_vel_vert = target_velocity(player_dist_vert - weapon_dist_vert, weapon_vel_vert, vert_accel);
	fixed target_vel_look_straight = target_velocity(player_dist_look_straight - weapon_dist_look_straight, weapon_vel_look_straight, look_straight_accel);
	fixed target_vel_look_side = target_velocity(player_dist_look_side - weapon_dist_look_side, weapon_vel_look_side, look_side_accel);
	
	for(;;) {
		struct Vec2	vel_horz = {ACS_GetActorVelX(0), ACS_GetActorVelY(0)};
		fixed 			vel_vert = ACS_GetActorVelZ(0);
		
		fixed angle = angle_to_radians(ACS_GetActorAngle(0));
		fixed pitch = pitch_to_radians(ACS_GetActorPitch(0));
		
		// horizontal movement
		struct Vec2 player_view = rotate_point(vel_horz, angle);
		fixed player_vel_strafe = player_view.x;
		
		player_dist_strafe += player_vel_strafe;
		weapon_dist_strafe += weapon_vel_strafe;
		
		// vertical movement
		
		// freelook
		
		ACS_Delay(1);
	}
}

[[call("ScriptS"), extern("ACS")]]
fixed get_gun_offset_x (void)
{
	return gun_offset.x;
}

[[call("ScriptS"), extern("ACS")]]
fixed get_gun_offset_y (void)
{
	return gun_offset.y;
}

fixed target_velocity(fixed d, fixed v, fixed a)
{
	a = copysign(a, d);
	return copysign(sqrt(v * (v - a) / 2 + a * d), d);
}

fixed update_velocity(fixed v, fixed x, fixed a)
{
	if (v < x) {
		v = clamp(v + abs(a), v, x);
	} else if (v > x) {
		v = clamp(v - abs(a), v, x);
	} else { // v == x
		v = clamp(v - a, v, x);
	}
	
	return v;
}
