/*

Файл называется "Graph10_main.c"

Назначение программы: находить путь передачи книги так,
чтобы она была у всех в руках и вернулась владельцу.

Назначение файла: считать кол-во человек (размер смежной матрицы)
и начальную вершину; вызвать функции создания матрицы смежности и нахождения пути книги.

Автор: Власов Евгений Максимович, группа ИВТ-13БО.
*/

#include <stdio.h>
#include <locale.h>
#include "Graph10_lib.h"
#define _CRT_SECURE_NO_WARNINGS
#define N 100

void main()
{
	
	//n- кол-во человек(размер матрицы смежности), А - матрица смежности,
	//start_vertex - стартовая вершина.
	int n;
	int A[N][N];
	int start_vertex;
	//Считываем кол-во человек и проверяем правильность ввода.
	printf_s("N:");
	if (!scanf_s("%d", &n)) {
		printf_s("This is not number\n");
		system("pause");
		exit(0);
	}
	if (n > 100 || n <= 1)
	{
		printf_s("Wrong number\n");
		system("pause");
		exit(0);
	}
	//Создание матрицы смежности.
	CreateAndCheckAdjacentMatrix(A, n);
	 
	//Считываем начальную вершину.
	printf_s("Start vertex:");
	if (!scanf_s("%d", &start_vertex)) {
		printf_s("This is not number.\n");
		system("pause");
		exit(0);
	}
	if (start_vertex >= n || start_vertex < 0) {
		printf_s("Incorrect start vertex.\n");
		system("pause");
		exit(0);
	}

	//Нахождение путей книги.
	FindingPaths(A, n, start_vertex);
	system("pause");
}

/*

Трудоёмкость: O((n-1)!).
n - размер матрицы смежности

Тесты:

2
1
0

3
1
1
1
0

4
1
0
1
1
0
1
0

5
1
0
0
1
1
0
0
1
0
1
0

6
1
0
1
0
1
1
0
1
0
1
0
1
1
0
1
0

8
0
1
0
0
1
1
1
0
1
1
0
1
1
1
0
1
1
0
1
1
0
0
1
0
1
0
0
1
0

9
1
0
0
0
0
0
1
0
1
0
0
0
0
1
0
1
0
1
0
0
1
1
1
0
0
0
1
0
0
0
1
0
0
1
1
1
0
*/
