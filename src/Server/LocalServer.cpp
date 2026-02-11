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
    running.store(true);

    runningThread = std::thread([this]()
                                {
            while (running.load())
            {
                std::vector<std::pair<PlayerID, std::shared_ptr<Client>>> activeClients;

                {
                    const std::lock_guard lock(clientsMutex);
                    for (auto it = clients.begin(); it != clients.end(); )
                    {
                        if (auto client = it->second.lock())
                        {
                            activeClients.emplace_back(it->first, client);
                            ++it;
                        }
                        else
                        {
                            it = clients.erase(it);
                        }
                    }
                }

                for (auto& [id, client] : activeClients)
                {
                    gameSession->queuePlayerStatus(id, client->status());
                }

                gameSession->updateGameWorld();

                for (auto& [id, client] : activeClients)
                {
                    client->update(gameSession->getUpdateForPlayer(id));
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            } }
    );
}

void LocalServer::stop()
{
    running.store(false);

    if (runningThread.joinable())
    {
        runningThread.join();
    }
}

PlayerID LocalServer::connect(const std::shared_ptr<Client>& client)
{
    PlayerID newPlayerId { -1 };

    const std::lock_guard<std::mutex> lockClients(clientsMutex);
    if (not isConnected(client))
    {
        newPlayerId = gameSession->addPlayer();
        clients[newPlayerId] = client;
    }

    return newPlayerId;
}

bool LocalServer::isConnected(const std::shared_ptr<Client>& client) const
{
    return (
        std::find_if(
            clients.begin(),
            clients.end(),
            [&client](const auto& gameplayClientPtr)
            {
                if (auto gameplayClient = gameplayClientPtr.second.lock())
                {
                    return gameplayClient == client;
                }
                return false;
            }
        ) != clients.end()
    );
}

void LocalServer::disconnect(const PlayerID& playerID)
{
    const std::lock_guard<std::mutex> lockClients(clientsMutex);
    if (clients.find(playerID) != clients.cend())
    {
        gameSession->removePlayer(playerID);
        clients.erase(playerID);
    }
}
