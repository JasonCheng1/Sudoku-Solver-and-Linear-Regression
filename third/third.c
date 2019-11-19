#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double **multiply(double **, int, int, double **, int, int);
double **createMatrix(int, int);
void freeMatrix(double **, int); // only need the row to free
double **tranpose(double **, int, int);
double **guassElimination(double **, int, int);
void traverse(double **, int, int);

double **createMatrix(int row, int col)
{
    double **temp = malloc(sizeof(double *) * row);
    for (int i = 0; i < row; i++)
    {
        temp[i] = malloc(sizeof(double) * col);
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            temp[i][j] = 0;
        }
    }
    return temp;
}
void freeMatrix(double **temp, int row)
{
    for (int i = 0; i < row; i++)
    {
        free(temp[i]);
    }
    free(temp);
}
double **multiply(double **A, int m1, int n1, double **B, int m2, int n2)
{
    if (n1 != m2)
    {
        return NULL;
    }
    // traverse(A, m1, n1);
    // printf("<----------------------------------------------------------------->");
    // traverse(B, m2, n2);
    /* Product Matrix */
    int m3 = m1;
    int n3 = n2;
    double **res = createMatrix(m3, n3);

    /* Calculating the Dot Product */
    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            double product = 0;
            for (int k = 0; k < n1; k++)
            {
                product += (A[i][k] * B[k][j]);
            }
            res[i][j] = product;
        }
    }
    return res;
}
double **transpose(double **temp, int row, int col)
{
    double **result = createMatrix(col, row);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            result[j][i] = temp[i][j];
        }
    }
    return result;
}
double **guassElimination(double **temp, int row, int col)
{
    int colA = 2 * col;
    double **aug = createMatrix(row, colA);
    for (int i = 0; i < row; i++)
    { //left portion of aug matrix which is the temp matrix
        for (int j = 0; j < col; j++)
        {
            aug[i][j] = temp[i][j];
        }
    }
    for (int i = 0, j = col; i < row && j < colA; i++, j++)
    {                  //right portion of aug matrix which is the identity matrix
        aug[i][j] = 1; //the diagonal is all one
    }
    // printf("Augmented Matrix: \n");
    // traverse(aug, row, colA);

    /*Guass-Jordan Elimination */
    /* Going down */
    for (int i = 0; i < row /*- 1*/; i++) //doesnt go to last row because last row you don't have anything below it so just divide that row by the pivot
    {
        //printf("Augmented Matrix (Pivot Column): \n\n");
        //traverse(aug, row, colA);

       /*
        double pivot = aug[i][i]; //bc we are dealing with a square
        if (pivot != 1)
        {
            if (pivot < 0)
            { //if any of the features are negative
                pivot *= -1;
            }
            for (int j = i; j < colA; j++)
            {
                aug[i][j] = aug[i][j] / pivot; //diving the pivot row by the pivot
            }
        }
       */

        //printf("Augmented Matrix (Normalizing): \n\n");
        //traverse(aug, row, colA);
       /*
        for (int x = i + 1; x < row; x++) //elementary row operations for this column (i)
        {
            //printf("Augmented Matrix (Row Operation): \n\n");
            //traverse(aug, row, colA);
            double num = aug[x][i];
            if (num == 0)
            {
                continue;
            }
            for (int y = i; y < colA; y++)
            {
                aug[x][y] = aug[x][y] - (num * aug[i][y]);
            }
        }
        */
        for(int x = 0; x < i; x++){//how deep we are going on each row thus how many operations we are doing
            // printf("Augmented Matrix (Row Operation): \n\n");
            // traverse(aug, row, colA);
            double num = aug[i][x];
            if (num == 0)
            {
                continue;
            }
            for (int y = x; y < colA; y++)
            {
                aug[i][y] = aug[i][y] - (num * aug[x][y]);
            }
        }
        double pivot = aug[i][i]; //bc we are dealing with a square
        if (pivot != 1)
        {
            if (pivot < 0)
            { //if any of the features are negative
                pivot *= -1;
            }
            for (int j = i; j < colA; j++)
            {
                aug[i][j] = aug[i][j] / pivot; //diving the pivot row by the pivot
            }
        }
        // printf("Augmented Matrix (Row Operation): \n\n");
        // traverse(aug, row, colA);
    }
    /* Going up */
    for (int i = row - 1; i > 0; i--)
    {
        //printf("Augmented Matrix (Pivot Column): \n\n");
        //traverse(aug, row, colA);
        for (int x = i - 1; x >= 0; x--)
        {
            //printf("Augmented Matrix (Row Operation): \n\n");
            //traverse(aug, row, colA);
            double num = aug[x][i];
            for (int y = i; y < colA; y++)
            {
                aug[x][y] = aug[x][y] - (num * aug[i][y]);
            }
        }
    }
   // traverse(aug, row, colA);
    double **res = createMatrix(row, col);
    for (int i = 0; i < row; i++)
    {
        for (int j = col, k = 0; j < colA; j++, k++)
        {
            res[i][k] = aug[i][j];
        }
    }
    // printf("Augmented Matrix: \n\n");
    // traverse(aug, row, colA);
    freeMatrix(aug, row);
    return res;
}
void traverse(double **temp, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%f\t", temp[i][j]);
        }
        printf("\n");
    }
}
int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        return 0;
    }
    int row = 0;
    int col = 0;
    double entry = 0;
    /* Training Data */
    fscanf(fp, "%d\n", &col);
    col += 2; //to account for price column
    fscanf(fp, "%d\n", &row);
    double **training = createMatrix(row, col);
    for (int i = 0; i < row; i++)
    {
        training[i][0] = 1;
        for (int j = 1; j < col; j++)
        {
            fscanf(fp, "%lf,", &entry);
            training[i][j] = entry;
        }
        fscanf(fp, "\n");
    }
    /* Divide up the training Data into Features and House Prices */
    int colF = col - 1;
    double **price = createMatrix(row, 1);
    double **feature = createMatrix(row, colF);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < colF; j++)
        {
            feature[i][j] = training[i][j];
        }
        price[i][0] = training[i][colF];
    }
    int newRow = 0;
    fp = fopen(argv[2], "r");
    if (fp == NULL)
    {
        return 0;
    }
    fscanf(fp, "%d\n", &newRow);
    double **testing = createMatrix(newRow, colF); //we use colF b/c in testing dataset there is no price column
    for (int i = 0; i < newRow; i++)
    {
        testing[i][0] = 1;
        for (int j = 1; j < colF; j++)
        {
            fscanf(fp, "%lf,", &entry);
            testing[i][j] = entry;
        }
        fscanf(fp, "\n");
    }
    // printf("Feature: \n");
    // traverse(feature, row, colF);
    // printf("Price: \n");
    // traverse(price, row, 1);

    double **xtranspose = transpose(feature, row, colF); // row = colF , colF = row
    // printf("Tranpose of X: \n");
    // traverse(xtranspose, colF, row);

    double **xtransposePrice = multiply(xtranspose, colF, row, price, row, 1); //row = colF, col = 1
    // printf("Tranpose of X * Price: \n");
    // traverse(xtransposePrice, colF, 1);

    double **xtransposeX = multiply(xtranspose, colF, row, feature, row, colF); //row = colF, col = colF
    // printf("Tranpose of X * X: \n");
    // traverse(xtransposeX, colF, colF);

    double **inverse = guassElimination(xtransposeX, colF, colF); //row = colF, col = colF
    // printf("Inverse of (Tranpose of X * X): \n");
    // traverse(inverse, colF, colF);

    double **weights = multiply(inverse, colF, colF, xtransposePrice, colF, 1); //row = colF, col = 1
    // printf("Weights: \n");
    // traverse(weights, colF, 1);

    // printf("Testing: \n");
    // traverse(testing, newRow, colF);

    double **predicted = multiply(testing, newRow, colF, weights, colF, 1); //row = newRow, col = 1
    // printf("Prediction: \n");
    for (int i = 0; i < newRow; i++)
    {
            printf("%0.0lf\n",predicted[i][0]);
    }
    fclose(fp);

    freeMatrix(training, row);
    freeMatrix(feature, row);
    freeMatrix(price, row);
    freeMatrix(testing, newRow);
    freeMatrix(xtranspose, colF);
    freeMatrix(xtransposePrice, colF);
    freeMatrix(xtransposeX, colF);
    freeMatrix(inverse, colF);
    freeMatrix(weights, colF);
    freeMatrix(predicted, newRow);
    return 0;
}