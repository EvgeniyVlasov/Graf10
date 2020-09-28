/*

Файл называется "Graph10_lib.h"
Это заголовочный файл.


Автор: Власов Евгений Максимович, группа ИВТ-13БО.
*/

//Защита от множественного включения.
#pragma once
#define N 100

//Это все функции, которые исп. в программе.
int* CreateAndCheckAdjacentMatrix(int A[N][N], int n);
int FindingPaths(int A[N][N], int n, int start_vertex);
int PalmerAlgorithm(int A[N][N], int n);

static int visit(int A[N][N], int n, int vertex, int path[N], int path_length, int visited[N]);
