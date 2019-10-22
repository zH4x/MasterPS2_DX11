#pragma once
#include <string>
#include <algorithm>
#include "..\EnumMacro.h"

DECLARE_ENUM(
Gender,

Male,
Female
)

DECLARE_ENUM(
GroundClasses,

Infiltrator,
LightAssault,
CombatMedic,
Engineer,
HeavyAssault,
MAX
)

DECLARE_ENUM(
GroundVehicules,

Quad,
Harasser,
Lightning,
Sunderer,
Prowler,
Vanguard,
Magrider,
Nanite
)

DECLARE_ENUM(
AirVehicules,

Valkyrie,
Liberator,
Galaxy,
Mosquito,
Reaver,
Scythe
)

enum class Faction
{
	VS = 1,	// Purple
	NC = 2, // Blue
	TR = 3,	// Red
	NS = 4,
	UnknownFaction
};

namespace Names
{
	static void toUpperCase(std::string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	}

	static bool ContainsString(std::string str, std::string substr)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		std::transform(substr.begin(), substr.end(), substr.begin(), ::toupper);

		return str.find(substr) != std::string::npos;
	}
}

