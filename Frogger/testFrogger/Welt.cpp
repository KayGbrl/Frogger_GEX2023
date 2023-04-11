#include "Welt.h"
#include "Category.h"
#include "SoundSystem.h"
#include "Frogger.h"
#include "Elemente.h"
#include "Animation.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML\System\Sleep.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>
#include <cmath>
#include <random>


World::World(sf::RenderTarget& outputTarget, const FontHolder_t& fonts)
	: target(outputTarget)
	, texturenWelt_()
	, weltSicht_(outputTarget.getDefaultView())
	, texturen_()
	, fonts(fonts)
	, Szene_()
	, SzenenStaffel_()
	, kommandoAbwarten_()
	, weltLimit_(0.f, 0.f, weltSicht_.getSize().x, weltSicht_.getSize().y)
	, spawnPosition_(weltSicht_.getSize().x / 2.f, weltLimit_.height - 20.f)
	, playerFrogger(nullptr)
{
	texturenWelt_.create(target.getSize().x, target.getSize().y);

	loadTextures();
	buildScene();

	spawnTablefurNPC_ = initializeNPCSpawnData();

	weltSicht_.setCenter(weltSicht_.getSize().x / 2.f, weltLimit_.height - weltSicht_.getSize().y / 2.f);

	SoundSystem::Instance().playMusic();
}

CommandQueue& World::getCommands()
{
	return kommandoAbwarten_;
}

bool World::playerAlive() const
{
	return playerFrogger->ueberbleibendeLeben() > 0;
}

bool World::reachedEnd() const
{
	return playerFrogger->SPielerZielErreicht();
}

void World::update(sf::Time dt) {

	entitiesOutsideView();

	Szene_.kaputteEntfernen();

	collisions();

	while (!kommandoAbwarten_.isEmpty()) {
		Szene_.onCommand(kommandoAbwarten_.pop(), dt);
	}

	// Pink Frog
	if (frogSpawnTimer != -1.f) { // not grabbed by player yet
		frogSpawnTimer += dt.asSeconds();
		if (frogSpawnTimer > 8.f) { // 8 seconds
			spawnTablefurNPC_[14].spawn = true;
			frogSpawnTimer = 0.f;
		}
	}

	// Alligator Kopf
	if (alligHeadTimer != -1)
		alligHeadTimer += dt.asSeconds();

	addEnemies();
	updateNPCSpawnTable(dt);

	Szene_.update(dt, getCommands());

	updateText();

	liveIndicator(playerFrogger->ueberbleibendeLeben() - 1);

	playerPosition();
}

void World::updateText()
{
	score->setString("" + std::to_string(playerFrogger->scorebekommen()));
	score->setPosition(370.f, 30.f);
}

void World::draw() {

	target.setView(weltSicht_);
	target.draw(Szene_);
}

void World::loadTextures() {
	texturen_.laden(TextureID::Hintergrund, "Media/Textures/background.png");
	texturen_.laden(TextureID::Frogger, "Media/Textures/froggerDataSheet.png");
	texturen_.laden(TextureID::Leben, "Media/Textures/lives.png");
}

void World::buildScene() {

	for (std::size_t i = 0; i < LayerCount; ++i) {
		Category::Typen category;
		switch (i) {
		case PlayingLayer:
			category = Category::Typen::BackgroundLayer;
			break;
		case River:
			category = Category::Typen::Fluss;
			break;
		default:
			category = Category::Typen::None;
			break;
		}

		SceneNode::Ptr layer(new SceneNode(category));

		SzenenStaffel_[i] = layer.get();

		Szene_.kindangehangt(std::move(layer));
	}

	auto positions = ZielPosition();

	for (int i = 0; i < positions.size(); ++i) {
		SceneNode::Ptr winningSpot(new InteractablePlaceHolder(Category::Typen::Ziel, positions[i]));
		zielGefulklt_.push_back(false);

		SzenenStaffel_[River]->kindangehangt(std::move(winningSpot));
	}

	sf::Texture& texture = texturen_.get(TextureID::Hintergrund);
	texture.setRepeated(true);

	float viewHeight = weltSicht_.getSize().y;
	sf::IntRect textureRect(weltLimit_);
	textureRect.height += static_cast<int>(viewHeight);

	std::unique_ptr<SpriteNode> background(new SpriteNode(texture, textureRect));
	background->setPosition(weltLimit_.left, weltLimit_.top - viewHeight);
	SzenenStaffel_[Background]->kindangehangt(std::move(background));

	std::unique_ptr<TextNode> scoreField(new TextNode(fonts, ""));
	score = scoreField.get();
	SzenenStaffel_[Background]->kindangehangt(std::move(scoreField));

	std::unique_ptr<Frogger> frog(new Frogger(texturen_, fonts));
	frog.get()->setPosition(spawnPosition_);
	frog.get()->GeschwindigkeitSetzen(0.f, 0.f);

	playerFrogger = frog.get();

	SzenenStaffel_[PlayingLayer]->kindangehangt(std::move(frog));

	buildLivesIndicator(playerFrogger->ueberbleibendeLeben() - 1);
}

