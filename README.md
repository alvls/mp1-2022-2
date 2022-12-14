# mp1-2022-2
Центральный репозиторий практики группы 22Б1ПР1 по курсу МП1

Ссылка на таблицу с баллами по СР и ЛР: https://clck.ru/325UuM

# Задание 1

Фирма «Умелые ручки» выпускает двухдверные одежные шкафы.

Состав шкафа:
- накладная задняя стенка из ДВП высотой h от 180 до 220 см, шириной w от 80 до 120 см и толщиной 5 мм,
- две боковины из ДСП высотой h, глубиной d от 50 до 90 см и толщиной 15 мм,
- накладные верхняя и нижняя крышки из ДСП шириной w, глубиной d и толщиной 15 мм,
- две накладные двери из дерева высотой h, общей шириной w и толщиной 1 см,
- внутренние полки в шкафу через каждый 40 см из ДСП.

Считая, что известны плотности ДСП, ДВП и дерева, найти массу шкафа в килограммах.

# Задание 2

Разработать программу «Угадай число».

В программе должно быть предусмотрено два режима.

**Режим 1**. Программа «загадывает» случайное число из диапазона от 1 до 1000. Пользователь должен вводить отгадки, на которые программа сообщает: «загаданное число больше», «загаданное число меньше», «угадали». Работа завершается, когда пользователь угадает число. Также программа должна подсчитывать число попыток и выводить его в конце работы.

**Режим 2**. Пользователь загадывает число из диапазона от 1 до 1000 и вводит его. Программа пытается «угадать» число, выводя на экран отгадки, на которые пользователь вводит >, < или =. Работа завершается, когда программа угадает число. Также программа должна подсчитывать число попыток и выводить его в конце работы. 

В режиме 2 считать, что пользователь ведет игру честно.

# Задание 3

Разработать программу, реализующую игру «Быки и коровы».

**Требования (правила)**
* Играют два игрока (человек и компьютер).
* Игрок выбирает длину загадываемого числа – n (от 2 до 5).
* Компьютер «задумывает» n-значное число с неповторяющимися цифрами.
* Игрок делает попытку отгадать число – вводит n-значное число с неповторяющимися цифрами.
* Компьютер сообщает, сколько цифр угадано без совпадения с их позициями в загаданном числе (то есть количество коров) и сколько угадано вплоть до позиции в загаданном числе (то есть количество быков).
* Игрок делает попытки, пока не отгадает всю последовательность или не сдастся.

**Пример**
* Пусть n = 4.
* Пусть задумано число «3219».
* Игрок ввел число «2310».
* Результат: две «коровы» (две цифры: «2» и «3» — угаданы, но находятся на других позициях) и один «бык» (одна цифра «1» угадана и находится на верной позиции).

# Задание 3'
Тем, кто быстро сделает задание 3, предлагаю дополнительную задачу.

Разработать для игры "Быки и коровы" интерфейс пользовательля с использованием возможностей по управлению консолью в Windows.

