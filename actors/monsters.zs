class Chomper : Actor
{
	Default
	{
		Health 20;
		Radius 24;
		Height 32;
		BloodColor "10, 240, 100";
		Monster;
		Obituary "%o was chomped up by an alien chomper.";
		DeathSound "chomper/death";
		+SHOOTABLE
		+SOLID
	}
	
	States
	{
		Spawn:
			CHMP A -1;
			Loop;
		Death:
			CHMP A -1 A_Scream;
			Stop;
	}
}

class Worker : Actor
{
	Default
	{
		Health 60;
		Radius 24;
		Height 64;
		BloodColor "10, 240, 100";
		Monster;
		Obituary "%o was slimed by an alien worker.";
		DeathSound "chomper/death";
		+SHOOTABLE
		+SOLID
	}
	
	States
	{
		Spawn:
			WORK A -1;
			Loop;
		Death:
			WORK A -1 A_Scream;
			Stop;
	}
}