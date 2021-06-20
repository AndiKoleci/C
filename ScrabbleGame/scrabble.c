#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util/print_board.h"
#include "util/scrabble.h"

void initialize_board(char game_board[BOARD_SIZE][BOARD_SIZE])
{
    //This function initializes the board with dots on each place.
    int i, j;

    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            game_board[i][j] = '.';
        }
    }
}

void add_scores(int score[26])
{
    //Gives each letter its respective score.
    score[0] = 1; //A
    score[1] = 3; //B
    score[2] = 3; //C
    score[3] = 2; //D
    score[4] = 1; //E
    score[5] = 4; //F
    score[6] = 2; //G
    score[7] = 4; //H
    score[8] = 1; //I
    score[9] = 8; //J
    score[10] = 5; //K
    score[11] = 1; //L
    score[12] = 3; //M
    score[13] = 1; //N
    score[14] = 1; //O
    score[15] = 3; //P
    score[16] = 10; //Q 
    score[17] = 1; //R
    score[18] = 1; //S
    score[19] = 1; //T
    score[20] = 1; //U
    score[21] = 4; //V
    score[22] = 4; //W
    score[23] = 8; //X
    score[24] = 4; //Y
    score[25] = 10; //Z
}

int get_number()
{
    //Reads the number of the task or the number of lines and it converts it into an int.
    int nr_words;
    static char line_read[1000];

    fgets(line_read, 1000, stdin);
    nr_words=strtol(line_read, NULL, 0);
    return nr_words;
}

void task1(char game_board[BOARD_SIZE][BOARD_SIZE])
{
    //Executes Task1.
    int i, j;
    int nr_words, line, column, direction;
    char *pointer;
    static char line_read[1000];

    nr_words = get_number();

    for (i = 0; i < nr_words; i++) {
        fgets(line_read, 90, stdin);
        line=strtol(line_read, &pointer, 0);
        column=strtol(pointer, &pointer, 0);
        direction=strtol(pointer, &pointer, 0);
        pointer+=1;
        for (j = 0; isalpha(pointer[j]); j++) { //Checks if the value is a letter.
            if (direction == 0) {
                game_board[line][column+j]=pointer[j];
            } else if (direction == 1) {
                game_board[line+j][column]=pointer[j];
            } 
        }
    }

    print_board(game_board);
}

void task2(char game_board[BOARD_SIZE][BOARD_SIZE])
{
    //Executes Task2.
    int i, j;
    int nr_words, line, column, direction;
    int p1score = 0, p2score = 0;
    static int score[26];
    char *pointer;
    static char line_read[1000];

    nr_words = get_number();
    add_scores(score);
    
    for (i = 0; i < nr_words; i++) {
        fgets(line_read, 90, stdin);
        line=strtol(line_read, &pointer, 0);
        column=strtol(pointer, &pointer, 0);
        direction=strtol(pointer, &pointer, 0);
        pointer += 1;
        for (j = 0; isalpha(pointer[j]); j++) { //Checks if the value is a letter.
            if (direction == 0) {
                game_board[line][column+j]=pointer[j];
            } else if (direction == 1) {
                game_board[line+j][column]=pointer[j];
            }
            if(i % 2 == 0){
                p1score+=score[pointer[j]-'A'];
            } else if (i % 2 == 1) {
                p2score+=score[pointer[j]-'A'];
            } 
        }
    }

    printf("Player 1: %d Points\n", p1score);
    printf("Player 2: %d Points", p2score);
}

