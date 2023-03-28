#include "DataTables.h"
#include "JsonFrameParser.h"

std::map<Arten::Type, Karachtere> artenData()
{
    std::map<Arten::Type, Karachtere> informationen;

    informationen[Arten::Type::Frogger].texturen = TextureID::Frogger;

    JsonFrameParser frames = JsonFrameParser("Media/Textures/frog.json");

     // WinnigSpot Frog
    informationen[Arten::Type::FroggerWinner].texturen = TextureID::Frogger;
    informationen[Arten::Type::FroggerWinner].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("gewinnerfrosh"));
    informationen[Arten::Type::FroggerWinner].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::FroggerWinner].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    // Death State 
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Tod].gameFrameSet(frames.getFramesFor("tod"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Tod].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Tod].gameRepeating(false);
    
    // Idle state for direction Up, down, left, right 
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Stehenhoch].gameFrameSet(frames.getFramesFor("stehenhoch"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Stehenhoch].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Stehenhoch].gameRepeating(true);

    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Stehenrunter].gameFrameSet(frames.getFramesFor("stehenrunter"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Stehenrunter].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Stehenrunter].gameRepeating(true);

    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Stehenlinks].gameFrameSet(frames.getFramesFor("stehenlinks"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Stehenlinks].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Stehenlinks].gameRepeating(true);

    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Stehenrechts].gameFrameSet(frames.getFramesFor("stehenrechts"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Stehenrechts].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Stehenrechts].gameRepeating(true);

    // state for direction Up, down, left, right 
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Runter].gameFrameSet(frames.getFramesFor("runter"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Runter].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Runter].gameRepeating(true);

    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Hoch].gameFrameSet(frames.getFramesFor("hoch"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Hoch].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Hoch].gameRepeating(false);

    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Links].gameFrameSet(frames.getFramesFor("links"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Links].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Links].gameRepeating(false);

    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Rechts].gameFrameSet(frames.getFramesFor("rechts"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Rechts].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Rechts].gameRepeating(false);

    // Alligator state
    informationen[Arten::Type::Alligator].texturen = TextureID::Frogger;
    informationen[Arten::Type::Alligator].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("alligator"));
    informationen[Arten::Type::Alligator].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Alligator].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    // Car state
    informationen[Arten::Type::Gelbesauto].texturen = TextureID::Frogger;
    informationen[Arten::Type::Gelbesauto].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("gelbesauto"));
    informationen[Arten::Type::Gelbesauto].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Gelbesauto].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    informationen[Arten::Type::Gruenesauto].texturen = TextureID::Frogger;
    informationen[Arten::Type::Gruenesauto].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("gruenesauto"));
    informationen[Arten::Type::Gruenesauto].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Gruenesauto].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    informationen[Arten::Type::Pinkesauto].texturen = TextureID::Frogger;
    informationen[Arten::Type::Pinkesauto].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("pinkesauto"));
    informationen[Arten::Type::Pinkesauto].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Pinkesauto].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    //Traktor
    informationen[Arten::Type::Traktor].texturen = TextureID::Frogger;
    informationen[Arten::Type::Traktor].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("traktor"));
    informationen[Arten::Type::Traktor].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Traktor].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    //Lkw
    informationen[Arten::Type::Lkw].texturen = TextureID::Frogger;
    informationen[Arten::Type::Lkw].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("lkw"));
    informationen[Arten::Type::Lkw].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Lkw].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    //Zweierkroete
    informationen[Arten::Type::Zweierkroete].texturen = TextureID::Frogger;
    informationen[Arten::Type::Zweierkroete].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("zweierkroete"));
    informationen[Arten::Type::Zweierkroete].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::Zweierkroete].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    // Zweierkroete_Untertauchen
    informationen[Arten::Type::Zweierkroete_Untertauchen].texturen = TextureID::Frogger;
    informationen[Arten::Type::Zweierkroete_Untertauchen].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("zweierkroete_untertauchen"));
    informationen[Arten::Type::Zweierkroete_Untertauchen].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::Zweierkroete_Untertauchen].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    //Dreierkroete
    informationen[Arten::Type::Dreierkroete].texturen = TextureID::Frogger;
    informationen[Arten::Type::Dreierkroete].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("dreierkroete"));
    informationen[Arten::Type::Dreierkroete].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(5.f));
    informationen[Arten::Type::Dreierkroete].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    // Dreierkroete_Untertauchen
    informationen[Arten::Type::Dreierkroete_Untertauchen].texturen = TextureID::Frogger;
    informationen[Arten::Type::Dreierkroete_Untertauchen].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("dreierkroete_untertauchen"));
    informationen[Arten::Type::Dreierkroete_Untertauchen].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::Dreierkroete_Untertauchen].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    //Stamm
    informationen[Arten::Type::Kleinerstamm].texturen = TextureID::Frogger;
    informationen[Arten::Type::Kleinerstamm].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("kleinerstamm"));
    informationen[Arten::Type::Kleinerstamm].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Kleinerstamm].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    informationen[Arten::Type::Grosserstamm].texturen = TextureID::Frogger;
    informationen[Arten::Type::Grosserstamm].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("grosserstamm"));
    informationen[Arten::Type::Grosserstamm].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Grosserstamm].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    //Pinkerfrosh
    informationen[Arten::Type::Pinkerfrosh].texturen = TextureID::Frogger;
    informationen[Arten::Type::Pinkerfrosh].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("pinkerfrosh"));
    informationen[Arten::Type::Pinkerfrosh].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::Pinkerfrosh].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    //Schlange 
    informationen[Arten::Type::Schlange].texturen = TextureID::Frogger;
    informationen[Arten::Type::Schlange].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("schlange"));
    informationen[Arten::Type::Schlange].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Schlange].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    //Fliege
    informationen[Arten::Type::Fliege].texturen = TextureID::Frogger;
    informationen[Arten::Type::Fliege].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("fliege"));
    informationen[Arten::Type::Fliege].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::Fliege].animationen[Arten::SpeilStatus::Still].gameRepeating(true);


    return informationen;
}

