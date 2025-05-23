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
	LNode<T>* newNode = new LNode<T>(value, priority, head);
	//Jesli lista jest pusta lub nowy ma wiekszy priorytet niz pierwszy element
	if (head == nullptr || priority > head->priority) {
		newNode->next = head;
		head = newNode;
		if (tail == nullptr) tail = newNode;
	}
	else {
		//szukamy miejsca do wstawienia
		LNode<T>* current = head;
		while (current->next != nullptr && current->next->priority > priority) {
			current = current->next;
		}
		// Teraz current->next ma priorytet <= new_priority.
		// Je�li priorytet r�wny, to newNode wstawi si� ZA istniej�cymi r�wnymi.
		while (current->next && current->next->priority == priority) {
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
	if (!head) throw std::runtime_error("extract_max(): kolejka jest pusta"); //je�li lista jest pusta
	val = head->data;
	LNode<T>* temp;
	temp = head;
	head = head->next;
	delete temp;
	size--;
	if (head == nullptr) tail = nullptr; //je�eli lista po usuni�ciu pusta, zerujemy tail
	return val;
}

template<typename T>
T ListQueue<T>::find_max() {
	if (!head) throw std::runtime_error("find_max(): kolejka jest pusta"); //je�li lista jest pusta
	return head->data;
}

template<typename T>
void ListQueue<T>::modify_key(T value, int newPriority) {
	//jesli lista jest pusta
	if (head == nullptr) return;
	LNode<T>* current = head;
	LNode<T>* prev = nullptr;
	LNode<T>* target = nullptr;
	//Szukamy elementu o zadanej wartosci
	while (current != nullptr) {
		if (current->data == value) {
			target = current;
			break;
		}
			prev = current;
			current = current->next;
	}
	// Je�li nie znaleziono - nic nie robimy
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
	LNode<T>* temp = head;
	while (temp) {
		std::cout << "Priorytet: " << temp->priority << " Wartosc: " << temp->data << "\n";
		temp = temp->next;
	}
	std::cout << std::endl;
}


// Usuwa wszystkie dane z listy (przydatne przed wczytaniem z pliku)
template<typename T>
void ListQueue<T>::clear() {
	while (head != nullptr) {
		LNode<T>* temp = head;
		head = head->next;
		delete temp;
	}
	tail = nullptr;
	size = 0;
}

// Buduje list� z pliku (czyta warto�ci ca�kowite z pliku)
template<typename T>
void ListQueue<T>::build_from_file(const std::string& filename) {
	clear(); // Usuwamy istniej�ce dane

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Nie mo�na otworzy� pliku: " << filename << std::endl;
		return;
	}
	T value;
	int priority;
	while (file >> value >> priority) {
		insert(value, priority);
	}
	file.close();
}

// Tworzy losow� struktur� o podanej wielko�ci
template<typename T>
void ListQueue<T>::generate_random(int count, int minVal, int maxVal) {
	clear(); // Usuwamy istniej�ce dane
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
		LNode<T>* temp = head;
		head = head->next;
		delete temp;
	}
	tail = nullptr;
}
template class ListQueue<int>;