#include <gtest/gtest.h>
#include "../include/NPC.h"
#include "../include/NPCFactory.h"
#include "../include/NPCManager.h"

// Тест для создания NPC через NPCFactory
TEST(NPCFactoryTest, CreateNPC) {
    auto bandit = NPCFactory::createNPC("Bandit", "Bandit1", 10, 20);
    ASSERT_NE(bandit, nullptr);
    EXPECT_EQ(bandit->getType(), "Bandit");
    EXPECT_EQ(bandit->getName(), "Bandit1");
    EXPECT_EQ(bandit->getX(), 10);
    EXPECT_EQ(bandit->getY(), 20);
    EXPECT_TRUE(bandit->isAlive());
}

// Тест для передвижения NPC
TEST(NPCManagerTest, MoveNPC) {
    NPCManager manager;
    manager.addNPC("Bandit", "Bandit1", 10, 20);
    manager.addNPC("WanderingKnight", "Knight1", 30, 40);

    auto& npcs = manager.getNPCs();
    auto& bandit = npcs[0];
    auto& knight = npcs[1];

    // Сохраняем начальные координаты
    int initialBanditX = bandit->getX();
    int initialBanditY = bandit->getY();
    int initialKnightX = knight->getX();
    int initialKnightY = knight->getY();

    // Передвигаем NPC
    manager.moveNPCs();

    // Проверяем, что координаты изменились
    EXPECT_NE(bandit->getX(), initialBanditX);
    EXPECT_NE(bandit->getY(), initialBanditY);
    EXPECT_NE(knight->getX(), initialKnightX);
    EXPECT_NE(knight->getY(), initialKnightY);
}

// Тест для боев между NPC
TEST(NPCManagerTest, BattleNPC) {
    NPCManager manager;
    manager.addNPC("Bandit", "Bandit1", 10, 20);
    manager.addNPC("WanderingKnight", "Knight1", 12, 22); // Близко к Bandit

    auto& npcs = manager.getNPCs();
    auto& bandit = npcs[0];
    auto& knight = npcs[1];

    // Проверяем, что оба NPC живы до боя
    EXPECT_TRUE(bandit->isAlive());
    EXPECT_TRUE(knight->isAlive());

    // Запускаем бой
    manager.battleNPCs();

    // Проверяем, что один из NPC убит
    EXPECT_TRUE(bandit->isAlive() || knight->isAlive());
    EXPECT_FALSE(bandit->isAlive() && knight->isAlive());
}

// Тест для вывода карты
TEST(NPCManagerTest, PrintMap) {
    testing::internal::CaptureStdout();

    NPCManager manager;
    manager.addNPC("Bandit", "Bandit1", 10, 20);
    manager.addNPC("WanderingKnight", "Knight1", 30, 40);

    manager.printMap();

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Bandit1"), std::string::npos);
    EXPECT_NE(output.find("Knight1"), std::string::npos);
}

// Тест для вывода списка выживших
TEST(NPCManagerTest, PrintSurvivors) {
    testing::internal::CaptureStdout();

    NPCManager manager;
    manager.addNPC("Bandit", "Bandit1", 10, 20);
    manager.addNPC("WanderingKnight", "Knight1", 30, 40);

    manager.printSurvivors();

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Bandit1"), std::string::npos);
    EXPECT_NE(output.find("Knight1"), std::string::npos);
}