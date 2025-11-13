#pragma once

#include "GameplayUpdate.hpp"
#include <PlayerStatus.hpp>

class GameSession
{
public:
    using PlayerID = int;

    virtual ~GameSession() = default;

    virtual void start();
    virtual void stop();
    [[nodiscard]] virtual PlayerID addPlayer();
    virtual void removePlayer(const PlayerID& playerId);
    virtual void queuePlayerStatus(const PlayerID& playerId, const PlayerStatus& playerStatus);
    virtual void updateGameWorld();
    [[nodiscard]] virtual GameplayUpdate getUpdateForPlayer(const PlayerID& playerId) const;
};
