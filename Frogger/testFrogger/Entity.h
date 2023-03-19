#pragma once

#include "SzenenElemente.h"

class Entity : public SceneNode
{
public:
	Entity(int hitPoints);
	void			GeschwindigkeitSetzen(sf::Vector2f v);
	void			GeschwindigkeitSetzen(float xv, float yv);

	void			beschleunigen(sf::Vector2f v);
	void			beschleunigen(float xv, float yv);

	sf::Vector2f	GeschwindigkeitGeben() const;

	int				PunkteBeiKontakt() const;
	void			reparieren(int points);
	void			schaden(int points);
	void			zestoeren();
	virtual bool	zerstoert() const;


protected:
	virtual void	aktuellesBild(sf::Time dt, CommandQueue& commands) override;

protected:
	sf::Vector2f	geschwindigkeit;
	int				punkte;

};

