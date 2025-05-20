#pragma once

#include "Menu.hpp"
#include <string>
#include <unordered_map>

using MenuName = std::string;
using Menus = std::unordered_map<MenuName, Menu>;
