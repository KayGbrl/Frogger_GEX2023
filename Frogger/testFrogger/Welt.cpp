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
	, sceneTexture()
	, worldView(outputTarget.getDefaultView())
	, textures()
	, fonts(fonts)
	, sceneGraph()
	, sceneLayers()
	, commandQueue()
	, worldBounds(0.f, 0.f, worldView.getSize().x, worldView.getSize().y)
	, spawnPosition(worldView.getSize().x / 2.f, worldBounds.height - 20.f)
	, playerFrogger(nullptr)
{
	sceneTexture.create(target.getSize().x, target.getSize().y);

	loadTextures();
	buildScene();

	npcSpawnTable = initializeNPCSpawnData();

	worldView.setCenter(worldView.getSize().x / 2.f, worldBounds.height - worldView.getSize().y / 2.f);

	SoundSystem::Instance().playMusic();
}

CommandQueue& World::getCommands()
{
	return commandQueue;
}

bool World::playerAlive() const
{
	return playerFrogger->getLivesLeft() > 0;
}

bool World::reachedEnd() const
{
	return playerFrogger->hasFroggerFilledSlots();
}

void World::update(sf::Time dt) {

	entitiesOutsideView();

	sceneGraph.kaputteEntfernen();

	collisions();

	while (!commandQueue.isEmpty()) {
		sceneGraph.onCommand(commandQueue.pop(), dt);
	}

	// Pink Frog
	if (frogSpawnTimer != -1.f) { // not grabbed by player yet
		frogSpawnTimer += dt.asSeconds();
		if (frogSpawnTimer > 8.f) { // 8 seconds
			npcSpawnTable[14].spawn = true;
			frogSpawnTimer = 0.f;
		}
	}

	addEnemies();
	updateNPCSpawnTable(dt);

	sceneGraph.update(dt, getCommands());

	updateText();

	liveIndicator(playerFrogger->getLivesLeft() - 1);

	playerPosition();
}

void World::updateText()
{
	score->setString("" + std::to_string(playerFrogger->getScore()));
	score->setPosition(370.f, 30.f);
}

void World::draw() {

	target.setView(worldView);
	target.draw(sceneGraph);
}

void World::loadTextures() {
	textures.laden(TextureID::Background, "Media/Textures/background.png");
	textures.laden(TextureID::Frogger, "Media/Textures/frog.png");
	textures.laden(TextureID::Live, "Media/Textures/lives.png");
}

void World::buildScene() {

	for (std::size_t i = 0; i < LayerCount; ++i) {
		Category::Typen category;
		switch (i) {
		case PlayingLayer:
			category = Category::Typen::BackgroundLayer;
			break;
		case River:
			category = Category::Typen::River;
			break;
		default:
			category = Category::Typen::None;
			break;
		}

		SceneNode::Ptr layer(new SceneNode(category));

		sceneLayers[i] = layer.get();

		sceneGraph.attachChild(std::move(layer));
	}

	auto positions = getWinningSpotPositions();

	for (int i = 0; i < positions.size(); ++i) {
		SceneNode::Ptr winningSpot(new InteractablePlaceHolder(Category::Typen::WinningSpot, positions[i]));
		winningSpotsFilled.push_back(false);

		sceneLayers[River]->attachChild(std::move(winningSpot));
	}

	sf::Texture& texture = textures.get(TextureID::Background);
	texture.setRepeated(true);

	float viewHeight = worldView.getSize().y;
	sf::IntRect textureRect(worldBounds);
	textureRect.height += static_cast<int>(viewHeight);

	std::unique_ptr<SpriteNode> background(new SpriteNode(texture, textureRect));
	background->setPosition(worldBounds.left, worldBounds.top - viewHeight);
	sceneLayers[Background]->attachChild(std::move(background));

	std::unique_ptr<TextNode> scoreField(new TextNode(fonts, ""));
	score = scoreField.get();
	sceneLayers[Background]->attachChild(std::move(scoreField));

	std::unique_ptr<Frogger> frog(new Frogger(textures, fonts));
	frog.get()->setPosition(spawnPosition);
	frog.get()->GeschwindigkeitSetzen(0.f, 0.f);

	playerFrogger = frog.get();

	sceneLayers[PlayingLayer]->attachChild(std::move(frog));

	buildLivesIndicator(playerFrogger->getLivesLeft() - 1);
}

