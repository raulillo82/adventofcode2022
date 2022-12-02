#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#define FILENAME "day2_data.txt"

//Chosen hand will be given by a letter each round. Different for opponent and yourself
#define OPPONENT_ROCK 'A'
#define OPPONENT_PAPER 'B'
#define OPPONENT_SCISSORS 'C'
#define OWN_ROCK 'X'
#define OWN_PAPER 'Y'
#define OWN_SCISSORS 'Z'

//New constants for the second part of the line
#define DO_WIN 'Z'
#define DO_DRAW 'Y'
#define DO_LOSE 'X'

//Constants for points
#define VICTORY 6
#define DRAW 3
#define LOSS 0

//Constants for hands played
#define ROCK 1
#define PAPER 2
#define SCISSORS 3

int get_total_points (char opponents_hand, char your_hand);
int get_game_points (char opponents_hand, char your_hand);
int get_total_points_second_part (char opponents_hand, char result);
char get_needed_hand (char opponents_hand, char result);

int get_total_points (char opponents_hand, char your_hand){
	int total_points = 0, game_points = 0;
	//First count the points for whatever you played, it's easier
	if (your_hand == OWN_ROCK)
		total_points += ROCK;
	else if (your_hand == OWN_PAPER)
		total_points += PAPER;
	else if (your_hand == OWN_SCISSORS)
		total_points += SCISSORS;
	printf ("Points given for your own move are %d\n", total_points);
	//Now give points according to results
	game_points = get_game_points (opponents_hand, your_hand);
	//Add them to the total result
	total_points += game_points;
	printf ("Adding up, this round was worth %d points, accumulate of %d points\n", game_points, total_points);
	return (total_points);
}

int get_game_points (char opponents_hand, char your_hand){
	int game_points = 0;

	switch (opponents_hand){
		case OPPONENT_ROCK:
			switch (your_hand){
				case OWN_ROCK:
					game_points = DRAW;
					break;
				case OWN_PAPER:	
					game_points = VICTORY;
					break;
				case OWN_SCISSORS:	
					game_points = LOSS;
					break;
			}
			break;
		case OPPONENT_PAPER:
			switch (your_hand){
				case OWN_ROCK:
					game_points = LOSS;
					break;
				case OWN_PAPER:	
					game_points = DRAW;
					break;
				case OWN_SCISSORS:	
					game_points = VICTORY;
					break;
			}
			break;
		case OPPONENT_SCISSORS:
			switch (your_hand){
				case OWN_ROCK:
					game_points = VICTORY;
					break;
				case OWN_PAPER:	
					game_points = LOSS;
					break;
				case OWN_SCISSORS:	
					game_points = DRAW;
					break;
			}
			break;
	}
	printf ("Game points for this line are: %d\n", game_points);
	return (game_points);
}

int get_total_points_second_part (char opponents_hand, char result){
	int total_points = 0, own_hand_points = 0;
	char needed_hand;
	//First count the points for the result, that you're already told
	if (result == DO_WIN)
		total_points += VICTORY;
	else if (result == DO_DRAW)
		total_points += DRAW;
	else if (result == DO_LOSE)
		total_points += LOSS;
	printf ("Points given for this line's game result (second version) are %d\n", total_points);
	//Now calculate your needed hand and the points it will be worth
	needed_hand = get_needed_hand (opponents_hand, result);
	if (needed_hand == OWN_ROCK)
		own_hand_points = ROCK;
	else if (needed_hand == OWN_PAPER)
		own_hand_points = PAPER;
	else if (needed_hand == OWN_SCISSORS)
		own_hand_points = SCISSORS;
	total_points += own_hand_points;
	printf ("Points give for your own hand this line are %d, accumulated %d points\n", own_hand_points, total_points);
	return (total_points);
}

char get_needed_hand (char opponents_hand, char result){
	char hand;
	switch (opponents_hand){
		case OPPONENT_ROCK:
			switch (result){
				case DO_WIN:
					hand = OWN_PAPER;
					break;
				case DO_DRAW:	
					hand = OWN_ROCK;
					break;
				case DO_LOSE:	
					hand = OWN_SCISSORS;
					break;
			}
			break;
		case OPPONENT_PAPER:
			switch (result){
				case DO_WIN:
					hand = OWN_SCISSORS;
					break;
				case DO_DRAW:	
					hand = OWN_PAPER;
					break;
				case DO_LOSE:	
					hand = OWN_ROCK;
					break;
			}
			break;
		case OPPONENT_SCISSORS:
			switch (result){
				case DO_WIN:
					hand = OWN_ROCK;
					break;
				case DO_DRAW:	
					hand = OWN_SCISSORS;
					break;
				case DO_LOSE:	
					hand = OWN_PAPER;
					break;
			}
			break;
	}
	printf ("Needed hand for the second game is %c\n", hand);
	return (hand);
}

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int points = 0; //Full points of all the games included in the file
    int points_secondpart = 0; //Points for the second version of the game
    
    fp = fopen(FILENAME , "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
	//variables to store opponent's play and your own
	char opponent, own;
	//opponent's is the first character of the line
	opponent = line [0];
	//your own is the 3rd character
	own = line [2];
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
	points += get_total_points (opponent, own);
	printf ("Accumulated result so far is %d points\n", points);
	points_secondpart += get_total_points_second_part (opponent, own);
	printf ("Accumulated result in the second version so far is %d points\n", points_secondpart);
    }

    printf ("\nTotal points counted are %d (first version)\n", points);
    printf ("\nTotal points counted are %d (second version)\n", points_secondpart);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