В качестве примера можно использовать написанную мной когда-то небольшую библиотеку функций (см. [Console.c](https://cloud.unn.ru/s/r473ZRGAb9C39Pf)).

# Задание 4

Разработать программу «Электронная касса».

Программа должна имитировать работу кассового аппарата по сканированию товаров и формированию чека за покупку.

Каждый товар идентифицируется штрих-кодом. Штрих-код хранится в виде массива из четырех символов. Каждый символ принимает значение от ‘0’ до ‘9’.

Один и тот же товар может сканироваться несколько раз, но в чек информация о каждом товаре входит в виде: «наименование – стоимость за единицу (для упрощения в рублях без копеек) – количество – общая стоимость за товар».

Чек состоит не менее чем из одной записи указанного вида. Чек дополнительно включает общую стоимость товаров в покупке, суммарную скидку и итоговую сумму к оплате (все в рублях).

Каждый товар описывается штрих-кодом, наименованием, стоимостью за единицу товара, скидкой в процентах от стоимости. Скидки устанавливаются на каждый товар независимо (в диапазоне от 5% до 50% с шагом 5%).

Программа должна предоставлять следующие операции:

- «сканировать» очередной товар,
- вывести описание отсканированного товара,
- добавить данные о товаре в чек, 
- сформировать чек за покупку, 
- рассчитать итоговую сумму к оплате.

# Задание 5

Разработать прототип файлового менеджера с функцией показа файлов в заданном каталоге, упорядоченных по возрастанию/убыванию размера.

Входные данные:
- Путь до директории, в которой необходимо отсортировать содержимое.
- Метод сортировки.

Выходные данные:
- Отсортированный список имен файлов с указанием размера.
- Время сортировки.

Программа должна предоставлять пользователю возможность сменить метод сортировки и повторно формировать выходные данные.

Программа должна реализовывать диалог с пользователем посредством интерфейса, который включает:
- возможность ввода пути до заданного каталога;
- возможность выбора метода сортировки;
- возможность просмотра отсортированного списка файлов с указанием размера.

Cписок методов сортировки:
1. "пузырьком": http://algolist.manual.ru/sort/bubble_sort.php
1. "выбором": http://algolist.manual.ru/sort/select_sort.php
1. "вставками": http://algolist.manual.ru/sort/insert_sort.php
1. "слиянием": http://algolist.manual.ru/sort/merge_sort.php
1. "Хоара": http://algolist.manual.ru/sort/quick_sort.php
1. "Шелла": http://algolist.manual.ru/sort/shell_sort.php
1. "подсчетом": https://ru.wikipedia.org/wiki/%D0%A1%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0_%D0%BF%D0%BE%D0%B4%D1%81%D1%87%D1%91%D1%82%D0%BE%D0%BC

# Работа с файлами в выбранном каталоге

Для выполнения Задания 5 требуется получать информацию об именах и некоторых параметрах файлов в выбранном каталоге.
Прикладываю программу, которую можно использовать, как пример.

```c++
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  
#include <time.h>  

int main(void)
{
  struct _finddata_t c_file;
  intptr_t hFile;
  char path[200];
  int count = 0;

  // Find first file in directory c:\temp
  if ((hFile = _findfirst("c:\\temp\\*.*", &c_file)) == -1L)
    printf("No files in current directory!\n");
  else
  {
    printf("Listing of .c files\n\n");
    printf("FILE         DATE %24c   SIZE\n", ' ');
    printf("----         ---- %24c   ----\n", ' ');
    do {
      char buffer[30];
      ctime_s(buffer, _countof(buffer), &c_file.time_write);
      if (count <= 20)
        printf("%-12.12s %.24s  %10ld\n", c_file.name, buffer, c_file.size);
      count++;
    } while (_findnext(hFile, &c_file) == 0);
    _findclose(hFile);
    printf("\ncount of files: %d", count);
  }
}
```

# Задание 6

Разработать программу, позволяющую выполнять расчет значений для некоторого набора функций в заданной точке с заданной погрешностью за счет разложения этих функций в ряд Тейлора.

Программа должна работать в двух режимах:
- Однократный расчет функции в заданной точке.
- Серийный эксперимент.

*При работе в режиме 1* пользователь должен иметь возможность:

* выбрать функцию,
* задать точку x, в которой необходимо вычислить значение,
* задать точность вычисления (>= 0.000001),
* задать число элементов ряда для выполнения расчета (N - от 1 до 1000).

Расчет оценки значения выбранной функции выполняется либо до достижения заданной точности, либо до исчерпания введенного числа слагаемых. По результатам расчета программа должна вывести следующую информацию:

* эталонное значение (полученное с использованием встроенных математических функций языка программирования С),
* вычисленную оценку значения функции,
* разницу между оценкой и эталонным значением,
* количество слагаемых, которое было вычислено.

*При работе в режиме 2* пользователь должен иметь возможность:

* выбрать функцию,
* задать точку x, в которой необходимо вычислить значение,
* задать число экспериментов (NMax - от 1 до 25).

По результатам расчета программа должна вывести следующую информацию:

* эталонное значение (полученное с использованием встроенных математических функций языка программирования С),
* таблицу из NMax строк со следующими столбцами: кол-во слагаемых (от 1 до NMax), вычисленную оценку значения функции, разницу между оценкой и эталонным значением.

*Технические требования:*

* Каждый студент должен реализовать расчет функций sin(x), cos(x), exp(x) и одной уникальной функции из списка ниже. Номер требуемой функции совпадает с номером в списке группы.
* По желанию можно выбрать дополнительные функции, кроме 4-х обязательных.
* Расчет функций должен быть реализован в виде функций языка С.
* В программе должен быть использован тип указатель на функцию.
* В программе желательно использовать модули.

## Уникальные функции:
1. Квадратный корень из 1+х - (1+x)^(1/2)
1. Логарифм от 1+х - ln(1+x)
1. Тангенс - tg(x)
1. Котангенс - ctg(x)
1. Арксинус - arcsin(x)
1. Арккосинус - arccos(x)
1. Арктангенс - arctg(x)
1. Арккотангенс - arcctg(x)
1. Гиперболический синус - sh(x)
1. Гиперболический косинус - ch(x)
1. Гиперболический тангенс - th(x)
1. Гиперболический котангенс - cth(x)
1. Обратный гиперболический синус - arsh(x)
1. Обратный гиперболический тангенс - arth(x)
1. Секанс - sec(x)
1. Косеканс - csc(x)
