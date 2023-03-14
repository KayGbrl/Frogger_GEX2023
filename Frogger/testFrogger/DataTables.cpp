#include "DataTables.h"
#include "JsonFrameParser.h"
#include "Werkzeug.h"

std::map<Arten::Type, ActorData> initializeActorData()
{
    std::map<Arten::Type, ActorData> data;

    data[Arten::Type::Frogger].texture = TextureID::Frogger;

    JsonFrameParser frames = JsonFrameParser("Media/Textures/frog.json");
    
    data[Arten::Type::Frogger].animations[Arten::State::Respawn].gameFrameSet(frames.getFramesFor("jumpUp 1"));
    data[Arten::Type::Frogger].animations[Arten::State::Respawn].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Frogger].animations[Arten::State::Respawn].gameRepeating(true);

    // Lives
    data[Arten::Type::FroggerWinner].texture = TextureID::Frogger;
    data[Arten::Type::FroggerWinner].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("small frog"));
    data[Arten::Type::FroggerWinner].animations[Arten::State::Idle].gameSetDuration(sf::seconds(3.f));
    data[Arten::Type::FroggerWinner].animations[Arten::State::Idle].gameRepeating(true);

    // Death State 
    data[Arten::Type::Frogger].animations[Arten::State::Death].gameFrameSet(frames.getFramesFor("death"));
    data[Arten::Type::Frogger].animations[Arten::State::Death].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Frogger].animations[Arten::State::Death].gameRepeating(false);
    
    // Idle state for direction Up, down, left, right 
    data[Arten::Type::Frogger].animations[Arten::State::IdleUp].gameFrameSet(frames.getFramesFor("jumpUp"));
    data[Arten::Type::Frogger].animations[Arten::State::IdleUp].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Frogger].animations[Arten::State::IdleUp].gameRepeating(true);

    data[Arten::Type::Frogger].animations[Arten::State::IdleDown].gameFrameSet(frames.getFramesFor("jumpDown"));
    data[Arten::Type::Frogger].animations[Arten::State::IdleDown].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Frogger].animations[Arten::State::IdleDown].gameRepeating(true);

    data[Arten::Type::Frogger].animations[Arten::State::IdleLeft].gameFrameSet(frames.getFramesFor("jumpLeft"));
    data[Arten::Type::Frogger].animations[Arten::State::IdleLeft].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Frogger].animations[Arten::State::IdleLeft].gameRepeating(true);

    data[Arten::Type::Frogger].animations[Arten::State::IdleRight].gameFrameSet(frames.getFramesFor("jumpRight"));
    data[Arten::Type::Frogger].animations[Arten::State::IdleRight].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Frogger].animations[Arten::State::IdleRight].gameRepeating(true);

    // state for direction Up, down, left, right 
    data[Arten::Type::Frogger].animations[Arten::State::JumpDown].gameFrameSet(frames.getFramesFor("jumpDown 2"));
    data[Arten::Type::Frogger].animations[Arten::State::JumpDown].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Frogger].animations[Arten::State::JumpDown].gameRepeating(true);

    data[Arten::Type::Frogger].animations[Arten::State::JumpUp].gameFrameSet(frames.getFramesFor("jumpUp 2"));
    data[Arten::Type::Frogger].animations[Arten::State::JumpUp].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Frogger].animations[Arten::State::JumpUp].gameRepeating(false);

    data[Arten::Type::Frogger].animations[Arten::State::JumpLeft].gameFrameSet(frames.getFramesFor("jumpLeft 2"));
    data[Arten::Type::Frogger].animations[Arten::State::JumpLeft].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Frogger].animations[Arten::State::JumpLeft].gameRepeating(false);

    data[Arten::Type::Frogger].animations[Arten::State::JumpRight].gameFrameSet(frames.getFramesFor("jumpRight 2"));
    data[Arten::Type::Frogger].animations[Arten::State::JumpRight].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Frogger].animations[Arten::State::JumpRight].gameRepeating(false);

    // Alligator state
    data[Arten::Type::Alligator].texture = TextureID::Frogger;
    data[Arten::Type::Alligator].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("gator-"));
    data[Arten::Type::Alligator].animations[Arten::State::Idle].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Alligator].animations[Arten::State::Idle].gameRepeating(true);

    // Car state
    data[Arten::Type::Car1].texture = TextureID::Frogger;
    data[Arten::Type::Car1].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("car1"));
    data[Arten::Type::Car1].animations[Arten::State::Idle].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Car1].animations[Arten::State::Idle].gameRepeating(true);

    data[Arten::Type::Car2].texture = TextureID::Frogger;
    data[Arten::Type::Car2].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("car2"));
    data[Arten::Type::Car2].animations[Arten::State::Idle].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Car2].animations[Arten::State::Idle].gameRepeating(true);

    data[Arten::Type::Car3].texture = TextureID::Frogger;
    data[Arten::Type::Car3].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("car3"));
    data[Arten::Type::Car3].animations[Arten::State::Idle].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Car3].animations[Arten::State::Idle].gameRepeating(true);

    //Tractor state
    data[Arten::Type::Truck1].texture = TextureID::Frogger;
    data[Arten::Type::Truck1].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("tractor"));
    data[Arten::Type::Truck1].animations[Arten::State::Idle].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Truck1].animations[Arten::State::Idle].gameRepeating(true);

    //Truck state
    data[Arten::Type::Truck2].texture = TextureID::Frogger;
    data[Arten::Type::Truck2].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("truck"));
    data[Arten::Type::Truck2].animations[Arten::State::Idle].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Truck2].animations[Arten::State::Idle].gameRepeating(true);

    //Turtle2 state
    data[Arten::Type::Turtle2].texture = TextureID::Frogger;
    data[Arten::Type::Turtle2].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("turtle2 "));
    data[Arten::Type::Turtle2].animations[Arten::State::Idle].gameSetDuration(sf::seconds(3.f));
    data[Arten::Type::Turtle2].animations[Arten::State::Idle].gameRepeating(true);

    // floating turtle2
    data[Arten::Type::Turtle2_floating].texture = TextureID::Frogger;
    data[Arten::Type::Turtle2_floating].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("turtle2_float"));
    data[Arten::Type::Turtle2_floating].animations[Arten::State::Idle].gameSetDuration(sf::seconds(3.f));
    data[Arten::Type::Turtle2_floating].animations[Arten::State::Idle].gameRepeating(true);

    //Turtle3 State
    data[Arten::Type::Turtle3].texture = TextureID::Frogger;
    data[Arten::Type::Turtle3].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("turtle3 "));
    data[Arten::Type::Turtle3].animations[Arten::State::Idle].gameSetDuration(sf::seconds(5.f));
    data[Arten::Type::Turtle3].animations[Arten::State::Idle].gameRepeating(true);

    // floating turtle3
    data[Arten::Type::Turtle3_floating].texture = TextureID::Frogger;
    data[Arten::Type::Turtle3_floating].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("turtle3_float"));
    data[Arten::Type::Turtle3_floating].animations[Arten::State::Idle].gameSetDuration(sf::seconds(3.f));
    data[Arten::Type::Turtle3_floating].animations[Arten::State::Idle].gameRepeating(true);

    //Log State
    data[Arten::Type::Log1].texture = TextureID::Frogger;
    data[Arten::Type::Log1].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("tree1"));
    data[Arten::Type::Log1].animations[Arten::State::Idle].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Log1].animations[Arten::State::Idle].gameRepeating(true);

    data[Arten::Type::Log2].texture = TextureID::Frogger;
    data[Arten::Type::Log2].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("tree2"));
    data[Arten::Type::Log2].animations[Arten::State::Idle].gameSetDuration(sf::seconds(1.f));
    data[Arten::Type::Log2].animations[Arten::State::Idle].gameRepeating(true);

    //Pink frog
    data[Arten::Type::PinkFrog].texture = TextureID::Frogger;
    data[Arten::Type::PinkFrog].animations[Arten::State::Idle].gameFrameSet(frames.getFramesFor("pinkfrog "));
    data[Arten::Type::PinkFrog].animations[Arten::State::Idle].gameSetDuration(sf::seconds(3.f));
    data[Arten::Type::PinkFrog].animations[Arten::State::Idle].gameRepeating(true);


    return data;
}

