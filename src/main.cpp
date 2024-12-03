#include <vector>
#include <memory>
#include "NPC.h"
#include "NPCFactory.h"
#include "BattleVisitor.h"
#include "Observer.h"

int main() {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(NPCFactory::createNPC("Bandit", "Bandit1", 100, 100));
    npcs.push_back(NPCFactory::createNPC("WanderingKnight", "Knight1", 200, 200));
    npcs.push_back(NPCFactory::createNPC("Elf", "Elf1", 300, 300));

    FileObserver fileObserver("log.txt");
    ScreenObserver screenObserver;

    BattleVisitor battleVisitor(100, npcs);
    for (auto& npc : npcs) {
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

    return 0;
}