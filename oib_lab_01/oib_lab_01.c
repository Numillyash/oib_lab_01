#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG

#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef DEBUG
#include <conio.h>
#endif // DEBUG

#define bool char
#define true 1
#define false 0
#define elif else if

int N_gr = 313; // Номер группы
int N_sp = 20; // Порядковый номер ученика в группе
int F_3 = 1; // Порядковый номер третей буквы фамилии в алфавите

/// <summary>
/// Функция для нахождения остатка от деления большого числа на малое
/// </summary>
/// <param name="a">Делимое</param>
/// <param name="b">Делитель</param>
/// <returns>Остаток</returns>
int del_ost(double a, int b)
{
    double c = a / b, prom;

    modf(c, &c);
    a -= b * c;
    if (a == 0)
        return 0;
    else
        return (int)a;
}

/// <summary>
/// Функция для нахождения остатка от деления большого числа (число a в степени t) на малое
/// </summary>
/// <param name="a">Делимое</param>
/// <param name="t">Делимое</param>
/// <param name="b">Делитель</param>
/// <returns>Остаток</returns>
int del_ost_pow(double a, double t, int b)
{
    int d = del_ost(a, b);
    int ost = d;

    if (d == 0)
        return 0;
    else
        for (int i = 1; i < t; i++)
        {
            ost = (ost*d) % b;
        }
    return ost;
}

/// <summary>
/// Подпрограмма, выполняющая задачу 1 
/// </summary>
void task1()
{
    int r1 = (int)((unsigned long long)(pow((N_gr + N_sp), 11) + F_3) % 11);
    printf("%d\n", r1);
}

/// <summary>
/// Подпрограмма, выполняющая задачу 2
/// </summary>
/// <param name="string">Строка с ФИО</param>
/// <param name="m">Мощность алфавита</param>
/// <param name="k">Сдвиг для шифра Цезаря</param>
void task2(const char* string, int m, int k)
{
    int symb_first_small = (int)'а';
    int symb_first_big = (int)'А';
    int length = strlen(string);
    // x -> (x+k)mod m
    int numb, rot_numb;
    char rot_symb;

    for (int i = 0; i < length; i++)
    {
        if (string[i] >= 'А' && string[i] <= 'Я')
        {
            numb = (int)string[i] - symb_first_big;
            rot_numb = (numb + k) % m;
            rot_symb = (char)(rot_numb + symb_first_big);
            printf("%c", rot_symb);
        }
        elif(string[i] >= 'а' && string[i] <= 'я')
        {
            numb = (int)string[i] - symb_first_small;
            rot_numb = (numb + k) % m;
            rot_symb = (char)(rot_numb + symb_first_small);
            printf("%c", rot_symb);
        }
        else
            printf("%c", ' ');
    }
    printf("\n");
}

/// <summary>
/// Алгоритм Евклида для двух целых чисел
/// </summary>
/// <param name="a">Первое число</param>
/// <param name="b">Второе число</param>
/// <returns>НОД трех чисел</returns>
int euclide_algorithm(int a, int b)
{
    if (a < b)
    {
        int _ = b;
        b = a;
        a = _;
    }
    //a = b * q_0 + r_1
    int r = a % b;
    #ifdef DEBUG
    printf("%d = %d * %d + %d\n", a, b, a/b, a%b);
    #endif // DEBUG

    if (r != 0)
        euclide_algorithm(b, r);
    else
        return b;
}

/// <summary>
/// Алгоритм Евклида для трех целых чисел
/// </summary>
/// <param name="a">Первое число</param>
/// <param name="b">Второе число</param>
/// <param name="c">Третье число</param>
/// <returns>НОД трех чисел</returns>
int euclide_algorithm_three(int a, int b, int c)
{
    int o_del = euclide_algorithm(a, b);
    if (o_del == 1)
        return 1;
    else
        return euclide_algorithm(c, o_del);
}

/// <summary>
/// Подпрограмма, выполняющая задачу 3
/// </summary>
void task3()
{
    int A = pow(N_gr * (8 + N_sp % 7),2);
    int B = 11032004;
    //printf("%d\n", r1);

    printf("%d\n", euclide_algorithm(A, (B % 95) + 900));
    printf("%d\n", euclide_algorithm(A, ((B + 50) % 97) + 700));
    printf("%d\n", euclide_algorithm_three(A, ((B + 20) % 101) + 1500, ((B -40) % 103) + 2500));
}

bool millers_method(int N)
{
    //N-1 = 2^s * t, t - нечетно
    int s = 0;
    int t = N - 1;
    while (t % 2 == 0)
    {
        t >>= 1;
        s++;
    }

#ifdef DEBUG
    printf("N-1 = 2^%d * %d\n", s, t);
#endif // DEBUG

    srand(time(NULL));
    int n = 1000;
    int a;
    bool fl1, fl2;
    for (int i = 0; i < n; i++)
    {
        fl1 = true; fl2 = true;

        a = 2 + rand()%(N-2);

        if (euclide_algorithm(N, a) != 1) //свойство 1
        {
            fl1 = false;
#ifdef DEBUG
            printf("\nУсловие 1 нарушено, a = %d, t = %d, N = %d. \nN кратно a", a, t, N);
#endif // DEBUG
        }            

        if (del_ost_pow(a, t, N) != 1) // свойство 2
        {
            int k = 1;
            fl2 = false;
            for (k = 1; k <= s; k++)
            {
                if (del_ost_pow(a, t * pow(2, k - 1), N) == N - 1)
                {
                    fl2 = true;
                }
            }
        #ifdef DEBUG
            if(fl2 == false)
                printf("\nУсловие 2 нарушено, a = %d, t = %d, k = %d, N = %d. \nМодули чисел: без k %d, с k %d", a, t, k, N, del_ost_pow(a, t, N), del_ost_pow(a, t * pow(2, k - 1), N));
        #endif // DEBUG
        }

        if (!fl1 || !fl2)
        {
#ifdef DEBUG
            printf("\n%s", (fl1 == false) ? "Условие 1 нарушено" : "Условие 1 не нарушено");
            printf("\n%s\n", (fl2 == false) ? "Условие 2 нарушено" : "Условие 2 не нарушено");
#endif // DEBUG
            return true;
        }
    }
    return false;
}

/// <summary>
/// Подпрограмма, выполняющая задачу 4
/// </summary>
void task4()
{
    int N = 10483;
    printf("%d: %s\n", N, (millers_method(N) == 1) ? "Составное" : "Простое");
    int N1 = 487;
    printf("%d: %s\n", N1, (millers_method(N1) == 1) ? "Составное" : "Простое");
}

int main() {
    setlocale(LC_ALL, "rus");

    /*
    task1();

    char fio[] = "Улановский Георгий Алексеевич";
    task2(fio, 32, 3);

    task3();

    task4();
    */


    #ifdef DEBUG
    _getch();
    #endif // DEBUG

    return 0;
}
