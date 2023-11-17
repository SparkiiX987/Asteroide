#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Player.h"
#include "Projectile.h"
#include "Asteroids.h"
#include "ennemis.h"

// réferencie toutes les fonctions et procédure des fichier .c

#ifndef REF_H
#define REF_H

Projectile projectileInit(sfSprite* sprite);
void updateP(Projectile* projectile, Player* joueur);
void shootInput(Projectile* projectile, Player* joueur);
Asteroid initialisationAsteroids(int taille);
void updateA(Asteroid* asteroid);
void warpA(Asteroid* asteroid);
void inputs(Player* joueur, int diff);
Player initialisationJoueur(sfSprite* sprite);
void warp(Player* joueur);
void update(Player* joueur);
int colVA(Player* joueur, Asteroid* asteroid);
int colAP(Projectile* projectile, Asteroid* asteroid);
float aleatoire(int min, int max);
Soucoupe initEnnemis(sfSprite* sprite);
void warpE(Soucoupe* soucoupe, Boss* boss);
int colPE(Projectile* projectile, Soucoupe* soucoupe);
void updateEnnemis(Soucoupe* soucoupe, Boss* boss);
ProjectileE projectileEInit(sfSprite* sprite);
void updatePE(ProjectileE* projectile, Soucoupe* soucoupe, Player* joueur);
int colVP(Player* joueur, ProjectileE* projectile);
int colPB(Projectile* projectile, Boss* boss);
Boss initBoss(sfSprite* sprite);
ProjectileB projectileBInit(sfSprite* sprite);
void updatePB(ProjectileB* projectile, Boss* boss, Player* joueur);

#endif