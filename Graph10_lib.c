/*

Название файла "Graph10_lib.c"

Назначение программы: находить путь передачи книги так,
чтобы она была у всех в руках и вернулась владельцу.

Назначение файла: создать матрицу смежности и найти путь книги.

Автор: Власов Евгений Маскимович, группа ИВТ-13БО.
*/

#include <stdio.h>
#include <locale.h>
#include "Queue.h"
#define _CRT_SECURE_NO_WARNINGS
#define N 100

//Создание смежной матрицы.
int* CreateAndCheckAdjacentMatrix(int A[N][N], int n)
{
	//matrix_element - элемент матрицы (0 - враги (нет связи), 1 - друзья (связь есть)).
	int matrix_element;
	//Создание матрицы смежности.
	for (int i = 0; i < n; i++)
	{
		vertex_degree = 0;
		for (int j = i; j < n; j++)
		{
			//Заполнение главной диагонали матрицы смежности нулями.
			if (i == j)
			{
				A[i][j] = 0;
				continue;
			}

			//Вывод столбца и строки матрицы смежности, чтобы пользователь ввёл число 0 или 1.
			printf_s("\n[%d][%d] -> ", i, j);
			//Считывание введённого числа и его проверка.
			if (!scanf_s("%d", &matrix_element)) {
				printf_s("This is not number.\n");
				system("pause");
				exit(0);
			}
			if (!(matrix_element == 1 || matrix_element == 0)) {
				printf_s("Wrong number.\n");
				system("pause");
				exit(0);
			}
			//Если связь есть, то увеличиваем счетчик связей.
			if (matrix_element == 1)
				vertex_degree++;
			//Заполняем симметричный относитеьно главной диагонали элемент смежной матрицы.
			A[i][j] = matrix_element;
			A[j][i] = matrix_element;
		}
	}
	
        return A;
}

//Нахождение пути книги
int FindingPaths(int A[N][N], int n, int start_vertex)
{
	//Путь.
	int path[N];
	//Уже посещённые узлы.
	int visited[N];
	//Инициализация массивов.
	for (int i = 0; i < n; i++) {
		path[i] = -1;
		visited[i] = 0;
	}
	//Если функция нашла путь, то выписываем его и завершаем цикл, иначе путь не найден.
	if (visit(A, n, start_vertex, path, 0, visited) == 1) {
		for (int i = 0; i < n; i++) {
			printf_s("%d -> ", path[i]);
		}
		printf_s("%d \n", path[0]);
	}
	else {
		printf_s("Not found \n");
	}
}

//Проверка условий теоремы Дирака. Если граф удовлетворяет условию теоремы, то в этом графе есть гамильтонов цикл.
int CheckDiracCondition(int A[N][N], int n) {
    //Если n четно, то dirac_constant = n/2; если n нечетно, то dirac_constant = [n/2]+1 (ближайшее целое сверху).
	int dirac_constant = n / 2 + n % 2;
	int min_vertex_deg = n - 1;

	//Нахождение минимальной степени вершины
	for (int i = 0; i < n; i++)
	{
		int current_deg = 0;
		for (int j = 0; j < n; j++)
		{
			if (A[i][j] == 1) {
				current_deg++;
			}
		}
		if (current_deg < min_vertex_deg) {
			min_vertex_deg = current_deg;
		}
	}
	//Если степень каждой вершины больше чем dirac_constant, гамильтонов цикл существует.
	if (min_vertex_deg < dirac_constant) {
		return 0;
	}
	else {
		return 1;
	}
}

