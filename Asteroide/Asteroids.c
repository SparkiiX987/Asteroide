#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Asteroids.h"
#include "Projectile.h" 
#include "stdio.h"
#include "math.h"
#include "Player.h"
#include "stdlib.h"
#define PI 3.14159265


  //////////////////////////////////////////////
 // fonction qui créé une rotation aléatoire //
//////////////////////////////////////////////
float aleatoire(int min, int max)
{
	return (float)(rand() % (max + 1 - min)) + min;
}

Asteroid initialisationAsteroids(int taille)
{
	Asteroid asteroid;
	asteroid.rotation = aleatoire(0, 360);
	asteroid.dx = cosf(asteroid.rotation * PI / 180);
	asteroid.dy = sinf(asteroid.rotation * PI / 180);
	asteroid.taille = taille;
	if (taille == 2)
	{
		asteroid.vitesse = 3.5f;
	}
	else if (taille == 1)
	{
		asteroid.vitesse = 5;
	}
	return asteroid;
}

void updateA(Asteroid* asteroid)
{
	asteroid->position.x = asteroid->position.x + asteroid->dx * asteroid->vitesse;
	asteroid->position.y = asteroid->position.y + asteroid->dy * asteroid->vitesse;
}

void warpA(Asteroid* asteroid)
{
	if (asteroid->position.y < -5)
	{
		asteroid->position.y = 1080;
	}
	if (asteroid->position.y > 1080)
	{
		asteroid->position.y = -5;
	}
	if (asteroid->position.x < -5)
	{
		asteroid->position.x = 1920;
	}
	if (asteroid->position.x > 1920)
	{
		asteroid->position.x = -5;
	}
}


int colAP(Projectile* projectile, Asteroid* asteroid)
{
	int AsteroidR;
	int Projectile = 4;
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
	int PX = projectile->position.x + Projectile;
	int PY = projectile->position.y + Projectile;
	int AX = asteroid->position.x + AsteroidR;
	int AY = asteroid->position.y + AsteroidR;

	int distance = (PX - AX) * (PX - AX) + (PY - AY) * (PY - AY);
	if (distance < (Projectile + AsteroidR) * (Projectile + AsteroidR))
	{
		return 1;
	}

	return 0;


	free(Projectile);
	free(AsteroidR);
}
