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
    queuedPlayerStatuses[playerId] = playerStatus;
}

void GameSession::updateGameWorld()
{
    for (const auto& status : queuedPlayerStatuses)
    {
        auto& player { playersObjects[status.first] };
        switch (status.second.moveDirection)
        {
            case Direction::FRONT:
            {
                player.rotation = 0.0F;
                player.position.y -= status.second.moveVelocity;
                break;
            }
            case Direction::FRONT_RIGHT:
            {
                player.rotation = 45.0F;
                player.position.x += status.second.moveVelocity;
                player.position.y -= status.second.moveVelocity;
                break;
            }
            case Direction::RIGHT:
            {
                player.rotation = 90.0F;
                player.position.x += status.second.moveVelocity;
                break;
            }
            case Direction::BACK_RIGHT:
            {
                player.rotation = 135.0F;
                player.position.x += status.second.moveVelocity;
                player.position.y += status.second.moveVelocity;
                break;
            }
            case Direction::BACK:
            {
                player.rotation = 180.0F;
                player.position.y += status.second.moveVelocity;
                break;
            }
            case Direction::BACK_LEFT:
            {
                player.rotation = 225.0F;
                player.position.x -= status.second.moveVelocity;
                player.position.y += status.second.moveVelocity;
                break;
            }
            case Direction::LEFT:
            {
                player.rotation = 270.0F;
                player.position.x -= status.second.moveVelocity;
                break;
            }
            case Direction::FRONT_LEFT:
            {
                player.rotation = 315.0F;
                player.position.x -= status.second.moveVelocity;
                player.position.y -= status.second.moveVelocity;
                break;
            }
        }
    }
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
        sceneUpdate.playerRotation = player.rotation;
        return update;
    }
    return GameplayUpdate {};
}