void World::addEnemies()
{
	for (int i = 0; i < npcSpawnTable.size(); ++i) {
		if (npcSpawnTable[i].elapsedTime >= npcSpawnTable[i].interval) {
			npcSpawnTable[i].elapsedTime = sf::Time(sf::seconds(0.f));

			// pink frog:
			// if ready to spawn and we're going to spawn a log -> (re)spawn
			// pink frog is index 14
			if (npcSpawnTable[14].spawn && i < 3) {
				if (npcSpawnTable[14].spawn) { // set to log values
					npcSpawnTable[14].position = npcSpawnTable[i].position;
					npcSpawnTable[14].richtung = npcSpawnTable[i].richtung;
					npcSpawnTable[14].speed = npcSpawnTable[i].speed;
					npcSpawnTable[14].interval = sf::seconds(6.f);
					npcSpawnTable[14].elapsedTime = sf::seconds(6.f);
				}
			}

			if (npcSpawnTable[i].type == Arten::Type::Snake) {
				npcSpawnTable[i].spawn = (randomInt(10) == 9); // 10% chance that the snake will spawn
			}
	
			if (npcSpawnTable[i].spawn) {
				std::unique_ptr<Arten> enemy(new Arten(npcSpawnTable[i].type, textures, fonts));

				enemy->setPosition(npcSpawnTable[i].position);
				enemy->GeschwindigkeitSetzen(npcSpawnTable[i].speed, 0.f);
				enemy->RichtungSetzen(npcSpawnTable[i].richtung);

				if (enemy.get()->getCategory() & Category::Typen::SwimmingNPC) {
					sceneLayers[River]->attachChild(std::move(enemy));
				}
				else {
					sceneLayers[PlayingLayer]->attachChild(std::move(enemy));
				}

				// only one pink frog at a time
				if (npcSpawnTable[i].type == Arten::Type::PinkFrog) npcSpawnTable[i].spawn = false;

				// only one snake at a time
				if (npcSpawnTable[i].type == Arten::Type::Snake) npcSpawnTable[i].spawn = false;
			}
		}
	}
}

void World::collisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	sceneGraph.checkSceneCollision(sceneGraph, collisionPairs);

	playerFrogger->GeschwindigkeitSetzen(0.f, 0.f);
	playerFrogger->resetPositionFlags();

	for (auto pair : collisionPairs) {
		if (categories(pair, Category::Frogger, Category::Vehicle)) {
			playerFrogger->setIsStruckByCar(true);
			return;
		}
		if (categories(pair, Category::Frogger, Category::Alligator)) {
			playerFrogger->setIsStruckByCar(true);
			return;
		}
		if (categories(pair, Category::Frogger, Category::River)) {
			playerFrogger->setIsInRiver(true);
		}
		if (categories(pair, Category::Frogger, Category::PinkFrog)) {
			playerFrogger->addScore(5);
			// place it outside view so it is removed
			pair.second->setPosition(1000.f, 1000.f);
			npcSpawnTable[14].spawn = false;
			frogSpawnTimer = -1.f; // set it so it does not appear any more
		}
		if (categories(pair, Category::Frogger, Category::Snake)) {
			playerFrogger->setIsStruckByCar(true);
			return;
		}
		if (categories(pair, Category::Frogger, Category::SwimmingNPC)) {
			if (pair.second->getCategory() == Category::Turtle2) {
				// TURTLE 2 is index 3
				if (npcSpawnTable[3].elapsedTime < npcSpawnTable[3].interval / 3.f) { // check in which frame is it
					playerFrogger->setIsInRiver(true);
					return;
				}
			}
			else if (pair.second->getCategory() == Category::Turtle3) {
				// TURTLE 3 is index 4
				if (npcSpawnTable[4].elapsedTime < npcSpawnTable[4].interval / 3.f) { // check in which frame is it
					playerFrogger->setIsInRiver(true);
					return;
				}
			}

			playerFrogger->playerOnSwimmingNPC(true);

			sf::Vector2f velocity = (static_cast<Arten&>(*pair.second)).GeschwindigkeitGeben();

			playerFrogger->GeschwindigkeitSetzen(velocity);
		}
		if (categories(pair, Category::Frogger, Category::WinningSpot)) {
			Kommando command;
			command.category = Category::BackgroundLayer;
			command.action = derivedAction<Frogger>([this, pair](Frogger& f, sf::Time t) {

			std::unique_ptr<Arten> winningFrogPicture(new Arten(Arten::Type::FroggerWinner, textures, fonts));
			sf::FloatRect posRect = (static_cast<InteractablePlaceHolder&>(*pair.second)).getPosition();
			sf::Vector2f posVector(posRect.left + posRect.width / 2, posRect.top + posRect.height / 2);

			int spotIndex = winnningSpotIndex(posRect);

			if (winningSpotsFilled[spotIndex]) {
				playerFrogger->setPosition(posVector);
				playerFrogger->setIsWinningSpotTaken();
			}
			else {
				winningSpotsFilled[spotIndex] = true;
				winningSpotsFilled[winnningSpotIndex(posRect)] = true;

				winningFrogPicture.get()->setPosition(posVector);
				winningFrogPicture.get()->GeschwindigkeitSetzen(0.f, 0.f);
				sceneLayers[Background]->attachChild(std::move(winningFrogPicture));

				playerFrogger->addScore(30);

				if (winningSpotsFull())
					playerFrogger->setHasFroggerFilledSlots();

				playerFrogger->respawnFrogger();
			}

				});
			commandQueue.push(command);
		}
	}

}