void World::addEnemies()
{
	for (int i = 0; i < spawnTablefurNPC_.size(); ++i) {
		if (spawnTablefurNPC_[i].abgelaufeneZeit >= spawnTablefurNPC_[i].interval) {
			spawnTablefurNPC_[i].abgelaufeneZeit = sf::Time(sf::seconds(0.f));

			// pink frog:
			// if ready to spawn and we're going to spawn a log -> (re)spawn
			// pink frog is index 14
			if (spawnTablefurNPC_[14].spawn && i < 3) {
				if (spawnTablefurNPC_[14].spawn) { // set to log values
					spawnTablefurNPC_[14].position = spawnTablefurNPC_[i].position;
					spawnTablefurNPC_[14].richtung = spawnTablefurNPC_[i].richtung;
					spawnTablefurNPC_[14].speed = spawnTablefurNPC_[i].speed;
					spawnTablefurNPC_[14].interval = sf::seconds(6.f);
					spawnTablefurNPC_[14].abgelaufeneZeit = sf::seconds(6.f);
				}
			}

			if (spawnTablefurNPC_[i].type == Arten::Type::Schlange) {
				spawnTablefurNPC_[i].spawn = (zuffalsZahl(10) == 9); // 10% chance that the snake will spawn
			}

			if (spawnTablefurNPC_[i].type == Arten::Type::KleinerAlligator && alligHeadTimer != -1 && !spawnTablefurNPC_[i].spawn) {
				spawnTablefurNPC_[i].spawn = (zuffalsZahl(10) < 2); // 20% chance that the AlligatorHead will spawn
			}
	
			if (spawnTablefurNPC_[i].spawn) {
				std::unique_ptr<Arten> enemy(new Arten(spawnTablefurNPC_[i].type, texturen_, fonts));

				enemy->setPosition(spawnTablefurNPC_[i].position);
				enemy->GeschwindigkeitSetzen(spawnTablefurNPC_[i].speed, 0.f);
				enemy->RichtungSetzen(spawnTablefurNPC_[i].richtung);

				if (enemy.get()->kategoryBekommen() & Category::Typen::SchwimmendeGegner) {
					SzenenStaffel_[River]->kindangehangt(std::move(enemy));
				}
				else {
					SzenenStaffel_[PlayingLayer]->kindangehangt(std::move(enemy));
				}

				// only one pink frog at a time
				if (spawnTablefurNPC_[i].type == Arten::Type::Pinkerfrosh) spawnTablefurNPC_[i].spawn = false;

				// only one snake at a time
				if (spawnTablefurNPC_[i].type == Arten::Type::Schlange) spawnTablefurNPC_[i].spawn = false;

				// only one Alligato head at a time
				if (spawnTablefurNPC_[i].type == Arten::Type::KleinerAlligator) spawnTablefurNPC_[i].spawn = false;
			}
		}
	}
}

