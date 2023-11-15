#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>*
#include "Asteroids.h"

#ifndef PLAYER_H
#define PLAYER_H

  //////////////////////////////////
 // structure qui gère le joueur //
//////////////////////////////////

typedef struct Player Player;
struct Player
{
    sfVector2f position;
    float vitesse;
    float rotation;
    int isDead;
    float dx;
    float dy;
    sfSprite* sprite;
};

#endif