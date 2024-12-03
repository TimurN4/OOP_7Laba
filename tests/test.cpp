#include <gtest/gtest.h>
#include "NPC.h"

TEST(NPCTest, Constructor) {
    Bandit bandit("Bandit1", 100, 100);
    EXPECT_EQ(bandit.getName(), "Bandit1");
    EXPECT_EQ(bandit.getX(), 100);
    EXPECT_EQ(bandit.getY(), 100);
    EXPECT_TRUE(bandit.isAlive());
}

TEST(NPCTest, SetAlive) {
    Bandit bandit("Bandit1", 100, 100);
    bandit.setAlive(false);
    EXPECT_FALSE(bandit.isAlive());
}

#include "NPCFactory.h"

TEST(NPCFactoryTest, CreateNPC) {
    auto bandit = NPCFactory::createNPC("Bandit", "Bandit1", 100, 100);
    EXPECT_NE(bandit, nullptr);
    EXPECT_EQ(bandit->getType(), "Bandit");
    EXPECT_EQ(bandit->getName(), "Bandit1");
    EXPECT_EQ(bandit->getX(), 100);
    EXPECT_EQ(bandit->getY(), 100);
}

TEST(NPCFactoryTest, LoadNPC) {
    std::ifstream file("npcs.txt");
    auto npc = NPCFactory::loadNPC(file);
    EXPECT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Bandit");
    EXPECT_EQ(npc->getName(), "Bandit1");
    EXPECT_EQ(npc->getX(), 100);
    EXPECT_EQ(npc->getY(), 100);
}

#include "BattleVisitor.h"
#include "NPCManager.h"

TEST(BattleVisitorTest, VisitBandit) {
    NPCManager npcManager;
    npcManager.addNPC("Bandit", "Bandit1", 100, 100);
    npcManager.addNPC("Elf", "Elf1", 100, 100);

    BattleVisitor battleVisitor(100, npcManager.getNPCs());
    battleVisitor.visit(dynamic_cast<Bandit&>(*npcManager.getNPCs()[0]));

    EXPECT_FALSE(npcManager.getNPCs()[1]->isAlive());
}

TEST(BattleVisitorTest, VisitWanderingKnight) {
    NPCManager npcManager;
    npcManager.addNPC("WanderingKnight", "Knight1", 100, 100);
    npcManager.addNPC("Bandit", "Bandit1", 100, 100);

    BattleVisitor battleVisitor(100, npcManager.getNPCs());
    battleVisitor.visit(dynamic_cast<WanderingKnight&>(*npcManager.getNPCs()[0]));

    EXPECT_FALSE(npcManager.getNPCs()[1]->isAlive());
}

TEST(BattleVisitorTest, VisitElf) {
    NPCManager npcManager;
    npcManager.addNPC("Elf", "Elf1", 100, 100);
    npcManager.addNPC("WanderingKnight", "Knight1", 100, 100);

    BattleVisitor battleVisitor(100, npcManager.getNPCs());
    battleVisitor.visit(dynamic_cast<Elf&>(*npcManager.getNPCs()[0]));

    EXPECT_FALSE(npcManager.getNPCs()[1]->isAlive());
}

#include "NPCManager.h"

TEST(NPCManagerTest, AddNPC) {
    NPCManager npcManager;
    npcManager.addNPC("Bandit", "Bandit1", 100, 100);
    EXPECT_EQ(npcManager.getNPCs().size(), 1);
    EXPECT_EQ(npcManager.getNPCs()[0]->getType(), "Bandit");
    EXPECT_EQ(npcManager.getNPCs()[0]->getName(), "Bandit1");
    EXPECT_EQ(npcManager.getNPCs()[0]->getX(), 100);
    EXPECT_EQ(npcManager.getNPCs()[0]->getY(), 100);
}

TEST(NPCManagerTest, SaveAndLoadNPCs) {
    NPCManager npcManager;
    npcManager.addNPC("Bandit", "Bandit1", 100, 100);
    npcManager.saveNPCs("npcs_test.txt");

    NPCManager npcManager2;
    npcManager2.loadNPCs("npcs_test.txt");

    EXPECT_EQ(npcManager2.getNPCs().size(), 1);
    EXPECT_EQ(npcManager2.getNPCs()[0]->getType(), "Bandit");
    EXPECT_EQ(npcManager2.getNPCs()[0]->getName(), "Bandit1");
    EXPECT_EQ(npcManager2.getNPCs()[0]->getX(), 100);
    EXPECT_EQ(npcManager2.getNPCs()[0]->getY(), 100);
}

TEST(NPCManagerTest, StartBattle) {
    NPCManager npcManager;
    npcManager.addNPC("Bandit", "Bandit1", 100, 100);
    npcManager.addNPC("Elf", "Elf1", 100, 100);

    npcManager.startBattle(100);

    EXPECT_EQ(npcManager.getNPCs().size(), 1);
    EXPECT_EQ(npcManager.getNPCs()[0]->getType(), "Bandit");
}