void task3(char game_board[BOARD_SIZE][BOARD_SIZE])
{
    //Executes Task3.
    int i, j, k;
    int nr_words, line, column, direction, nr_letters = 0;
    int p1score = 0, p2score = 0;
    int multiplier1 = 1, multiplier2 = 1, wordscore1 = 0, wordscore2 = 0;
    int condition1 = 0, condition2 = 0, nr_of_1 = 0, nr_of_2 = 0;
    static int score[26];
    char *pointer;
    static char line_read[1000];
    static char bonus1[4];
    static char bonus2[4];
    
    fgets(bonus1, 4, stdin);
    fgets(bonus2, 4, stdin);
    nr_words = get_number();
    add_scores(score);
    
    for (i = 0; i < nr_words; i++) {
        fgets(line_read, 90, stdin);
        line=strtol(line_read, &pointer, 0);
        column=strtol(pointer, &pointer, 0);
        direction=strtol(pointer, &pointer, 0);
        pointer += 1;
        for (j = 0; isalpha(pointer[j]); j++) { //Checks if the value is a letter.
            if (direction == 0) {
                game_board[line][column+j] = pointer[j];
                if (bonus_board[line][column+j] == 1) {
                    nr_of_1++;
                } else if (bonus_board[line][column+j] == 2) {
                    nr_of_2++;
                }
            } else if (direction == 1) {
                game_board[line+j][column] = pointer[j];
                if (bonus_board[line+j][column] == 1) {
                    nr_of_1++;
                } else if (bonus_board[line+j][column] == 2) {
                    nr_of_2++;
                }
            }
            if (i % 2 == 0) {
                wordscore1+=score[pointer[j] - 'A'];
            } else if (i % 2 == 1) {
                wordscore2+=score[pointer[j] - 'A'];
            }
            nr_letters++; 
        }
        //easter egg
        for (j = 0; j < nr_letters-1; j++) {
            if ((bonus1[0] == pointer[j]) && (bonus1[1] == pointer[j+1])) {
                condition1 = 1;
            }
        }
        if (bonus2[0] == pointer[nr_letters-2]) {
            if (bonus2[1] == pointer[nr_letters-1]) {
                condition2 = 1;
            }
        }

        if (i % 2 == 0) {
            if (condition1 == 1) {
                for (k = 0; k < nr_of_1; k++) {
                    multiplier1 *= 2;
                }
            }
            if (condition2 == 1) {
                for (k = 0; k < nr_of_2; k++) {
                    multiplier1 *= 3;
                }
            }     
        } else if (i % 2 == 1) {
            if(condition1 == 1){
                for(k = 0; k < nr_of_1; k++){
                    multiplier2 *= 2;
                }
            }
            if (condition2 == 1) {
                for (k = 0; k < nr_of_2; k++) {
                    multiplier2 *= 3;
                }
            }     
        }
        p1score += wordscore1*multiplier1;
        p2score += wordscore2*multiplier2;
        
        wordscore1 = 0;
        wordscore2 = 0;
        multiplier1 = 1;
        multiplier2 = 1;
        nr_letters = 0;
        condition1 = 0;
        condition2 = 0;
        nr_of_1 = 0;
        nr_of_2 = 0;
    }

    printf("Player 1: %d Points\n", p1score);
    printf("Player 2: %d Points", p2score);
}

void task4(char game_board[BOARD_SIZE][BOARD_SIZE])
{
    //Executes Task4.
    int i, j, k, l;
    int nr_words, line, column, direction, nr_letters;
    static int len[NUM_WORDS];
    char *pointer;
    static char line_read[1000];
    static char used[NUM_WORDS];
    
    fgets(line_read, 4, stdin);
    fgets(line_read, 4, stdin);
    nr_words = get_number();

    for (i = 0; i < NUM_WORDS; i++) {
        len[i] = strlen(words[i]);
    }

    for (i = 0; i < nr_words; i++) {
        nr_letters = 0;
        fgets(line_read, 90, stdin);
        line=strtol(line_read, &pointer, 0);
        column=strtol(pointer, &pointer, 0);
        direction=strtol(pointer, &pointer, 0);
        pointer+=1;
        for (j = 0; isalpha(pointer[j]); j++) { //Checks if the value is a letter
            if (direction == 0) {
                game_board[line][column+j] = pointer[j];
            } else if (direction == 1) {
                game_board[line+j][column] = pointer[j];
            }
            nr_letters++;
        }
        for (j = 0; j < NUM_WORDS; j++) {
            if (len[j] == nr_letters) {
                if (strncmp(pointer, words[j], nr_letters) == 0) {
                    used[j] = 1; //Checks if the word was used.
                }
            }
        }
    }
    for (k = 0; k < NUM_WORDS; k++) {
        if (used[k] == 1) {
            continue;
        }
        for (i = 0; i < 15; i++) {
            for (j = 0; j < 15; j++) {
                if (words[k][0] == game_board[i][j]) { //First letter is found on board.
                    
                    //Horizontal
                    for (l = j+1; l < 15; l++) {
                        if (game_board[i][l] != '.') {
                            break;
                        }
                    }
                    if (len[k] <= l-j) {
                        for (l = j; l-j < len[k]; l++) {
                            game_board[i][l] = words[k][l-j];
                        }
                        print_board(game_board);
                        return;
                    }
                    
                    //Vertical
                    for (l = i+1; l < 15; l++) {
                        if (game_board[l][j] != '.') {
                            break;
                        }
                    }
                    if (len[k] <= l-i) {
                        for (l = i; l-i < len[k]; l++) {
                            game_board[l][j] = words[k][l-i];
                        }
                        print_board(game_board);
                        return;
                    }
                }
            }
        }
    }
}

