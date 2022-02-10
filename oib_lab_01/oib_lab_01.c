#define _CRT_SECURE_NO_WARNINGS
#define DEBUG

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
    double c = a / b;

    modf(c, &c);
    a -= (double)b * c;
    if (a == 0)
        return 0;
    else
        return ((int)a < 0)? a+b : a;
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
    double d = del_ost(a, b);
    double ost = d;

    if (d == 0)
        return 0;
    else
        for (int i = 1; i < t; i++)
        {
            ost = del_ost(ost*d, b);
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
    k = k % m;

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
    if (abs(a) < abs(b))
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

int euclide_algorithm_modifyed(int s, int t, int *a) {
    if (s < t)
    {
        int _ = t;
        t = s;
        s = _;
    }
    //s = t * q_0 + r_1
    int r = s % t;
    int q = s / t;
    #ifdef DEBUG
    printf("%d = %d * %d + %d\n", s, t, s / t, s % t);
    #endif // DEBUG

    if (r != 0)
    {
        euclide_algorithm_modifyed(t, r, a);
        int _a, _b, _c, _d;
        _a = a[0];
        _b = a[1];
        _c = a[2];
        _d = a[3];
        a[0] = _b;
        a[1] = _a - _b * q;
        a[2] = _d;
        a[3] = _c - _d * q;
    }
    else
    {
        int _a, _b, _c, _d;
        _a = a[0];
        _b = a[1];
        _c = a[2];
        _d = a[3];
        a[0] = _b;
        a[1] = _a - _b * q;
        a[2] = _d;
        a[3] = _c - _d * q;
        return t;
    }
}

/// <summary>
/// Подпрограмма, выполняющая задачу 5
/// </summary>
void task5()
{
    int p = 3557, q = 2579;
    int n = p * q;
    int phi_n = (p - 1) * (q - 1); //9173503
    int e = 67;
    
    int a[4] = {1,0,0,1};
    euclide_algorithm_modifyed(phi_n, e, a);
    #ifdef DEBUG
    printf("|%d %d|\n|%d %d|\n", a[0], a[1], a[2], a[3]);
    #endif // DEBUG

    int d = a[1]; // 2462875

#ifdef DEBUG
    printf("e = %lf, d = %lf, e*d = %lf, phi_n = %lf\n", (double)e, (double)d, (double)e * (double)d, (double)phi_n);
    printf("%d\n", del_ost((double)e * (double)d, phi_n));
#endif // DEBUG
}

/// <summary>
/// Подпрограмма, выполняющая задачу 6
/// </summary>
void task6(char* x)
{
    int p = 3557, q = 2579;
    int n = p * q; // 9173503
    int e = 67;
    int phi_n = (p - 1) * (q - 1); //9173503
    int d = 2462875; //взято из расчетов задачи 5
    int str_len = strlen(x);

    int* xy = (int*)malloc(str_len);
    char* xyx = (char*)malloc(str_len+1);

    for (int i = 0; i < str_len; i++)
    {
        int symb = (int)x[i];
        xy[i] = del_ost_pow(symb,e,n);
    }
    for (int i = 0; i < str_len; i++)
    {
        int symb = xy[i];
        xyx[i] = (char)del_ost_pow(symb, d, n);
    }
    xyx[str_len] = '\0';

#ifdef DEBUG
    for (int i = 0; i < str_len; i++)
    {
        printf("%d ", (int)x[i]);
    }
    printf("\n");
    for (int i = 0; i < str_len; i++)
    {
        printf("%d ", (int)xy[i]);
    }
    printf("\n");
    for (int i = 0; i < str_len; i++)
    {
        printf("%d ", (int)xyx[i]);
    }
    printf("\n");
#endif // DEBUG


    printf("%s\n", xyx);
}

int main() {
    setlocale(LC_ALL, "rus");

    /*
    task1();

    char fio[] = "Улановский Георгий Алексеевич";
    task2(fio, 32, 3);

    task3();

    task4();
    
    task5();
    
    fio[] = "Numillyash";
    task6(fio);
    */
    #ifdef DEBUG
    _getch();
    #endif // DEBUG

    return 0;
}
