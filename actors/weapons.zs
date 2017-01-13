// credit to Nash from weapon sway replacements
class X_DoomPlayer : DoomPlayer replaces DoomPlayer
{
	Default
	{
		Player.StartItem "X_Pistol";
		Player.StartItem "X_Fist";
		Player.StartItem "Clip", 50;
		Player.WeaponSlot 1, "X_Fist", "X_Chainsaw";
		Player.WeaponSlot 2, "X_Pistol";
		Player.WeaponSlot 3, "X_Shotgun", "X_SuperShotgun";
		Player.WeaponSlot 4, "X_Chaingun";
		Player.WeaponSlot 5, "X_RocketLauncher";
		Player.WeaponSlot 6, "X_PlasmaRifle";
		Player.WeaponSlot 7, "X_BFG9000";
	}
}

class X_Fist : Fist replaces Fist
{
	States
	{
		Ready:
			PUNG A 1
			{
				A_WeaponReady(0);
				A_WeaponOffset(CallACS("get_gun_offset_x"),
					CallACS("get_gun_offset_y", WOF_INTERPOLATE));
			}
			Loop;
		Fire:
			PUNG B 4;
			PUNG C 4 A_Punch;
			PUNG D 5;
			PUNG C 4;
			PUNG B 5 A_ReFire;
			Goto Ready;
	}
}

class X_Pistol : Pistol replaces Pistol
{
	Default
	{
		Weapon.BobRangeX 0.0;
		Weapon.BobRangeY 0.5;
		Weapon.BobSpeed 1.5;
		Weapon.BobStyle "Normal";
	}
	
	States
	{
		Ready:
			PISG A 1
			{
				A_WeaponReady(0);
				A_WeaponOffset(CallACS("get_gun_offset_x"),
					CallACS("get_gun_offset_y", WOF_INTERPOLATE));
			}
			Loop;
		Fire:
			PISG A 4;
			PISG B 6 A_FirePistol;
			PISG C 4;
			PISG B 5 A_ReFire;
			Goto Ready;
	}
}

class X_Chainsaw : Chainsaw replaces Chainsaw
{
	States
	{
		Ready:
			SAWG CD 4
			{
				A_WeaponReady(0);
				A_WeaponOffset(CallACS("get_gun_offset_x"),
					CallACS("get_gun_offset_y", WOF_INTERPOLATE));
			}
			Loop;
		Fire:
			SAWG AB 4 A_Saw;
			SAWG B 0 A_ReFire;
			Goto Ready;
	}
}

class X_Shotgun : Shotgun replaces Shotgun
{
	States
	{
		Ready:
			SHTG A 1
			{
				A_WeaponReady(0);
				A_WeaponOffset(CallACS("get_gun_offset_x"),
					CallACS("get_gun_offset_y", WOF_INTERPOLATE));
			}
			Loop;
		Fire:
			SHTG A 3;
			SHTG A 7 A_FireShotgun;
			SHTG BC 5;
			SHTG D 4;
			SHTG CB 5;
			SHTG A 3;
			SHTG A 7 A_ReFire;
			Goto Ready;
	}
}

class X_SuperShotgun : SuperShotgun replaces SuperShotgun
{
	States
	{
		Ready:
			SHT2 A 1
			{
				A_WeaponReady(0);
				A_WeaponOffset(CallACS("get_gun_offset_x"),
					CallACS("get_gun_offset_y", WOF_INTERPOLATE));
			}
			Loop;
		Fire:
			SHT2 A 3;
			SHT2 A 7 A_FireShotgun2;
			SHT2 B 7;
			SHT2 C 7 A_CheckReload;
			SHT2 D 7 A_OpenShotgun2;
			SHT2 E 7;
			SHT2 F 7 A_LoadShotgun2;
			SHT2 G 6;
			SHT2 H 6 A_CloseShotgun2;
			SHT2 A 5 A_ReFire;
			Goto Ready;
	}
}

class X_Chaingun : Chaingun replaces Chaingun
{
	States
	{
		Ready:
			CHGG A 1
			{
				A_WeaponReady(0);
				A_WeaponOffset(CallACS("get_gun_offset_x"),
					CallACS("get_gun_offset_y", WOF_INTERPOLATE));
			}
			Loop;
		Fire:
			CHGG AB 4 A_FireCGun;
			CHGG B 0 A_ReFire;
			Goto Ready;
	}
}

class X_RocketLauncher : RocketLauncher replaces RocketLauncher
{
	States
	{
		Ready:
			MISG A 1
			{
				A_WeaponReady(0);
				A_WeaponOffset(CallACS("get_gun_offset_x"),
					CallACS("get_gun_offset_y", WOF_INTERPOLATE));
			}
			Loop;
		Fire:
			MISG B 8 A_GunFlash;
			MISG B 12 A_FireMissile;
			MISG B 0 A_ReFire;
			Goto Ready;
	}
}

class X_PlasmaRifle : PlasmaRifle replaces PlasmaRifle
{
	States
	{
		Ready:
			PLSG A 1
			{
				A_WeaponReady(0);
				A_WeaponOffset(CallACS("get_gun_offset_x"),
					CallACS("get_gun_offset_y", WOF_INTERPOLATE));
			}
			Loop;
		Fire:
			PLSG A 3 A_FirePlasma;
			PLSG B 20 A_ReFire;
			Goto Ready;
	}
}

class X_BFG9000 : BFG9000 replaces BFG9000
{
	States
	{
		Ready:
			BFGG A 1
			{
				A_WeaponReady(0);
				A_WeaponOffset(CallACS("get_gun_offset_x"),
					CallACS("get_gun_offset_y", WOF_INTERPOLATE));
			}
			Loop;
		Fire:
			BFGG A 20 A_BFGsound;
			BFGG B 10 A_GunFlash;
			BFGG B 10 A_FireBFG;
			BFGG B 20 A_ReFire;
			Goto Ready;
	}
}
