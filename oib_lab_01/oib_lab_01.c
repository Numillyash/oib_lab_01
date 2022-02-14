#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG

#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
        return ((int)a < 0) ? a + b : a;
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
            ost = del_ost(ost * d, b);
        }
    return ost;
}

/// <summary>
/// Подпрограмма, выполняющая задачу 1 
/// </summary>
void task1()
{
    int r1 = del_ost(F_3 + del_ost_pow((N_gr + N_sp), 11, 11), 11);

    printf("Задание #1.\nN_gr = %d, N_sp = %d, F_3 = %d\nResult: %d\n\n", N_gr, N_sp, F_3, r1);
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

    printf("Задание #2.\nИсходная строка = %s\nМощность алфавита: %d\nСдвиг: %d\nЗашифрованная строка (без учета буквы ё): ", string, m, k);
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
    printf("\n\n");
}

/// <summary>
/// Алгоритм Евклида для двух целых чисел
/// </summary>
/// <param name="a">Первое число</param>
/// <param name="b">Второе число</param>
/// <returns>НОД двух чисел</returns>
int euclide_algorithm(int a, int b)
{
    //a = b * q_0 + r_1
    if (abs(a) < abs(b))
    {
        int _ = b;
        b = a;
        a = _;
    }
    int r = a % b;

#ifdef DEBUG
    printf("%d = %d * %d + %d\n", a, b, a / b, a % b);
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
    int A = pow(N_gr * (8 + N_sp % 7), 2);
    int B = 11032004;

    printf("Задание #3.\nЧисло А = %d\nЧисло В: %d\n", A, B);
    printf("НОД(А, В(mod 95) + 900) = %d\n", euclide_algorithm(A, (B % 95) + 900));
    printf("НОД(А, (В+50)(mod 97) + 700) = %d\n", euclide_algorithm(A, ((B + 50) % 97) + 700));
    printf("НОД(А, (В+20)(mod 101) + 1500, (В-40)(mod 103) + 2500) = %d\n\n", euclide_algorithm_three(A, ((B + 20) % 101) + 1500, ((B - 40) % 103) + 2500));
}

/// <summary>
/// Подпрограмма, проверяющая число на "простоту" с помощью метода Миллера
/// </summary>
/// <param name="N">Число, которое необходимо проверить</param>
/// <returns>1 - если число составное, 0 - если число простое</returns>
bool millers_method(int N)
{
    //N-1 = 2^s * t, t - нечетно
    int s = 0;
    int t = N - 1;

    while (t & 1 == 0)
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
        a = 2 + rand() % (N - 2);
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
            if (fl2 == false)
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
    printf("Задание #4.\n");
    int N = 10483;
    printf("По методу миллера посчитано, что число %d: %s\n", N, (millers_method(N) == 1) ? "Составное" : "Простое");
    int N1 = 487;
    printf("По методу миллера посчитано, что число %d: %s\n\n", N1, (millers_method(N1) == 1) ? "Составное" : "Простое");
}

