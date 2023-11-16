#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

#ifndef Projectile_H
#define Projectile_H

// structure pour le procjectile du joueur
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
// structure pour le procjectile de la soucoupe
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
// structure pour le procjectile du boss
typedef struct ProjectileB ProjectileB;
struct ProjectileB
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