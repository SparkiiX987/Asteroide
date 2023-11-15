#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

#ifndef ASTEROID_H
#define ASTEROID_H

  //////////////////////////////////////
 // structure qui gère les asteroids //
//////////////////////////////////////

typedef struct Asteroid Asteroid;
struct Asteroid
{
    sfVector2f position;
    float vitesse;
    float rotation;
    float dx;
    float dy;
    int taille; // 1 petit, 2 grand
    sfSprite* sprite;
};

typedef struct Asteroids Asteroids;
struct Asteroids
{
    Asteroid asteroid[50]; // nombre d'asteroids max
    int taille;
};

#endif