#include "LocalServer.hpp"
#include "MockGameSession.hpp"
#include <Client.hpp>
#include <LocalClient.hpp>
#include <MockClient.hpp>
#include <MockDisplay.hpp>
#include <MockPlayerInput.hpp>
#include <chrono>
#include <future>
#include <gtest/gtest.h>

#ifdef THREAD_SANITIZE
#define SKIP_IF_THREAD_SANITIZE() \
    GTEST_SKIP() << "Skipped under ThreadSanitizer."
#else
#define SKIP_IF_THREAD_SANITIZE()
#endif

using namespace testing;

class LocalServerTestable : public LocalServer
{
public:
    using LocalServer::LocalServer;

    bool isRunning()
    {
        return running;
    }

    [[nodiscard]] const Clients& getClients() const
    {
        return clients;
    }
};

class LocalServerTests : public ::testing::Test
{
public:
    void SetUp() override
    {
        firstTickPromise = std::make_shared<std::promise<void>>();
        firstTickFuture = firstTickPromise->get_future();
    }

    void syncThreadsBegin()
    {
        try
        {
            firstTickPromise->set_value();
        }
        catch (const std::future_error& exception)
        {
            if (exception.code() != std::make_error_code(std::future_errc::promise_already_satisfied))
            {
                throw;
            }
        }
    }

    void syncThreadsEnd()
    {
        auto status = firstTickFuture.wait_for(std::chrono::seconds(1));
        ASSERT_EQ(status, std::future_status::ready)
            << "Server thread did not call client->status() in time";
    }

    static std::unique_ptr<MockPlayerInput> getMockPlayerInput()
    {
        auto playerInput { std::make_unique<MockPlayerInput>() };
        EXPECT_CALL(*playerInput, setInputReceiver(_));
        EXPECT_CALL(*playerInput, getPlayerStatus()).WillRepeatedly(Return(PlayerStatus {}));
        return playerInput;
    }

    static std::shared_ptr<LocalClient> getLocalClient()
    {
        return std::make_shared<LocalClient>(
            std::make_unique<MockDisplay>(),
            getMockPlayerInput()
        );
    }

private:
    std::shared_ptr<std::promise<void>> firstTickPromise;
    std::future<void> firstTickFuture;
};

TEST_F(LocalServerTests, connect_AddOneClient_ClientsContainsOneElement)
{
    auto gameSession { std::make_unique<MockGameSession>() };
    const GameSession::PlayerID expectedPlayerId { 42 };
    EXPECT_CALL(*gameSession, addPlayer()).WillOnce(Return(expectedPlayerId));
    auto client { std::make_shared<MockClient>() };
    LocalServerTestable server { std::move(gameSession) };

    server.connect(client);

    const auto& resultClients { server.getClients() };
    ASSERT_EQ(1, resultClients.size());
    EXPECT_EQ(client, resultClients.at(expectedPlayerId));
}

TEST_F(LocalServerTests, connect_AddOneClientConnectedTwice_ClientsContainsOneElement)
{
    auto gameSession { std::make_unique<MockGameSession>() };
    const GameSession::PlayerID expectedPlayerId { 0 };
    EXPECT_CALL(*gameSession, addPlayer()).WillOnce(Return(expectedPlayerId));
    auto client { std::make_shared<MockClient>() };
    LocalServerTestable server { std::move(gameSession) };

    server.connect(client);
    server.connect(client);

    const auto& resultClients { server.getClients() };
    ASSERT_EQ(1, resultClients.size());
    EXPECT_EQ(client, resultClients.at(expectedPlayerId));
}

TEST_F(LocalServerTests, disconnect_ClientThatNotConnected_DoNothing)
{
    auto gameSession { std::make_unique<MockGameSession>() };
    EXPECT_CALL(*gameSession, removePlayer(_)).Times(0);
    auto client { std::make_shared<MockClient>() };
    LocalServerTestable server { std::move(gameSession) };

    server.disconnect(client);

    const auto& resultClients { server.getClients() };
    ASSERT_EQ(0, resultClients.size());
}

TEST_F(LocalServerTests, disconnect_ClientConnected_RemoveClientFromGameplay)
{
    const GameSession::PlayerID expectedPlayerId { 0 };
    auto gameSession { std::make_unique<MockGameSession>() };
    EXPECT_CALL(*gameSession, addPlayer()).WillOnce(Return(expectedPlayerId));
    EXPECT_CALL(*gameSession, removePlayer(expectedPlayerId));
    auto client { std::make_shared<MockClient>() };
    LocalServerTestable server { std::move(gameSession) };
    server.connect(client);

    server.disconnect(client);

    const auto& resultClients { server.getClients() };
    ASSERT_EQ(0, resultClients.size());
}

TEST_F(LocalServerTests, disconnect_ClientConnectedTryDisconnectwice_RemoveClientFromGameplayOnlyOnce)
{
    const GameSession::PlayerID expectedPlayerId { 0 };
    auto gameSession { std::make_unique<MockGameSession>() };
    EXPECT_CALL(*gameSession, addPlayer()).WillOnce(Return(expectedPlayerId));
    EXPECT_CALL(*gameSession, removePlayer(expectedPlayerId));
    auto client { std::make_shared<MockClient>() };
    LocalServerTestable server { std::move(gameSession) };
    server.connect(client);

    server.disconnect(client);
    server.disconnect(client);

    const auto& resultClients { server.getClients() };
    ASSERT_EQ(0, resultClients.size());
}

