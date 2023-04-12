#include "DataTables.h"
#include "JsonFrameParser.h"

std::map<Arten::Type, Karachtere> artenData()
{
    std::map<Arten::Type, Karachtere> informationen;

    informationen[Arten::Type::Frogger].texturen = TextureID::Frogger;

    JsonFrameParser frames = JsonFrameParser("Media/Textures/frogger.json");

     // ZielGebiet
    informationen[Arten::Type::FroggerWinner].texturen = TextureID::Frogger;
    informationen[Arten::Type::FroggerWinner].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("gewinnerfrosh"));
    informationen[Arten::Type::FroggerWinner].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::FroggerWinner].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    // Tod des Spielers
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Tod].gameFrameSet(frames.getFramesFor("tod"));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Tod].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Frogger].animationen[Arten::SpeilStatus::Tod].gameRepeating(false);
    
    // Still status
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

    // Richtungen 
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

    // Alligator 
    informationen[Arten::Type::Alligator].texturen = TextureID::Frogger;
    informationen[Arten::Type::Alligator].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("alligator"));
    informationen[Arten::Type::Alligator].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(1.f));
    informationen[Arten::Type::Alligator].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    // Auto
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

    //KleienrAlliagtor
    informationen[Arten::Type::KleinerAlligator].texturen = TextureID::Frogger;
    informationen[Arten::Type::KleinerAlligator].animationen[Arten::SpeilStatus::Still].gameFrameSet(frames.getFramesFor("kleineralligator"));
    informationen[Arten::Type::KleinerAlligator].animationen[Arten::SpeilStatus::Still].gameSetDuration(sf::seconds(3.f));
    informationen[Arten::Type::KleinerAlligator].animationen[Arten::SpeilStatus::Still].gameRepeating(true);

    return informationen;
}

