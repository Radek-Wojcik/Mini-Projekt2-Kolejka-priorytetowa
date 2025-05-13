#include "Priority_queue_list.h"
#include<iostream>
#include<string>
#include<fstream>

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
void ListQueue<T>::modify_key(T value, int newPriority) {
	//jesli lista jest pusta
	if (head == nullptr) return;
	LNode* current = head;
	LNode* prev = nullptr;
	LNode* target = nullptr;
	//Szukamy elementu o zadanej wartosci
	while (current != nullptr) {
		if (current->value == value) {
			if (current->value == value) {
				target = current;
				break;
			}
			prev = current;
			current = current->next;
		}
	}
	// Jeœli nie znaleziono - nic nie robimy
	if (target == nullptr) return;

	// Usuwamy element z listy
	if (target == head) {
		head = head->next;
		if (target == tail) {
			tail = nullptr;
		}
	}
	else {
		prev->next = target->next;
		if (target == tail) {
			tail = prev;
		}
	}

	delete target;
	size--;

	// Wstawiamy go ponownie z nowym priorytetem
	insert(value, newPriority);
}

//funkcje do menu
template<typename T>
void ListQueue<T>::show() const {
	LNode* temp = head;
	while (temp) {
		std::cout << temp->priority << ": " << temp->data << " -> ";
		temp = temp->next;
	}
	std::cout << std::endl;
}


// Usuwa wszystkie dane z listy (przydatne przed wczytaniem z pliku)
template<typename T>
void ListQueue<T>::clear() {
	while (head != nullptr) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	tail = nullptr;
	size = 0;
}

// Buduje listê z pliku (czyta wartoœci ca³kowite z pliku)
template<typename T>
void ListQueue<T>::build_from_file(const std::string& filename) {
	clear(); // Usuwamy istniej¹ce dane

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Nie mo¿na otworzyæ pliku: " << filename << std::endl;
		return;
	}
	T value;
	int priority;
	while (file >> value >> priority) {
		insert(value, priority);
	}
	file.close();
}

// Tworzy losow¹ strukturê o podanej wielkoœci
template<typename T>
void ListQueue<T>::generate_random(int count, int minVal, int maxVal) {
	clear(); // Usuwamy istniej¹ce dane
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	for (int i = 0; i < count; ++i) {
		T value = static_cast<T>(minVal + std::rand() % (maxVal - minVal + 1));
		int priority = std::rand() % 100; // losowy priorytet od 0 do 99
		insert(value, priority);
	}
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