#include <stdlib.h>
#include <stdio.h>

int **board;

int **createBoard();
void traverse(int **);
int *search(int **, int, int, int *);
int rowTraverse(int **, int, int);
int colTraverse(int **, int, int);
int miniTraverse(int **, int, int);
int check(int **);
int solver(int **, int, int, int*, int*);
char converter(int);
int converter2(char);
int* all3(int**, int, int, int*);

int converter2(char x){
    switch(x){
        case '0':
            return 0; 
            
        case '1':
            return 1; 
            
        case '2':
            return 2; 
            
        case '3':
            return 3;
            
        case '4':
            return 4;
            
        case '5':
            return 5;
            
        case '6':
            return 6;
            
        case '7':
            return 7; 
            
        case '8':
            return 8; 
            
        case '9':
            return 9; 
            
        case 'A':
            return 10;
            
        case 'B':
            return 11; 
            
        case 'C':
            return 12; 
            
        case 'D':
            return 13; 
            
        case 'E':
            return 14; 
            
        case 'F':
            return 15; 
            
        case '-':
            return 16;
        default:
            return 0;    
    }   
}
char converter(int x){
    switch(x){
        case 0:
            return '0';
            
        case 1:
            return '1';
            
        case 2:
            return '2';
            
        case 3:
            return '3';
            
        case 4:
            return '4';
            
        case 5:
            return '5';
            
        case 6:
            return '6';
            
        case 7:
            return '7';
            
        case 8:
            return '8';
            
        case 9:
            return '9';
            
        case 10:
            return 'A';
            
        case 11:
            return 'B';
            
        case 12:
            return 'C';
            
        case 13:
            return 'D';
            
        case 14:
            return 'E';
            
        case 15:
            return 'F';
            
        case 16:
            return '-';
        default:
            return '0';
    }
            
}
int** createBoard()
{
    /* Allocate Space for board */
    int **temp = malloc(sizeof(int *) * 16);
    for (int i = 0; i < 16; i++)
    {
        temp[i] = malloc(sizeof(int) * 16);
    }
    return temp;
}
void traverse(int **temp)
{
    char entry;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            entry = converter(board[i][j]);
            printf("%c\t", entry);
        }
        entry = converter(board[i][15]);
        printf("%c\n", entry);
    }
}
int *search(int **board, int x, int y, int *arr)
{

    if (y < 15)
    {
        y += 1;
    }
    else if (x < 15 && y == 15)
    {
        x += 1;
        y = 0;
    }
    else if (x == 15 && y == 15)
    {
        x = 0;
        y = 0;
    }

    for (int i = x; i < 16; i++)
    {
        for (int j = y; j < 16; j++)
        {
            if (board[i][j] == 16)
            {
                arr[0] = i;
                arr[1] = j;
                return arr;
            }
        }
        y = 0;
    }
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (board[i][j] == 16)
            {
                arr[0] = i;
                arr[1] = j;
                return arr;
            }
        }
    }
    return NULL;
}
int rowTraverse(int **board, int x, int y)
{
    int *set = malloc(sizeof(int) * 17);
    for (int i = 0; i < 17; i++)
    {
        set[i] = 0;
    }
    /* Row Traverse */
    for (int i = 0; i < 16; i++)
    {
        int entry = board[x][i];
        set[entry]++;
       
    }
        for (int i = 0; i < 16; i++)
        {
            if (set[i] > 1)
            {
                free(set);
                return 0;
            }
        }
    free(set);
    return 1;
}
int colTraverse(int **board, int x, int y)
{
    int *set = malloc(sizeof(int) * 17);
    for (int i = 0; i < 17; i++)
    {
        set[i] = 0;
    }
    /* Col Traverse */
    for (int i = 0; i < 16; i++)
    {
        int entry = board[i][y];
        set[entry]++;
        
    }
        for (int i = 0; i < 16; i++)
        {
            if(set[i] > 1){
                free(set);
                return 0;
            }
        }
    free(set);
    return 1;
}
int miniTraverse(int **board, int x, int y)
{
    int newx = x / 4;
    int newy = y / 4;
    int *set = malloc(sizeof(int) * 17);
    for (int i = 0; i < 17; i++)
    {
        set[i] = 0;
    }
    for (int i = newx * 4; i < (newx * 4) + 4; i++)
    {
        for (int j = newy * 4; j < (newy * 4) + 4; j++)
        {
            int entry = board[i][j];
            set[entry]++;
            
        }
    }
        for (int i = 0; i < 16; i++)
        {
            if (set[i] >  1)
            {
                free(set);
                return 0;             
            }
        }
    free(set);
    return 1;
}
int check(int **board)
{
    int *set = malloc(sizeof(int) * 17);
    for (int i = 0; i < 17; i++)
    {
        set[i] = 0;
    }

    /* Check each Row Traverse */
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int entry = board[i][j];
            set[entry]++;
        }
        for (int i = 0; i < 16; i++)
        {
            if (set[i] > 1)
            {
                free(set);
                return 0;
            }
        }
        for (int i = 0; i < 17; i++)
        {
            set[i] = 0;
        }
    }
    /* Check Every Column */
    for (int j = 0; j < 16; j++)
    {
        for (int i = 0; i < 16; i++)
        {
            int entry = board[i][j];
            set[entry]++;
        }
        for (int i = 0; i < 16; i++)
        {
            if (set[i] > 1)
            {
                free(set);
                return 0;
            }
        }
        for (int i = 0; i < 17; i++)
        {
            set[i] = 0;
        }
    }
    for (int r = 0; r < 16; r += 4)
    {
        for (int c = 0; c < 16; c += 4)
        {
            for (int i = r; i < r + 4; i++)
            {
                for (int j = c; j < c + 4; j++)
                {
                    int entry = board[i][j];
                    set[entry]++;
                }
            }
            for (int i = 0; i < 16; i++)
            {
                if (set[i] > 1)
                {
                    free(set);
                    return 0;
                }
            }
            for (int i = 0; i < 17; i++)
            {
                set[i] = 0;
            }
        }
    }
    free(set);
    return 1;
}
int sanity(int **board, int x, int y)
{
    if (rowTraverse(board, x, y) == 1 && colTraverse(board, x, y) == 1 && miniTraverse(board, x, y) == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int* all3(int **board, int x, int y, int* set)
{
    //int *set = malloc(sizeof(int) * 17);
    for (int i = 0; i < 17; i++)
    {
        set[i] = 0;
    }
    for (int i = 0; i < 16; i++)
    {
        int entry = board[x][i];
        set[entry]++;
    }
    for (int i = 0; i < 16; i++)
    {
        int entry = board[i][y];
        set[entry]++;
    }
    int newx = x / 4;
    int newy = y / 4;
    for (int i = newx * 4; i < (newx * 4) + 4; i++)
    {
        for (int j = newy * 4; j < (newy * 4) + 4; j++)
        {
            int entry = board[i][j];
            set[entry]++;
        }
    }
    return set;
}
int solver(int **board, int x, int y, int* arr, int* set)
{
    //
    if (sanity(board, x, y) == 0)
    {
        //printf("sanity %d, %d\n", x, y);
        return 0;
    }
    //int *arr = malloc(sizeof(int) * 2);
    arr = search(board, x, y, arr);
    if (arr == NULL)
    {
        //free(arr);
        return 1;
    }
    else
    {
        x = arr[0];
        y = arr[1];
        //free(arr);
        printf("Board (Valid): %d,%d\n",x , y);
        traverse(board);
        set = all3(board, x, y, set);
        for (int i = 0; i < 16; i++)
        {  
            if(set[i] == 0){
                 //printf("%d\n", i);
                board[x][y] = i;
                if(solver(board,x,y, arr, set) == 1){
                    
                    return 1;
                }
            }
        } 
        //free(set);  
    }
    x = arr[0];
    y = arr[1];
    board[x][y] = '-';
    // printf("Board (BackTracking): %d, %d\n", x, y);
    // traverse(board);
    //free(arr);
    return 0;
}
int main(int argc, char **argv)
{
    //remember to free the matrix later
    /* Fill in the board */
    board = createBoard();
    char entry;
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        return 0;
    }
    /* Fill in the Board */
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            fscanf(fp, "%c\t", &entry);
            board[i][j] = converter2(entry);
        }
        fscanf(fp, "\n");
    }
    fclose(fp);
    
    /* Sudoku Algo */
    int *arr = malloc(sizeof(int) * 2);
    arr[0] = 0;
    arr[1] = 0;
    int *set = malloc(sizeof(int) * 17);
    if (check(board) == 1)
    {
        if (solver(board, 0, 0, arr, set) == 1)
        {
            traverse(board);
        }
        else
        {
            printf("no-solution");
        }
    }else{
        printf("no-solution");
    }
    free(set);
    free(arr);
    /* Traverse to Print out Board*/
    for (int i = 0; i < 16; i++)
    {
        free(board[i]);
    }
    //free(coordinate);
    free(board);
    return 0;
}