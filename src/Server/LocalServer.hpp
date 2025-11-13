#pragma once

#include "GameSession.hpp"
#include "Server.hpp"
#include <Client.hpp>
#include <atomic>
#include <memory>
#include <thread>
#include <map>
#include <utility>

class LocalServer : public Server
{
public:
    using GameplayClient = std::pair<GameSession::PlayerID, std::shared_ptr<Client>>;
    using Clients = std::map<GameplayClient::first_type, GameplayClient::second_type>;

    explicit LocalServer(std::unique_ptr<GameSession> newGameSession);
    ~LocalServer() override;

    void start() override;
    void stop() override;
    void connect(std::shared_ptr<Client> client) override;
    void disconnect(std::shared_ptr<Client> client) override;

protected:
    std::atomic<bool> running { false };
    Clients clients;

private:
    std::thread runningThread;
    std::unique_ptr<GameSession> gameSession;

    [[nodiscard]] bool isConnected(const std::shared_ptr<Client>& client) const;
    [[nodiscard]] const GameSession::PlayerID& getPlayerId(const std::shared_ptr<Client>& client) const;
};