std::vector<NPCSpawnData> initializeNPCSpawnData()
{
    std::vector<NPCSpawnData> NPCLeben(18);

    sf::Time time;

    // logs always as 0, 1 and 2, other code depends on it
    NPCLeben[0] = NPCSpawnData();
    NPCLeben[0].position = sf::Vector2f(-50.f, 260.f);
    NPCLeben[0].richtung = Arten::Direction::Rechts;
    NPCLeben[0].type = Arten::Type::Kleinerstamm;
    NPCLeben[0].speed = 60.f;
    NPCLeben[0].interval = sf::seconds(6);
    NPCLeben[0].elapsedTime = sf::seconds(3);
    NPCLeben[0].spawn = true;

    NPCLeben[1] = NPCSpawnData();
    NPCLeben[1].position = sf::Vector2f(-50.f, 180.f);
    NPCLeben[1].richtung = Arten::Direction::Rechts;
    NPCLeben[1].type = Arten::Type::Kleinerstamm;
    NPCLeben[1].speed = 70.f;
    NPCLeben[1].interval = sf::seconds(5);
    NPCLeben[1].elapsedTime = sf::seconds(5);
    NPCLeben[1].spawn = true;

    NPCLeben[2] = NPCSpawnData();
    NPCLeben[2].position = sf::Vector2f(530.f, 300);
    NPCLeben[2].richtung = Arten::Direction::Links;
    NPCLeben[2].type = Arten::Type::Grosserstamm;
    NPCLeben[2].speed = -70.f;
    NPCLeben[2].interval = sf::seconds(5);
    NPCLeben[2].elapsedTime = NPCLeben[2].interval;
    NPCLeben[2].spawn = true;

    // Leave always turtle 2 and 3 as index 3 and 4, other code depends on it
    NPCLeben[3] = NPCSpawnData();
    NPCLeben[3].position = sf::Vector2f(530.f, 230.f);
    NPCLeben[3].richtung = Arten::Direction::Links;
    NPCLeben[3].type = Arten::Type::Zweierkroete;
    NPCLeben[3].speed = -100.f;
    NPCLeben[3].interval = sf::seconds(4);
    NPCLeben[3].elapsedTime = NPCLeben[3].interval;
    NPCLeben[3].spawn = true;

    NPCLeben[4] = NPCSpawnData();
    NPCLeben[4].position = sf::Vector2f(530.f, 140.f);
    NPCLeben[4].richtung = Arten::Direction::Links;
    NPCLeben[4].type = Arten::Type::Dreierkroete;
    NPCLeben[4].speed = -50.f;
    NPCLeben[4].interval = sf::seconds(5);
    NPCLeben[4].elapsedTime = NPCLeben[4].interval;
    NPCLeben[4].spawn = true;

    // Leave always Car 1, 2 and 3 as Index 5,6 and 7
    NPCLeben[5] = NPCSpawnData();
    NPCLeben[5].position = sf::Vector2f(530.f, 530.f);
    NPCLeben[5].richtung = Arten::Direction::Links;
    NPCLeben[5].type = Arten::Type::Gelbesauto;
    NPCLeben[5].speed = -100.f;
    NPCLeben[5].interval = sf::seconds(2);
    NPCLeben[5].elapsedTime = NPCLeben[5].interval;
    NPCLeben[5].spawn = true;

    NPCLeben[6] = NPCSpawnData();
    NPCLeben[6].position = sf::Vector2f(530.f, 450.f);
    NPCLeben[6].richtung = Arten::Direction::Links;
    NPCLeben[6].type = Arten::Type::Pinkesauto;
    NPCLeben[6].speed = -150.f;
    NPCLeben[6].interval = sf::seconds(2);
    NPCLeben[6].elapsedTime = NPCLeben[6].interval;
    NPCLeben[6].spawn = true;

    NPCLeben[7] = NPCSpawnData();
    NPCLeben[7].position = sf::Vector2f(-50.f, 410.f);
    NPCLeben[7].richtung = Arten::Direction::Rechts;
    NPCLeben[7].type = Arten::Type::Gruenesauto;
    NPCLeben[7].speed = 100.f;
    NPCLeben[7].interval = sf::seconds(4);
    NPCLeben[7].elapsedTime = NPCLeben[7].interval;
    NPCLeben[7].spawn = true;

    // Leave always Truck 1 and 2 as Index 8 and 9
    NPCLeben[8] = NPCSpawnData();
    NPCLeben[8].position = sf::Vector2f(530.f, 370.f);
    NPCLeben[8].richtung = Arten::Direction::Links;
    NPCLeben[8].type = Arten::Type::Lkw;
    NPCLeben[8].speed = -60.f;
    NPCLeben[8].interval = sf::seconds(3);
    NPCLeben[8].elapsedTime = NPCLeben[8].interval;
    NPCLeben[8].spawn = true;

    NPCLeben[9].position = sf::Vector2f(-50.f, 490.f);
    NPCLeben[9].richtung = Arten::Direction::Rechts;
    NPCLeben[9].type = Arten::Type::Traktor;
    NPCLeben[9].speed = 40.f;
    NPCLeben[9].interval = sf::seconds(3);
    NPCLeben[9].elapsedTime = NPCLeben[9].interval;
    NPCLeben[9].spawn = true;

    // Leave alligaton as Index 10
    NPCLeben[10] = NPCSpawnData();
    NPCLeben[10].position = sf::Vector2f(-50.f, 260.f);
    NPCLeben[10].richtung = Arten::Direction::Rechts;
    NPCLeben[10].type = Arten::Type::Alligator;
    NPCLeben[10].speed = 70.f;
    NPCLeben[10].interval = sf::seconds(6);
    NPCLeben[10].elapsedTime = sf::seconds(6);
    NPCLeben[10].spawn = true;

    // Leave floating turtle2 as Index 11
    NPCLeben[11] = NPCSpawnData();
    NPCLeben[11].position = sf::Vector2f(530.f, 230.f);
    NPCLeben[11].richtung = Arten::Direction::Links;
    NPCLeben[11].type = Arten::Type::Zweierkroete_Untertauchen;
    NPCLeben[11].speed = -100.f;
    NPCLeben[11].interval = sf::seconds(4);
    NPCLeben[11].elapsedTime = NPCLeben[11].interval / 2.f;
    NPCLeben[11].spawn = true;

    // Leave floating turtle3 as Index 12
    NPCLeben[12] = NPCSpawnData();
    NPCLeben[12].position = sf::Vector2f(530.f, 140.f);
    NPCLeben[12].richtung = Arten::Direction::Links;
    NPCLeben[12].type = Arten::Type::Dreierkroete_Untertauchen;
    NPCLeben[12].speed = -50.f;
    NPCLeben[12].interval = sf::seconds(5);
    NPCLeben[12].elapsedTime = NPCLeben[12].interval / 2.f;
    NPCLeben[12].spawn = true;

    //Leave alligator swimming left Index 13
    NPCLeben[13] = NPCSpawnData();
    NPCLeben[13].position = sf::Vector2f(-50.f, 180.f);
    NPCLeben[13].richtung = Arten::Direction::Links;
    NPCLeben[13].type = Arten::Type::Alligator;
    NPCLeben[13].speed = 80.f;
    NPCLeben[13].interval = sf::seconds(5);
    NPCLeben[13].elapsedTime = sf::seconds(2.5);
    NPCLeben[13].spawn = true;

    // Leave always as index 14
    NPCLeben[14] = NPCSpawnData();
    NPCLeben[14].position = sf::Vector2f(0.f, 0.f); // variable
    NPCLeben[14].richtung = Arten::Direction::Rechts;
    NPCLeben[14].type = Arten::Type::Pinkerfrosh;
    NPCLeben[14].speed = 60.f;
    NPCLeben[14].interval = sf::seconds(6);
    NPCLeben[14].elapsedTime = sf::seconds(3);
    NPCLeben[14].spawn = true;

    // Leave always as index 15
    NPCLeben[15] = NPCSpawnData();
    NPCLeben[15].position = sf::Vector2f(-50.f, 340.f);
    NPCLeben[15].richtung = Arten::Direction::Links;
    NPCLeben[15].type = Arten::Type::Schlange;
    NPCLeben[15].speed = 80.f;
    NPCLeben[15].interval = sf::seconds(2);
    NPCLeben[15].elapsedTime = sf::seconds(2);
    NPCLeben[15].spawn = false;

    // Leave always as index 16
    NPCLeben[16] = NPCSpawnData();
    sf::FloatRect pos = ZielPosition()[randomInt(5)];
    NPCLeben[16].position = sf::Vector2f(pos.left + 20.f, pos.top + 20.f);
    NPCLeben[16].richtung = Arten::Direction::Oben;
    NPCLeben[16].type = Arten::Type::Fliege;
    NPCLeben[16].speed = 0.f;
    NPCLeben[16].interval = sf::seconds(1.f);
    NPCLeben[16].elapsedTime = sf::seconds(1.f);
    NPCLeben[16].spawn = true;

    // Leave always as index 17
    NPCLeben[17] = NPCSpawnData();
    sf::FloatRect pos2;
    do { // different spot that the one for the fly
        pos2 = ZielPosition()[randomInt(5)];
    } while (pos2.top == pos.top && pos2.left == pos.left);

    NPCLeben[17].position = sf::Vector2f(pos2.left + 20.f, pos2.top + 20.f);
    NPCLeben[17].richtung = Arten::Direction::Oben;
    NPCLeben[17].type = Arten::Type::KleinerAlligator;
    NPCLeben[17].speed = 0.f;
    NPCLeben[17].interval = sf::seconds(1.f);
    NPCLeben[17].elapsedTime = sf::seconds(1.f);
    NPCLeben[17].spawn = true;

    return NPCLeben;
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

