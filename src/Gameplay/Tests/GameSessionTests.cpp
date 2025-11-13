#include "GameSession.hpp"
#include "MockGameObjectFactory.hpp"
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class GameSessionTestable : public GameSession
{
public:
    using GameSession::GameSession;

    [[nodiscard]] const PlayersObjects& getPlayersObjects() const
    {
        return playersObjects;
    }
};

class GameSessionTests : public Test
{
};

TEST_F(GameSessionTests, addPlayer_OneNewPlayer_ReturnNewPlayerIdAndAddPlayerGameObject)
{
    auto factory { std::make_unique<MockGameObjectFactory>() };
    EXPECT_CALL(*factory, create(_, _));
    GameSessionTestable gameSession { std::move(factory) };

    const auto resultPlayerId { gameSession.addPlayer() };

    EXPECT_EQ(0, resultPlayerId);
    const auto& resultPlayerObjects { gameSession.getPlayersObjects() };
    EXPECT_EQ(1, resultPlayerObjects.size());
    EXPECT_NO_THROW(resultPlayerObjects.at(resultPlayerId));
}

TEST_F(GameSessionTests, addPlayer_TwoNewPlayers_ReturnUniqueIdPerPlayerAndAddPlayerGameObjects)
{
    auto factory { std::make_unique<MockGameObjectFactory>() };
    EXPECT_CALL(*factory, create(_, _)).Times(2);
    GameSessionTestable gameSession { std::move(factory) };

    const auto resultPlayer1Id { gameSession.addPlayer() };
    const auto resultPlayer2Id { gameSession.addPlayer() };

    EXPECT_EQ(0, resultPlayer1Id);
    EXPECT_EQ(1, resultPlayer2Id);
    const auto& resultPlayerObjects { gameSession.getPlayersObjects() };
    EXPECT_EQ(2, resultPlayerObjects.size());
    EXPECT_NO_THROW(resultPlayerObjects.at(resultPlayer1Id));
    EXPECT_NO_THROW(resultPlayerObjects.at(resultPlayer2Id));
}

TEST_F(GameSessionTests, removePlayer_PlayerIdMatch_RemovePlayerFromSession)
{
    auto factory { std::make_unique<MockGameObjectFactory>() };
    EXPECT_CALL(*factory, create(_, _));
    GameSessionTestable gameSession { std::move(factory) };
    const auto playerIdToRemove { gameSession.addPlayer() };

    gameSession.removePlayer(playerIdToRemove);

    const auto& resultPlayerObjects { gameSession.getPlayersObjects() };
    EXPECT_TRUE(resultPlayerObjects.empty());
}

TEST_F(GameSessionTests, removePlayer_PlayerIdNotMatch_DoNothing)
{
    auto factory { std::make_unique<MockGameObjectFactory>() };
    EXPECT_CALL(*factory, create(_, _));
    GameSessionTestable gameSession { std::move(factory) };
    const auto playerId { gameSession.addPlayer() };

    ASSERT_NO_THROW(gameSession.removePlayer(542));

    const auto& resultPlayerObjects { gameSession.getPlayersObjects() };
    EXPECT_FALSE(resultPlayerObjects.empty());
    EXPECT_NO_THROW(resultPlayerObjects.at(playerId));
}

TEST_F(GameSessionTests, getUpdateForPlayer_NoAddedPlayers_ReturnEmptyGameplayUpdate)
{
    auto factory { std::make_unique<MockGameObjectFactory>() };
    const GameSessionTestable gameSession { std::move(factory) };

    const auto resultGameplayUpdate { gameSession.getUpdateForPlayer(0) };

    const auto resultGameSceneUpdate { resultGameplayUpdate.gameSceneUpdate };
    EXPECT_TRUE(resultGameSceneUpdate.gameObjects.empty());
}

TEST_F(GameSessionTests, getUpdateForPlayer_OnePlayerAddedButIdNotMatch_ReturnEmptyGameplayUpdate)
{
    auto factory { std::make_unique<MockGameObjectFactory>() };
    EXPECT_CALL(*factory, create(_, _));
    GameSessionTestable gameSession { std::move(factory) };
    const auto playerId { gameSession.addPlayer() };

    const auto resultGameplayUpdate { gameSession.getUpdateForPlayer(1) };

    EXPECT_EQ(0, playerId);
    const auto resultGameSceneUpdate { resultGameplayUpdate.gameSceneUpdate };
    EXPECT_TRUE(resultGameSceneUpdate.gameObjects.empty());
}

TEST_F(GameSessionTests, getUpdateForPlayer_OnePlayerAddedAndIdMatch_ReturnEGameplayUpdateWithOneGameObject)
{
    auto factory { std::make_unique<MockGameObjectFactory>() };
    EXPECT_CALL(*factory, create(_, _));
    GameSessionTestable gameSession { std::move(factory) };
    const auto playerId { gameSession.addPlayer() };

    const auto resultGameplayUpdate { gameSession.getUpdateForPlayer(playerId) };

    const auto resultGameSceneUpdate { resultGameplayUpdate.gameSceneUpdate };
    EXPECT_EQ(1, resultGameSceneUpdate.gameObjects.size());
}
