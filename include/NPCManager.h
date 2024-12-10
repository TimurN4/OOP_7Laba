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
#include "../include/NPC.h"
#include "../include/NPCFactory.h"

class NPCManager {
public:
    NPCManager();
    ~NPCManager();

    void addNPC(const std::string& type, const std::string& name, int x, int y);
    void moveNPCs();
    void battleNPCs();
    void printMap() const; // Метод остается const
    void runThreads();

private:
    std::vector<std::unique_ptr<NPC>> npcs;
    mutable std::shared_mutex npcsMutex; // Для управления доступом к npcs
    mutable std::mutex coutMutex; // Для управления доступом к std::cout (сделаем mutable)
    std::thread moveThread;
    std::thread battleThread;
    std::thread printThread;
    bool running;

    void moveNPC(NPC& npc);
    void battle(NPC& attacker, NPC& defender);
};

#endif