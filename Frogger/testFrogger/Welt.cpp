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
	, texturenSzene_()
	, weltAnsicht_(outputTarget.getDefaultView())
	, texturen_()
	, fonts(fonts)
	, szenen_()
	, szenenSchichten_()
	, kommando_()
	, worldBounds(0.f, 0.f, weltAnsicht_.getSize().x, weltAnsicht_.getSize().y)
	, spawnPosition(weltAnsicht_.getSize().x / 2.f, worldBounds.height - 20.f)
	, playerFrogger(nullptr)
{
	texturenSzene_.create(target.getSize().x, target.getSize().y);

	loadTextures();
	buildScene();

	npcErscheinung_ = initializeNPCSpawnData();

	weltAnsicht_.setCenter(weltAnsicht_.getSize().x / 2.f, worldBounds.height - weltAnsicht_.getSize().y / 2.f);

	SoundSystem::Instance().playMusic();
}

CommandQueue& World::getCommands()
{
	return kommando_;
}

bool World::playerAlive() const
{
	return playerFrogger->lebenUbrigBekommen() > 0;
}

bool World::reachedEnd() const
{
	return playerFrogger->froggerhatZielErreicht();
}

void World::update(sf::Time dt) {

	entitiesOutsideView();

	szenen_.kaputteEntfernen();

	collisions();

	while (!kommando_.isEmpty()) {
		szenen_.kommandAbgeben(kommando_.pop(), dt);
	}

	// Pink Frog
	if (frogSpawnTimer != -1.f) { // not grabbed by player yet
		frogSpawnTimer += dt.asSeconds();
		if (frogSpawnTimer > 8.f) { // 8 seconds
			npcErscheinung_[14].spawn = true;
			frogSpawnTimer = 0.f;
		}
	}

	addEnemies();
	NPCDaten(dt);

	szenen_.update(dt, getCommands());

	updateText();

	lebensAnzeige(playerFrogger->lebenUbrigBekommen() - 1);

	playerPosition();
}

void World::updateText()
{
	score->setString("" + std::to_string(playerFrogger->punktezahlBekommen()));
	score->setPosition(370.f, 30.f);
}

void World::draw() {

	target.setView(weltAnsicht_);
	target.draw(szenen_);
}

void World::loadTextures() {
	texturen_.laden(TextureID::Background, "Media/Textures/background.png");
	texturen_.laden(TextureID::Frogger, "Media/Textures/frogger.png");
	texturen_.laden(TextureID::Live, "Media/Textures/lives.png");
}

void World::buildScene() {

	for (std::size_t i = 0; i < LagenDerWelt; ++i) {
		Category::Typen category;
		switch (i) {
		case SpielFeld:
			category = Category::Typen::BackgroundLayer;
			break;
		case Fluss:
			category = Category::Typen::Fluss;
			break;
		default:
			category = Category::Typen::None;
			break;
		}

		SceneNode::Ptr layer(new SceneNode(category));

		szenenSchichten_[i] = layer.get();

		szenen_.kindAnhenagen(std::move(layer));
	}

	auto positions = ZielPosition();

	for (int i = 0; i < positions.size(); ++i) {
		SceneNode::Ptr winningSpot(new InteractablePlaceHolder(Category::Typen::Ziel, positions[i]));
		zielistGefullt_.push_back(false);

		szenenSchichten_[Fluss]->kindAnhenagen(std::move(winningSpot));
	}

	sf::Texture& texture = texturen_.get(TextureID::Background);
	texture.setRepeated(true);

	float viewHeight = weltAnsicht_.getSize().y;
	sf::IntRect textureRect(worldBounds);
	textureRect.height += static_cast<int>(viewHeight);

	std::unique_ptr<SpriteNode> background(new SpriteNode(texture, textureRect));
	background->setPosition(worldBounds.left, worldBounds.top - viewHeight);
	szenenSchichten_[Hintergrund]->kindAnhenagen(std::move(background));

	std::unique_ptr<TextNode> scoreField(new TextNode(fonts, ""));
	score = scoreField.get();
	szenenSchichten_[Hintergrund]->kindAnhenagen(std::move(scoreField));

	std::unique_ptr<Frogger> frog(new Frogger(texturen_, fonts));
	frog.get()->setPosition(spawnPosition);
	frog.get()->GeschwindigkeitSetzen(0.f, 0.f);

	playerFrogger = frog.get();

	szenenSchichten_[SpielFeld]->kindAnhenagen(std::move(frog));

	lebensAnzeigeAufbauen(playerFrogger->lebenUbrigBekommen() - 1);
}

