#include "GameSession.hpp"
#include "MockSceneItemFactory.hpp"
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

TEST_F(GameSessionTests, addPlayer_OneNewPlayer_ReturnNewPlayerIdAndAddPlayerSceneItem)
{
    auto factory { std::make_unique<MockSceneItemFactory>() };
    EXPECT_CALL(*factory, create(_, _, _));
    GameSessionTestable gameSession { std::move(factory) };

    const auto resultPlayerId { gameSession.addPlayer() };

    EXPECT_EQ(0, resultPlayerId);
    const auto& resultPlayerObjects { gameSession.getPlayersObjects() };
    EXPECT_EQ(1, resultPlayerObjects.size());
    EXPECT_NO_THROW(resultPlayerObjects.at(resultPlayerId));
}

TEST_F(GameSessionTests, addPlayer_TwoNewPlayers_ReturnUniqueIdPerPlayerAndAddPlayerSceneItems)
{
    auto factory { std::make_unique<MockSceneItemFactory>() };
    EXPECT_CALL(*factory, create(_, _, _)).Times(2);
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
    auto factory { std::make_unique<MockSceneItemFactory>() };
    EXPECT_CALL(*factory, create(_, _, _));
    GameSessionTestable gameSession { std::move(factory) };
    const auto playerIdToRemove { gameSession.addPlayer() };

    gameSession.removePlayer(playerIdToRemove);

    const auto& resultPlayerObjects { gameSession.getPlayersObjects() };
    EXPECT_TRUE(resultPlayerObjects.empty());
}

TEST_F(GameSessionTests, removePlayer_PlayerIdNotMatch_DoNothing)
{
    auto factory { std::make_unique<MockSceneItemFactory>() };
    EXPECT_CALL(*factory, create(_, _, _));
    GameSessionTestable gameSession { std::move(factory) };
    const auto playerId { gameSession.addPlayer() };

    ASSERT_NO_THROW(gameSession.removePlayer(542));

    const auto& resultPlayerObjects { gameSession.getPlayersObjects() };
    EXPECT_FALSE(resultPlayerObjects.empty());
    EXPECT_NO_THROW(resultPlayerObjects.at(playerId));
}

TEST_F(GameSessionTests, getUpdateForPlayer_NoAddedPlayers_ReturnEmptyGameplayUpdate)
{
    auto factory { std::make_unique<MockSceneItemFactory>() };
    const GameSessionTestable gameSession { std::move(factory) };

    const auto resultGameplayUpdate { gameSession.getUpdateForPlayer(0) };

    const auto resultSceneUpdate { resultGameplayUpdate.gameSceneUpdate };
    EXPECT_TRUE(resultSceneUpdate.sceneItems.empty());
}

TEST_F(GameSessionTests, getUpdateForPlayer_OnePlayerAddedButIdNotMatch_ReturnEmptyGameplayUpdate)
{
    const Position expectedPlayerPosition { 0.0F, 0.0F };
    auto factory { std::make_unique<MockSceneItemFactory>() };
    EXPECT_CALL(*factory, create(_, _, _));
    GameSessionTestable gameSession { std::move(factory) };
    const auto playerId { gameSession.addPlayer() };

    const auto resultGameplayUpdate { gameSession.getUpdateForPlayer(1) };

    EXPECT_EQ(0, playerId);
    const auto resultSceneUpdate { resultGameplayUpdate.gameSceneUpdate };
    EXPECT_TRUE(resultSceneUpdate.mapName.empty());
    EXPECT_EQ(expectedPlayerPosition, resultSceneUpdate.playerGlobalPosition);
    EXPECT_TRUE(resultSceneUpdate.sceneItems.empty());
}

TEST_F(GameSessionTests, getUpdateForPlayer_OnePlayerAddedAndIdMatch_ReturnGameplayUpdateWithMapNameAndPlayerPosition)
{
    const Position expectedPlayerPosition { 2500.0F, 2500.0F };
    auto factory { std::make_unique<MockSceneItemFactory>() };
    EXPECT_CALL(*factory, create(_, _, _)).WillOnce(Return(SceneItem { 0, SceneItemType::PLAYER, expectedPlayerPosition, 0.0F }));
    GameSessionTestable gameSession { std::move(factory) };
    const auto playerId { gameSession.addPlayer() };

    const auto resultGameplayUpdate { gameSession.getUpdateForPlayer(playerId) };

    const auto resultSceneUpdate { resultGameplayUpdate.gameSceneUpdate };
    EXPECT_EQ("map01", resultSceneUpdate.mapName);
    EXPECT_EQ(expectedPlayerPosition, resultSceneUpdate.playerGlobalPosition);
    EXPECT_EQ(0, resultSceneUpdate.sceneItems.size());
}

struct MovePlayerParams
{
    Direction moveDirection;
    Velocity moveVelocity;
    Position expectedPlayerPosition;
    Rotation expectedPlayerRotation;
};

class GameSessionTestsWithMovePlayer : public TestWithParam<MovePlayerParams>
{
};

const std::vector<MovePlayerParams> movePlayerParams {
    {
        Direction::FRONT,
        0.0F,
        { 2500.0F, 2500.0F },
        0.0F,
    },
    {
        Direction::FRONT,
        1.0F,
        { 2500.0F, 2499.0F },
        0.0F,
    },
    {
        Direction::FRONT_RIGHT,
        2.0F,
        { 2502.0F, 2498.0F },
        45.0F,
    },
    {
        Direction::RIGHT,
        1.0F,
        { 2501.0F, 2500.0F },
        90.0F,
    },
    {
        Direction::BACK_RIGHT,
        1.0F,
        { 2501.0F, 2501.0F },
        135.0F,
    },
    {
        Direction::BACK,
        1.0F,
        { 2500.0F, 2501.0F },
        180.0F,
    },
    {
        Direction::BACK_LEFT,
        1.0F,
        { 2499.0F, 2501.0F },
        225.0F,
    },
    {
        Direction::LEFT,
        1.0F,
        { 2499.0F, 2500.0F },
        270.0F,
    },
    {
        Direction::FRONT_LEFT,
        1.0F,
        { 2499.0F, 2499.0F },
        315.0F,
    }
};

TEST_P(GameSessionTestsWithMovePlayer, updateGameWorld_PlayerMove_UpdatePlayerPositionAndRotation)
{
    const auto& params = GetParam();
    auto factory { std::make_unique<MockSceneItemFactory>() };
    EXPECT_CALL(*factory, create(_, _, _)).WillOnce(Return(SceneItem { 0, SceneItemType::PLAYER, Position{ 2500.0F, 2500.0F }, 0.0F }));
    GameSessionTestable gameSession { std::move(factory) };
    const auto playerId { gameSession.addPlayer() };
    PlayerStatus status;
    status.moveDirection = params.moveDirection;
    status.moveVelocity = params.moveVelocity;
    gameSession.queuePlayerStatus(playerId, status);

    gameSession.updateGameWorld();

    const auto resultGameplayUpdate { gameSession.getUpdateForPlayer(playerId) };
    const auto resultSceneUpdate { resultGameplayUpdate.gameSceneUpdate };
    EXPECT_EQ(params.expectedPlayerPosition, resultSceneUpdate.playerGlobalPosition);
    EXPECT_EQ(params.expectedPlayerRotation, resultSceneUpdate.playerRotation);
}

INSTANTIATE_TEST_CASE_P(MovePlayer, GameSessionTestsWithMovePlayer, ValuesIn(movePlayerParams));
