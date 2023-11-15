#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>
#include "ennemis.h"
#include "Projectile.h"
#include "Asteroids.h"
#include "math.h"
#define PI 3.14159265


Soucoupe initEnnemis(sfSprite* sprite)
{
    Soucoupe soucoupe;
    soucoupe.position = (sfVector2f){0, 0};
    soucoupe.vitesse = 6;
    soucoupe.dx = cosf(aleatoire(0, 360) * PI / 180);
    soucoupe.dy = sinf(aleatoire(0, 360) * PI / 180);
    soucoupe.sprite = sprite;
    soucoupe.hasShoot = 0;
    soucoupe.isDead = 1;
    soucoupe.ticks = 300;
	soucoupe.tickm = 150;
    return soucoupe;
}

Boss initBoss(sfSprite* sprite)
{
	Boss boss;
	boss.position = (sfVector2f){ 0, 0 };
	boss.vitesse = 9;
	boss.rotation = aleatoire(0, 360);
	boss.dx = cosf(boss.rotation * PI / 180);
	boss.dy = sinf(boss.rotation * PI / 180);
	boss.sprite = sprite;
	boss.hasShoot = 0;
	boss.isDead = 1;
	boss.ticks = 300;
	boss.tickm = 150;
	boss.health = 5;
	return boss;
}

void warpE(Soucoupe* soucoupe, Boss* boss)
{
	if (soucoupe->isDead == 0)
	{
		if (soucoupe->position.y < -5)
		{
			soucoupe->position.y = 1080;
		}
		if (soucoupe->position.y > 1080)
		{
			soucoupe->position.y = -5;
		}
		if (soucoupe->position.x < -5)
		{
			soucoupe->position.x = 1920;
		}
		if (soucoupe->position.x > 1920)
		{
			soucoupe->position.x = -5;
		}
	}
	if (boss->isDead == 0)
	{
		if (boss->position.y < -5)
		{
			boss->position.y = 1080;
		}
		if (boss->position.y > 1080)
		{
			boss->position.y = -5;
		}
		if (boss->position.x < -5)
		{
			boss->position.x = 1920;
		}
		if (boss->position.x > 1920)
		{
			boss->position.x = -5;
		}
	}
	
}

int colPE(Projectile* projectile, Soucoupe* soucoupe)
{
	int SoucoupeR = 15;
	int Projectile = 4;
	int PX = projectile->position.x + Projectile;
	int PY = projectile->position.y + Projectile;
	int SX = soucoupe->position.x + SoucoupeR;
	int SY = soucoupe->position.y + SoucoupeR;

	int distance = (PX - SX) * (PX - SX) + (PY - SY) * (PY - SY);
	if (distance < (Projectile + SoucoupeR) * (Projectile + SoucoupeR) && projectile->isShoot == 1)
	{
		return 1;
	}

	return 0;
}

int colPB(Projectile* projectile, Boss* boss)
{
	int BossR = 32;
	int Projectile = 4;
	int PX = projectile->position.x + Projectile;
	int PY = projectile->position.y + Projectile;
	int SX = boss->position.x + BossR;
	int SY = boss->position.y + BossR;

	int distance = (PX - SX) * (PX - SX) + (PY - SY) * (PY - SY);
	if (distance < (Projectile + BossR) * (Projectile + BossR) && projectile->isShoot == 1)
	{
		return 1;
	}

	return 0;
}

void updateEnnemis(Soucoupe* soucoupe, Boss* boss)
{
	if (soucoupe->isDead == 0)
	{
		soucoupe->position.x = soucoupe->position.x + soucoupe->dx * soucoupe->vitesse;
		soucoupe->position.y = soucoupe->position.y + soucoupe->dy * soucoupe->vitesse;
		if (soucoupe->tickm == 0)
		{
			soucoupe->dx = cosf(aleatoire(0, 360) * PI / 180);
			soucoupe->dy = sinf(aleatoire(0, 360) * PI / 180);
			soucoupe->tickm = 150;
		}
		else
		{
			soucoupe->tickm += -1;
		}
	}
	if (boss->isDead == 0)
	{
		boss->position.x = boss->position.x + boss->dx * boss->vitesse;
		boss->position.y = boss->position.y + boss->dy * boss->vitesse;
		if (boss->tickm == 0)
		{
			boss->rotation = aleatoire(0, 360);
			boss->dx = cosf(boss->rotation * PI / 180);
			boss->dy = sinf(boss->rotation * PI / 180);
			boss->tickm = 150;
		}
		else
		{
			boss->tickm += -1;
		}
	}
}
