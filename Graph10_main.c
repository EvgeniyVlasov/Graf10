/*

���� ���������� "Graph10_main.c"

���������� ���������: �������� ���� �������� ����� ���,
����� ��� ���� � ���� � ����� � ��������� ���������.

���������� �����: ������� ���-�� ������� (������ ������� �������)
� ��������� �������; ������� ������� �������� ������� ��������� � ���������� ���� �����.

�����: ������ ������� ����������, ������ ���-13��.
*/

#include <stdio.h>
#include <locale.h>
#include "Graph10_lib.h"
#define _CRT_SECURE_NO_WARNINGS
#define N 100

void main()
{
	
	//n- ���-�� �������(������ ������� ���������), � - ������� ���������,
	//start_vertex - ��������� �������.
	int n;
	int A[N][N];
	int start_vertex;
	//��������� ���-�� ������� � ��������� ������������ �����.
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
	//�������� ������� ���������.
	CreateAndCheckAdjacentMatrix(A, n);
	 
	//��������� ��������� �������.
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

	//���������� ����� �����.
	FindingPaths(A, n, start_vertex);
	system("pause");
}

/*

�����������: O((n-1)!).
n - ������ ������� ���������

�����:

2
1

3
1
1
1

4
1
0
1
1
0
1

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
*/
