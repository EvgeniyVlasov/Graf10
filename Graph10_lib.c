/*

Название файла "Graph10_lib.c"

Назначение программы: находить путь передачи книги так,
чтобы она была у всех в руках и вернулась владельцу.

Назначение файла: создать матрицу смежности и найти путь книги.

Автор: Власов Евгений Маскимович, группа ИВТ-13БО.
*/

#include <stdio.h>
#include <locale.h>
#define _CRT_SECURE_NO_WARNINGS
#define N 100

//Создание смежной матрицы.
int* CreateAndCheckAdjacentMatrix(int A[N][N], int n)
{
	//connection - числа в матрице (0 - враги (нет связи), 1 - друзья (связь есть)).
	
	//Число связей каждой вершины (если степень каждой вершины больше чем dirac_constant, нужный путь существует).
	//Если n четно, то dirac_constant = n/2; если n нечетно, то dirac_constant = [n/2]+1 (ближайшее целое сверху).
	int dirac_constant = n/2+n%2;
	int min_vertex_degree = n-1;
	int vertex_degree;
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
		//Находим вершину с минимальный кол-вом связей.
		if (vertex_degree < min_vertex_degree) {
			min_vertex_degree = vertex_degree;
		}
	}
	//Если минимальое число связей вершины меньше константы Дирака,
	//то предупреждение о том, что путь может быть не найден.
	if (min_vertex_degree < dirac_constant) {
		printf_s("Warning! Solution may not exist!\n");
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

//Функция нахождения нужного пути.
static int visit(int A[N][N], int n, int vertex, int path[N], int path_length, int visited[N]) {
	//Помечаем вершину посещённой.
	visited[vertex] = 1;
	//Переход на следующую вершину.
	path[path_length] = vertex;
	//Пусть стал длиннее на 1 связь.
	path_length++;
	//Если пути больше нет...
	if (path_length == n) {
		int first_vertex = path[0];
		int last_vertex = path[n-1];
		//Если связь есть, то путь найден, иначе возвращаемся на предыдущую вершину
		//и убираем текущую вершину из посещённых.
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
	//Находим следующий шаг пути.
	for (int child = 0; child < n; child++) {
		//Если связь есть и узел ещё не посещён, то если можно создать путь, то идём дальше.
		if (A[vertex][child] == 1 && visited[child] == 0) {
			if (visit(A, n, child, path, path_length, visited) == 1) {
				return 1;
			}
		}
	}
	//Если следующий шан пути не найден, то возвращаемся на предыдущую вершину
	//и убираем текущую вершину из посещённых.
	path_length--;
	path[path_length] = -1;
	visited[vertex] = 0;
	return 0;
}