/// <summary>
/// Модифицированный алгоритм Евклида.
/// </summary>
/// <param name="s">Первое число для НОД</param>
/// <param name="t">Второе число для НОД</param>
/// <param name="a">Массив, в котором хранится матрица для матричного представления алгоритма Евклида</param>
/// <returns>НОД двух чисел</returns>
int euclide_algorithm_modified(int s, int t, int* a) {
    if (s < t)
    {
        int _ = t;
        t = s;
        s = _;
    }

    int r = s % t;
    int q = s / t;

#ifdef DEBUG
    printf("%d = %d * %d + %d\n", s, t, s / t, s % t);
#endif // DEBUG

    if (r != 0)
    {
        euclide_algorithm_modified(t, r, a);
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
    int a[4] = { 1,0,0,1 };

    printf("Задание #5.\nЧисло p = %d, число q = %d\nЧисло n = %d\nф(n) = %d\ne = %d\n", p, q, n, phi_n, e);
    euclide_algorithm_modified(phi_n, e, a);
    int d = a[1]; // 2462875
    printf("d = %d\n\n", d);
}

/// <summary>
/// Подпрограмма, выполняющая задачу 6
/// </summary>
/// <param name="x">Строка, которую необходимо зашифровать</param>
void task6(char* x)
{
    int p = 3557, q = 2579;
    int n = p * q; // 9173503
    int e = 67;
    int phi_n = (p - 1) * (q - 1); //9173503
    int d = 2462875; //взято из расчетов задачи 5
    int str_len = strlen(x);

    printf("Задание #6.\nИсходная строка: %s\nЗакодированная строка: ", x);
    int* xy = (int*)malloc(str_len);
    char* xyx = (char*)malloc(str_len + 1);
    for (int i = 0; i < str_len; i++)
    {
        int symb = (int)x[i];
        xy[i] = del_ost_pow(symb, e, n);
        printf("%d ", xy[i]);
    }
    printf("\nРаскодированная строка: ");
    for (int i = 0; i < str_len; i++)
    {
        int symb = xy[i];
        xyx[i] = (char)del_ost_pow(symb, d, n);
    }
    xyx[str_len] = '\0';
    printf("%s\n\n", xyx);
}

/// <summary>
/// Подпрограмма, выполняющая задачу 7
/// </summary>
void task7(char* x)
{
    int p = 3557, q = 2579;
    int n = p * q; // 9173503
    int e = 67;
    int phi_n = (p - 1) * (q - 1); //9173503
    int d = 2462875; //взято из расчетов задачи 5
    int str_len = strlen(x);

    printf("Задание #7.\nИсходная строка: %s\nПодпись s: ", x);
    int* xy = (int*)malloc(str_len);
    char* xyx = (char*)malloc(str_len + 1);
    for (int i = 0; i < str_len; i++)
    {
        int symb = (int)x[i];
        xy[i] = del_ost_pow(symb, d, n);
        printf("%d ", xy[i]);
    }
    printf("\nРаскодированная подпись: ");
    for (int i = 0; i < str_len; i++)
    {
        int symb = xy[i];
        xyx[i] = (char)del_ost_pow(symb, e, n);
    }
    xyx[str_len] = '\0';
    printf("%s\n\n", xyx);
}

/// <summary>
/// Подпрограмма, выполняющая задачу 8
/// </summary>
/// <param name="a">Параметр а для сеансового ключа</param>
void task8(int a)
{
    int p = 3557, q = 2579;
    int n = p * q; // 9173503
    int e = 67;
    int phi_n = (p - 1) * (q - 1); //9173503
    int d = 2462875; //взято из расчетов задачи 5

    int x = 2 + rand() % (phi_n - 2);
    int y = 2 + rand() % (phi_n - 2);
    int A = del_ost_pow(a, x, n);
    int B = del_ost_pow(a, y, n);
    int key = del_ost_pow(a, x * y, n);

    int ax_y = del_ost_pow(del_ost_pow(a, x, n), y, n);
    int ay_x = del_ost_pow(del_ost_pow(a, y, n), x, n);

    printf("Задание #8.\nЧисло x, число А: %d, %d\nЧисло y, число В: %d, %d\n", x, A, y, B);
    printf("(a^x)^y = %d (mod %d)\n(a^y)^x = %d (mod %d)\na^(y*x) = %d (mod %d)\n\n", ax_y, n, ay_x, n, key, n);
}

/// <summary>
/// Подпрограмма, выполняющая задачу 9. 
/// <para>Утилита шифрования/дешифрования, алгоритм Меркля-Хеллмана</para>
/// </summary>
int task9()
{
    int closed_key[] = { 2, 3, 6, 13, 27, 52, 105, 210 };
    int m = 420;
    int n = 37;
    int key = 0;
    int a[4] = { 1,0,0,1 };
    euclide_algorithm_modified(m, n, a);
    key = a[1];
    int opened_key[8];
    
    printf("m = %d, n = %d\nОткрытый ключ: { ",m,n);
    for (int i = 0; i < 8; i++)
    {
        opened_key[i] = (closed_key[i] * n) % m;
        printf("%d ", opened_key[i]);
    }
    printf("}\n");

    printf("Введите 'ш' чтобы шифровать или 'д' чтобы дешифровать : ");
    char ans;
    scanf("%c", &ans);
    if (ans == 'ш')
    {
        system("cls");
        printf("Введите сообщение (не более 10 символов) : ");
        unsigned char text[11];
        scanf("%11s%*[^\n]%*c", text);
        int str_len = strlen(text);
        int* cipher_text = (int*) malloc(str_len);

        
        for (int i = 0; i < str_len; i++)
        {
            cipher_text[i] = 0;
        }

        for (int i = 0; i < str_len; i++)
        {
            int code = (int)text[i];
            for (int j = 7; j >= 0; j--)
            {
                cipher_text[i] += (code & 1) * opened_key[j];
                code >>= 1;    
            }
            printf("Шифротекст для %c (%d) : %d\n", text[i], (int)text[i], cipher_text[i]);
        }
    }
    elif(ans == 'д')
    {
        system("cls");
        printf("Введите число символов в сообщении : ");
        int str_len;
        scanf("%d%*[^\n]%*c", &str_len);
        unsigned char* uncipher_text = (unsigned char*)malloc(str_len+1);
        int* cipher_text = (int*)malloc(str_len);
        printf("Введите числа сообщения через enter : \n");
        for (int i = 0; i < str_len; i++)
        {
            scanf("%d", &cipher_text[i]);
            uncipher_text[i] = (char)0;
        }

        bool binary_code[8];

        for (int i = 0; i < str_len; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                binary_code[j] = 0;
            }
            int code = (cipher_text[i] * key) % m;
            code = (code < 0) ? code + m : code;
            for (int j = 7; j >= 0; j--)
            {
                if (code >= closed_key[j])
                {
                    binary_code[j] = 1;
                    code -= closed_key[j];
                }
            }
            for (int j = 0; j <=7; j++)
            {
                uncipher_text[i] <<= 1;
                uncipher_text[i] += binary_code[j];
            }
            printf("Буква для %d : %c (%d)\n", cipher_text[i], uncipher_text[i], (int)uncipher_text[i]);
        }
        printf("Сообщение: %s\n", uncipher_text);
    }
    return -1;
}

int main() {
    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

    task1();

    char fio[] = "Улановский Георгий Алексеевич";
    task2(fio, 32, 3);

    task3();

    task4();

    task5();

    char str[] = "Numillyash";
    task6(str);

    task7(str);

    task8(239);
    
    //task9();
    
    return 0;
}
