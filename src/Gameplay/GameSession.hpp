#pragma once

#include "GameplayUpdate.hpp"
#include <SceneItem.hpp>
#include <SceneItemFactory.hpp>
#include <PlayerStatus.hpp>
#include <map>
#include <memory>

class GameSession
{
public:
    using PlayerID = int;
    using PlayersObjects = std::map<PlayerID, SceneItem>;

    explicit GameSession(std::unique_ptr<SceneItemFactory> inputFactory = nullptr);
    virtual ~GameSession() = default;

    [[nodiscard]] virtual PlayerID addPlayer();
    virtual void removePlayer(const PlayerID& playerId);
    virtual void queuePlayerStatus(const PlayerID& playerId, const PlayerStatus& playerStatus);
    virtual void updateGameWorld();
    [[nodiscard]] virtual GameplayUpdate getUpdateForPlayer(const PlayerID& playerId) const;

protected:
    std::unique_ptr<SceneItemFactory> factory;
    PlayersObjects playersObjects;

private:
    PlayerID playerIdCounter { 0 };
};
