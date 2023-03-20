#include "DataTables.h"
#include "JsonFrameParser.h"

std::map<Arten::Type, Karachtere> artenData()
{
    std::map<Arten::Type, Karachtere> informationen;

    informationen[Arten::Type::Frogger].texturen = TextureID::Frogger;

    JsonFrameParser frames = JsonFrameParser("Media/Textures/frog.json");

     // WinnigSpot Frog
    informationen[Arten::Type::FroggerWinner].texturen = TextureID::Frogger;
    informationen[Arten::Type::FroggerWinner].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("gewinnerfrosh"));
    informationen[Arten::Type::FroggerWinner].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::FroggerWinner].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    // Death State 
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Dead].gameFrameSet(frames.getFramesFor("tod"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Dead].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Dead].gameRepeating(false);
    
    // Idle state for direction Up, down, left, right 
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::IdleUp].gameFrameSet(frames.getFramesFor("stehenhoch"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::IdleUp].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::IdleUp].gameRepeating(true);

    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::IdleDown].gameFrameSet(frames.getFramesFor("stehenrunter"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::IdleDown].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::IdleDown].gameRepeating(true);

    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::IdleLeft].gameFrameSet(frames.getFramesFor("stehenlinks"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::IdleLeft].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::IdleLeft].gameRepeating(true);

    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::IdleRight].gameFrameSet(frames.getFramesFor("stehenrechts"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::IdleRight].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::IdleRight].gameRepeating(true);

    // state for direction Up, down, left, right 
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::JumpDown].gameFrameSet(frames.getFramesFor("runter"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::JumpDown].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::JumpDown].gameRepeating(true);

    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::JumpUp].gameFrameSet(frames.getFramesFor("hoch"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::JumpUp].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::JumpUp].gameRepeating(false);

    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::JumpLeft].gameFrameSet(frames.getFramesFor("links"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::JumpLeft].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::JumpLeft].gameRepeating(false);

    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::JumpRight].gameFrameSet(frames.getFramesFor("rechts"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::JumpRight].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::JumpRight].gameRepeating(false);

    // Alligator state
    informationen[Arten::Type::Alligator].texturen = TextureID::Frogger;
    informationen[Arten::Type::Alligator].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("alligator"));
    informationen[Arten::Type::Alligator].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Alligator].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    // Car state
    informationen[Arten::Type::Car1].texturen = TextureID::Frogger;
    informationen[Arten::Type::Car1].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("gelbesauto"));
    informationen[Arten::Type::Car1].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Car1].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    informationen[Arten::Type::Car2].texturen = TextureID::Frogger;
    informationen[Arten::Type::Car2].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("gruenesauto"));
    informationen[Arten::Type::Car2].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Car2].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    informationen[Arten::Type::Car3].texturen = TextureID::Frogger;
    informationen[Arten::Type::Car3].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("pinkesauto"));
    informationen[Arten::Type::Car3].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Car3].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    //Tractor state
    informationen[Arten::Type::Truck1].texturen = TextureID::Frogger;
    informationen[Arten::Type::Truck1].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("traktor"));
    informationen[Arten::Type::Truck1].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Truck1].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    //Truck state
    informationen[Arten::Type::Truck2].texturen = TextureID::Frogger;
    informationen[Arten::Type::Truck2].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("lkw"));
    informationen[Arten::Type::Truck2].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Truck2].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    //Turtle2 state
    informationen[Arten::Type::Turtle2].texturen = TextureID::Frogger;
    informationen[Arten::Type::Turtle2].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("zweierkroete"));
    informationen[Arten::Type::Turtle2].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::Turtle2].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    // floating turtle2
    informationen[Arten::Type::Turtle2_floating].texturen = TextureID::Frogger;
    informationen[Arten::Type::Turtle2_floating].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("zweierkroete_untertauchen"));
    informationen[Arten::Type::Turtle2_floating].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::Turtle2_floating].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    //Turtle3 State
    informationen[Arten::Type::Turtle3].texturen = TextureID::Frogger;
    informationen[Arten::Type::Turtle3].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("dreierkroete"));
    informationen[Arten::Type::Turtle3].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(5.f));
    informationen[Arten::Type::Turtle3].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    // floating turtle3
    informationen[Arten::Type::Turtle3_floating].texturen = TextureID::Frogger;
    informationen[Arten::Type::Turtle3_floating].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("dreierkroete_untertauchen"));
    informationen[Arten::Type::Turtle3_floating].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::Turtle3_floating].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    //Log State
    informationen[Arten::Type::Log1].texturen = TextureID::Frogger;
    informationen[Arten::Type::Log1].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("kleinerstamm"));
    informationen[Arten::Type::Log1].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Log1].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    informationen[Arten::Type::Log2].texturen = TextureID::Frogger;
    informationen[Arten::Type::Log2].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("grosserstamm"));
    informationen[Arten::Type::Log2].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Log2].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    //Pink frog
    informationen[Arten::Type::PinkFrog].texturen = TextureID::Frogger;
    informationen[Arten::Type::PinkFrog].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("pinkerfrosh"));
    informationen[Arten::Type::PinkFrog].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::PinkFrog].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);

    //Snake 
    informationen[Arten::Type::Snake].texturen = TextureID::Frogger;
    informationen[Arten::Type::Snake].animationen[Arten::SpeilStatus::Idle].gameFrameSet(frames.getFramesFor("schlange"));
    informationen[Arten::Type::Snake].animationen[Arten::SpeilStatus::Idle].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Snake].animationen[Arten::SpeilStatus::Idle].gameRepeating(true);


    return informationen;
}

