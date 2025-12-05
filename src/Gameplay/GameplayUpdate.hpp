#pragma once

#include "SceneUpdate.hpp"
#include <utility>

using Health = float;
using Armor = float;
using Magazine = int;
using NumOfMagazines = int;
using Ammo = std::pair<Magazine, NumOfMagazines>;

struct HUDUpdate
{
    Health health { 0.0 };
    Armor armor { 0.0 };
    Ammo ammo { 0, 0 };
};

struct GameplayUpdate
{
    SceneUpdate gameSceneUpdate;
    HUDUpdate hudUpdate;
};