void World::collisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	Szene_.checkSceneCollision(Szene_, collisionPairs);

	playerFrogger->GeschwindigkeitSetzen(0.f, 0.f);
	playerFrogger->zurusetzenFlagge();

	for (auto pair : collisionPairs) {
		if (categories(pair, Category::Frogger, Category::Fahrzeuge)) {
			playerFrogger->imWasser(true);
			return;
		}
		if (categories(pair, Category::Frogger, Category::Alligator)) {
			playerFrogger->imWasser(true);
			return;
		}
		if (categories(pair, Category::Frogger, Category::Fluss)) {
			playerFrogger->imWasserGestzt(true);
		}
		if (categories(pair, Category::Frogger, Category::Pinkerfrosh)) {
			playerFrogger->punkteAufrechnen(5);
			// place it outside view so it is removed
			pair.second->setPosition(1000.f, 1000.f);
			spawnTablefurNPC_[14].spawn = false;
			frogSpawnTimer = -1.f; // set it so it does not appear any more
		}
		if (categories(pair, Category::Frogger, Category::Schlange)) {
			playerFrogger->imWasser(true);
			return;
		}
		if (categories(pair, Category::Frogger, Category::Fliege)) {
			playerFrogger->punkteAufrechnen(5);
			// place it outside view so it is removed
			pair.second->setPosition(1000.f, 1000.f);
			spawnTablefurNPC_[16].spawn = false;
		}
		if (categories(pair, Category::Ziel, Category::KleinerAlligator)) {
			if (alligHeadTimer > 12.f) { // despawn
				alligHeadTimer = -1; // end
				// set outside view
				pair.second->setPosition(1000.f, 1000.f);
				spawnTablefurNPC_[17].spawn = false;
				//return;
			}
		}
		if (categories(pair, Category::Frogger, Category::SchwimmendeGegner)) {
			if (pair.second->kategoryBekommen() == Category::Zweierkroete) {
				// TURTLE 2 is index 3
				if (spawnTablefurNPC_[3].abgelaufeneZeit < spawnTablefurNPC_[3].interval / 3.f) { // check in which frame is it
					playerFrogger->imWasserGestzt(true);
					return;
				}
			}
			else if (pair.second->kategoryBekommen() == Category::Dreierkroete) {
				// TURTLE 3 is index 4
				if (spawnTablefurNPC_[4].abgelaufeneZeit < spawnTablefurNPC_[4].interval / 3.f) { // check in which frame is it
					playerFrogger->imWasserGestzt(true);
					return;
				}
			}

			playerFrogger->spielerAufSchwimmendeGegner(true);

			sf::Vector2f velocity = (static_cast<Arten&>(*pair.second)).GeschwindigkeitGeben();

			playerFrogger->GeschwindigkeitSetzen(velocity);
		}
		if (categories(pair, Category::Frogger, Category::Ziel)) {

			if (alligHeadTimer > 0.f && alligHeadTimer < 12.f) {
				sf::FloatRect alligHeadSpot;
				alligHeadSpot.left = spawnTablefurNPC_[17].position.x;
				alligHeadSpot.top = spawnTablefurNPC_[17].position.y;
				alligHeadSpot.height = 40;
				alligHeadSpot.width = 40;

				int allegHeadIndex = winnningSpotIndex(alligHeadSpot);
				sf::FloatRect posRect = (static_cast<InteractablePlaceHolder&>(*pair.first)).getPosition();
				int spotIndex = winnningSpotIndex(posRect);

				if (spotIndex == allegHeadIndex) { // if on same spot
					playerFrogger->imWasser(true);
					return;
				}
			}
			Kommando command;
			command.category = Category::BackgroundLayer;
			command.action = derivedAction<Frogger>([this, pair](Frogger& f, sf::Time t) {

			std::unique_ptr<Arten> winningFrogPicture(new Arten(Arten::Type::FroggerWinner, texturen_, fonts));
			sf::FloatRect posRect = (static_cast<InteractablePlaceHolder&>(*pair.second)).getPosition();
			sf::Vector2f posVector(posRect.left + posRect.width / 2, posRect.top + posRect.height / 2);

			int spotIndex = winnningSpotIndex(posRect);

			if (zielGefulklt_[spotIndex]) {
				playerFrogger->setPosition(posVector);
				playerFrogger->Zieleingenommen();
			}
			else {
				zielGefulklt_[spotIndex] = true;
				zielGefulklt_[winnningSpotIndex(posRect)] = true;

				winningFrogPicture.get()->setPosition(posVector);
				winningFrogPicture.get()->GeschwindigkeitSetzen(0.f, 0.f);
				SzenenStaffel_[Background]->kindangehangt(std::move(winningFrogPicture));

				playerFrogger->punkteAufrechnen(30);

				if (winningSpotsFull())
					playerFrogger->alleZielegefullt();

				playerFrogger->respawnFrogger();
			}

				});
			kommandoAbwarten_.push(command);
		}
	}

}

