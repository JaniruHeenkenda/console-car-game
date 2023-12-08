#include <stdio.h>
#include <stdlib.h>
#include "gameMove.h"
#include "gamePrint.h"
#include "terminal.h"

void move_cars(char **map, int map_row, int map_col, int *car_cols, int num_ofroads, int *car_direction) {
    int i;
    for (i = 1; i < map_row+1; i++) {
        if (i % 2 == 0) {
            car_cols[(i-2)/2] += car_direction[(i-2)/2];
            /*Reverse car direction if it reaches the edge*/
            if (car_cols[(i-2)/2] == 1 || car_cols[(i-2)/2] == map_col ) {
                car_direction[(i-2)/2] *= -1;
                
            }
            map[i][car_cols[(i-2)/2]] = (car_direction[(i-2)/2] == 1) ? '>' : '<';
        }
    }
}

void move(char ** map, int* player_row, int* player_col, int map_row, int map_col, int goal_row, int goal_col, int *car_cols, int num_ofroads, int *car_direction)
{
    int i;
    int new_player_row; 
    int new_player_col; 
    char input;
    
    disableBuffer();
    scanf(" %c", &input);
    enableBuffer();

    
   
    new_player_row = *player_row;
    new_player_col = *player_col;



    if (input == 'w') {
        new_player_row--;
        move_cars(map, map_row, map_col, car_cols, num_ofroads, car_direction);
    } else if (input == 's') {
        new_player_row++;
        move_cars(map, map_row, map_col, car_cols, num_ofroads, car_direction);
    } else if (input == 'a') {
        for (i = 0; i < map_row; i++) {
            if (i % 2 == 0 && new_player_row==i) {
                if (( new_player_col == car_cols[(i-2)/2]+1 && car_direction[(i-2)/2]==1) ) {
                map[i][car_cols[(i-2)/2]+1]=(car_direction[(i-2)/2] == 1) ? '>' : '<';
                map[i][new_player_col-1]='.';
                map[i][new_player_col+1]='.';
                printOver(map,map_row, map_col, car_cols, car_direction);
                exit(1);
                }
            }
        }
        new_player_col--;
        move_cars(map, map_row, map_col, car_cols, num_ofroads, car_direction);
    } else if (input == 'd') {
        for (i = 0; i < map_row; i++) {
            if (i % 2 == 0 && new_player_row==i) {
                if (( new_player_col == car_cols[(i-2)/2]-1 && car_direction[(i-2)/2]==-1) ) {
                map[i][car_cols[(i-2)/2]-1]=(car_direction[(i-2)/2] == 1) ? '>' : '<';
                map[i][new_player_col-1]='.';
                map[i][new_player_col+1]='.';
                printOver(map,map_row, map_col, car_cols, car_direction);
                exit(1);
                }
            }
        }
        new_player_col++;
        move_cars(map, map_row, map_col, car_cols, num_ofroads, car_direction);
    }
      else{
      	printf("Invalid Input!\n");
    }

    if (new_player_row > 0 && new_player_row < map_row+1 && new_player_col > 0 && new_player_col < map_col + 1) {
        /*Check if the new position coincides with a car*/
        for (i = 0; i < map_row; i++) {
            if (i % 2 == 0) {
                if ((new_player_row==i && new_player_col == car_cols[(i-2)/2]) ) {
                    map[i][car_cols[(i-2)/2]+1]=(car_direction[(i-2)/2] == 1) ? '>' : '<';
                    map[i][new_player_col-1]='.';
                    map[i][new_player_col+1]='.';
                    map[i+1][new_player_col]=' ';
                    map[i-1][new_player_col]=' ';
                    printOver(map,map_row, map_col, car_cols, car_direction);
                    exit(1);
                }

            }         
        }
    
        *player_row = new_player_row;
        *player_col = new_player_col;
    }
}   

