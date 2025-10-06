#pragma once

#include <PlayerInput.hpp>
#include <functional>
#include <memory>
#include <utility>

enum class GameCommand : char
{
    Pause = 0,
    NoCommand = 1
};

using GameConnection = std::function<void(const GameCommand&)>;

struct GameSceneUpdate
{

};

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
    GameSceneUpdate gameSceneUpdate;
    HUDUpdate hudUpdate;
};


class Client
{
public:
    virtual ~Client() = default;

    virtual void connect(const GameConnection& connection) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void receive(const PlayerInputCommand& command) = 0;
    [[nodiscard]] virtual PlayerStatus status() const = 0;
    virtual void update(std::unique_ptr<GameplayUpdate> gameplayUpdate) = 0;
};
