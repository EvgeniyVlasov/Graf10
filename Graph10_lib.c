/*

�������� ����� "Graph10_lib.c"

���������� ���������: �������� ���� �������� ����� ���,
����� ��� ���� � ���� � ����� � ��������� ���������.

���������� �����: ������� ������� ��������� � ����� ���� �����.

�����: ������ ������� ����������, ������ ���-13��.
*/

#include <stdio.h>
#include <locale.h>
#define _CRT_SECURE_NO_WARNINGS
#define N 100

//�������� ������� �������.
int* CreateAndCheckAdjacentMatrix(int A[N][N], int n)
{
	//connection - ����� � ������� (0 - ����� (��� �����), 1 - ������ (����� ����)).
	
	//����� ������ ������ ������� (���� ������� ������ ������� ������ ��� dirac_constant, ������ ���� ����������).
	//���� n �����, �� dirac_constant = n/2; ���� n �������, �� dirac_constant = [n/2]+1 (��������� ����� ������).
	int dirac_constant = n/2+n%2;
	int min_vertex_degree = n-1;
	int vertex_degree;
	int matrix_element;
	//�������� ������� ���������.
	for (int i = 0; i < n; i++)
	{
		vertex_degree = 0;
		for (int j = i; j < n; j++)
		{
			//���������� ������� ��������� ������� ��������� ������.
			if (i == j)
			{
				A[i][j] = 0;
				continue;
			}

			//����� ������� � ������ ������� ���������, ����� ������������ ��� ����� 0 ��� 1.
			printf_s("\n[%d][%d] -> ", i, j);
			//���������� ��������� ����� � ��� ��������.
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
			//���� ����� ����, �� ����������� ������� ������.
			if (matrix_element == 1)
				vertex_degree++;
			//��������� ������������ ����������� ������� ��������� ������� ������� �������.
			A[i][j] = matrix_element;
			A[j][i] = matrix_element;
		}
		//������� ������� � ����������� ���-��� ������.
		if (vertex_degree < min_vertex_degree) {
			min_vertex_degree = vertex_degree;
		}
	}
	//���� ���������� ����� ������ ������� ������ ��������� ������,
	//�� �������������� � ���, ��� ���� ����� ���� �� ������.
	if (min_vertex_degree < dirac_constant) {
		printf_s("Warning! Solution may not exist!\n");
	}
	return A;
}

//���������� ���� �����
int FindingPaths(int A[N][N], int n, int start_vertex)
{
	//����.
	int path[N];
	//��� ���������� ����.
	int visited[N];
	//������������� ��������.
	for (int i = 0; i < n; i++) {
		path[i] = -1;
		visited[i] = 0;
	}
	//���� ������� ����� ����, �� ���������� ��� � ��������� ����, ����� ���� �� ������.
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

//������� ���������� ������� ����.
static int visit(int A[N][N], int n, int vertex, int path[N], int path_length, int visited[N]) {
	//�������� ������� ����������.
	visited[vertex] = 1;
	//������� �� ��������� �������.
	path[path_length] = vertex;
	//����� ���� ������� �� 1 �����.
	path_length++;
	//���� ���� ������ ���...
	if (path_length == n) {
		int first_vertex = path[0];
		int last_vertex = path[n-1];
		//���� ����� ����, �� ���� ������, ����� ������������ �� ���������� �������
		//� ������� ������� ������� �� ����������.
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
	//������� ��������� ��� ����.
	for (int child = 0; child < n; child++) {
		//���� ����� ���� � ���� ��� �� �������, �� ���� ����� ������� ����, �� ��� ������.
		if (A[vertex][child] == 1 && visited[child] == 0) {
			if (visit(A, n, child, path, path_length, visited) == 1) {
				return 1;
			}
		}
	}
	//���� ��������� ��� ���� �� ������, �� ������������ �� ���������� �������
	//� ������� ������� ������� �� ����������.
	path_length--;
	path[path_length] = -1;
	visited[vertex] = 0;
	return 0;
}
