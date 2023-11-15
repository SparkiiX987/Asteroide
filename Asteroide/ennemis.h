#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

#ifndef ENNEMIS_H
#define ENNEMIS_H

typedef struct Soucoupe Soucoupe;
struct Soucoupe
{
    sfVector2f position;
    float vitesse;
    float dx;
    float dy;
    sfSprite* sprite;
    int hasShoot;
    int isDead;
    int ticks;
    int tickm;
};

typedef struct Boss Boss;
struct Boss
{
    sfVector2f position;
    float vitesse;
    float dx;
    float dy;
    float rotation;
    sfSprite* sprite;
    int hasShoot;
    int isDead;
    int ticks;
    int tickm;
    int health;
};

#endif