void World::addEnemies()
{
	for (int i = 0; i < npcErscheinung_.size(); ++i) {
		if (npcErscheinung_[i].elapsedTime >= npcErscheinung_[i].interval) {
			npcErscheinung_[i].elapsedTime = sf::Time(sf::seconds(0.f));

			// pink frog:
			// if ready to spawn and we're going to spawn a log -> (re)spawn
			// pink frog is index 14
			if (npcErscheinung_[14].spawn && i < 3) {
				if (npcErscheinung_[14].spawn) { // set to log values
					npcErscheinung_[14].position = npcErscheinung_[i].position;
					npcErscheinung_[14].richtung = npcErscheinung_[i].richtung;
					npcErscheinung_[14].speed = npcErscheinung_[i].speed;
					npcErscheinung_[14].interval = sf::seconds(6.f);
					npcErscheinung_[14].elapsedTime = sf::seconds(6.f);
				}
			}

			if (npcErscheinung_[i].type == Arten::Type::Schlange) {
				npcErscheinung_[i].spawn = (randomInt(10) == 9); // 10% chance that the snake will spawn
			}

			if (npcErscheinung_[i].type == Arten::Type::KleinerAlligator && alligHeadTimer != -1 && !npcErscheinung_[i].spawn) {
				npcErscheinung_[i].spawn = (randomInt(10) < 2); // 20% chance that the AlligatorHead will spawn
			}
	
			if (npcErscheinung_[i].spawn) {
				std::unique_ptr<Arten> enemy(new Arten(npcErscheinung_[i].type, texturen_, fonts));

				enemy->setPosition(npcErscheinung_[i].position);
				enemy->GeschwindigkeitSetzen(npcErscheinung_[i].speed, 0.f);
				enemy->RichtungSetzen(npcErscheinung_[i].richtung);

				if (enemy.get()->getCategory() & Category::Typen::SchwimmendeGegner) {
					szenenSchichten_[Fluss]->kindAnhenagen(std::move(enemy));
				}
				else {
					szenenSchichten_[SpielFeld]->kindAnhenagen(std::move(enemy));
				}

				// only one pink frog at a time
				if (npcErscheinung_[i].type == Arten::Type::Pinkerfrosh) npcErscheinung_[i].spawn = false;

				// only one snake at a time
				if (npcErscheinung_[i].type == Arten::Type::Schlange) npcErscheinung_[i].spawn = false;

				// only one Alligato head at a time
				if (npcErscheinung_[i].type == Arten::Type::KleinerAlligator) npcErscheinung_[i].spawn = false;
			}
		}
	}
}

