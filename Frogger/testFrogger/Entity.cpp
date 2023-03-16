
#include "Entity.h"

#include <cassert>

Entity::Entity(int punkte)
	: punkte(punkte)
{}

void Entity::GeschwindigkeitSetzen(sf::Vector2f v) {
	geschwindigkeit = v;
}

void Entity::GeschwindigkeitSetzen(float xv, float yv) {
	geschwindigkeit.x = xv;
	geschwindigkeit.y = yv;
}

void Entity::beschleunigen(sf::Vector2f v) {
	geschwindigkeit += v;
}

void Entity::beschleunigen(float xv, float yv) {
	geschwindigkeit.x += xv;
	geschwindigkeit.y += yv;
}

sf::Vector2f Entity::GeschwindigkeitGeben() const {
	return geschwindigkeit;
}

int Entity::PunkteBeiKontakt() const
{
	return punkte;
}

void Entity::reparieren(int zahlen)
{
	assert(zahlen > 0);
	punkte += zahlen;
}

void Entity::schaden(int zahlen)
{
	assert(zahlen > 0);
	punkte -= zahlen;
}

void Entity::zestoeren()
{
	punkte = 0;
}

bool Entity::zerstoert() const
{
	return punkte <= 0;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands) {
	move(geschwindigkeit * dt.asSeconds());
}