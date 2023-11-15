#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Player.h"
#include "stdio.h"
#include "stdlib.h"
#include "Asteroids.h"
#include "Projectile.h"
#include "Texte.h"
#include "ennemis.h"
#include "ref.h"
#include "Menu.h"

sfTexture* moyenC;

sfSprite* creerSprite(sfTexture* texture, float o)
{
    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfFalse);
    sfVector2f origin = { o, o };
    sfSprite_setOrigin(sprite, origin);
    return sprite;
}

Asteroid creerAsteroid(int taille, sfTexture* texture, int spriteT, sfVector2f position)
{

    Asteroid asteroid = initialisationAsteroids(taille);
    asteroid.sprite = creerSprite(texture, spriteT);
    sfSprite_setPosition(asteroid.sprite, asteroid.position);
    asteroid.position = position;
    return asteroid;
}


void divisionA(Asteroids* asteroids, Projectile* projectile, Player* joueur, int i)
{
    printf("aaaa");
    sfVector2f pos = asteroids->asteroid[i].position;
    if (asteroids->asteroid[i].taille == 1)
    {
        printf(" a ");
        asteroids->taille += -1;
    }
    else if (asteroids->asteroid[i].taille == 2)
    {
        asteroids->taille += 1;
        asteroids->asteroid[asteroids->taille - 2] = creerAsteroid(1, moyenC, 16, pos);
        asteroids->asteroid[asteroids->taille - 1] = creerAsteroid(1, moyenC, 16, pos);
        printf(" aa ");
    }
    if (i < asteroids->taille - 1)
    {
        asteroids->asteroid[i] = asteroids->asteroid[asteroids->taille - 1];
    }
}

void generateAsteroids(Asteroids* asteroids, sfSprite * grosC)
{
    for (int i = 0; i < asteroids->taille; i++)
    {
        asteroids->asteroid[i] = creerAsteroid(2, grosC, 32, (sfVector2f) { aleatoire(0, 1920), aleatoire(0, 1080) });
        if ((asteroids->asteroid[i].position.x < 650 && asteroids->asteroid[i].position.x > 450) && (asteroids->asteroid[i].position.y < 650 && asteroids->asteroid[i].position.y > 450))
        {
            asteroids->asteroid[i].position.x = aleatoire(0, 1920);
            asteroids->asteroid[i].position.y = aleatoire(0, 1080);
        }
    }
}

