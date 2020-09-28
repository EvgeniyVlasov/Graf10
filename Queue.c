#include <stdio.h>
#define QUEUE_SIZE 100


int items[QUEUE_SIZE];

//������ ������ �������.
int head = 0;
//������ ����� �������.
int tail = -1;
//����� ��������� �������.
int itemCount = 0;

//���������� ������� �� ������ �������.
int peek(int* buffer) {
    if (isEmpty()) {
        printf("Queue is empty.");
        return 1;
    }
    *buffer = items[head];
    return 0;
}

int isEmpty() {
    if (itemCount == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int isFull() {
    if (itemCount == QUEUE_SIZE) {
        return 1;
    }
    else {
        return 0;
    }
}

//����� ��������� � �������.
int size() {
    return itemCount;
}

//���������� �������� � ����� �������.
int enque(int data) {
    if (!isFull()) {
        if (tail == QUEUE_SIZE - 1) {
            tail = -1;
        }
		//������� ���������� 1 � �����, ����� ���������� ���� data.
        items[++tail] = data;
        itemCount++;
        return 0;
    }
    else {
        //� ������ ������������, ������� �� �����������.
        printf("Queue is full.");
        return 1;
    }
}

//�������� �������� �� ������ �������.
int deque(int* buffer) {
    if (!isEmpty()) {
        *buffer = items[head++];
        if (head == QUEUE_SIZE) {
            head = 0;
        }
        itemCount--;
        return 0;
    }
    else {
        //��������� ��������� � �������, � ������ ������� �������� �� ������ �������.
        printf("Queue is empty.");
        return 1;
    }
}

int itemAt(int index, int* buffer) {
    if (index < size()) {
        *buffer = items[(index + head) % QUEUE_SIZE];
        return 0;
    }
    else {
        //��������� ��������� � �������, ���� ������ �� ���������.
        printf("Incorrect index.");
        return 1;
    }
}

//��������������� �������, ������� �������� ���������� � �������������� �������� � ���.
//��������, ���� � ������� �������� x1 x2 ... xi x(i+1) ... xj x(j+1) ... xn,
//�� ����� ������ ������ ������� ����� ��������� �������� x1 x2 ... xj x(j-1) ... x(i+1) xi x(j+1) ... xn.
void reverseSubqueue(int i, int j) {
    while (i < j) {
        int tmp = items[(i + head)% QUEUE_SIZE];
        items[(i + head) % QUEUE_SIZE] = items[(j + head)% QUEUE_SIZE];
        items[(j + head) % QUEUE_SIZE] = tmp;
        i++;
        j--;
    }
}