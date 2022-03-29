#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

int mainMenu(void);
int rockPaperScissors(void);
void clearInputBuffer(void);
int generateComputerAnswer(void);


int main() {
    int playerScore = 0;
    int computerScore = 0;
    bool running = true;
    while (running) {
        int mode = mainMenu();
        if (mode == 1) {
            int result = rockPaperScissors();
            if (result == 0) {
                printf("You lose! Adding one point to computers score!\n");
                computerScore += 1;
            }
            else {
                printf("You win! Adding one point to your score!\n");
                playerScore += 1;
            }
        }

        else if (mode == 2) {
            printf("Current score for this session:\n");
            printf("User: %d - Computer %d\n", playerScore, computerScore);
        }

        else if (mode == 3) {
            running = false;
        }

        else {
            printf("The only valid options are 1-3 please try again\n");
        }
    }


}


int mainMenu(void) {
    printf("Welcome to Rock Paper Scissors!\n");
    printf("Press 1 to start a game\n");
    printf("Press 2 to show the score of score of the current session\n");
    printf("Press 3 to end this session\n");
    int userInput = 0;
    while (scanf("%d", &userInput)) {
        if (userInput == 1) {
            // Returns 1 for the switch case in main method to run the rock paper scissors game.
            printf("Beginning game...\n");
            return 1;
        }
        else if (userInput == 2) {
            // Returns to for switch case found in main to load a save game.
            printf("Show the score");
            return 2;
        }
        else if (userInput == 3) {
            // Ends session.
            printf("Goodbye!");
            return 3;
        }
        else {
            printf("The only valid options are 1-3 please try again\n");
        }
    }
    clearInputBuffer();
}

/*
 *
 *  returns 0 if user lost and returns 1 if the user won.
 */
int rockPaperScissors() {
    char moves[][10] = {"Rock", "Paper", "Scissors"};
    bool lookingForValidUserInput = true;
    char userAnswer[10];
    bool nobodyHasWon = true;
    while (nobodyHasWon) {
        while (lookingForValidUserInput) {
            printf("It's your turn! Please select Rock, Paper, or Scissors:\n");
            scanf("%s", &userAnswer);
            int resultOfStringComparison;
            for (int i = 0; i < 3; i++) {
                resultOfStringComparison = strcmp(userAnswer, *(moves+i));
                if (resultOfStringComparison == 0) {
                    break;
                }
            }
            if (resultOfStringComparison == 0) {
                lookingForValidUserInput = false;
            }
            else {
                printf("The only valid options are Rock, Paper, or Scissors. Note that a capital letter in front is important!\n");
            }
        }


        //Determines the answer for the computer.
        char computerAnswer[10];
        // Sleep call is a system call that will add a delay of 3 seconds before printing the computers answer. Gives the illusion of a computer thinking.
        printf("Computer thinking of answer.....\n");
        Sleep(2000);

        int computerAnswerNumber = generateComputerAnswer();
        if (computerAnswerNumber == 0) {
            strcpy(computerAnswer, "Rock");
            printf("Computer plays Rock!\n");
        }
        else if (computerAnswerNumber == 1) {
            strcpy(computerAnswer, "Paper");
            printf("Computer plays Paper!\n");
        }
        else if (computerAnswerNumber == 2) {
            strcpy(computerAnswer, "Scissors");
            printf("Computer plays Scissors!\n");
        }


        // Prints tie and doesn't break the loop if user and computer choose the same move.
        if (strcmp(userAnswer, computerAnswer) == 0) {
            printf("Tie!\n");
            printf(userAnswer);
            printf(computerAnswer);
            lookingForValidUserInput = true;
        }

        else {
            // Compares computer answers to the user answer of Rock.
            if (strcmp(userAnswer, "Rock") == 0) {
                if (strcmp(computerAnswer, "Paper")) {
                    return 0;
                }
                if (strcmp(computerAnswer, "Scissors")) {
                    return 1;
                }
            }
            // Compares computer answers to the user answer of Paper.
            if (strcmp(userAnswer, "Paper")) {
                if (strcmp(computerAnswer, "Rock")) {
                    return 1;
                }
                if (strcmp(computerAnswer, "Scissors")) {
                    return 0;
                }
            }

            if (strcmp(userAnswer, "Scissors")) {
                if (strcmp(computerAnswer, "Rock")) {
                    return 0;
                }
                if (strcmp(computerAnswer, "Paper")) {
                    return 1;
                }
            }
            nobodyHasWon = false;
        }
    }
}

// Generates a random answer for the computer to play. Used in rockPaperScissors() to determine computers answer/move.
int generateComputerAnswer(void) {
    // Generates a random number 0-2.
    int randomNumber;
    srand(time(NULL));
    randomNumber = rand() % 3;
    return randomNumber;
}

void clearInputBuffer() {
    char c;
    while ((c = getchar()) != '\n');
}