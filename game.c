#include <stdio.h>
#include <stdlib.h>
#include "gamePrint.h"
#include "random.h"

#define MAP_BORDER '*'
#define PLAYER 'P'
#define GOAL 'G'
#define ROAD '.'
#define CAR_LEFT '<'
#define CAR_RIGHT '>'
#define PATH ' '

int main(int argc, char* argv[]) {
    int i,j;
    int map_row, map_col, player_row, player_col , goal_row , goal_col , num_ofroads;
    char **map;
    int* car_cols;
    int* car_direction;
    

    map_row = atoi(argv[1]);
    map_col = atoi(argv[2]);

    if (map_col < 0 || map_row < 0) {
        printf("Enter positive numbers only \n");
        printf("usage : ./traffic <map_row> <map_col> \n");
        return 1;
    }

    if (map_row % 2 == 0 || map_row < 3 || map_col < 5) {
        printf("Invalid map size\n");
        printf("usage : ./traffic <map_row> <map_col> \n");
        return 1;
    }

  
    player_row = 1;
    player_col = 1;
    goal_row = map_row;
    goal_col = map_col;

    
    for ( i = 2; i <= map_row; i += 2) {
        num_ofroads++;
    }
    initRandom();

    map = (char **)malloc((map_row + 2) * sizeof(char*));
    for (i = 0; i < map_row + 2; i++) {
        map[i] = (char*)malloc((map_col + 2) * sizeof(char));
    }

    for ( i = 0; i < map_row + 2; i++) {
        for ( j = 0; j < map_col + 2; j++) {
            map[i][j] = ROAD;

            if (i == 0 || i == map_row + 1 || j == 0 || j == map_col + 1) {
                map[i][j] = MAP_BORDER;
            } else if (i == player_row && j == player_col) {
                map[i][j] = PLAYER;
            } else if (i == goal_row && j == goal_col) {
                map[i][j] = GOAL;
            } else if (i % 2 == 1) {
                map[i][j] = PATH;
            }
        }
    }

    car_cols = (int*)malloc(num_ofroads * sizeof(int));
    car_direction = (int*)malloc(num_ofroads * sizeof(int));
    for ( i = 1; i < map_row; i++) {
        if (i % 2 == 0) {
            car_cols[(i-2)/2] = randomUCP(2, map_col-1);
            car_direction[(i-2)/2] = randomUCP(0, 1);
            if (car_direction[(i-2)/2] == 0) {
                car_direction[(i-2)/2] = -1;
            }
            map[i][car_cols[(i-2)/2]] = (randomUCP(0, 1) == 1) ? CAR_RIGHT : CAR_LEFT;
            
        }
    }

    print(map, player_row, player_col, map_row, map_col, goal_row, goal_col, car_cols, num_ofroads, car_direction);

    free(car_cols);
    free(car_direction);
    for (i = 0; i < map_row + 2; i++) {
        free(map[i]);
    }
    free(map);

    return 0;
}

int endGame(){
    return 1;
}