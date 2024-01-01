#include "names.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
/*This is the definition section!
 * main(void)-the main implementation of the program
 * roll_the_pig(void)-this function is used to create a roll from 0 to 6 to indicate which position that the user rolled.
 * points_checker(int positions)-this function is used to get the amount of points the user earns based on what position the user rolled.  */
int roll_the_pig(void) {
    int roll = random() % 7;
    return roll;
}

int points_checker(int positions) {
    if (positions == 0) {
        return 0;
    } else if (positions == 1) {
        return 10;
    } else if (positions == 2) {
        return 10;
    } else if (positions == 3) {
        return 15;
    } else if (positions == 4) {
        return 5;
    }
    return 0;
}
int main(void) {
    int num_players = 2;
    printf("Number of players (2 to 10)? ");
    int scanf_result = scanf("%d", &num_players);
    if (scanf_result < 1 || num_players < 2 || num_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        num_players = 2;
    }
    unsigned seed = 2023;
    printf("Random-number seed? ");
    int num_assignments = scanf("%u", &seed);
    if (num_assignments < 1) {
        fprintf(stderr, "Invalid seed. Using 2023 instead.\n");
        seed = 2023;
    }
    typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
    const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };
    int players_score_board[MAX_PLAYERS];
    int counter = 0;
    while (counter < num_players) {
        players_score_board[counter] = 0;
        counter++;
    }
    int player = 0;
    int winner = 0;
    int roll = 0;
    srandom(seed);
    /*The first loop is in charge of going to each player continously until one reaches 100*/
    while (true) {
        printf("%s\n", player_name[player]);
        /*Inside loop is in charge of rolling the pig until they win or get a side*/
        while (true) {
            roll = roll_the_pig();
            /*printf("roll=%d\n",roll);*/
            int positions = pig[roll];
            /*printf("position=%d\n",positions);*/
            int rolls = points_checker(positions);
            /*printf("points=%d\n",rolls);*/
            players_score_board[player] += rolls;
            printf(" rolls %d, has %d\n", rolls, players_score_board[player]);
            if (roll == 0 || roll == 1) {
                break;
            } else if (players_score_board[player] >= 100) {
                winner = 1;
                break;
            }
        }
        if (winner == 1) {
            printf("%s won!\n", player_name[player]);
            break;
        }
        if (player < num_players - 1) {
            player++;
        } else {
            player = 0;
        }
    }
    return 0;
}