TEST_F(LocalServerTests, stop_NotStarted_StillRunningFalse)
{
    LocalServerTestable server {};

    EXPECT_NO_THROW(server.stop());

    EXPECT_FALSE(server.isRunning());
}

TEST_F(LocalServerTests, stop_ServerStarted_StopAndSetRunningFalse)
{
    LocalServerTestable server {};
    server.start();

    const bool isRunningBeforeStop { server.isRunning() };
    EXPECT_NO_THROW(server.stop());

    EXPECT_TRUE(isRunningBeforeStop);
    EXPECT_FALSE(server.isRunning());
}

TEST_F(LocalServerTests, start_NoClients_RunningSetToTrue)
{
    LocalServerTestable server {};

    server.start();

    EXPECT_TRUE(server.isRunning());
    EXPECT_NO_THROW(server.stop());
}

TEST_F(LocalServerTests, start_OneClientConnected_RunningGetStatusUpdateGameWorldAndSentGameplayUpdate)
{
    SKIP_IF_THREAD_SANITIZE();
    const GameSession::PlayerID expectedPlayerId { 0 };
    auto gameSession { std::make_unique<MockGameSession>() };
    EXPECT_CALL(*gameSession, addPlayer()).WillOnce(Return(expectedPlayerId));
    auto client { std::make_shared<MockClient>() };
    EXPECT_CALL(*client, status()).Times(AtLeast(1)).WillRepeatedly(Invoke([&]()
                                                                           {
            syncThreadsBegin();
            return PlayerStatus{}; }));
    EXPECT_CALL(*gameSession, queuePlayerStatus(expectedPlayerId, _)).Times(AtLeast(1));
    EXPECT_CALL(*gameSession, updateGameWorld()).Times(AtLeast(1));
    EXPECT_CALL(*gameSession, getUpdateForPlayer(expectedPlayerId)).Times(AtLeast(1)).WillRepeatedly(Invoke([](auto)
                                                                                                            { return std::make_unique<GameplayUpdate>(); }));
    EXPECT_CALL(*client, update(_)).Times(AtLeast(1));
    LocalServerTestable server { std::move(gameSession) };
    server.connect(client);

    server.start();

    syncThreadsEnd();
    EXPECT_TRUE(server.isRunning());
    EXPECT_NO_THROW(server.stop());
}

TEST_F(LocalServerTests, start_ThreeClientsConnected_RunningGetStatusFromAllUpdateGameWorldOnceAndSentGameplayUpdateToAll)
{
    SKIP_IF_THREAD_SANITIZE();
    auto gameSession { std::make_unique<MockGameSession>() };
    EXPECT_CALL(*gameSession, addPlayer()).Times(3).WillOnce(Return(0)).WillOnce(Return(1)).WillOnce(Return(2));
    EXPECT_CALL(*gameSession, queuePlayerStatus(_, _)).Times(AtLeast(3));
    EXPECT_CALL(*gameSession, updateGameWorld()).Times(AtLeast(1));
    EXPECT_CALL(*gameSession, getUpdateForPlayer(_)).Times(AtLeast(3)).WillRepeatedly(Invoke([](auto)
                                                                                             { return std::make_unique<GameplayUpdate>(); }));
    LocalServerTestable server { std::move(gameSession) };
    auto client1 { std::make_shared<MockClient>() };
    EXPECT_CALL(*client1, status()).Times(AtLeast(1)).WillOnce(Invoke([&]()
                                                                      {
            syncThreadsBegin();
            return PlayerStatus{}; }))
        .WillRepeatedly(Return(PlayerStatus {}));
    EXPECT_CALL(*client1, update(_)).Times(AtLeast(1));
    server.connect(client1);
    auto client2 { std::make_shared<MockClient>() };
    EXPECT_CALL(*client2, status()).Times(AtLeast(1)).WillRepeatedly(Return(PlayerStatus {}));
    EXPECT_CALL(*client2, update(_)).Times(AtLeast(1));
    server.connect(client2);
    auto client3 { std::make_shared<MockClient>() };
    EXPECT_CALL(*client3, status()).Times(AtLeast(1)).WillRepeatedly(Return(PlayerStatus {}));
    EXPECT_CALL(*client3, update(_)).Times(AtLeast(1));
    server.connect(client3);

    server.start();

    syncThreadsEnd();
    EXPECT_TRUE(server.isRunning());
    EXPECT_NO_THROW(server.stop());
}

TEST_F(LocalServerTests, start_ThreeClientsConnected_IsRunningTrue)
{
    LocalServerTestable server;
    auto client1 { getLocalClient() };
    server.connect(client1);
    auto client2 { getLocalClient() };
    server.connect(client2);
    auto client3 { getLocalClient() };
    server.connect(client3);

    server.start();

    EXPECT_TRUE(server.isRunning());
    EXPECT_NO_THROW(server.stop());
}
