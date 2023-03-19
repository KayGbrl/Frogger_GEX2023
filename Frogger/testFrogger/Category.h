#pragma once

namespace Category
{
	enum Typen
	{
		None = 0,
		BackgroundLayer = 1 << 0,
		Frogger = 1 << 1,

		Car = 1 << 2,
		Truck = 1 << 3,
		Alligator = 1 << 4,
		Turtle2 = 1 << 5,
		Turtle2_floating = 1 << 6,
		Turtle3 = 1 << 7,
		Turtle3_floating = 1 << 8,
		Log = 1 << 9,
		PinkFrog = 1 << 10,
		Snake = 1 << 11,

		River = 1 << 13,
		WinningSpot = 1 << 14,

		Score = 1 << 15,

		Vehicle = Car | Truck,
		SwimmingNPC = Alligator | Turtle2 | Turtle2_floating | Turtle3 | Turtle3_floating | Log | WinningSpot,

		NPC = Vehicle | SwimmingNPC
	};
}

