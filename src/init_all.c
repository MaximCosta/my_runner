/*
** EPITECH PROJECT, 2021
** test [SSH: 192.168.177.128]
** File description:
** init_all
*/

#include "game.h"
#include "my.h"
#include "my_printf.h"

void init_ground(game_t *games)
{
    int g[17] = {0, 1, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 21, 22, -1};
    char path[60] = {0};
    char buf[3] = {0};

    games->sp_ground = malloc(sizeof(sfSprite*) * 22);
    games->ground = malloc(sizeof(sfTexture*) * 22);
    for (int k = 0; g[k] != -1; k++) {
        for (int i = 0; i <= 60; path[i++] = 0);
        games->sp_ground[g[k]] = sfSprite_create();
        my_strcat(path, "./assets/images/connect-ground/ground-1-");
        my_itoa(g[k], buf, 10);
        my_strcat(path, buf);
        my_strcat(path, ".png");
        games->ground[g[k]] = sfTexture_createFromFile(path, NULL);
        sfSprite_setTexture(games->sp_ground[g[k]], games->ground[g[k]], sfTrue);
    }
}

void init_player(game_t *games)
{
    char path[60] = {1};
    char buf[3] = {0};
    int nb = 1;

    games->player = malloc(sizeof(player_t));
    games->player->tx = malloc(sizeof(sfTexture*) * nb);
    games->player->sp = malloc(sizeof(sfSprite*) * nb);
    games->player->jump = 0;
    games->player->px = 0;
    games->player->py = 0;
    games->player->m = 0;
    for (int i = 0; i < nb; i++) {
        for (int j = 0; j <= 60; path[j++] = 0);
        games->player->sp[i] = sfSprite_create();
        my_strcat(path, "./assets/images/players/player-");
        my_itoa(i, buf, 10);
        my_strcat(path, buf);
        my_strcat(path, ".png");
        games->player->tx[i] = sfTexture_createFromFile(path, NULL);
        sfSprite_setTexture(games->player->sp[i], games->player->tx[i], sfTrue);
        sfSprite_setOrigin(games->player->sp[i], (sfVector2f){17.5, 17.5});
        sfSprite_setPosition(games->player->sp[i], (sfVector2f){50, 50});
    }
}

void load_wallpaper(const char *filename, game_t *games, int order)
{
    int index;

    for (int i = 0; i < 2; i++) {
        index = (2 * order) + i;
        games->sp_back[index] = sfSprite_create();
        games->back[index] = sfTexture_createFromFile(filename, NULL);
        sfSprite_setTexture(games->sp_back[index], games->back[index], sfTrue);
        if (index % 2 == 0)
            sfSprite_setPosition(games->sp_back[index], (sfVector2f){1920, 0});
    }
}

void init_wallpaper(game_t *games)
{
    games->sp_back = malloc(sizeof(sfSprite*) * (2 * layers));
    games->back = malloc(sizeof(sfTexture*) * (2 * layers));
    load_wallpaper("./assets/images/back-1.png", games, 0);
    load_wallpaper("./assets/images/back-2.png", games, 1);
    load_wallpaper("./assets/images/back-3.png", games, 2);

}

void init_music(game_t *games)
{
    games->music = sfMusic_createFromFile("./assets/music/play_loop.ogg");
    sfMusic_setLoop(games->music, true);
    //sfMusic_play(games->music);
}