void World::collisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	szenen_.collisionInSzene(szenen_, collisionPairs);

	playerFrogger->GeschwindigkeitSetzen(0.f, 0.f);
	playerFrogger->zuruscksetzenPosition();

	for (auto pair : collisionPairs) {
		if (kategorien(pair, Category::Frogger, Category::Fahrzeuge)) {
			playerFrogger->vomAutiGetroffenFestsetzen(true);
			return;
		}
		if (kategorien(pair, Category::Frogger, Category::Alligator)) {
			playerFrogger->vomAutiGetroffenFestsetzen(true);
			return;
		}
		if (kategorien(pair, Category::Frogger, Category::Fluss)) {
			playerFrogger->imFlussFestgesetzt(true);
		}
		if (kategorien(pair, Category::Frogger, Category::Pinkerfrosh)) {
			playerFrogger->punktezahldDraufrechnen(5);
			// place it outside view so it is removed
			pair.second->setPosition(1000.f, 1000.f);
			npcErscheinung_[14].spawn = false;
			frogSpawnTimer = -1.f; // set it so it does not appear any more
		}
		if (kategorien(pair, Category::Frogger, Category::Schlange)) {
			playerFrogger->vomAutiGetroffenFestsetzen(true);
			return;
		}
		if (kategorien(pair, Category::Frogger, Category::Fliege)) {
			playerFrogger->punktezahldDraufrechnen(5);
			// place it outside view so it is removed
			pair.second->setPosition(1000.f, 1000.f);
			npcErscheinung_[16].spawn = false;
		}
		if (kategorien(pair, Category::Ziel, Category::KleinerAlligator)) {
			if (alligHeadTimer > 12.f) { // despawn
				alligHeadTimer = -1; // end
				// place it outside view so it is removed
				pair.second->setPosition(1000.f, 1000.f);
				npcErscheinung_[17].spawn = false;
				//return;
			}
		}
		if (kategorien(pair, Category::Frogger, Category::SchwimmendeGegner)) {
			if (pair.second->getCategory() == Category::Zweierkroete) {
				// TURTLE 2 is index 3
				if (npcErscheinung_[3].elapsedTime < npcErscheinung_[3].interval / 3.f) { // check in which frame is it
					playerFrogger->imFlussFestgesetzt(true);
					return;
				}
			}
			else if (pair.second->getCategory() == Category::Dreierkroete) {
				// TURTLE 3 is index 4
				if (npcErscheinung_[4].elapsedTime < npcErscheinung_[4].interval / 3.f) { // check in which frame is it
					playerFrogger->imFlussFestgesetzt(true);
					return;
				}
			}

			playerFrogger->spieleraufSchwimmendenGegener(true);

			sf::Vector2f velocity = (static_cast<Arten&>(*pair.second)).GeschwindigkeitGeben();

			playerFrogger->GeschwindigkeitSetzen(velocity);
		}
		if (kategorien(pair, Category::Frogger, Category::Ziel)) {

			if (alligHeadTimer > 0.f && alligHeadTimer < 12.f) {
				sf::FloatRect alligHeadSpot;
				alligHeadSpot.left = npcErscheinung_[17].position.x;
				alligHeadSpot.top = npcErscheinung_[17].position.y;
				alligHeadSpot.height = 40;
				alligHeadSpot.width = 40;

				int allegHeadIndex = ziellocationI(alligHeadSpot);
				sf::FloatRect posRect = (static_cast<InteractablePlaceHolder&>(*pair.first)).getPosition();
				int spotIndex = ziellocationI(posRect);

				if (spotIndex == allegHeadIndex) { // if on same spot
					playerFrogger->vomAutiGetroffenFestsetzen(true);
					return;
				}
			}

			Kommando command;
			command.category = Category::BackgroundLayer;
			command.action = derivedAction<Frogger>([this, pair](Frogger& f, sf::Time t) {

			std::unique_ptr<Arten> winningFrogPicture(new Arten(Arten::Type::FroggerWinner, texturen_, fonts));
			sf::FloatRect posRect = (static_cast<InteractablePlaceHolder&>(*pair.second)).getPosition();
			sf::Vector2f posVector(posRect.left + posRect.width / 2, posRect.top + posRect.height / 2);

			int spotIndex = ziellocationI(posRect);

			if (zielistGefullt_[spotIndex]) {
				playerFrogger->setPosition(posVector);
				playerFrogger->istImZiel();
			}
			else {
				zielistGefullt_[spotIndex] = true;
				zielistGefullt_[ziellocationI(posRect)] = true;

				winningFrogPicture.get()->setPosition(posVector);
				winningFrogPicture.get()->GeschwindigkeitSetzen(0.f, 0.f);
				szenenSchichten_[Hintergrund]->kindAnhenagen(std::move(winningFrogPicture));

				playerFrogger->punktezahldDraufrechnen(50);

				if (zielGefulltKomplett())
					playerFrogger->hatFroggerZielGefulltsetzen();

				playerFrogger->respawnFrogger();
			}

				});
			kommando_.push(command);
		}
	}

}

