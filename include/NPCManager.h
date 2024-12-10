#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <random>
#include <chrono>
#include <iostream>
#include <queue>
#include <condition_variable>
#include "../include/NPC.h"
#include "../include/NPCFactory.h"

class NPCManager {
public:
    NPCManager();
    ~NPCManager();

    void initializeNPCs(); // Метод для создания 50 NPC в случайных локациях
    void addNPC(const std::string& type, const std::string& name, int x, int y);
    void moveNPCs();
    void battleNPCs();
    void printMap() const;
    void runThreads();
    void stopGame();
    void printSurvivors() const;

private:
    std::vector<std::unique_ptr<NPC>> npcs;
    mutable std::shared_mutex npcsMutex; // Для управления доступом к npcs
    mutable std::mutex coutMutex; // Для управления доступом к std::cout
    std::thread moveThread;
    std::thread battleThread;
    std::thread printThread;
    bool running;

    // Очередь задач для боев
    std::queue<std::pair<NPC*, NPC*>> battleQueue;
    std::mutex battleQueueMutex;
    std::condition_variable battleQueueCV;

    // Константы для размера карты
    static constexpr int MAP_WIDTH = 100;
    static constexpr int MAP_HEIGHT = 100;

    void moveNPC(NPC& npc);
    void battle(NPC& attacker, NPC& defender);
    void checkForBattles();
};

#endif