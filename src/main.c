/*
** EPITECH PROJECT, 2021
** test [WSL: Ubuntu]
** File description:
** main
*/

#include "game.h"
#include "my.h"
#include "my_printf.h"
#include <math.h>
/*
48 / 27
  5
1 0 7
  9
*/

void player_render(game_t* games)
{
    //sfSprite_setPosition(games->player->sp[games->player->m], (sfVector2f){50, 50});
    sfRenderWindow_drawSprite(games->window, games->player->sp[games->player->m], NULL);
}

void player_gravity(game_t *games, maps_t *maps)
{
    sfVector2f pos = sfSprite_getPosition(games->player->sp[games->player->m]);
    int y = (int)(pos.y - 17.5) / 40;
    int x = (int)(pos.x - 17.5) / 40 + (int)maps->time;
    float my = 0;

    if (maps->board[y + 1][x + 1] == 0) my = 5;
    if (games->player->jump != 0) {
        my = 5 * -(games->player->jump--);
    }
    sfSprite_move(games->player->sp[games->player->m], (sfVector2f){maps->time - maps->m, my});
    printf("(%d, %d) -> %d\n", y, x, maps->board[y][x]);
    //sfSprite_rotate(games->player->sp[games->player->m], 10);
}

void init_all(game_t *games)
{
    sfVideoMode mode = {1920, 1080, 32};

    games->window = sfRenderWindow_create(mode, "runner", sfFullscreen | sfClose, NULL);
    games->clock = sfClock_create();
    init_music(games);
    init_wallpaper(games);
    init_ground(games);
    init_player(games);
    sfRenderWindow_setFramerateLimit(games->window, 60);
}

void get_move(game_t *games)
{
    float speed = .25;

    for (int i = 0; i < (2 * layers); i++) {
        if (i % 2 == 0) speed *= 2;
        sfSprite_move(games->sp_back[i], (sfVector2f){-speed, 0});
    }
}

void get_destroy(game_t *games)
{
    sfMusic_destroy(games->music);
    for (int i = 0; i < 2; i++) {
        sfSprite_destroy(games->sp_back[i]);
        sfTexture_destroy(games->back[i]);
    }
    free(games->sp_back);
    free(games->back);
    sfRenderWindow_destroy(games->window);
    free(games);
}

void reset_pos_back(game_t *games)
{
    for (int i = 0; i < (2 * layers); i++) {
        if (sfSprite_getPosition(games->sp_back[i]).x <= -1920)
            sfSprite_setPosition(games->sp_back[i], (sfVector2f){1920, 0});
    }
}

void draw_sprites(game_t *games)
{
    for (int i = 0; i < (2 * layers); i++)
        sfRenderWindow_drawSprite(games->window, games->sp_back[i], NULL);
}

void player_jump(game_t *games, maps_t *maps)
{
    sfVector2f pos = sfSprite_getPosition(games->player->sp[games->player->m]);
    int y = (int)(pos.y - 17.5) / 40;
    int x = (int)(pos.x - 17.5) / 40 + (int)maps->time;

    if (games->player->jump == 0 && maps->board[y + 1][x + 1] != 0)
        games->player->jump = 10;
}

void game_event(game_t *games, maps_t *maps)
{
    while (sfRenderWindow_pollEvent(games->window, &games->event)) {
        if (games->event.type == sfEvtClosed)
            sfRenderWindow_close(games->window);
        if (games->event.type == sfEvtKeyPressed &&
            games->event.key.code == sfKeyEscape)
            sfRenderWindow_close(games->window);
        if (games->event.type == sfEvtKeyPressed &&
            games->event.key.code == sfKeySpace)
            player_jump(games, maps);
    }
}

int main(int argc, char *argv[])
{
    game_t *games = malloc(sizeof(game_t));
    maps_t *maps;

    if (argc == 1) help(0);
    if (my_strcmp(argv[1], "-h") == 0) help(1);
    maps = create_map(argv[1]);
    init_all(games);
    while (sfRenderWindow_isOpen(games->window)) {
        maps->time = sfTime_asSeconds(sfClock_getElapsedTime(games->clock));
        maps->m = maps->w - maps->time < 48 ? maps->w - 48 : maps->time;
        game_event(games, maps);
        sfRenderWindow_clear(games->window, sfRed);
        reset_pos_back(games);
        get_move(games);
        draw_sprites(games);
        tmp_map_render(games, maps);
        player_gravity(games, maps);
        player_render(games);
        sfRenderWindow_display(games->window);
    }
    for (int i = 0; i < maps->h; free(maps->board[i++]));
    free(maps);
    get_destroy(games);
    return 0;
}