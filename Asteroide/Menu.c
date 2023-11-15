#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "stdio.h"

int start(sfWindow* w, sfVector2i mousePos)
{
	if ((mousePos.x > 675 && mousePos.x < 1271) && (mousePos.y > 254 && mousePos.y < 408) && sfMouse_isButtonPressed(sfMouseLeft))
	{
		return 1;
	}
	return 0;
}
void exitGame(sfWindow* w, sfVector2i mousePos)
{
	if ((mousePos.x > 706 && mousePos.x < 1247) && (mousePos.y > 683 && mousePos.y < 856) && sfMouse_isButtonPressed(sfMouseLeft))
	{
		sfRenderWindow_close(w);
	}
}

int restart(sfWindow* w, sfVector2i mousePos)
{
	if ((mousePos.x > 230 && mousePos.x < 772) && (mousePos.y > 672 && mousePos.y < 980) && sfMouse_isButtonPressed(sfMouseLeft))
	{
		return 1;
	}
	return 0;
}

int retourMenu(sfWindow* w, sfVector2i mousePos)
{
	if ((mousePos.x > 1226 && mousePos.x < 1756) && (mousePos.y > 662 && mousePos.y < 963) && sfMouse_isButtonPressed(sfMouseLeft))
	{
		return 1;
	}
	return 0;
}