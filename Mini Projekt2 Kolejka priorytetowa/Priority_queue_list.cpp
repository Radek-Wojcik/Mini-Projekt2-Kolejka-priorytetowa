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
void ListQueue<T>::insert(T value, int priority) {
	LNode* newNode = new LNode(value, priority, head);
	//Jesli lista jest pusta lub nowy ma wiekszy priorytet niz pierwszy element
	if (head == nullptr || priority > head->priority) {
		newNode->next = head;
		head = newNode;
		if (tail == nultptr) tail = newNode;
	}
	else {
		//szukamy miejsca do wstawienia
		LNode* current = head;
		while (current->next != nullptr && current->next->priority >= priority) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
		//jesli wstawiamy na koniec aktualizujemy tail
		if (newNode->next == nullptr) tail = newNode;
	}
	size++;
}

template<typename T>
T ListQueue<T>::extract_max() {
	T val;
	if (head == nullptr) return; //jeœli lista jest pusta
	val = head->data;
	LNode* temp;
	temp = head;
	head = head->next;
	delete temp;
	size--;
	if (head == nullptr) tail = nullptr; //je¿eli lista po usuniêciu pusta, zerujemy tail
	return val;
}

template<typename T>
T ListQueue<T>::find_max() {
	if (head == nullptr) return; //jeœli lista jest pusta
	return head->data;
}

template<typename T>
ListQueue<T>::~ListQueue() {
	while (head != nullptr) {
		LNode* temp = head;
		head = head->next;
		delete temp;
	}
	tail = nullptr;
}