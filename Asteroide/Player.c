#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Player.h"
#include "Asteroids.h"
#include "Projectile.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#define PI 3.14159265


Player initialisationJoueur(sfSprite *sprite)
{
	Player joueur;
	joueur.position.x = 500;
	joueur.position.y = 500;
	joueur.vitesse = 0;
	joueur.rotation = 0;
	joueur.isDead = 0;
	joueur.dx = cosf(joueur.rotation * PI / 180);
	joueur.dy = sinf(joueur.rotation * PI / 180);
	joueur.sprite = sprite;
	return joueur;
}

void update(Player* joueur)
{
	joueur->position.x = joueur->position.x + joueur->dx * joueur->vitesse;
	joueur->position.y = joueur->position.y + joueur->dy * joueur->vitesse;
}

void inputs(Player* joueur)
{	
	if (joueur->isDead != 1)
	{
		if (sfKeyboard_isKeyPressed(sfKeyD))
		{
			joueur->rotation += 5.5;
		}

		if (sfKeyboard_isKeyPressed(sfKeyQ))
		{
			joueur->rotation += -5.5;

		}

		if (sfKeyboard_isKeyPressed(sfKeyZ))
		{
			if (joueur->vitesse < 8)
			{
				joueur->vitesse += 1;
			}
			joueur->dx = cosf(joueur->rotation * PI / 180);
			joueur->dy = sinf(joueur->rotation * PI / 180);

		}
		else
		{
			joueur->vitesse = joueur->vitesse * 0.99;
		}
	}
}

void warp(Player* joueur)
{
	if (joueur->position.y < -5)
	{
		joueur->position.y = 1085;
	}
	if (joueur->position.y > 1085)
	{
		joueur->position.y = -5;
	}
	if (joueur->position.x < -5)
	{
		joueur->position.x = 1925;
	}
	if (joueur->position.x > 1925)
	{
		joueur->position.x = -5;
	}
}

int colVA(Player* joueur, Asteroid* asteroid)
{
	int AsteroidR;
	int playerR = 16;
	if (asteroid->taille == 2)
	{
		AsteroidR = 64;
	}
	else if (asteroid->taille == 1)
	{
		AsteroidR = 32;
	}
	else
	{
		AsteroidR = 0;
	}
	int PX = joueur->position.x + playerR;
	int PY = joueur->position.y + playerR;
	int AX = asteroid->position.x + AsteroidR;
	int AY = asteroid->position.y + AsteroidR;

	int distance = (PX - AX) * (PX - AX) + (PY - AY) * (PY - AY);
	if (distance < (playerR + AsteroidR) * (playerR + AsteroidR)) 
	{ 
		return 1;
	}
			
	return 0;
}

int colVP(Player* joueur, ProjectileE* projectile)
{
	int ProjectileR = 8;
	int playerR = 16;
	int PX = joueur->position.x + playerR;
	int PY = joueur->position.y + playerR;
	int AX = projectile->position.x + ProjectileR;
	int AY = projectile->position.y + ProjectileR;

	int distance = (PX - AX) * (PX - AX) + (PY - AY) * (PY - AY);
	if (distance < (playerR + ProjectileR) * (playerR + ProjectileR))
	{
		return 1;
	}

	return 0;
}