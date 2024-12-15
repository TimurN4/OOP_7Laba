#include "../include/NPCManager.h"

NPCManager::NPCManager() : running(true) {
    initializeNPCs();
}

NPCManager::~NPCManager() {
    stopGame();
}

void NPCManager::initializeNPCs() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, MAP_WIDTH);
    std::uniform_int_distribution<> typeDis(0, 2);

    for (int i = 0; i < 50; ++i) {
        std::string type;
        int typeIndex = typeDis(gen);
        if (typeIndex == 0) type = "Bandit";
        else if (typeIndex == 1) type = "WanderingKnight";
        else type = "Elf";

        addNPC(type, type + std::to_string(i), dis(gen), dis(gen));
    }
}

void NPCManager::addNPC(const std::string& type, const std::string& name, int x, int y) {
    if (x < 0 || x > MAP_WIDTH || y < 0 || y > MAP_HEIGHT) {
        std::cerr << "Coordinates out of range (0 <= x, y <= " << MAP_WIDTH << ")" << std::endl;
        return;
    }
    std::unique_lock<std::shared_mutex> lock(npcsMutex);
    npcs.push_back(NPCFactory::createNPC(type, name, x, y));
}

void NPCManager::moveNPCs() {
    while (running) {
        std::shared_lock<std::shared_mutex> lock(npcsMutex);
        for (auto& npc : npcs) {
            if (npc->isAlive()) { 
                moveNPC(*npc);
            }
        }
        checkForBattles(); 
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void NPCManager::moveNPC(NPC& npc) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-npc.getMoveDistance(), npc.getMoveDistance());

    int dx = dis(gen);
    int dy = dis(gen);
    int newX = npc.getX() + dx;
    int newY = npc.getY() + dy;

    if (newX >= 0 && newX <= MAP_WIDTH && newY >= 0 && newY <= MAP_HEIGHT) {
        npc.setX(newX);
        npc.setY(newY);
    }
}

void NPCManager::checkForBattles() {
    std::shared_lock<std::shared_mutex> lock(npcsMutex);
    for (auto& attacker : npcs) {
        if (attacker->isAlive()) {
            for (auto& defender : npcs) {
                if (defender->isAlive() && attacker != defender) {
                    double distance = std::sqrt(std::pow(attacker->getX() - defender->getX(), 2) + std::pow(attacker->getY() - defender->getY(), 2));
                    if (distance <= attacker->getKillDistance()) {
                        std::lock_guard<std::mutex> battleLock(battleQueueMutex);
                        battleQueue.push({attacker.get(), defender.get()}); 
                        battleQueueCV.notify_one(); 
                    }
                }
            }
        }
    }
}

void NPCManager::battleNPCs() {
    while (running) {
        std::unique_lock<std::mutex> battleLock(battleQueueMutex);
        battleQueueCV.wait(battleLock, [this] { return !battleQueue.empty() || !running; });

        if (!running && battleQueue.empty()) break;

        auto [attacker, defender] = battleQueue.front();
        battleQueue.pop();
        battleLock.unlock();

        battle(*attacker, *defender);
    }
}

void NPCManager::battle(NPC& attacker, NPC& defender) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6); 

    int attack = dis(gen); 
    int defense = dis(gen); 

    std::lock_guard<std::mutex> coutLock(coutMutex);
    std::cout << attacker.getName() << " attacks with strength " << attack << ", "
              << defender.getName() << " defends with strength " << defense << std::endl;

    if (attack > defense) {
        std::unique_lock<std::shared_mutex> lock(npcsMutex);
        defender.setAlive(false);
        std::cout << attacker.getName() << " killed " << defender.getName() << std::endl;
    } else {
        std::cout << defender.getName() << " survived the attack!" << std::endl;
    }
}

void NPCManager::printMap() const {
    while (running) {
        std::shared_lock<std::shared_mutex> lock(npcsMutex);
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Map:" << std::endl;
        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                std::cout << "Type: " << npc->getType() << ", Name: " << npc->getName() << ", Coords: (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void NPCManager::runThreads() {
    moveThread = std::thread(&NPCManager::moveNPCs, this);
    battleThread = std::thread(&NPCManager::battleNPCs, this);
    printThread = std::thread(&NPCManager::printMap, this);
}

void NPCManager::stopGame() {
    running = false;
    battleQueueCV.notify_all(); 
    if (moveThread.joinable()) moveThread.join();
    if (battleThread.joinable()) battleThread.join();
    if (printThread.joinable()) printThread.join();
}

void NPCManager::printSurvivors() const {
    std::shared_lock<std::shared_mutex> lock(npcsMutex);
    std::lock_guard<std::mutex> coutLock(coutMutex);
    std::cout << "Survivors:" << std::endl;
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            std::cout << "Type: " << npc->getType() << ", Name: " << npc->getName() << ", Coords: (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
        }
    }
}