std::vector<NPCSpawnData> initializeNPCSpawnData()
{
    std::vector<NPCSpawnData> spawnData(17);

    sf::Time time;

    // logs always as 0, 1 and 2, other code depends on it
    spawnData[0] = NPCSpawnData();
    spawnData[0].position = sf::Vector2f(-50.f, 260.f);
    spawnData[0].richtung = Arten::Direction::Rechts;
    spawnData[0].type = Arten::Type::Kleinerstamm;
    spawnData[0].speed = 60.f;
    spawnData[0].interval = sf::seconds(6);
    spawnData[0].elapsedTime = sf::seconds(3);
    spawnData[0].spawn = true;

    spawnData[1] = NPCSpawnData();
    spawnData[1].position = sf::Vector2f(-50.f, 180.f);
    spawnData[1].richtung = Arten::Direction::Rechts;
    spawnData[1].type = Arten::Type::Kleinerstamm;
    spawnData[1].speed = 70.f;
    spawnData[1].interval = sf::seconds(5);
    spawnData[1].elapsedTime = sf::seconds(5);
    spawnData[1].spawn = true;

    spawnData[2] = NPCSpawnData();
    spawnData[2].position = sf::Vector2f(530.f, 300);
    spawnData[2].richtung = Arten::Direction::Links;
    spawnData[2].type = Arten::Type::Grosserstamm;
    spawnData[2].speed = -70.f;
    spawnData[2].interval = sf::seconds(5);
    spawnData[2].elapsedTime = spawnData[2].interval;
    spawnData[2].spawn = true;

    // Leave always turtle 2 and 3 as index 3 and 4, other code depends on it
    spawnData[3] = NPCSpawnData();
    spawnData[3].position = sf::Vector2f(530.f, 230.f);
    spawnData[3].richtung = Arten::Direction::Links;
    spawnData[3].type = Arten::Type::Zweierkroete;
    spawnData[3].speed = -100.f;
    spawnData[3].interval = sf::seconds(4);
    spawnData[3].elapsedTime = spawnData[3].interval;
    spawnData[3].spawn = true;

    spawnData[4] = NPCSpawnData();
    spawnData[4].position = sf::Vector2f(530.f, 140.f);
    spawnData[4].richtung = Arten::Direction::Links;
    spawnData[4].type = Arten::Type::Dreierkroete;
    spawnData[4].speed = -50.f;
    spawnData[4].interval = sf::seconds(5);
    spawnData[4].elapsedTime = spawnData[4].interval;
    spawnData[4].spawn = true;

    // Leave always Car 1, 2 and 3 as Index 5,6 and 7
    spawnData[5] = NPCSpawnData();
    spawnData[5].position = sf::Vector2f(530.f, 530.f);
    spawnData[5].richtung = Arten::Direction::Links;
    spawnData[5].type = Arten::Type::Gelbesauto;
    spawnData[5].speed = -100.f;
    spawnData[5].interval = sf::seconds(2);
    spawnData[5].elapsedTime = spawnData[5].interval;
    spawnData[5].spawn = true;

    spawnData[6] = NPCSpawnData();
    spawnData[6].position = sf::Vector2f(530.f, 450.f);
    spawnData[6].richtung = Arten::Direction::Links;
    spawnData[6].type = Arten::Type::Pinkesauto;
    spawnData[6].speed = -150.f;
    spawnData[6].interval = sf::seconds(2);
    spawnData[6].elapsedTime = spawnData[6].interval;
    spawnData[6].spawn = true;

    spawnData[7] = NPCSpawnData();
    spawnData[7].position = sf::Vector2f(-50.f, 410.f);
    spawnData[7].richtung = Arten::Direction::Rechts;
    spawnData[7].type = Arten::Type::Gruenesauto;
    spawnData[7].speed = 100.f;
    spawnData[7].interval = sf::seconds(4);
    spawnData[7].elapsedTime = spawnData[7].interval;
    spawnData[7].spawn = true;

    // Leave always Truck 1 and 2 as Index 8 and 9
    spawnData[8] = NPCSpawnData();
    spawnData[8].position = sf::Vector2f(530.f, 370.f);
    spawnData[8].richtung = Arten::Direction::Links;
    spawnData[8].type = Arten::Type::Lkw;
    spawnData[8].speed = -60.f;
    spawnData[8].interval = sf::seconds(3);
    spawnData[8].elapsedTime = spawnData[8].interval;
    spawnData[8].spawn = true;

    spawnData[9].position = sf::Vector2f(-50.f, 490.f);
    spawnData[9].richtung = Arten::Direction::Rechts;
    spawnData[9].type = Arten::Type::Traktor;
    spawnData[9].speed = 40.f;
    spawnData[9].interval = sf::seconds(3);
    spawnData[9].elapsedTime = spawnData[9].interval;
    spawnData[9].spawn = true;

    // Leave alligaton as Index 10
    spawnData[10] = NPCSpawnData();
    spawnData[10].position = sf::Vector2f(-50.f, 260.f);
    spawnData[10].richtung = Arten::Direction::Rechts;
    spawnData[10].type = Arten::Type::Alligator;
    spawnData[10].speed = 70.f;
    spawnData[10].interval = sf::seconds(6);
    spawnData[10].elapsedTime = sf::seconds(6);
    spawnData[10].spawn = true;

    // Leave floating turtle2 as Index 11
    spawnData[11] = NPCSpawnData();
    spawnData[11].position = sf::Vector2f(530.f, 230.f);
    spawnData[11].richtung = Arten::Direction::Links;
    spawnData[11].type = Arten::Type::Zweierkroete_Untertauchen;
    spawnData[11].speed = -100.f;
    spawnData[11].interval = sf::seconds(4);
    spawnData[11].elapsedTime = spawnData[11].interval / 2.f;
    spawnData[11].spawn = true;

    // Leave floating turtle3 as Index 12
    spawnData[12] = NPCSpawnData();
    spawnData[12].position = sf::Vector2f(530.f, 140.f);
    spawnData[12].richtung = Arten::Direction::Links;
    spawnData[12].type = Arten::Type::Dreierkroete_Untertauchen;
    spawnData[12].speed = -50.f;
    spawnData[12].interval = sf::seconds(5);
    spawnData[12].elapsedTime = spawnData[12].interval / 2.f;
    spawnData[12].spawn = true;

    //Leave alligator swimming left Index 13
    spawnData[13] = NPCSpawnData();
    spawnData[13].position = sf::Vector2f(-50.f, 180.f);
    spawnData[13].richtung = Arten::Direction::Links;
    spawnData[13].type = Arten::Type::Alligator;
    spawnData[13].speed = 80.f;
    spawnData[13].interval = sf::seconds(5);
    spawnData[13].elapsedTime = sf::seconds(2.5);
    spawnData[13].spawn = true;

    // Leave always as index 14
    spawnData[14] = NPCSpawnData();
    spawnData[14].position = sf::Vector2f(0.f, 0.f); // variable
    spawnData[14].richtung = Arten::Direction::Rechts;
    spawnData[14].type = Arten::Type::Pinkerfrosh;
    spawnData[14].speed = 60.f;
    spawnData[14].interval = sf::seconds(6);
    spawnData[14].elapsedTime = sf::seconds(3);
    spawnData[14].spawn = true;

    // Leave always as index 15
    spawnData[15] = NPCSpawnData();
    spawnData[15].position = sf::Vector2f(-50.f, 340.f);
    spawnData[15].richtung = Arten::Direction::Links;
    spawnData[15].type = Arten::Type::Schlange;
    spawnData[15].speed = 80.f;
    spawnData[15].interval = sf::seconds(2);
    spawnData[15].elapsedTime = sf::seconds(2);
    spawnData[15].spawn = false;

    // Leave always as index 16
    spawnData[16] = NPCSpawnData();
    sf::FloatRect pos = ZielPosition()[randomInt(5)];
    spawnData[16].position = sf::Vector2f(pos.left + 20.f, pos.top + 20.f);
    spawnData[16].richtung = Arten::Direction::Oben;
    spawnData[16].type = Arten::Type::Fliege;
    spawnData[16].speed = 0.f;
    spawnData[16].interval = sf::seconds(1.f);
    spawnData[16].elapsedTime = sf::seconds(1.f);
    spawnData[16].spawn = true;

    return spawnData;
}

std::vector<sf::FloatRect> ZielPosition()
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