std::vector<NPCSpawnData> initializeNPCSpawnData()
{
    std::vector<NPCSpawnData> spawnData(17);

    sf::Time time;

    // logs always as 0, 1 and 2, other code depends on it
    spawnData[0] = NPCSpawnData();
    spawnData[0].position = sf::Vector2f(-50.f, 260.f);
    spawnData[0].direction = Arten::Direction::Right;
    spawnData[0].type = Arten::Type::Log1;
    spawnData[0].speed = 60.f;
    spawnData[0].interval = sf::seconds(6);
    spawnData[0].elapsedTime = sf::seconds(3);
    spawnData[0].spawn = true;

    spawnData[1] = NPCSpawnData();
    spawnData[1].position = sf::Vector2f(-50.f, 180.f);
    spawnData[1].direction = Arten::Direction::Right;
    spawnData[1].type = Arten::Type::Log1;
    spawnData[1].speed = 70.f;
    spawnData[1].interval = sf::seconds(5);
    spawnData[1].elapsedTime = sf::seconds(5);
    spawnData[1].spawn = true;

    spawnData[2] = NPCSpawnData();
    spawnData[2].position = sf::Vector2f(530.f, 300);
    spawnData[2].direction = Arten::Direction::Left;
    spawnData[2].type = Arten::Type::Log2;
    spawnData[2].speed = -70.f;
    spawnData[2].interval = sf::seconds(5);
    spawnData[2].elapsedTime = spawnData[2].interval;
    spawnData[2].spawn = true;

    // Leave always turtle 2 and 3 as index 3 and 4, other code depends on it
    spawnData[3] = NPCSpawnData();
    spawnData[3].position = sf::Vector2f(530.f, 230.f);
    spawnData[3].direction = Arten::Direction::Left;
    spawnData[3].type = Arten::Type::Turtle2;
    spawnData[3].speed = -100.f;
    spawnData[3].interval = sf::seconds(4);
    spawnData[3].elapsedTime = spawnData[3].interval;
    spawnData[3].spawn = true;

    spawnData[4] = NPCSpawnData();
    spawnData[4].position = sf::Vector2f(530.f, 140.f);
    spawnData[4].direction = Arten::Direction::Left;
    spawnData[4].type = Arten::Type::Turtle3;
    spawnData[4].speed = -50.f;
    spawnData[4].interval = sf::seconds(5);
    spawnData[4].elapsedTime = spawnData[4].interval;
    spawnData[4].spawn = true;

    // Leave always Car 1, 2 and 3 as Index 5,6 and 7
    spawnData[5] = NPCSpawnData();
    spawnData[5].position = sf::Vector2f(530.f, 530.f);
    spawnData[5].direction = Arten::Direction::Left;
    spawnData[5].type = Arten::Type::Car1;
    spawnData[5].speed = -100.f;
    spawnData[5].interval = sf::seconds(2);
    spawnData[5].elapsedTime = spawnData[5].interval;
    spawnData[5].spawn = true;

    spawnData[6] = NPCSpawnData();
    spawnData[6].position = sf::Vector2f(530.f, 450.f);
    spawnData[6].direction = Arten::Direction::Left;
    spawnData[6].type = Arten::Type::Car3;
    spawnData[6].speed = -150.f;
    spawnData[6].interval = sf::seconds(2);
    spawnData[6].elapsedTime = spawnData[6].interval;
    spawnData[6].spawn = true;

    spawnData[7] = NPCSpawnData();
    spawnData[7].position = sf::Vector2f(-50.f, 410.f);
    spawnData[7].direction = Arten::Direction::Right;
    spawnData[7].type = Arten::Type::Car2;
    spawnData[7].speed = 100.f;
    spawnData[7].interval = sf::seconds(4);
    spawnData[7].elapsedTime = spawnData[7].interval;
    spawnData[7].spawn = true;

    // Leave always Truck 1 and 2 as Index 8 and 9
    spawnData[8] = NPCSpawnData();
    spawnData[8].position = sf::Vector2f(530.f, 370.f);
    spawnData[8].direction = Arten::Direction::Left;
    spawnData[8].type = Arten::Type::Truck2;
    spawnData[8].speed = -60.f;
    spawnData[8].interval = sf::seconds(3);
    spawnData[8].elapsedTime = spawnData[8].interval;
    spawnData[8].spawn = true;

    spawnData[9].position = sf::Vector2f(-50.f, 490.f);
    spawnData[9].direction = Arten::Direction::Right;
    spawnData[9].type = Arten::Type::Truck1;
    spawnData[9].speed = 40.f;
    spawnData[9].interval = sf::seconds(3);
    spawnData[9].elapsedTime = spawnData[9].interval;
    spawnData[9].spawn = true;

    // Leave alligaton as Index 10
    spawnData[10] = NPCSpawnData();
    spawnData[10].position = sf::Vector2f(-50.f, 260.f);
    spawnData[10].direction = Arten::Direction::Right;
    spawnData[10].type = Arten::Type::Alligator;
    spawnData[10].speed = 70.f;
    spawnData[10].interval = sf::seconds(6);
    spawnData[10].elapsedTime = sf::seconds(6);
    spawnData[10].spawn = true;

    // Leave floating turtle2 as Index 11
    spawnData[11] = NPCSpawnData();
    spawnData[11].position = sf::Vector2f(530.f, 230.f);
    spawnData[11].direction = Arten::Direction::Left;
    spawnData[11].type = Arten::Type::Turtle2_floating;
    spawnData[11].speed = -100.f;
    spawnData[11].interval = sf::seconds(4);
    spawnData[11].elapsedTime = spawnData[11].interval / 2.f;
    spawnData[11].spawn = true;

    // Leave floating turtle3 as Index 12
    spawnData[12] = NPCSpawnData();
    spawnData[12].position = sf::Vector2f(530.f, 140.f);
    spawnData[12].direction = Arten::Direction::Left;
    spawnData[12].type = Arten::Type::Turtle3_floating;
    spawnData[12].speed = -50.f;
    spawnData[12].interval = sf::seconds(5);
    spawnData[12].elapsedTime = spawnData[12].interval / 2.f;
    spawnData[12].spawn = true;

    //Leave alligator swimming left Index 13
    spawnData[13] = NPCSpawnData();
    spawnData[13].position = sf::Vector2f(-50.f, 180.f);
    spawnData[13].direction = Arten::Direction::Left;
    spawnData[13].type = Arten::Type::Alligator;
    spawnData[13].speed = 80.f;
    spawnData[13].interval = sf::seconds(5);
    spawnData[13].elapsedTime = sf::seconds(2.5);
    spawnData[13].spawn = true;

    // Leave always as index 14
    spawnData[14] = NPCSpawnData();
    spawnData[14].position = sf::Vector2f(0.f, 0.f); // variable
    spawnData[14].direction = Arten::Direction::Right;
    spawnData[14].type = Arten::Type::PinkFrog;
    spawnData[14].speed = 60.f;
    spawnData[14].interval = sf::seconds(6);
    spawnData[14].elapsedTime = sf::seconds(3);
    spawnData[14].spawn = true;

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