//Алгоритм Палмера нахождения гамильтонова пути в графе, удовлетворяющем условиям теоремы Дирака.
void PalmerAlgorithm(int A[N][N], int n) {
	for (int i = 0; i < n; i++){
		//Заносим в очередь все вершины v1 v2 v3 .... vn и будем постепенно строить гамильтонов цикл.
		enque(i);
	}
	for (int k = 0; k < n * (n - 1); k++) {
		int v0, v1;
		itemAt(0, &v0);
		itemAt(1, &v1);
		if (A[v0][v1] == 0) {
			//Если между первой и второй вершиной в очереди нет связи, то ищем такую вершину vi, что vi связана с v1 и v(i+1) связана с v2.
			//Из теоремы Дирака следует, что такая вершина точно найдется.
			int i = 2;
			int vi, vi1;
			itemAt(i, &vi);
			itemAt(i + 1, &vi1);
			while (A[v0][vi] == 0 || A[v1][vi1] == 0) {
				i++;
				itemAt(i, &vi);
				itemAt(i + 1, &vi1);
			}

			//После того, как нашли нужную вершину, то преобразуем путь следующим образом:
			//v1 v2 ... vi v(i+1) ... vn  --> v1 vi v(i-1) v(i-2) ... v3 v2 v(i+1) ... vn
			//После такого преобразования мы увеличили число пар вершин, которые связаны на 2
			//и быть может уменьшили их количество на 1. В любом случае, число пар после этого шага увеличилось минимум на 1.
			//Всего возможно n пар, поэтому этот шаг будет вызван не более чем n раз. Трудоёмкость шага O(n).
			reverseSubqueue(1, i);

		}
		//Теперь между v1 и v2 есть связь. Перемещаем v1 в конец очереди.
		int head;
		deque(&head);
		enque(head);
	}
	//После выполнения этой процедуры в очереди находится гамильтонов цикл.
	//Всего было n(n-1) итераций, среди которых не более n итераций сложностью O(n), а остальные n(n-2).
	//Итерации выполнялись с трудоёмкостью O(1) т.к. мы просто смотрели в ячейку матрицы. Итоговая трудоёмкость O(n^2).

	//Печатаем цикл.
	int first_vertex;
	peek(&first_vertex);
	while (!isEmpty()){
		int v;
		deque(&v);
		printf_s("%d -> ", v);
	}
	printf_s("%d ", first_vertex);
}

//Нахождение пути книги
int FindingPaths(int A[N][N], int n)
{
	if (CheckDiracCondition(A, n) == 1) {
		//Если для графа выполнены условия теоремы Дирака, то вызываем алгоритм Палмера, который работает только для таких графов.
		printf_s("Executing Palmer's algorithm...\n");
		PalmerAlgorithm(A, n);
		
	}
	else {
		//Если для графа не выполнены условия теоремы Дирака, то вызываем backtracking алгоритм, который работает для любого графа, но является медленным.
		printf_s("Warning! Solution may not exist!\n");
		printf_s("Executing backtracking algorithm...\n");
		int path[N];
		int visited[N];
		for (int i = 0; i < n; i++) {
			path[i] = -1;
			visited[i] = 0;
		}
		if (visit(A, n, 0, path, 0, visited) == 1) {
			for (int i = 0; i < n; i++) {
				printf_s("%d -> ", path[i]);
			}
			printf_s("%d \n", path[0]);
		}
		else {
			printf_s("Not found \n");
		}
	}
}

int visit(int A[N][N], int n, int vertex, int path[N], int path_length, int visited[N]) {
	visited[vertex] = 1;
	path[path_length] = vertex;
	path_length++;
	if (path_length == n) {
		int first_vertex = path[0];
		int last_vertex = path[n-1];
		if (A[first_vertex][last_vertex] == 1) {
			return 1;
		}
		else {
			path_length--;
			path[path_length] = -1;
			visited[vertex] = 0;
			return 0;
		}
	}
	for (int child = 0; child < n; child++) {
		if (A[vertex][child] == 1 && visited[child] == 0) {
			if (visit(A, n, child, path, path_length, visited) == 1) {
				return 1;
			}
		}
	}
	path_length--;
	path[path_length] = -1;
	visited[vertex] = 0;
	return 0;
}

