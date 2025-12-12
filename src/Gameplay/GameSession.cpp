#include "GameSession.hpp"

GameSession::GameSession(std::unique_ptr<SceneItemFactory> inputFactory)
    : factory(std::move(inputFactory))
{
    if (factory == nullptr)
    {
        factory = std::make_unique<SceneItemFactory>();
    }
}

GameSession::PlayerID GameSession::addPlayer()
{
    playersObjects[playerIdCounter] = factory->create(SceneItemType::PLAYER, { 2500.0, 2500.0 }, 0.0);
    return playerIdCounter++;
}

void GameSession::removePlayer(const PlayerID& playerId)
{
    playersObjects.erase(playerId);
}

void GameSession::queuePlayerStatus(const PlayerID& playerId, const PlayerStatus& playerStatus)
{
    (void)playerId;
    (void)playerStatus;
}

void GameSession::updateGameWorld()
{
}

GameplayUpdate GameSession::getUpdateForPlayer(const PlayerID& playerId) const
{
    if (playersObjects.find(playerId) != playersObjects.end())
    {
        GameplayUpdate update;
        auto& sceneUpdate { update.gameSceneUpdate };
        sceneUpdate.mapName = "map01";
        const auto& player { playersObjects.at(playerId) };
        sceneUpdate.playerGlobalPosition.x = player.position.x;
        sceneUpdate.playerGlobalPosition.y = player.position.y;
        return update;
    }
    return GameplayUpdate {};
}
