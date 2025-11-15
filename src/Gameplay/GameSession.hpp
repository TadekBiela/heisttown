#pragma once

#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include "GameplayUpdate.hpp"
#include <PlayerStatus.hpp>
#include <map>
#include <memory>

class GameSession
{
public:
    using PlayerID = int;
    using PlayersObjects = std::map<PlayerID, GameObject>;

    explicit GameSession(std::unique_ptr<GameObjectFactory> inputFactory = nullptr);
    virtual ~GameSession() = default;

    virtual void start();
    virtual void stop();
    [[nodiscard]] virtual PlayerID addPlayer();
    virtual void removePlayer(const PlayerID& playerId);
    virtual void queuePlayerStatus(const PlayerID& playerId, const PlayerStatus& playerStatus);
    virtual void updateGameWorld();
    [[nodiscard]] virtual GameplayUpdate getUpdateForPlayer(const PlayerID& playerId) const;

protected:
    std::unique_ptr<GameObjectFactory> factory;
    PlayersObjects playersObjects;

private:
    PlayerID playerIdCounter { 0 };
};
