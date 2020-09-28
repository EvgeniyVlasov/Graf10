#pragma once

int peek(int* buffer);
int isEmpty();
int isFull();
int size();
int enque(int data);
int deque(int* buffer);
int itemAt(int index, int* buffer);
void reverseSubqueue(int i, int j);
