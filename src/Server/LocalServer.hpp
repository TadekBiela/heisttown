#pragma once

#include "Server.hpp"
#include <Client.hpp>
#include <GameSession.hpp>
#include <atomic>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

class LocalServer : public Server
{
public:
    using GameplayClient = std::pair<PlayerID, std::weak_ptr<Client>>;
    using Clients = std::map<GameplayClient::first_type, GameplayClient::second_type>;

    explicit LocalServer(std::unique_ptr<GameSession> newGameSession = nullptr);
    ~LocalServer() override;

    void start() override;
    void stop() override;
    PlayerID connect(const std::shared_ptr<Client>& client) override;
    void disconnect(const PlayerID& playerID) override;

protected:
    std::atomic<bool> running { false };
    Clients clients;
    mutable std::mutex clientsMutex;

private:
    std::thread runningThread;
    std::unique_ptr<GameSession> gameSession;

    [[nodiscard]] bool isConnected(const std::shared_ptr<Client>& client) const;
};
