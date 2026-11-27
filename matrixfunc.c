#include <stdio.h>
#include "matrixfunc.h"

int find_max_element(int *matptr, size_t rows, size_t cols, size_t *max_row, size_t *max_col)
{
    if (matptr == NULL || max_row == NULL || max_col == NULL ||
        rows == 0 || cols == 0)
    {
        return 1;
    }

    int max = *matptr;

    *max_row = 0;
    *max_col = 0;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            int value = *(matptr + i * cols + j);

            if (value > max)
            {
                max = value;
                *max_row = i;
                *max_col = j;
            }
        }
    }
    return 0;
}


int sum_less_than_k(int *matptr, size_t rows, size_t cols, int k, int *sum)
{
    if (matptr == NULL || sum == NULL || rows == 0 || cols == 0)
    {
        return 1;
    }

    *sum = 0;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            int value = *(matptr + i * cols + j);

            if (value < k)
            {
                *sum += value;
            }
        }
    }
    return 0;
}


int sum_main_diagonal(int *matptr, size_t rows, size_t cols, int *sum)
{
    if (matptr == NULL || sum == NULL || rows == 0 || cols == 0)
    {
        return 1;
    }

    *sum = 0;

    size_t limit = (rows < cols) ? rows : cols;

    for (size_t i = 0; i < limit; i++)
    {
        *sum += *(matptr + i * cols + i);
    }
    return 0;
}