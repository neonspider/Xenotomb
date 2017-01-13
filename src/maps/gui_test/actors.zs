class GuiCursor : BulletPuff	// from zk-chase.pk3
{
	Default
	{
		VSpeed 0;	// stops it moving upwards
		+ALLOWTHRUFLAGS
		+THRUACTORS
		+ACTIVATEIMPACT
		Radius 0;
		Height 0;
	}
}

class GuiShooter : MapSpot
{
	Default
	{
		Radius 0;
		Height 0;
	}
}

class GuiMarker : MapSpot
{
	Default
	{
		Radius 0;
		Height 0;
	}
}
