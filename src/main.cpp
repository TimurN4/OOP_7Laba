#include <vector>
#include <memory>
#include "NPC.h"
#include "NPCFactory.h"
#include "BattleVisitor.h"
#include "Observer.h"
#include "NPCManager.h"

int main() {
    NPCManager npcManager;

    // Добавление NPC
    npcManager.addNPC("Bandit", "Bandit1", 100, 100);
    npcManager.addNPC("WanderingKnight", "Knight1", 200, 200);
    npcManager.addNPC("Elf", "Elf1", 300, 300);

    // Печать NPC
    npcManager.printNPCs();

    // Сохранение NPC в файл
    npcManager.saveNPCs("npcs.txt");

    // Загрузка NPC из файла
    npcManager.loadNPCs("npcs.txt");

    // Печать NPC после загрузки
    npcManager.printNPCs();

    // Боевой режим
    FileObserver fileObserver("log.txt");
    ScreenObserver screenObserver;

    BattleVisitor battleVisitor(100, npcManager.getNPCs());
    for (auto& npc : npcManager.getNPCs()) {
        if (npc->getType() == "Bandit") {
            battleVisitor.visit(dynamic_cast<Bandit&>(*npc));
            screenObserver.update("Bandit " + npc->getName() + " fights");
            fileObserver.update("Bandit " + npc->getName() + " fights");
        }
        if (npc->getType() == "WanderingKnight") {
            battleVisitor.visit(dynamic_cast<WanderingKnight&>(*npc));
            screenObserver.update("WanderingKnight " + npc->getName() + " fights");
            fileObserver.update("WanderingKnight " + npc->getName() + " fights");
        }
        if (npc->getType() == "Elf") {
            battleVisitor.visit(dynamic_cast<Elf&>(*npc));
            screenObserver.update("Elf " + npc->getName() + " fights");
            fileObserver.update("Elf " + npc->getName() + " fights");
        }
    }

    // Печать NPC после боя
    npcManager.printNPCs();

    return 0;
}