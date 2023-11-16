#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>

// fonction pour créer un un texte a partir d'un int
sfText* printInt(int number, sfFont* font, int size, sfVector2f position)
{
    sfText* integer = sfText_create();// créer un text
    char str[12];
    snprintf(str, 12, "%d", number);// convertie l'int en str

    sfText_setString(integer, str);//transforme la chaine de characters en text
    sfText_setFont(integer, font);
    sfText_setCharacterSize(integer, size);
    sfText_setPosition(integer, position);
    return integer;
}
