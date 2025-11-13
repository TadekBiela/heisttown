#include "GameSession.hpp"

void GameSession::start()
{
}

void GameSession::stop()
{
}

GameSession::PlayerID GameSession::addPlayer()
{
    return 0;
}

void GameSession::removePlayer(const PlayerID& playerId)
{
    (void)playerId;
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
    (void)playerId;
    return GameplayUpdate{};
}