// Check what category it belongs
bool World::categories(SceneNode::Pair& colliders, Category::Typen type1, Category::Typen type2)
{
	unsigned int category1 = colliders.first->kategoryBekommen();
	unsigned int category2 = colliders.second->kategoryBekommen();

	if (type1 & category1 && type2 & category2) {
		return true;
	}
	else if (type2 & category1 && type1 & category2) {
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else {
		return false;
	}
}

//Remove entities outside view
void World::entitiesOutsideView()
{
	Kommando command;
	command.category = Category::NPC;
	command.action = derivedAction<Arten>([this](Arten& a, sf::Time t) {
		if (!gameBounds().intersects(a.ruckstossBekommenRechteck())) {
			a.zumEntfernenMArker(true);
		}
		});
	kommandoAbwarten_.push(command);
}

void World::liveIndicator(int frogLives)
{
	if (playerFrogger->statusBekommen() == Arten::SpeilStatus::Tod) {
		int interval = 25;
		int curPosition = 5;
		int positionY = 570;
		int livesIndexInSceneLayers = 1;

		Szene_.detachChild(*SzenenStaffel_[Lives]);

		SceneNode::Ptr lives(new SceneNode(Category::None));

		for (int i = 0; i < frogLives - 1; ++i) {
			std::unique_ptr<SpriteNode> live(new SpriteNode(texturen_.get(TextureID::Leben)));
			live->setPosition(curPosition, positionY);
			curPosition += interval;
			lives->kindangehangt(std::move(live));
		}
		SzenenStaffel_[livesIndexInSceneLayers] = lives.get();

		Szene_.kindangehangt(std::move(lives));
	}
}

void World::buildLivesIndicator(int frogLives)
{
	int interval = 25;
	int curPosition = 5;
	int positionY = 570;

	for (int i = 0; i < frogLives; ++i) {
		std::unique_ptr<SpriteNode> live(new SpriteNode(texturen_.get(TextureID::Leben)));
		live->setPosition(curPosition, positionY);
		curPosition += interval;
		SzenenStaffel_[Lives]->kindangehangt(std::move(live));
	}
}

void World::updateNPCSpawnTable(sf::Time dt)
{
	for (int i = 0; i < spawnTablefurNPC_.size(); ++i) {
		spawnTablefurNPC_[i].abgelaufeneZeit += dt;
	}
}

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(weltSicht_.getCenter() - weltSicht_.getSize() / 2.f, weltSicht_.getSize());
}

sf::FloatRect World::gameBounds() const
{
	auto bounds = getViewBounds();

	bounds.left -= 50.f;
	bounds.width += 100.f;

	return bounds;
}

int World::winnningSpotIndex(sf::FloatRect pos)
{
	auto v = ZielPosition();

	for (int i = 0; i < zielGefulklt_.size(); ++i) {
		if (abs(pos.left - v[i].left) < 0.1) {
			return i;
		}
	}
	return -1;
}

bool World::winningSpotsFull()
{
	for (int i = 0; i < zielGefulklt_.size(); ++i) {
		if (!zielGefulklt_[i])
			return false;
	}
	return true;
}


void World::playerPosition()
{
	sf::Vector2f position = playerFrogger->getPosition();
	float left = weltSicht_.getCenter().x - weltSicht_.getSize().x / 2.f;
	float right = weltSicht_.getCenter().x + weltSicht_.getSize().x / 2.f;
	float top = weltSicht_.getCenter().y - weltSicht_.getSize().y / 2.f;
	float bottom = weltSicht_.getCenter().y + weltSicht_.getSize().y / 2.f;

	const float borderDistance = 20.f;

	if (position.x < left + borderDistance) {
		playerFrogger->setPosition(left + borderDistance, position.y);
	}
	else if (position.x > right - borderDistance) {
		playerFrogger->setPosition(right - borderDistance, position.y);
	}
	else if (position.y > bottom - borderDistance) {
		playerFrogger->setPosition(position.x, bottom - borderDistance);
	}
	else if (position.y < top + borderDistance) {
		playerFrogger->setPosition(position.x, top + borderDistance);
	}
}

// Welt Wand und Kontakt
InteractablePlaceHolder::InteractablePlaceHolder(Category::Typen category)
	:SceneNode(category)
{}

InteractablePlaceHolder::InteractablePlaceHolder(Category::Typen category, sf::FloatRect pos)
	: SceneNode(category)
	, position(pos)
{
}

sf::FloatRect InteractablePlaceHolder::getPosition() const
{
	return position;
}

void InteractablePlaceHolder::setPosition(sf::FloatRect pos)
{
	position = pos;
}

sf::FloatRect InteractablePlaceHolder::getBoundingRect() const
{
	return position;
}

//Zufalls system
namespace {
	const float PI = 3.1415927;

	std::mt19937 createRandomEngine() {
		std::random_device r;
		return std::mt19937(r());
	}

	auto RandomEngine = createRandomEngine();
}

void zentrierterPunkt(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void zentrierterPunkt(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

float mass(float radian) {
	return (radian * 180) / PI;
}

float radiant(float degree) {
	return (degree * PI) / 180;
}

float lange(sf::Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f normalisieren(sf::Vector2f v) {
	if (lange(v) > 0) {
		return (v / lange(v));
	}
	return v;
}

int	zuffalsZahl(int exclusiveMax) {
	std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
	return distr(RandomEngine);
}

sf::IntRect drehen(const sf::IntRect& rec)
{
	auto tmp = rec;
	tmp.left += tmp.width;
	tmp.width *= -1;
	return tmp;
}