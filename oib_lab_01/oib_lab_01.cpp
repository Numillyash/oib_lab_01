#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string.h>

#define elif else if

int N_gr = 3;
int N_sp = 20;
int F_3 = 1;

void Ciesar_sipher(const char* string)
{
    int m = 33; // мощность массива
    int k = 3; // сдвиг
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
}

int main() {
    setlocale(LC_ALL, "rus");
    char fio[] = "Улановский Георгий Алексеевич";

    int r1 = (int)((unsigned long long)(pow((N_gr + N_sp), 11) + F_3) % 11);
    printf("%d\n", r1);
    printf("%s\n", fio);

    Ciesar_sipher(fio);

    scanf("%d");
    return 0;
}
