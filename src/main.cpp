#include "../include/NPCManager.h"
#include <chrono>
#include <thread>

int main() {
    NPCManager npcManager;
    npcManager.runThreads();

    std::this_thread::sleep_for(std::chrono::seconds(30)); 

    npcManager.stopGame(); 
    npcManager.printSurvivors(); 
    return 0;
}