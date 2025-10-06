#pragma once

#include <Client.hpp>
#include <PlayerStatus.hpp>
#include <memory>

class GameSession
{
public:
    using PlayerID = int;

    virtual ~GameSession() = default;

    virtual void start();
    virtual void stop();
    virtual PlayerID addPlayer();
    virtual void removePlayer(const PlayerID& playerId);
    virtual void queuePlayerStatus(const PlayerID& playerId, const PlayerStatus& playerStatus);
    virtual void updateGameWorld();
    virtual std::unique_ptr<GameplayUpdate> getUpdateForPlayer(const PlayerID& playerId) const;
};
