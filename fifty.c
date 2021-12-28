/* Name: Matthew Hise
   Date: 10-25-18
   Class: CS102-06

   Program: This program allows two users to play the dice game Fifty and keep track of their scores until the end of the round.

*/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int process_turn(char player[], int score, int key); // prototype the turn-handling function
int roll(int score); // prototype the roll function
void check_final(char contestant[], int contestant_score, char other_player[], int other_score); // prototype the function to check the final scores
int turns = 0;

int main(void) {
	srand((unsigned)time(NULL)); // seed the current time to the rand function
	char player1_name[20], player2_name[20]; // declare the variables for the players' names
	int player1_score = 0, player2_score = 0; // initialize the scores to 0

	printf("This program allows two players to play the dice game Fifty. Please enter the name of Player 1, who will go first:\n");
	scanf("%s", player1_name); // accept player 1's name
	printf("Okay, now please enter the name of Player 2:\n");
	scanf("%s", player2_name); // accept player 2's name

	printf("Let the games begin!\n---------------------------------------\n");

	while (1) {
		player1_score = process_turn(player1_name, player1_score, 1); // process the first player's turn
		check_final(player1_name, player1_score, player2_name, player2_score); // check if the first player won

		player2_score = process_turn(player2_name, player2_score, 2); // process the second player's turn
		check_final(player2_name, player2_score, player1_name, player1_score); // check if the second player won
	}

	return 0;
}

int process_turn(char player[], int score, int key) {
	int roll_key = 0;
	turns++; // update the number of turns taken
	printf("It is %s's turn to roll the dice. Press %d then ENTER to roll: ", player, key);

	while (roll_key != key) { // until the user enters the correct key
		scanf(" %d", &roll_key); // accept the command to roll from the user
	}

	score = roll(score); // update the score with the new roll
	printf("\n%s's score -> %d.\n---------------------------------------\n", player, score);
	return score; // return the new score
}

int roll(int score) {
	int dice1 = (rand() % 6) + 1;
	int dice2 = (rand() % 6) + 1;

	if (dice1 == dice2) { // if the dice are equal
		printf("You rolled two %d's! ", dice1);
		switch (dice1) {
			case 3: // reset their score to 0 if the player rolled 3's
				if (score > 0) {
					printf("Your score is reset to 0! :(");
				}
				else {
					printf("You're staying at 0.");
				}
				return 0;
			case 6: // increment the player's score by 25 points if they rolled 6's
				printf("You get 25 points added to your score!");
				return score + 25;
			default: // otherwise increment their score by 5
				printf("You get 5 points!");
				return score + 5;
		}
	}

	printf("You rolled %d and %d. You get 0 points.", dice1, dice2);
	return score; // return the unchanged score if the dice values were not equal
}

void check_final(char contestant[], int contestant_score, char other_player[], int other_score) {
	if (contestant_score >= 50) { // if the user won, output the congratulatory message
		printf("\nAfter %d total turns, %s won this round with %d points to %s's %d points! Congratulations, %s!\n", turns, contestant, contestant_score, other_player, other_score, contestant);
		exit(0); // exit the program
	}
}