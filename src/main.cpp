#include <vector>
#include <memory>
#include "../include/NPC.h"
#include "../include/NPCFactory.h"
#include "../include/Observer.h"
#include "../include/NPCManager.h"

int main() {
    NPCManager npcManager;

    npcManager.addNPC("Bandit", "Bandit1", 100, 100);
    npcManager.addNPC("WanderingKnight", "Knight1", 200, 200);
    npcManager.addNPC("Elf", "Elf1", 300, 300);

    npcManager.printNPCs();

    npcManager.saveNPCs("npcs.txt");

    npcManager.loadNPCs("npcs.txt");

    npcManager.printNPCs();

    FileObserver fileObserver("log.txt");
    ScreenObserver screenObserver;

    npcManager.startBattle(300);

    npcManager.printNPCs();

    return 0;
}