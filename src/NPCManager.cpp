#include "../include/NPCManager.h"

NPCManager::NPCManager() : running(true) {
    // Создаем 50 NPC в случайных локациях
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
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

NPCManager::~NPCManager() {
    running = false;
    if (moveThread.joinable()) moveThread.join();
    if (battleThread.joinable()) battleThread.join();
    if (printThread.joinable()) printThread.join();
}

void NPCManager::addNPC(const std::string& type, const std::string& name, int x, int y) {
    if (x < 0 || x > 100 || y < 0 || y > 100) {
        std::cerr << "Coordinates out of range (0 <= x, y <= 100)" << std::endl;
        return;
    }
    std::unique_lock<std::shared_mutex> lock(npcsMutex); // Используем unique_lock для записи
    npcs.push_back(NPCFactory::createNPC(type, name, x, y));
}

void NPCManager::moveNPCs() {
    while (running) {
        std::shared_lock<std::shared_mutex> lock(npcsMutex); // Используем shared_lock для чтения
        for (auto& npc : npcs) {
            if (npc->isAlive()) {
                moveNPC(*npc);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void NPCManager::moveNPC(NPC& npc) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-5, 5);

    int dx = dis(gen);
    int dy = dis(gen);
    int newX = npc.getX() + dx;
    int newY = npc.getY() + dy;

    if (newX >= 0 && newX <= 100 && newY >= 0 && newY <= 100) {
        npc.setX(newX);
        npc.setY(newY);
    }
}

void NPCManager::battleNPCs() {
    while (running) {
        std::shared_lock<std::shared_mutex> lock(npcsMutex); // Используем shared_lock для чтения
        for (auto& attacker : npcs) {
            if (attacker->isAlive()) {
                for (auto& defender : npcs) {
                    if (defender->isAlive() && attacker != defender) {
                        double distance = std::sqrt(std::pow(attacker->getX() - defender->getX(), 2) + std::pow(attacker->getY() - defender->getY(), 2));
                        if (distance <= 10) { // Расстояние убийства
                            battle(*attacker, *defender);
                        }
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void NPCManager::battle(NPC& attacker, NPC& defender) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    int attack = dis(gen);
    int defense = dis(gen);

    if (attack > defense) {
        std::unique_lock<std::shared_mutex> lock(npcsMutex); // Используем unique_lock для записи
        defender.setAlive(false);
        std::lock_guard<std::mutex> coutLock(coutMutex); // Используем lock_guard для std::cout
        std::cout << attacker.getName() << " killed " << defender.getName() << std::endl;
    }
}

void NPCManager::printMap() const {
    while (running) {
        std::shared_lock<std::shared_mutex> lock(npcsMutex); // Используем shared_lock для чтения
        std::lock_guard<std::mutex> coutLock(coutMutex); // Используем lock_guard для std::cout
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