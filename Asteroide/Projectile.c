#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Projectile.h"
#include "ennemis.h"
#include "Player.h"
#include "math.h"
#define PI 3.14159265

// initialise le projectile du joueur
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

// met a jour la position du projectile du joueur
void updateP(Projectile* projectile, Player* joueur)
{
	// calque la vitesse du projectile en fonction du joueur
	projectile->vitesse = 12 + joueur->vitesse;
	if (projectile->isShoot == 1)
	{
		projectile->position.x = projectile->position.x + projectile->dx * projectile->vitesse;
		projectile->position.y = projectile->position.y + projectile->dy * projectile->vitesse;
		projectile->ticks = projectile->ticks + 1;
		// pour que le projecile ne sorte pas de l'écran mais soit tp de l'autre coté si il touche un bord de l'écran
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
	// intervale de tire
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

// verifie si on appuis sur espace pour tirer le projectile
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

// initialise le projectile de la soucoupe
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

// met a jour la position du projectile de la soucoupe et le tire a intervale regulier sur le joueur
void updatePE(ProjectileE* projectile, Soucoupe* soucoupe, Player* joueur)
{
	if (soucoupe->isDead == 0)
	{
		float dist; // varriable utiliser pour calculer la distance entre la soucoupe et le joueur
		projectile->vitesse = soucoupe->vitesse + 1;
		// tire le projectile si le projectile
		if (projectile->isShoot == 0 && projectile->ticks == 0)
		{
			projectile->position.x = soucoupe->position.x;
			projectile->position.y = soucoupe->position.y;
		}
		// détruit le projectile un certain temps apres avoir ete tirer
		if (projectile->ticks > 10 && projectile->isShoot == 1)
		{
			projectile->position.x = projectile->position.x + projectile->dx * projectile->vitesse;
			projectile->position.y = projectile->position.y + projectile->dy * projectile->vitesse;
			projectile->ticks += -1;
		}
		// apres un certain temps d'attente le projectile de l'ennemis peut etre retirer
		if (projectile->ticks <= 10 && projectile->ticks != 0)
		{
			projectile->isShoot = 0;
			projectile->ticks += -1;
		}
		// si le projectile peut etre tirer la soucoupe vise le joueur sur sa position
		if (projectile->ticks == 0)
		{
			projectile->isShoot = 1;
			projectile->ticks = 100;
			dist = sqrt((joueur->position.x * joueur->position.x) + (joueur->position.y * joueur->position.y));
			projectile->dx = (joueur->position.x - soucoupe->position.x) / dist;
			projectile->dy = (joueur->position.y - soucoupe->position.y) / dist;
		}
	}
}

// initialise le projectile du boss
ProjectileB projectileBInit(sfSprite* sprite)
{
	ProjectileB projectile;
	projectile.position.x = 0;
	projectile.position.y = 0;
	projectile.vitesse = 3;
	projectile.dx = 0;
	projectile.dy = 0;
	projectile.sprite = sprite;
	projectile.isShoot = 0;
	projectile.ticks = 0;
	return projectile;
}

// met a jour la position du projectile du boss et le tire a intervale regulier sur le joueur de la meme manière que pour le projectile de la soucoupe 
void updatePB(ProjectileB* projectile, Boss* boss, Player* joueur)
{
	projectile->vitesse = boss->vitesse + 12;
	if (boss->isDead == 0)
	{
		float dist;
		projectile->vitesse = boss->vitesse + 5;
		if (projectile->isShoot == 0)
		{
			projectile->position.x = boss->position.x;
			projectile->position.y = boss->position.y;
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
			projectile->dx = (joueur->position.x - boss->position.x) / dist;
			projectile->dy = (joueur->position.y - boss->position.y) / dist;
		}
	}
}
