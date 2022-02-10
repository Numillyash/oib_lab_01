#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#include <conio.h>

//#define DEBUG
#define elif else if

int N_gr = 3; // Номер группы
int N_sp = 20; // Порядковый номер ученика в группе
int F_3 = 1; // Порядковый номер третей буквы фамилии в алфавите

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
int euclide_algorithm(int a, int b, int c)
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
    printf("%d\n", euclide_algorithm(A, ((B + 20) % 101) + 1500, ((B -40) % 103) + 2500));
}

int main() {
    setlocale(LC_ALL, "rus");

    task1();

    char fio[] = "Улановский Георгий Алексеевич";
    task2(fio, 32, 3);

    task3();
    _getch();
    return 0;
}
