/*

���� ���������� "Graph10_lib.h"
��� ������������ ����.


�����: ������ ������� ����������, ������ ���-13��.
*/

//������ �� �������������� ���������.
#pragma once
#define N 100

//��� ��� �������, ������� ���. � ���������.
int* CreateAndCheckAdjacentMatrix(int A[N][N], int n);
int FindingPaths(int A[N][N], int n, int start_vertex);
