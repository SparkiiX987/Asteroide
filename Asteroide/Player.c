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

// initialise le joueur
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

// deplace le joueur
void update(Player* joueur)
{
	joueur->position.x = joueur->position.x + joueur->dx * joueur->vitesse;
	joueur->position.y = joueur->position.y + joueur->dy * joueur->vitesse;
}
// gère les inputs du joueur ( pour tourner avancer et freinner
void inputs(Player* joueur, int diff)
{	
	if (joueur->isDead != 1)
	{
		// pour tourner
		if (sfKeyboard_isKeyPressed(sfKeyD))
		{
			if (diff == 1 || diff == 2)
				joueur->rotation += 5.5;
			if (diff == 3)
				joueur->rotation += -5.5;
		}

		if (sfKeyboard_isKeyPressed(sfKeyQ))
		{
			if (diff == 1 || diff == 2)
				joueur->rotation += -5.5;
			if (diff == 3)
				joueur->rotation += 5.5;

		}
		// pour avancer
		if (sfKeyboard_isKeyPressed(sfKeyZ))
		{
			if (diff == 1)
			{
				if (joueur->vitesse < 8)
				{
					joueur->vitesse += 0.5;
				}
			}
			if (diff == 2)
			{
				if (joueur->vitesse < 20)
				{
					joueur->vitesse += 0.5;
				}
			}
			if (diff == 3)
			{
				if (joueur->vitesse > 0)
				{
					joueur->vitesse += -0.3;
				}
			}
			joueur->dx = cosf(joueur->rotation * PI / 180);
			joueur->dy = sinf(joueur->rotation * PI / 180);

		}
		// poure freinner
		else if (sfKeyboard_isKeyPressed(sfKeyS))
		{
			if (joueur->vitesse > 0)
			{
				if (diff == 1 || diff == 2)
					joueur->vitesse += - 0.3;
			}
			if (diff == 3)
			{
				if (joueur->vitesse < 8)
				{
					joueur->vitesse += 0.5;
				}
				joueur->dx = cosf(joueur->rotation * PI / 180);
				joueur->dy = sinf(joueur->rotation * PI / 180);
			}
		}
		// ralentit le joueur si il n'avance pas
		else
		{
			joueur->vitesse = joueur->vitesse * 0.99;
		}
	}
}

// fait reaparaitre le joueur de l'autre coté de l'écran si il tente de sortir
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

// gère les collisions entre l'asteroide et le joueur
int colVA(Player* joueur, Asteroid* asteroid)
{
	int AsteroidR;
	int playerR = 16;
	// définit le rayon de l'asteroids en fonction de sa taille
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
// gère les collisions entre le projectile de l'enemis et le joueur
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