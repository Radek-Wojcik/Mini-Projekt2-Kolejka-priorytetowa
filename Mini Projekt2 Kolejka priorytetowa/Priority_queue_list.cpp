#include "Priority_queue_list.h"
#include<iostream>
#include<string>

template<typename T>
ListQueue<T>::ListQueue() : head(nullptr), tail(nullptr), size(0) {}

template<typename T>
int ListQueue<T>::get_size() const {
	return size;
}



template<typename T>
ListQueue<T>::~LinkedList() {
	while (head != nullptr) {
		LNode* temp = head;
		head = head->next;
		delete temp;
	}
	tail = nullptr;
}