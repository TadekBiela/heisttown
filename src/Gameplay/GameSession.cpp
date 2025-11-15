#include "GameSession.hpp"

GameSession::GameSession(std::unique_ptr<GameObjectFactory> inputFactory)
    : factory(std::move(inputFactory))
{
    if (factory == nullptr)
    {
        factory = std::make_unique<GameObjectFactory>();
    }
}

void GameSession::start()
{
}

void GameSession::stop()
{
}

GameSession::PlayerID GameSession::addPlayer()
{
    playersObjects[playerIdCounter] = factory->create(GoType::PLAYER, { 0, 0 }, 0);
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
        sceneUpdate.gameObjects.push_back(playersObjects.at(playerId));
        return update;
    }
    return GameplayUpdate {};
}
