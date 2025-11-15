#include "LocalServer.hpp"
#include <Client.hpp>
#include <memory>

LocalServer::LocalServer(std::unique_ptr<GameSession> newGameSession)
    : gameSession(std::move(newGameSession))
{
    if (gameSession == nullptr)
    {
        gameSession = std::make_unique<GameSession>();
    }
}

LocalServer::~LocalServer()
{
    if (runningThread.joinable())
    {
        runningThread.join();
    }
}

void LocalServer::start()
{
    running = true;

    runningThread = std::thread(
        [this]()
        {
            while (running)
            {
                for (const auto& client : clients)
                {
                    gameSession->queuePlayerStatus(client.first, client.second->status());
                }

                gameSession->updateGameWorld();

                for (auto& client : clients)
                {
                    client.second->update(gameSession->getUpdateForPlayer(client.first));
                }
            }
        }
    );
}

void LocalServer::stop()
{
    running = false;

    if (runningThread.joinable())
    {
        runningThread.join();
    }
}

void LocalServer::connect(std::shared_ptr<Client> client)
{
    if (not isConnected(client))
    {
        clients[gameSession->addPlayer()] = client;
    }
}

bool LocalServer::isConnected(const std::shared_ptr<Client>& client) const
{
    return (
        std::find_if(
            clients.begin(),
            clients.end(),
            [&client](const auto& gameplayClient)
            {
                return gameplayClient.second == client;
            }
        ) != clients.end()
    );
}

void LocalServer::disconnect(std::shared_ptr<Client> client)
{
    if (isConnected(client))
    {
        const auto removingPlayerId { getPlayerId(client) };
        gameSession->removePlayer(removingPlayerId);
        clients.erase(removingPlayerId);
    }
}

const GameSession::PlayerID& LocalServer::getPlayerId(const std::shared_ptr<Client>& client) const
{
    const auto& gameplayClient {
        std::find_if(
            clients.begin(),
            clients.end(),
            [&client](const auto& gameplayClient)
            {
                return gameplayClient.second == client;
            }
        )
    };
    return gameplayClient->first;
}