int main()
{
    char str[12];
    int score = 0;
    sfTexture* playerT = sfTexture_createFromFile("textures/Player.png", NULL);
    sfTexture* projectileT = sfTexture_createFromFile("textures/Projectile.png", NULL);
    sfTexture* projectileeT = sfTexture_createFromFile("textures/Projectilee.png", NULL);
    sfTexture* grosC = sfTexture_createFromFile("textures/grosCailloux.png", NULL);
    sfTexture* soucoupeT =  sfTexture_createFromFile("textures/Soucoupe.png", NULL);
    moyenC = sfTexture_createFromFile("textures/moyenCailloux.png", NULL);
    sfTexture* BossT = sfTexture_createFromFile("textures/Boss.png", NULL);

    sfWindow* w;
    sfVideoMode VideoMode = { 1920, 1080, 32 };
    w = sfRenderWindow_create(VideoMode, "Asteroids", sfClose, NULL);
    sfRenderWindow_setFramerateLimit(w, 60);
    sfEvent event;
    sfColor noir = sfColor_fromRGBA(0, 0, 0, 0);
    sfFont* font = sfFont_createFromFile("font/arial.ttf");
    sfText* scoreInt = printInt(score, font, 24, (sfVector2f) { 83, 0 }, w);
    sfText* scoreTexte = sfText_create();
    sfText_setFont(scoreTexte, font);
    sfText_setString(scoreTexte, "Score : ");
    sfText_setCharacterSize(scoreTexte, 24);
    sfText_setPosition(scoreTexte, (sfVector2f) { 0, 0 });
    sfText* gameOver = sfText_create();
    sfText_setFont(gameOver, font);
    sfText_setString(gameOver, "Game Over");
    sfText_setCharacterSize(gameOver, 100);
    sfText_setPosition(gameOver, (sfVector2f) { 650, 400 });

    Player joueur = initialisationJoueur(creerSprite(playerT, 12));
    Projectile projectile = projectileInit(creerSprite(projectileT, 4));
    ProjectileE projectilee = projectileEInit(creerSprite(projectileeT, 4));
    ProjectileB projectileb = projectileBInit(creerSprite(projectileeT, 4));
    Soucoupe soucoupe = initEnnemis(creerSprite(soucoupeT, 16));
    Asteroids asteroids;
    Boss boss = initBoss(creerSprite(BossT, 64));
    sfSprite_setScale(boss.sprite, (sfVector2f) { 0.08, 0.08 });
    asteroids.taille = 4;
    generateAsteroids(&asteroids, grosC);

    sfTexture* MenuT = sfTexture_createFromFile("textures/Menu.png", NULL);
    sfSprite* MenuS = sfSprite_create();
    sfSprite_setTexture(MenuS, MenuT, NULL);
    sfVector2i mousePos;
    int inMenu = 1; // 1 = dans les menu, 0 = pas dans les menu
    sfTexture* gameOverT = sfTexture_createFromFile("textures/GameOver.png", NULL);
    sfSprite* gameOverS = sfSprite_create();
    sfSprite_setTexture(gameOverS, gameOverT, NULL);
    
    while (sfRenderWindow_isOpen(w))
    {
        mousePos = sfMouse_getPosition(w);
        if (inMenu == 1)
        {
            sfRenderWindow_drawSprite(w, MenuS, NULL);
            exitGame(w, mousePos);
            if (start(w, mousePos) == 1)
                inMenu = 0;
            if (sfRenderWindow_pollEvent(w, &event))
            {
                if (event.type == sfEvtClosed)
                    sfRenderWindow_close(w);

            }
            sfRenderWindow_display(w);

        }

        else if (inMenu == 0)
        {
            sfRenderWindow_clear(w, noir);

            if (sfRenderWindow_pollEvent(w, &event))
            {
                if (event.type == sfEvtClosed)
                    sfRenderWindow_close(w);

            }
            inputs(&joueur);
            shootInput(&projectile, &joueur);
            warp(&joueur);
            update(&joueur);
            sfSprite_setPosition(joueur.sprite, joueur.position);
            sfSprite_setRotation(joueur.sprite, joueur.rotation);
            if (projectile.isShoot == 0)
            {
                sfSprite_setRotation(projectile.sprite, joueur.rotation);
            }


            for (int i = 0; i < asteroids.taille; i++)
            {
                sfSprite_setPosition(asteroids.asteroid[i].sprite, asteroids.asteroid[i].position);
                warpA(&asteroids.asteroid[i]);
                updateA(&asteroids.asteroid[i]);
                sfRenderWindow_drawSprite(w, asteroids.asteroid[i].sprite, NULL);
            }

            if (asteroids.taille == 0 && boss.isDead == 1)
            {
                asteroids.taille = 4;
                generateAsteroids(&asteroids, grosC);
            }

            for (int i = 0; i < asteroids.taille; i++)
            {
                if (colVA(&joueur, &asteroids.asteroid[i]) == 1 && boss.isDead == 1)
                {
                    joueur.isDead = 1;
                    sfText_setPosition(scoreTexte, (sfVector2f) { 800, 500 });
                    sfText_setPosition(scoreInt, (sfVector2f) { 975, 500 });
                    sfText_setCharacterSize(scoreTexte, 50);
                    sfText_setCharacterSize(scoreInt, 50);
                    joueur.position.x = 500;
                    joueur.position.y = 500;
                    joueur.vitesse = 0;
                    joueur.rotation = 0;
                    score = 0;
                    printf(" a ");
                }
                if ((colAP(&projectile, &asteroids.asteroid[i])) == 1 && projectile.isShoot == 1)
                {
                    projectile.isShoot = 0;
                    score += 100;
                    updateP(&projectile, &joueur);
                    divisionA(&asteroids, &projectile, &joueur, i);
                }
            }

            if (joueur.isDead == 0)
            {
                if (score == 1000 || score == 2000 || score == 3000 || score == 4000)
                {
                    soucoupe.isDead = 0;
                }
                if (score == 2500 || score == 5000)
                {
                    boss.isDead = 0;
                    asteroids.taille = -1;
                    asteroids.taille = 0;
                }
                if (soucoupe.isDead == 0 || boss.isDead == 0)
                {
                    updateEnnemis(&soucoupe, &boss);
                    warpE(&soucoupe, &boss);
                    if (soucoupe.isDead == 0)
                    {
                        sfSprite_setPosition(soucoupe.sprite, soucoupe.position);
                        sfRenderWindow_drawSprite(w, soucoupe.sprite, NULL);
                        updatePE(&projectilee, &soucoupe, &joueur);
                        sfSprite_setPosition(projectilee.sprite, projectilee.position);
                        sfRenderWindow_drawSprite(w, projectilee.sprite, NULL);
                    }
                    if (boss.isDead == 0)
                    {
                        sfSprite_setRotation(boss.sprite, boss.rotation + 90);
                        sfSprite_setPosition(boss.sprite, boss.position);
                        sfSprite_setPosition(projectileb.sprite, projectileb.position);
                        updatePB(&projectileb, &boss, &joueur);
                        sfRenderWindow_drawSprite(w, boss.sprite, NULL);
                        sfRenderWindow_drawSprite(w, projectileb.sprite, NULL);

                    }
                }
                sfRenderWindow_drawSprite(w, projectile.sprite, NULL);
                if (colPE(&projectile, &soucoupe) == 1 && joueur.isDead == 0)
                {
                    soucoupe.isDead = 1;
                    projectile.isShoot = 0;
                    score += 500;
                }
                if (colPB(&projectile, &boss) == 1 && joueur.isDead == 0)
                {
                    if (boss.health > 0)
                    {
                        boss.health += -1;
                    }
                    if(boss.health == 0)
                    {
                        boss.isDead = 1;
                        projectile.isShoot = 0;
                        score += 1000;
                        asteroids.taille = 4;
                        generateAsteroids(&asteroids, grosC);
                    }
                }
                if (colVP(&joueur, &projectilee) == 1 && soucoupe.isDead == 0)
                {
                    joueur.isDead = 1;
                    sfText_setPosition(scoreTexte, (sfVector2f) { 800, 500 });
                    sfText_setPosition(scoreInt, (sfVector2f) { 975, 500 });
                    sfText_setCharacterSize(scoreTexte, 50);
                    sfText_setCharacterSize(scoreInt, 50);
                    joueur.position.x = 500;
                    joueur.position.y = 500;
                    joueur.rotation = 0;
                    joueur.vitesse = 0;
                }
                updateP(&projectile, &joueur);
                sfSprite_setPosition(projectile.sprite, projectile.position);
                sfRenderWindow_drawSprite(w, joueur.sprite, NULL);
                snprintf(str, 12, "%d", score);
                sfText_setString(scoreInt, str);
            }
            else
            {
                sfRenderWindow_drawSprite(w, gameOverS, NULL);
                sfRenderWindow_drawText(w, gameOver, NULL);
                if (restart(w, mousePos) == 1)
                {
                    joueur.isDead = 0;
                    boss.isDead = 1;
                    soucoupe.isDead = 1;
                    sfText_setCharacterSize(scoreTexte, 24);
                    sfText_setPosition(scoreTexte, (sfVector2f) { 0, 0 });
                    sfText_setCharacterSize(scoreInt, 24);
                    sfText_setPosition(scoreInt, (sfVector2f) { 83, 0 });
                    asteroids.taille = 0;
                    asteroids.taille = 4;
                    generateAsteroids(&asteroids, grosC);
                }
                if (retourMenu(w, mousePos) == 1)
                {
                    inMenu = 1;
                    joueur.isDead = 0;
                    boss.isDead = 1;
                    soucoupe.isDead = 1;
                    sfText_setCharacterSize(scoreTexte, 24);
                    sfText_setPosition(scoreTexte, (sfVector2f) { 0, 0 });
                    sfText_setCharacterSize(scoreInt, 24);
                    sfText_setPosition(scoreInt, (sfVector2f) { 83, 0 });
                    asteroids.taille = 0;
                    asteroids.taille = 4;
                    generateAsteroids(&asteroids, grosC);
                }
            }

            sfRenderWindow_drawText(w, scoreTexte, NULL);
            sfRenderWindow_drawText(w, scoreInt, NULL);
            sfRenderWindow_display(w);
        }
    }



    // supprime tous les sprites / textures / autres
    sfText_destroy(gameOver);
    sfText_destroy(scoreInt);
    sfText_destroy(scoreTexte);
    sfSprite_destroy(MenuS);
    sfSprite_destroy(joueur.sprite);
    sfSprite_destroy(projectile.sprite);
    sfSprite_destroy(projectilee.sprite);
    sfTexture_destroy(MenuT);
    sfTexture_destroy(projectileT);
    sfTexture_destroy(projectileeT);
    sfTexture_destroy(playerT);
    sfTexture_destroy(grosC);
    sfTexture_destroy(moyenC);
    sfRenderWindow_destroy(w);
    for (int i = 0; i < asteroids.taille - 1; ++i)
    {
        sfSprite_destroy(asteroids.asteroid[i].sprite);
    }

    return 0;
}