/*
** EPITECH PROJECT, 2021
** test [WSL: Ubuntu]
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_
    #define layers 3
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <ncurses.h>
    #include <unistd.h>
    #include <assert.h>
    #include <string.h>
    #include <dirent.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <time.h>
    #include <pwd.h>
typedef struct maps_s {
    int **board;
    float time;
    float m;
    int h;
    int w;
} maps_t;
typedef	struct player_s {
    sfTexture **tx;
    sfSprite **sp;
    float jump;
    int px;
    int py;
    int m;
} player_t;
typedef struct game_s {
    sfRenderWindow *window;
    sfSprite **sp_ground;
    sfSprite **sp_back;
    sfTexture **ground;
    sfTexture **back;
    player_t *player;
    sfClock *clock;
    sfIntRect *rec;
    sfMusic *music;
    sfEvent event;
} game_t;

/* init_all.c */
void init_ground(game_t *games);
void init_player(game_t *games);
void init_wallpaper(game_t *games);
void init_music(game_t *games);
void load_wallpaper(const char *filename, game_t *games, int order);
/* help.c */
void help(int stat);
/* maps_render.c */
void tmp_map_render_2(game_t *games, maps_t *maps, int i, int j);
void tmp_map_render(game_t *games, maps_t *maps);
maps_t *create_map(char const *filename);
#endif /* !GAME_H_ */