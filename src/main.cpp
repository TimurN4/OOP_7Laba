#include <vector>
#include <memory>
#include "NPC.h"
#include "NPCFactory.h"
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

    // Создание наблюдателей
    FileObserver fileObserver("log.txt");
    ScreenObserver screenObserver;

    // Боевой режим
    npcManager.startBattle(300);

    // Печать NPC после боя
    npcManager.printNPCs();

    return 0;
}