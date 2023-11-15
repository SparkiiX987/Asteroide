#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

#ifndef MENU_H
#define MENU_H

int start(sfWindow* w, sfVector2i mousePos);
void exitGame(sfWindow* w, sfVector2i mousePos);
int restart(sfWindow* w, sfVector2i mousePos);
int retourMenu(sfWindow* w, sfVector2i mousePos);

#endif
