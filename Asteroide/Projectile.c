#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Projectile.h"
#include "ennemis.h"
#include "Player.h"
#include "math.h"
#define PI 3.14159265

Projectile projectileInit(sfSprite *sprite)
{
	Projectile projectile;
    projectile.position.x = 0;
    projectile.position.y = 0;
    projectile.vitesse = 6;
    projectile.dx = 0;
    projectile.dy = 0;
    projectile.sprite = sprite;
    projectile.isShoot = 0;
    projectile.ticks = 100;
	return projectile;
}


void updateP(Projectile* projectile, Player* joueur)
{
	projectile->vitesse = 6 + joueur->vitesse;
	if (projectile->isShoot == 1 && projectile->ticks != 200)
	{
		projectile->position.x = projectile->position.x + projectile->dx * projectile->vitesse;
		projectile->position.y = projectile->position.y + projectile->dy * projectile->vitesse;
		projectile->ticks = projectile->ticks + 1;
		if (projectile->position.y < 0)
		{
			projectile->position.y = 1080;
		}
		if (projectile->position.y > 1080)
		{
			projectile->position.y = 0;
		}
		if (projectile->position.x < -5)
		{
			projectile->position.x = 1920;
		}
		if (projectile->position.x > 1920)
		{
			projectile->position.x = -5;
		}
	}
	if (projectile->ticks == 100)
	{
		projectile->isShoot = 0;
	}
	if (projectile->isShoot == 0)
	{
		projectile->position.x = joueur->position.x;
		projectile->position.y = joueur->position.y;
	}
}

void shootInput(Projectile* projectile, Player* joueur)
{
	if (projectile->isShoot == 0)
	{
		if (sfKeyboard_isKeyPressed(sfKeySpace))
		{
			projectile->isShoot = 1;
			projectile->dx = cosf(joueur->rotation * PI / 180);
			projectile->dy = sinf(joueur->rotation * PI / 180);
			projectile->ticks = 0;
		}
	}
}


ProjectileE projectileEInit(sfSprite* sprite)
{
	ProjectileE projectile;
	projectile.position.x = 0;
	projectile.position.y = 0;
	projectile.vitesse = 2;
	projectile.dx = 0;
	projectile.dy = 0;
	projectile.sprite = sprite;
	projectile.isShoot = 0;
	projectile.ticks = 0;
	return projectile;
}


void updatePE(ProjectileE* projectile, Soucoupe* soucoupe, Player* joueur)
{
	float dist;
	projectile->vitesse = soucoupe->vitesse + 1;
	if (projectile->isShoot == 0)
	{
		projectile->position.x = soucoupe->position.x;
		projectile->position.y = soucoupe->position.y;
	}
	if (projectile->ticks > 10 && projectile->isShoot == 1)
	{
		projectile->position.x = projectile->position.x + projectile->dx * projectile->vitesse;
		projectile->position.y = projectile->position.y + projectile->dy * projectile->vitesse;
		projectile->ticks += -1;
	}
	if (projectile->ticks <= 10 && projectile->ticks != 0)
	{
		projectile->isShoot = 0;
		projectile->ticks += -1;
	}
	if (projectile->ticks == 0)
	{
		projectile->isShoot = 1;
		projectile->ticks = 100;
		dist = sqrt((joueur->position.x * joueur->position.x) + (joueur->position.y * joueur->position.y));
		projectile->dx = (joueur->position.x - soucoupe->position.x) / dist;
		projectile->dy = (joueur->position.y - soucoupe->position.y) / dist;
	}
}
