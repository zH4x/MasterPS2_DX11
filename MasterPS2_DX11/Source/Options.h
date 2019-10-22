#pragma once

#include <string>

#define OPTION(type, var, val) type var = val

class Option
{
public:
	// 
	// AIMBOT
	// 
	OPTION(bool, aimbot, true);
	OPTION(bool, aimbot_aimtohead, false);
	OPTION(bool, aimbot_circlerange, true);
	OPTION(int, aimbot_fov, 150);

	// 
	// VISUALS
	// 
	OPTION(bool, visuals, true);
	OPTION(bool, visuals_box, true);
	OPTION(bool, visuals_snaplines, true);
	OPTION(bool, visuals_showdistance, true);
	OPTION(bool, visuals_showname, false);

	OPTION(bool, visuals_showplayers, true);
	OPTION(bool, visuals_showvehicules, false);
	OPTION(bool, visuals_showallies, false);

	OPTION(bool, visuals_notreeleaves, true);

	// 
	// MISK
	// 
	OPTION(bool, speedhack, true);
	OPTION(int, speedhack_velocity, 8);

	OPTION(bool, jetpack, false);
	OPTION(int, jetpack_velocity, 310);

	// 
	// NOCLIP
	// 
	OPTION(bool, noclip, true);
	OPTION(bool, noclip_active, false);
	OPTION(int, noclip_speed, 0); // 0 to 4

	// 
	// TELEPORT
	// 
	OPTION(bool, teleport, false);
	OPTION(bool, teleport_active, false);

};

extern Option g_Options;

