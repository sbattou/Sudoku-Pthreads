#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int row;
    int col;
    int (* board)[9];
} parameters;

void * RowThread(void * params);
void * ColumnThread(void * params);
void * SquareThread(void * params);

int main(void)
{
    int board[9][9] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}
    };

    parameters * param0 = (parameters *) malloc(sizeof(parameters));
    param0->row = 0;
    param0->col = 0;
    param0->board = board;

    parameters * param1 = (parameters *) malloc(sizeof(parameters));
    param1->row = 0;
    param1->col = 0;
    param1->board = board;

    parameters * param2 = (parameters *) malloc(sizeof(parameters));
    param2->row = 0;
    param2->col = 3;
    param2->board = board;

    parameters * param3 = (parameters *) malloc(sizeof(parameters));
    param3->row = 0;
    param3->col = 6;
    param3->board = board;

    parameters * param4 = (parameters *) malloc(sizeof(parameters));
    param4->row = 3;
    param4->col = 0;
    param4->board = board;

    parameters * param5 = (parameters *) malloc(sizeof(parameters));
    param5->row = 3;
    param5->col = 3;
    param5->board = board;

    parameters * param6 = (parameters *) malloc(sizeof(parameters));
    param6->row = 3;
    param6->col = 6;
    param6->board = board;

    parameters * param7 = (parameters *) malloc(sizeof(parameters));
    param7->row = 6;
    param7->col = 0;
    param7->board = board;

    parameters * param8 = (parameters *) malloc(sizeof(parameters));
    param8->row = 6;
    param8->col = 3;
    param8->board = board;

    parameters * param9 = (parameters *) malloc(sizeof(parameters));
    param9->row = 6;
    param9->col = 6;
    param9->board = board;

    pthread_t thread_rows, thread_cols, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;

    void * all_rows;
    void * all_cols;
    void * square1;
    void * square2;
    void * square3;
    void * square4;
    void * square5;
    void * square6;
    void * square7;
    void * square8;
    void * square9;

    pthread_create(&thread_rows, NULL, RowThread, (void *) param0);
    pthread_create(&thread_cols, NULL, ColumnThread, (void *) param0);
    pthread_create(&thread1, NULL, SquareThread, (void *) param1);
    pthread_create(&thread2, NULL, SquareThread, (void *) param2);
    pthread_create(&thread3, NULL, SquareThread, (void *) param3);
    pthread_create(&thread4, NULL, SquareThread, (void *) param4);
    pthread_create(&thread5, NULL, SquareThread, (void *) param5);
    pthread_create(&thread6, NULL, SquareThread, (void *) param6);
    pthread_create(&thread7, NULL, SquareThread, (void *) param7);
    pthread_create(&thread8, NULL, SquareThread, (void *) param8);
    pthread_create(&thread9, NULL, SquareThread, (void *) param9);

    pthread_join(thread_rows, &all_rows);
    pthread_join(thread_cols, &all_cols);
    pthread_join(thread1, &square1);
    pthread_join(thread2, &square2);
    pthread_join(thread3, &square3);
    pthread_join(thread4, &square4);
    pthread_join(thread5, &square5);
    pthread_join(thread6, &square6);
    pthread_join(thread7, &square7);
    pthread_join(thread8, &square8);
    pthread_join(thread9, &square9);

    if ((int) all_rows == 1){
	printf("%s \n","All rows are good");
	}
    else{
	printf("%s \n","Some rows are bad");
	}

    if ((int) all_cols == 1){
    printf("%s \n","All columns are good");
	}
    else{
	printf("%s \n","Some columns are bad");
	}
	if ((int) square1 == 1 && (int) square2 == 1 && (int) square3 == 1 && (int) square4 == 1 && (int) square5 == 1 &&
    (int) square6 == 1 && (int) square7 == 1 && (int) square8 == 1 && (int) square9 == 1 ){
    printf("%s \n","All squares are good");
	}
    else{
	printf("%s \n","Some squares are bad");
	}
    if (    (int) all_rows == 1 &&
            (int) all_cols == 1 &&
            (int) square1 == 1 &&
            (int) square2 == 1 &&
            (int) square3 == 1 &&
            (int) square4 == 1 &&
            (int) square5 == 1 &&
            (int) square6 == 1 &&
            (int) square7 == 1 &&
            (int) square8 == 1 &&
            (int) square9 == 1 ) {
        printf("The Sudoku is solved!\n");
    }
    else {
        printf("The Sudoku is not solved.\n");
    }

    return 0;
}

void * RowThread(void * params) {
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    for (int i = startRow; i < 9; ++i) {
        int row[10] = {0};
        for (int j = startCol; j < 9; ++j) {
            int val = data->board[i][j];
            if (row[val] != 0) {
                return (void *) 0;
            }
            else{
                row[val] = 1;
            }
        }
    }
    return (void *) 1;
}

void * ColumnThread(void * params) {
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    for (int i = startCol; i < 9; ++i) {
        int col[10] = {0};
        for (int j = startRow; j < 9; ++j) {
            int val = data->board[j][i];
            if (col[val] != 0) {
                return (void *) 0;
            }
            else{
                col[val] = 1;
            }
        }
    }
    return (void *) 1;
}

void * SquareThread(void * params) {
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    int saved[10] = {0};
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            int val = data->board[i][j];
            if (saved[val] != 0) {
                return (void *) 0;
            }
            else{
                saved[val] = 1;
            }
        }
    }
    return (void *) 1;
}
