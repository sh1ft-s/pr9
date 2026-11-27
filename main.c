#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include "matrixfunc.h"

// Очистка входного буфера
void clear_input(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

// Вывод меню
void print_menu(void)
{
    printf("\n========== ПР №9 ==========\n");
    printf("a. Задать размер матрицы\n");
    printf("b. Заполнить матрицу\n");
    printf("c. Представление матрицы\n");
    printf("d. Поиск максимального элемента\n");
    printf("e. Сумма элементов меньше k\n");
    printf("f. Сумма главной диагонали\n");
    printf("g. Выход\n");
    printf("===========================\n");
    printf("Выберите пункт: ");
}

int main(void)
{
    size_t rows, cols;
    char choice;

    int running = 1;

    // Внешний цикл: создание матрицы
    while (running)
    {
        printf("\nВведите количество строк: ");

        if (scanf("%zu", &rows) != 1)
        {
            printf("Ошибка ввода!\n");
            clear_input();
            break;
        }

        printf("Введите количество столбцов: ");

        if (scanf("%zu", &cols) != 1)
        {
            printf("Ошибка ввода!\n");
            clear_input();
            break;
        }

        // Проверка размеров
        if (rows == 0 || cols == 0 ||
            rows > SIZE_MAX / cols ||
            rows * cols > SIZE_MAX / sizeof(int))
        {
            printf("Некорректные размеры матрицы!\n");
            continue;
        }

        // Создание двумерного массива переменной длины
        int matrix[rows][cols];

        int *matptr = &matrix[0][0];

        int filled = 0;
        int change_size = 0;

        printf("Матрица размером %zu x %zu создана.\n",
               rows, cols);

        // Внутренний цикл: меню
        print_menu();

        while (scanf(" %c", &choice) == 1 && choice != 'g')
        {
            switch (choice)
            {
                // Изменение размеров матрицы
                case 'a':
                {
                    change_size = 1;
                    printf("Повторный ввод размеров матрицы.\n");
                    break;
                }

                // Заполнение матрицы
                case 'b':
                {
                    printf("Введите элементы матрицы:\n");

                    int input_error = 0;

                    for (size_t i = 0; i < rows && !input_error; i++)
                    {
                        for (size_t j = 0; j < cols; j++)
                        {
                            printf("Элемент [%zu][%zu]: ", i, j);

                            if (scanf("%d", &matrix[i][j]) != 1)
                            {
                                printf("Ошибка ввода!\n");
                                clear_input();
                                input_error = 1;
                                break;
                            }
                        }
                    }

                    if (!input_error)
                    {
                        filled = 1;
                        printf("Матрица успешно заполнена.\n");
                    }

                    break;
                }

                // Просмотр матрицы и адресов элементов
                case 'c':
                {
                    if (!filled)
                    {
                        printf("Сначала заполните матрицу!\n");
                        break;
                    }

                    printf("\nМатрица:\n");

                    for (size_t i = 0; i < rows; i++)
                    {
                        for (size_t j = 0; j < cols; j++)
                        {
                            printf("%6d ", matrix[i][j]);
                        }

                        printf("\n");
                    }

                    printf("\nАдреса элементов:\n");

                    for (size_t i = 0; i < rows; i++)
                    {
                        for (size_t j = 0; j < cols; j++)
                        {
                            printf("[%zu][%zu]: %p\n", i, j, (void *)&matrix[i][j]);
                        }
                    }

                    break;
                }

                // Поиск максимального элемента
                case 'd':
                {
                    if (!filled)
                    {
                        printf("Сначала заполните матрицу!\n");
                        break;
                    }

                    size_t max_row, max_col;

                    if (find_max_element(matptr, rows, cols, &max_row, &max_col) == 0)
                    {
                        printf("Максимальный элемент: %d\n",
                               matrix[max_row][max_col]);

                        printf("Строка: %zu\n", max_row);
                        printf("Столбец: %zu\n", max_col);
                    }
                    else
                    {
                        printf("Ошибка поиска максимального элемента!\n");
                    }

                    break;
                }

                // Сумма элементов меньше k
                case 'e':
                {
                    if (!filled)
                    {
                        printf("Сначала заполните матрицу!\n");
                        break;
                    }

                    int k, sum;

                    printf("Введите k: ");

                    if (scanf("%d", &k) != 1)
                    {
                        printf("Ошибка ввода!\n");
                        clear_input();
                        break;
                    }

                    if (sum_less_than_k(matptr, rows, cols, k, &sum) == 0)
                    {
                        printf("Сумма элементов меньше %d: %d\n",
                               k, sum);
                    }
                    else
                    {
                        printf("Ошибка вычисления суммы!\n");
                    }

                    break;
                }

                // Сумма главной диагонали
                case 'f':
                {
                    if (!filled)
                    {
                        printf("Сначала заполните матрицу!\n");
                        break;
                    }

                    int sum;

                    if (sum_main_diagonal(matptr, rows, cols, &sum) == 0)
                    {
                        printf("Сумма элементов главной диагонали: %d\n",
                               sum);
                    }
                    else
                    {
                        printf("Ошибка вычисления суммы!\n");
                    }

                    break;
                }

                default:
                {
                    printf("Неизвестный пункт меню!\n");
                    break;
                }
            }

            // Если выбрали изменение размеров, выходим из внутреннего цикла
            if (change_size)
                break;

            print_menu();
        }

        // Если ввод завершился или выбрали выход
        if (choice == 'g' || !change_size)
            running = 0;
    }

    printf("\nПрограмма завершена.\n");
    return 0;
}