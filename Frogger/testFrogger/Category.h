#pragma once

namespace Category
{
	enum Typen
	{
		None = 0,
		BackgroundLayer = 1 << 0,
		Frogger = 1 << 1,

		Auto = 1 << 2,
		Truck = 1 << 3,
		Alligator = 1 << 4,
		Zweierkroete = 1 << 5,
		Zweierkroete_Untertauchen = 1 << 6,
		Dreierkroete = 1 << 7,
		Dreierkroete_Untertauchen = 1 << 8,
		Stamm = 1 << 9,
		Pinkerfrosh = 1 << 10,
		Schlange = 1 << 11,
		Fliege = 1 << 12,
		

		Fluss = 1 << 13,
		Ziel = 1 << 14,

		Punkte = 1 << 15,

		Fahrzeuge = Auto | Truck,
		SchwimmendeGegner = Alligator | Zweierkroete | Zweierkroete_Untertauchen | Dreierkroete | Dreierkroete_Untertauchen | Stamm | Ziel,

		NPC = Fahrzeuge | SchwimmendeGegner
	};
}

