/*
** EPITECH PROJECT, 2021
** test [SSH: 192.168.177.128]
** File description:
** maps_render
*/

#include "game.h"
#include "my.h"
#include "my_printf.h"

void tmp_map_render_2(game_t *games, maps_t *maps, int i, int j)
{
    int pos[4][3] = {{i-1, j, 5}, {i, j-1, 1}, {i+1, j, 9}, {i, j+1, 7}};
    int texture = 0;

    if (maps->board[i][j] == 1) {
        for (int k = 0; k < 4; k++) {
            if ((0 <= pos[k][0] && pos[k][0] < maps->h) &&
                (0 <= pos[k][1] && pos[k][1] < maps->w) &&
                (maps->board[pos[k][0]][pos[k][1]] == 1)) {
                texture += pos[k][2];
            }
        }
        sfSprite_setPosition(games->sp_ground[texture], (sfVector2f){(j - maps->m) * 40, i * 40});
        sfRenderWindow_drawSprite(games->window, games->sp_ground[texture], NULL);
    }
}

void tmp_map_render(game_t *games, maps_t *maps)
{
    for (int i = 0; i < maps->h; i++)
        for (int j = maps->m; j < maps->w; j++)
            tmp_map_render_2(games, maps, i, j);
}

maps_t *create_map(char const *filename)
{
    maps_t *maps = malloc(sizeof(maps_t));
    char *line = malloc(21);
    char *back = line;
    FILE* file;

    if ((file = fopen(filename, "r")) == NULL) exit(84);
    fgets(line, 21, file);
    maps->h = my_strtol(line, &line);
    maps->w = my_strtol(line, &line);
    line = my_realloc(back ,maps->w + 3);
    maps->board = malloc(sizeof(int*) * (maps->h + 1));
    for (int j = 0; fgets(line, maps->w + 3, file) || j <= maps->h; j++) {
        maps->board[j] = malloc(sizeof(int) * maps->w);
        for (int i = 0; i < maps->w; i++)
            maps->board[j][i] = NUM(line[i]);
    }
    maps->m = 0;
    free(line);
    fclose(file);
    return maps;
}