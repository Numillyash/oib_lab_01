#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#include <conio.h>

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

    for (int i = 0; i < length - 1; i++)
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

int main() {
    setlocale(LC_ALL, "rus");

    task1();

    char fio[] = "Улановский Георгий Алексеевич";
    task2(fio, 33, 3);

    _getch();
    return 0;
}