void task5(char game_board[BOARD_SIZE][BOARD_SIZE])
{
    //Executes Task5.
    int i, j, k, l;
    int nr_words, nr_letters = 0, line, column, direction;
    int newscr = 0, max = 0, found;
    char *pointer;
    static char line_read[1000];
    int p1score = 0, p2score = 0;
    int multiplier1 = 1, multiplier2 = 1, wordscore1 = 0, wordscore2 = 0;
    int condition1 = 0, condition2 = 0, nr_of_1 = 0, nr_of_2 = 0;
    static int newscore[100], direct[100], xpos[100], ypos[100];
    static int len[NUM_WORDS];
    static int score[26];
    static char bonus1[4];
    static char bonus2[4];
    static char used[NUM_WORDS];
    
    fgets(bonus1, 4, stdin);
    fgets(bonus2, 4, stdin);
    nr_words = get_number();
    add_scores(score);
    
    for (i=0; i<NUM_WORDS; i++) {
        len[i] = strlen(words[i]);
    }
    
    for (i = 0; i < nr_words; i++) {
        fgets(line_read, 90, stdin);
        line=strtol(line_read, &pointer, 0);
        column=strtol(pointer, &pointer, 0);
        direction=strtol(pointer, &pointer, 0);
        pointer+=1;
        for (j = 0; isalpha(pointer[j]); j++) { //Checks if the value is a letter.
            if (direction == 0) {
                game_board[line][column+j] = pointer[j];
                if (bonus_board[line][column+j] == 1) {
                    nr_of_1++;
                }
                if (bonus_board[line][column+j] == 2) {
                    nr_of_2++;
                }
            } else if (direction == 1) {
                game_board[line+j][column] = pointer[j];
                if (bonus_board[line+j][column] == 1) {
                    nr_of_1++;
                }
                if (bonus_board[line+j][column] == 2) {
                    nr_of_2++;
                }
            }
            if (i % 2 == 0) {
                wordscore1+=score[pointer[j] - 'A'];
            } else if (i % 2 == 1) {
                wordscore2+=score[pointer[j] - 'A'];
            }
            nr_letters++; 
        }
        for (j = 0; j < NUM_WORDS; j++) {
            if (len[j] == nr_letters) {
                if (strncmp(pointer, words[j], nr_letters) == 0) {
                    used[j] = 1; //Checks if the word was used.
                }
            }
        }
        //easter egg
        for (j = 0; j < nr_letters-1; j++) {
            if ((bonus1[0] == pointer[j]) && (bonus1[1] == pointer[j+1])) {
                condition1 = 1;
            }
        }
        if (bonus2[0] == pointer[nr_letters-2]) {
            if (bonus2[1] == pointer[nr_letters-1]) {
                condition2 = 1;
            }
        }

        if (i % 2 == 0) {
            if (condition1 == 1) {
                for (k = 0; k < nr_of_1; k++) {
                    multiplier1 *= 2;
                }
            }
            if (condition2 == 1) {
                for (k = 0; k < nr_of_2; k++) {
                    multiplier1 *= 3;
                }
            }     
        } else if (i % 2 == 1) {
            if (condition1 == 1) {
                for (k = 0; k < nr_of_1; k++) {
                    multiplier2 *= 2;
                }
            }
            if (condition2 == 1) {
                for (k = 0; k < nr_of_2; k++) {
                    multiplier2 *= 3;
                }
            }     
        }
        p1score += wordscore1*multiplier1;
        p2score += wordscore2*multiplier2;
        
        wordscore1 = 0;
        wordscore2 = 0;
        multiplier1 = 1;
        multiplier2 = 1;
        nr_letters = 0;
        condition1 = 0;
        condition2 = 0;
        nr_of_1 = 0;
        nr_of_2 = 0;

        for (j = 0; j < NUM_WORDS; j++) {
            if (len[j] == nr_letters) {
                if (strncmp(pointer, words[j], nr_letters) == 0) {
                    used[j] = 1; //Checks if the word was used.
                }
            }
        }
    }
    //Until there I calculate the players' scores and check which words were used

    for (k = 0; k < NUM_WORDS; k++) {
        if (used[k] == 1) {
            continue;
        }
        for (i = 0; i < 15; i++) {
            for (j = 0; j < 15; j++) {
                if (words[k][0] == game_board[i][j]) { //First letter is found on board.
                    //Horizontal
                    for (l = j+1; l < 15; l++) {
                        if (game_board[i][l] != '.') {
                            break;
                        }
                    }
                    if (len[k] <= l-j) {
                        //Word can be horizontal.
                        for (l = j; l-j < len[k]; l++) {
                            if (bonus_board[i][l] == 1) {
                                nr_of_1++;
                            }
                            if (bonus_board[i][l] == 2) {
                                nr_of_2++;
                            }
                            wordscore2 += score[words[k][l-j] - 'A'];
                        }
                        for (l = j; l < len[k]-1; l++) {
                            if (bonus1[0] == words[k][l]) { 
                                if (bonus1[1] == words[k][l+1]) {
                                    condition1 = 1;
                                }
                            }
                        }
                        if (bonus2[0] == words[k][len[k]-2]) {
                            if (bonus2[1] == words[k][len[k]-1]) {
                                condition2 = 1;
                            }
                        }
                        if (condition1 == 1) {
                            for (l = 0; l < nr_of_1; l++) {
                                multiplier2 *= 2;
                            }   
                        }
                        if (condition2 == 1) {
                            for (l = 0; l < nr_of_2; l++) {
                                multiplier2 *= 3;
                            }
                        }
                        newscr = wordscore2*multiplier2;
        
                        wordscore2 = 0;
                        multiplier2 = 1;
                        condition1 = 0;
                        condition2 = 0;
                        nr_of_1 = 0;
                        nr_of_2 = 0;

                        if (newscr >= newscore[k]) {
                            newscore[k] = newscr;
                            direct[k] = 0;
                            xpos[k] = i;
                            ypos[k] = j;
                        }
                        newscr = 0; 
                    }
                    
                    //Vertical
                    for (l = i+1; l < 15; l++) {
                        if (game_board[l][j] != '.') {
                            break;
                        }
                    }
                    if (len[k] <= l-i) {
                        //Word can be vertical.
                        for (l = i; l-i < len[k]; l++) {
                            if (bonus_board[l][j] == 1) {
                                nr_of_1++;
                            }
                            if (bonus_board[l][j] == 2) {
                                nr_of_2++;
                            }
                            wordscore2 += score[words[k][l-i] - 'A'];
                        }
                        for (l = 0; l < (len[k]-1); l++) {
                            if (bonus1[0] == words[k][l]) { 
                                if (bonus1[1] == words[k][l+1]) {
                                    condition1 = 1;
                                }
                            }
                        }
                        if (bonus2[0] == words[k][len[k]-2]) {
                            if (bonus2[1] == words[k][len[k]-1]) {
                                condition2 = 1;
                            }
                        }
                        if (condition1 == 1) {
                            for (l = 0; l < nr_of_1; l++) {
                                multiplier2 *= 2;
                            }   
                        }
                        if (condition2 == 1) {
                            for (l = 0; l < nr_of_2; l++) {
                                multiplier2 *= 3;
                            }
                        }
                        newscr += wordscore2*multiplier2;
                        wordscore2 = 0;
                        multiplier2 = 1;
                        condition1 = 0;
                        condition2 = 0;
                        nr_of_1 = 0;
                        nr_of_2 = 0;  

                        if (newscr > newscore[k]) {
                            newscore[k] = newscr;
                            direct[k] = 1;
                            xpos[k] = i;
                            ypos[k] = j;
                        }
                        
                        newscr = 0; 
                    } 
                }
            }
        }
    }
    
    for (i = 0; i < 100; i++) {
        if(newscore[i] > max){
            max = newscore[i];
        }
    }
    for (i = 0; i < 100; i++) {
        if (newscore[i] == max) {
            found = i;
        }
    }
    if (direct[found] == 0) {
        for (i = ypos[found]; i < len[found]+ypos[found]; i++) {
            game_board[xpos[found]][i] = words[found][i-ypos[found]];
        }
    }
    if (direct[found] == 1) {
        for (i = xpos[found]; i < len[found]+xpos[found]; i++) {
            game_board[i][ypos[found]] = words[found][i-xpos[found]];
        }
    }

    if (p2score + newscore[found] >= p1score) {
        print_board(game_board);
    } else {
        printf("Fail!");
    }
}

int main()
{
    int task;
    static char game_board[BOARD_SIZE][BOARD_SIZE];
    
    initialize_board(game_board);
    
    //Read task number.

    task = get_number();
    
    //Executing the tasks.
    if (task==0) {
        print_board(game_board);
    } else if (task == 1) {
        task1(game_board);
    } else if (task == 2) {
        task2(game_board);
    } else if (task == 3) {
        task3(game_board);
    } else if (task == 4) {
        task4(game_board);
    } else if (task == 5) {
        task5(game_board);
    }

    return 0;
}