#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

#ifndef TEXTES_H
#define TEXTES_H
// réferencie la fonction pour créer un texte
sfText* printInt(int number, sfFont* font, int size, sfVector2f position);

#endif