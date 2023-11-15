#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

#ifndef Projectile_H
#define Projectile_H

typedef struct Projectile Projectile;
struct Projectile
{
    sfVector2f position;
    float vitesse;
    float dx;
    float dy;
    sfSprite* sprite;
    int isShoot;
    int ticks;
};

typedef struct ProjectileE ProjectileE;
struct ProjectileE
{
    sfVector2f position;
    float vitesse;
    float dx;
    float dy;
    sfSprite* sprite;
    int isShoot;
    int ticks;
};

#endif