bool World::categories(SceneNode::Pair& colliders, Category::Typen type1, Category::Typen type2)
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
	commandQueue.push(command);
}

void World::liveIndicator(int frogLives)
{
	if (playerFrogger->getState() == Arten::SpeilStatus::Dead) {
		int interval = 25;
		int curPosition = 5;
		int positionY = 570;
		int livesIndexInSceneLayers = 1;

		sceneGraph.detachChild(*sceneLayers[Lives]);

		SceneNode::Ptr lives(new SceneNode(Category::None));

		for (int i = 0; i < frogLives - 1; ++i) {
			std::unique_ptr<SpriteNode> live(new SpriteNode(textures.get(TextureID::Live)));
			live->setPosition(curPosition, positionY);
			curPosition += interval;
			lives->attachChild(std::move(live));
		}
		sceneLayers[livesIndexInSceneLayers] = lives.get();

		sceneGraph.attachChild(std::move(lives));
	}
}

void World::buildLivesIndicator(int frogLives)
{
	int interval = 25;
	int curPosition = 5;
	int positionY = 570;

	for (int i = 0; i < frogLives; ++i) {
		std::unique_ptr<SpriteNode> live(new SpriteNode(textures.get(TextureID::Live)));
		live->setPosition(curPosition, positionY);
		curPosition += interval;
		sceneLayers[Lives]->attachChild(std::move(live));
	}
}

void World::updateNPCSpawnTable(sf::Time dt)
{
	for (int i = 0; i < npcSpawnTable.size(); ++i) {
		npcSpawnTable[i].elapsedTime += dt;
	}
}

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(worldView.getCenter() - worldView.getSize() / 2.f, worldView.getSize());
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
	auto v = getWinningSpotPositions();

	for (int i = 0; i < winningSpotsFilled.size(); ++i) {
		if (abs(pos.left - v[i].left) < 0.1) {
			return i;
		}
	}
	return -1;
}

bool World::winningSpotsFull()
{
	for (int i = 0; i < winningSpotsFilled.size(); ++i) {
		if (!winningSpotsFilled[i])
			return false;
	}
	return true;
}


void World::playerPosition()
{
	sf::Vector2f position = playerFrogger->getPosition();
	float left = worldView.getCenter().x - worldView.getSize().x / 2.f;
	float right = worldView.getCenter().x + worldView.getSize().x / 2.f;
	float top = worldView.getCenter().y - worldView.getSize().y / 2.f;
	float bottom = worldView.getCenter().y + worldView.getSize().y / 2.f;

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