#include <stdio.h>
#define QUEUE_SIZE 100


int items[QUEUE_SIZE];

//Индекс начала очереди.
int head = 0;
//Индекс конца очереди.
int tail = -1;
//Число элементов очереди.
int itemCount = 0;

//Возвращает элемент из начала очереди.
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

//Число элементов в очереди.
int size() {
    return itemCount;
}

//Добавление элемента в конец очереди.
int enque(int data) {
    if (!isFull()) {
        if (tail == QUEUE_SIZE - 1) {
            tail = -1;
        }
		//Сначала прибавляем 1 к концу, потом записываем туда data.
        items[++tail] = data;
        itemCount++;
        return 0;
    }
    else {
        //В случае переполнения, элемент не добавляется.
        printf("Queue is full.");
        return 1;
    }
}

//Удаление элемента из начала очереди.
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
        //Завершаем программу с ошибкой, в случае попытки удаления из пустой очереди.
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
        //Завершаем программу с ошибкой, если индекс не корректен.
        printf("Incorrect index.");
        return 1;
    }
}

//Вспомогательная функция, которая выделяет подочередь и переворачивает элементы в ней.
//Например, если в очереди элементы x1 x2 ... xi x(i+1) ... xj x(j+1) ... xn,
//то после вызова метода очередь будет содержать элементы x1 x2 ... xj x(j-1) ... x(i+1) xi x(j+1) ... xn.
void reverseSubqueue(int i, int j) {
    while (i < j) {
        int tmp = items[(i + head)% QUEUE_SIZE];
        items[(i + head) % QUEUE_SIZE] = items[(j + head)% QUEUE_SIZE];
        items[(j + head) % QUEUE_SIZE] = tmp;
        i++;
        j--;
    }
}