std::vector<NPCSpawnData> initializeNPCSpawnData()
{
    std::vector<NPCSpawnData> spawnData(17);

    sf::Time time;

    // logs always as 0, 1 and 2, other code depends on it
    spawnData[0] = NPCSpawnData();
    spawnData[0].position = sf::Vector2f(-50.f, 260.f);
    spawnData[0].richtung = Arten::Direction::Right;
    spawnData[0].type = Arten::Type::Log1;
    spawnData[0].speed = 60.f;
    spawnData[0].interval = sf::seconds(6);
    spawnData[0].elapsedTime = sf::seconds(3);
    spawnData[0].spawn = true;

    spawnData[1] = NPCSpawnData();
    spawnData[1].position = sf::Vector2f(-50.f, 180.f);
    spawnData[1].richtung = Arten::Direction::Right;
    spawnData[1].type = Arten::Type::Log1;
    spawnData[1].speed = 70.f;
    spawnData[1].interval = sf::seconds(5);
    spawnData[1].elapsedTime = sf::seconds(5);
    spawnData[1].spawn = true;

    spawnData[2] = NPCSpawnData();
    spawnData[2].position = sf::Vector2f(530.f, 300);
    spawnData[2].richtung = Arten::Direction::Left;
    spawnData[2].type = Arten::Type::Log2;
    spawnData[2].speed = -70.f;
    spawnData[2].interval = sf::seconds(5);
    spawnData[2].elapsedTime = spawnData[2].interval;
    spawnData[2].spawn = true;

    // Leave always turtle 2 and 3 as index 3 and 4, other code depends on it
    spawnData[3] = NPCSpawnData();
    spawnData[3].position = sf::Vector2f(530.f, 230.f);
    spawnData[3].richtung = Arten::Direction::Left;
    spawnData[3].type = Arten::Type::Turtle2;
    spawnData[3].speed = -100.f;
    spawnData[3].interval = sf::seconds(4);
    spawnData[3].elapsedTime = spawnData[3].interval;
    spawnData[3].spawn = true;

    spawnData[4] = NPCSpawnData();
    spawnData[4].position = sf::Vector2f(530.f, 140.f);
    spawnData[4].richtung = Arten::Direction::Left;
    spawnData[4].type = Arten::Type::Turtle3;
    spawnData[4].speed = -50.f;
    spawnData[4].interval = sf::seconds(5);
    spawnData[4].elapsedTime = spawnData[4].interval;
    spawnData[4].spawn = true;

    // Leave always Car 1, 2 and 3 as Index 5,6 and 7
    spawnData[5] = NPCSpawnData();
    spawnData[5].position = sf::Vector2f(530.f, 530.f);
    spawnData[5].richtung = Arten::Direction::Left;
    spawnData[5].type = Arten::Type::Car1;
    spawnData[5].speed = -100.f;
    spawnData[5].interval = sf::seconds(2);
    spawnData[5].elapsedTime = spawnData[5].interval;
    spawnData[5].spawn = true;

    spawnData[6] = NPCSpawnData();
    spawnData[6].position = sf::Vector2f(530.f, 450.f);
    spawnData[6].richtung = Arten::Direction::Left;
    spawnData[6].type = Arten::Type::Car3;
    spawnData[6].speed = -150.f;
    spawnData[6].interval = sf::seconds(2);
    spawnData[6].elapsedTime = spawnData[6].interval;
    spawnData[6].spawn = true;

    spawnData[7] = NPCSpawnData();
    spawnData[7].position = sf::Vector2f(-50.f, 410.f);
    spawnData[7].richtung = Arten::Direction::Right;
    spawnData[7].type = Arten::Type::Car2;
    spawnData[7].speed = 100.f;
    spawnData[7].interval = sf::seconds(4);
    spawnData[7].elapsedTime = spawnData[7].interval;
    spawnData[7].spawn = true;

    // Leave always Truck 1 and 2 as Index 8 and 9
    spawnData[8] = NPCSpawnData();
    spawnData[8].position = sf::Vector2f(530.f, 370.f);
    spawnData[8].richtung = Arten::Direction::Left;
    spawnData[8].type = Arten::Type::Truck2;
    spawnData[8].speed = -60.f;
    spawnData[8].interval = sf::seconds(3);
    spawnData[8].elapsedTime = spawnData[8].interval;
    spawnData[8].spawn = true;

    spawnData[9].position = sf::Vector2f(-50.f, 490.f);
    spawnData[9].richtung = Arten::Direction::Right;
    spawnData[9].type = Arten::Type::Truck1;
    spawnData[9].speed = 40.f;
    spawnData[9].interval = sf::seconds(3);
    spawnData[9].elapsedTime = spawnData[9].interval;
    spawnData[9].spawn = true;

    // Leave alligaton as Index 10
    spawnData[10] = NPCSpawnData();
    spawnData[10].position = sf::Vector2f(-50.f, 260.f);
    spawnData[10].richtung = Arten::Direction::Right;
    spawnData[10].type = Arten::Type::Alligator;
    spawnData[10].speed = 70.f;
    spawnData[10].interval = sf::seconds(6);
    spawnData[10].elapsedTime = sf::seconds(6);
    spawnData[10].spawn = true;

    // Leave floating turtle2 as Index 11
    spawnData[11] = NPCSpawnData();
    spawnData[11].position = sf::Vector2f(530.f, 230.f);
    spawnData[11].richtung = Arten::Direction::Left;
    spawnData[11].type = Arten::Type::Turtle2_floating;
    spawnData[11].speed = -100.f;
    spawnData[11].interval = sf::seconds(4);
    spawnData[11].elapsedTime = spawnData[11].interval / 2.f;
    spawnData[11].spawn = true;

    // Leave floating turtle3 as Index 12
    spawnData[12] = NPCSpawnData();
    spawnData[12].position = sf::Vector2f(530.f, 140.f);
    spawnData[12].richtung = Arten::Direction::Left;
    spawnData[12].type = Arten::Type::Turtle3_floating;
    spawnData[12].speed = -50.f;
    spawnData[12].interval = sf::seconds(5);
    spawnData[12].elapsedTime = spawnData[12].interval / 2.f;
    spawnData[12].spawn = true;

    //Leave alligator swimming left Index 13
    spawnData[13] = NPCSpawnData();
    spawnData[13].position = sf::Vector2f(-50.f, 180.f);
    spawnData[13].richtung = Arten::Direction::Left;
    spawnData[13].type = Arten::Type::Alligator;
    spawnData[13].speed = 80.f;
    spawnData[13].interval = sf::seconds(5);
    spawnData[13].elapsedTime = sf::seconds(2.5);
    spawnData[13].spawn = true;

    // Leave always as index 14
    spawnData[14] = NPCSpawnData();
    spawnData[14].position = sf::Vector2f(0.f, 0.f); // variable
    spawnData[14].richtung = Arten::Direction::Right;
    spawnData[14].type = Arten::Type::PinkFrog;
    spawnData[14].speed = 60.f;
    spawnData[14].interval = sf::seconds(6);
    spawnData[14].elapsedTime = sf::seconds(3);
    spawnData[14].spawn = true;

    // Leave always as index 16
    spawnData[15] = NPCSpawnData();
    spawnData[15].position = sf::Vector2f(-50.f, 340.f);
    spawnData[15].richtung = Arten::Direction::Left;
    spawnData[15].type = Arten::Type::Snake;
    spawnData[15].speed = 80.f;
    spawnData[15].interval = sf::seconds(2);
    spawnData[15].elapsedTime = sf::seconds(2);
    spawnData[15].spawn = false;

    return spawnData;
}

std::vector<sf::FloatRect> getWinningSpotPositions()
{
    std::vector<sf::FloatRect> positions;

    float height = 26.f;
    float width = 42.f;
    float top = 78.f;
    float left = 15.f;
    float interval = 102.f;

    for (int i = 0; i < 5; ++i) {
        positions.push_back(sf::FloatRect(left, top, width, height));
        left += interval;
    }

    return positions;
}

