#include "../include/NPCManager.h"
#include <chrono>
#include <thread>

int main() {
    NPCManager npcManager;
    npcManager.runThreads();

    std::this_thread::sleep_for(std::chrono::seconds(30)); // Игра длится 30 секунд

    npcManager.stopGame(); // Останавливаем игру
    npcManager.printSurvivors(); // Выводим выживших NPC

    return 0;
}