bool World::kategorien(SceneNode::Pair& colliders, Category::Typen type1, Category::Typen type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

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

void World::entitiesOutsideView()
{
	Kommando command;
	command.category = Category::NPC;
	command.action = derivedAction<Arten>([this](Arten& a, sf::Time t) {
		if (!gameBounds().intersects(a.getBoundingRect())) {
			a.setMarkedForRemoval(true);
		}
		});
	kommando_.push(command);
}

void World::lebensAnzeige(int frogLives)
{
	if (playerFrogger->getState() == Arten::SpeilStatus::Tod) {
		int interval = 25;
		int curPosition = 5;
		int positionY = 570;
		int livesIndexInSceneLayers = 1;

		szenen_.kindentfernen(*szenenSchichten_[Leben]);

		SceneNode::Ptr lives(new SceneNode(Category::None));

		for (int i = 0; i < frogLives - 1; ++i) {
			std::unique_ptr<SpriteNode> live(new SpriteNode(texturen_.get(TextureID::Live)));
			live->setPosition(curPosition, positionY);
			curPosition += interval;
			lives->kindAnhenagen(std::move(live));
		}
		szenenSchichten_[livesIndexInSceneLayers] = lives.get();

		szenen_.kindAnhenagen(std::move(lives));
	}
}

void World::lebensAnzeigeAufbauen(int frogLives)
{
	int interval = 25;
	int curPosition = 5;
	int positionY = 570;

	for (int i = 0; i < frogLives; ++i) {
		std::unique_ptr<SpriteNode> live(new SpriteNode(texturen_.get(TextureID::Live)));
		live->setPosition(curPosition, positionY);
		curPosition += interval;
		szenenSchichten_[Leben]->kindAnhenagen(std::move(live));
	}
}

void World::NPCDaten(sf::Time dt)
{
	for (int i = 0; i < npcErscheinung_.size(); ++i) {
		npcErscheinung_[i].elapsedTime += dt;
	}
}

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(weltAnsicht_.getCenter() - weltAnsicht_.getSize() / 2.f, weltAnsicht_.getSize());
}

sf::FloatRect World::gameBounds() const
{
	auto bounds = getViewBounds();

	bounds.left -= 50.f;
	bounds.width += 100.f;

	return bounds;
}

int World::ziellocationI(sf::FloatRect pos)
{
	auto v = ZielPosition();

	for (int i = 0; i < zielistGefullt_.size(); ++i) {
		if (abs(pos.left - v[i].left) < 0.1) {
			return i;
		}
	}
	return -1;
}

bool World::zielGefulltKomplett()
{
	for (int i = 0; i < zielistGefullt_.size(); ++i) {
		if (!zielistGefullt_[i])
			return false;
	}
	return true;
}


void World::playerPosition()
{
	sf::Vector2f position = playerFrogger->getPosition();
	float left = weltAnsicht_.getCenter().x - weltAnsicht_.getSize().x / 2.f;
	float right = weltAnsicht_.getCenter().x + weltAnsicht_.getSize().x / 2.f;
	float top = weltAnsicht_.getCenter().y - weltAnsicht_.getSize().y / 2.f;
	float bottom = weltAnsicht_.getCenter().y + weltAnsicht_.getSize().y / 2.f;

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

void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

float toDegree(float radian) {
	return (radian * 180) / PI;
}

float toRadian(float degree) {
	return (degree * PI) / 180;
}

float length(sf::Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f normalize(sf::Vector2f v) {
	if (length(v) > 0) {
		return (v / length(v));
	}
	return v;
}

int	randomInt(int exclusiveMax) {
	std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
	return distr(RandomEngine);
}

sf::IntRect flip(const sf::IntRect& rec)
{
	auto tmp = rec;
	tmp.left += tmp.width;
	tmp.width *= -1;
	return tmp;
}