#include <stdio.h>
#include <stdlib.h>
#include "gamePrint.h"
#include "gameMove.h"
#include "terminal.h"

void print(char ** map, int player_row, int player_col, int map_row, int map_col, int goal_row, int goal_col, int* car_cols, int num_ofroads, int* car_direction)
{
    #define MAP_BORDER '*'
    #define PLAYER 'P'
    #define GOAL 'G'
    #define ROAD '.'
    #define CAR_LEFT '<'
    #define CAR_RIGHT '>'
    #define PATH ' '
    
    int i, j,k; 

    while ((player_row != goal_row) || (player_col != goal_col)) {
        system("clear");
        for ( i = 0; i < map_row + 2; i++) {
            for ( j = 0; j < map_col + 2; j++) {
                map[i][j] = ROAD;
                
                if (i == 0 || i == map_row + 1 || j == 0 || j == map_col + 1) {
                    map[i][j] = MAP_BORDER;
                }
                else if (i == player_row && j == player_col) {
                    map[i][j] = PLAYER;
                }
                else if (i == map_row  && j == map_col) {
                    map[i][j] = GOAL ;
                }
                else if (i % 2 == 1) {
                    map[i][j] = PATH;
                }
                for ( k = 1; k < map_row; k++) {
        		if (k % 2 == 0) {
            			
            			map[k][car_cols[(k-2)/2]] = (car_direction[(k-2)/2] == 1) ? CAR_RIGHT : CAR_LEFT;
        		}
    		}
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
        
        for (i = 1; i < map_row; i++) {
            if (i % 2 == 0) {
                map[i][car_cols[(i-2)/2]] = (car_direction[(i-2)/2] == 1) ? CAR_RIGHT : CAR_LEFT;
            }
        }
        
        printf("Move the player to the goal to win the game!\n");
        printf("Press w to move up\n");
        printf("Press s to move down\n");
        printf("Press a to move left\n");
        printf("Press d to move right\n");
        move(map, &player_row, &player_col, map_row, map_col, goal_row, goal_col, car_cols, num_ofroads, car_direction);
    }
    
    system("clear");
    
    for (i = 0; i < map_row + 2; i++) {
        for (j = 0; j < map_col + 2; j++) {
            if (i == goal_row && j == goal_col) {
                map[i][j] = PLAYER;
            }
            else if(i == goal_row-1 && j == goal_col ){
                map[i][j] = ROAD;
            }
            else if(i==goal_row && j==goal_col-1){
                map[i][j] = PATH;
            }
            for ( k = 1; k < map_row; k++) {
        		if (k % 2 == 0) {
                    if(car_direction[(k-2)/2]==1){
                        map[k][car_cols[(k-2)/2]-1] = ROAD;
                    }
                    else{
                        map[k][car_cols[(k-2)/2]+1] =PATH;
                    }
        		}
            }
        }
     
    }
    for (i = 0; i < map_row + 2; i++) {
        for (j = 0; j < map_col + 2; j++) {
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
    
    printf("Move the player to the goal to win the game!\n");
    printf("Press w to move up\n");
    printf("Press s to move down\n");
    printf("Press a to move left\n");
    printf("Press d to move right\n");
    printf("You Won!!!\n");
}

void printOver(char ** map,int map_row, int map_col, int* car_cols, int* car_direction){
    int i,j,k;
    system("clear");
    for (i = 0; i < map_row + 2; i++) {
        for (j = 0; j < map_col + 2; j++) {
                for ( k = 1; k < map_row; k++) {
        		    if (k % 2 == 0) {
                        map[k][car_cols[(k-2)/2]+1] = ROAD;
                        map[k][car_cols[(k-2)/2]-1] = ROAD;

                        if(car_direction[(k-2)/2]==1){
                            if(car_cols[(k-2)/2] == 1 || car_cols[(k-2)/2] == map_col || car_cols[(k-2)/2] == 1 || car_cols[(k-2)/2] == map_col){
                                map[k][car_cols[(k-2)/2]-1] = MAP_BORDER;
                            }
                        }
                        else if (car_direction[(k-2)/2]==-1){
                            if(car_cols[(k-2)/2] == 1 || car_cols[(k-2)/2] == map_col || car_cols[(k-2)/2] == 1 || car_cols[(k-2)/2] == map_col){
                                map[k][car_cols[(k-2)/2]+1] = MAP_BORDER;
                            }
                        }
        		    }   
                }
            printf("%c",map[i][j]);

        }
        printf("\n");
    }
    
    printf("YOU HIT A CAR!\nGAME OVER \nTo restart: ./traffic <number of rows> <number of columns>");

    free(car_cols);
    free(car_direction);
    for (i = 0; i < map_row + 2; i++) {
        free(map[i]);
    }
    free(map);

}
