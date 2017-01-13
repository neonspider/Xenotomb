#include "actors/weapons.zs"
#include "actors/monsters.zs"
#include "actors/decorations.zs"

#include "src/maps/gui_test/actors.zs"

class XenoPlayer : DoomPlayer // Change Player Speed
{
	Default
	{
		Player.ForwardMove 0.7;
		Player.SideMove 0.7;
		Player.JumpZ 10;
	}
}

class CutsceneMode : Inventory // used to hide STBAR during cutscenes
{
	Default
	{
		Inventory.MaxAmount 1;
	}
}
