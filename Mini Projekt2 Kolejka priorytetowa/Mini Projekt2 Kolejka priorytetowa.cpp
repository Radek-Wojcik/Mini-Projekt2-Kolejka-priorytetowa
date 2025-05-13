#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include "heap_prio_queue.h"
#include "Priority_queue_list.h"

using namespace std;
using Clock = chrono::high_resolution_clock;

void testHeapPriority();
void testListPriority();
//void testAllStructures();
void generateRandomFile(const string& filename, int count);

int main() {
    int choice;
    do {
        cout << "======== MENU TESTOWANIA ========\n";
        cout << "1. Test listy priorytetowej zaimplementowanej za pomoca kopca\n";
        cout << "2. Test listy priorytetowej zaimplementowanej za pomoca listy jednokierunkowej\n";
        cout << "3. Pomiary czasowe wszystkich struktur\n";
        cout << "4. Generowanie pliku z liczbami losowymi do testowania wydajnosci\n";
        cout << "0. Wyjscie\n";
        cout << "Wybierz opcje: ";
        cin >> choice;
        switch (choice) {
        case 1: testHeapPriority(); break;
        case 2: testListPriority(); break;
       // case 3: testAllStructures(); break;
        case 4: {
            int capacity;
            cout << "Podaj wielkosc generowanego pliku: ";
            cin >> capacity;
            generateRandomFile("Liczby.txt", capacity);
            break;
        }
        case 0:
            cout << "Zamykanie programu." << endl;
            break;
        default:
            cout << "Nieprawidlowa opcja." << endl;
        }
    } while (choice != 0);
    return 0;
}

void testHeapPriority() {
    HeapPrioQueue<int> heap(0, 100);
    int choice;
    do {
        cout << "\n===== TEST KOLEJKI PRIORYTETOWEJ - KOPIEC =====\n";
        cout << "1. Zbuduj z pliku\n";
        cout << "2. Dodaj element e o priorytecie p\n";
        cout << "3. Usun i zwroc element o najwiekszym priorytecie\n";
        cout << "4. Zwroc element o najwiekszym priorytecie\n";
        cout << "5. Zmien priorytet elementu e na p\n";
        cout << "6. Wypelnij kolejke losowo\n";
        cout << "7. Wyswietl kolejke\n";
        cout << "0. Wyjdz\n";
        cout << "Twoj wybor: "; cin >> choice;
        switch (choice) {
        case 1: {
            string fname;
            cout << "Podaj nazwe pliku: "; cin >> fname;
            heap.buildFromFile(fname);
            break;
        }
        case 2: {
            int e, p;
            cout << "Element: "; cin >> e;
            cout << "Priorytet: "; cin >> p;
            heap.insert(e, p);
            break;
        }
        case 3:
            cout << "Usunieto: " << heap.extractMax() << endl;
            break;
        case 4:
            cout << "Max: " << heap.findMax() << endl;
            break;
        case 5: {
            int e, p;
            cout << "Element: "; cin >> e;
            cout << "Nowy priorytet: "; cin >> p;
            heap.modifyKey(e, p);
            break;
        }
        case 6: {
            int size;
            cout << "Rozmiar: "; cin >> size;
            heap.createRandom(size);
            break;
        }
        case 7:
            heap.display();
            break;
        case 0:
            break;
        default:
            cout << "Nieprawidlowa opcja." << endl;
        }
    } while (choice != 0);
}

void testListPriority() {
    ListQueue<int> list;
    int choice;
    do {
        cout << "\n===== TEST KOLEJKI PRIORYTETOWEJ - LISTA =====\n";
        cout << "1. Zbuduj z pliku\n";
        cout << "2. Dodaj element e o priorytecie p\n";
        cout << "3. Usun i zwroc element o najwiekszym priorytecie\n";
        cout << "4. Zwroc element o najwiekszym priorytecie\n";
        cout << "5. Zmien priorytet elementu e na p\n";
        cout << "6. Wypelnij kolejke losowo\n";
        cout << "7. Wyswietl kolejke\n";
        cout << "0. Wyjdz\n";
        cout << "Twoj wybor: "; cin >> choice;
        switch (choice) {
        case 1: {
            string fname;
            cout << "Podaj nazwe pliku: "; cin >> fname;
            list.build_from_file(fname);
            break;
        }
        case 2: {
            int e, p;
            cout << "Element: "; cin >> e;
            cout << "Priorytet: "; cin >> p;
            list.insert(e, p);
            break;
        }
        case 3:
            cout << "Usunieto: " << list.extract_max() << endl;
            break;
        case 4:
            cout << "Max: " << list.find_max() << endl;
            break;
        case 5: {
            int e, p;
            cout << "Element: "; cin >> e;
            cout << "Nowy priorytet: "; cin >> p;
            list.modify_key(e, p);
            break;
        }
        case 6: {
            int size;
            cout << "Rozmiar: "; cin >> size;
            list.generate_random(size, 0, 100);
            break;
        }
        case 7:
            list.show();
            break;
        case 0:
            break;
        default:
            cout << "Nieprawidlowa opcja." << endl;
        }
    } while (choice != 0);
}

/*void testAllStructures() {
    const int sizes[] = { 20000, 40000, 60000, 80000, 100000, 120000, 140000,  };
    const int iterations = 100;
    ofstream out("wyniki.txt");
    out << "Struktura\tRozmiar\tbuildFromFile(ms)\trandomFill(ms)\tExtractMax(ms)\n";

    for (int n : sizes) {
        generateRandomFile("Liczby.txt", n);
        // Test kopiec
        HeapPrioQueue<int> heap(0, 100);
        long sumBuild = 0, sumRandom = 0, sumExtract = 0;
        for (int i = 0; i < iterations; i++) {
            auto t0 = Clock::now(); heap.buildFromFile("Liczby.txt"); sumBuild += chrono::duration_cast<chrono::milliseconds>(Clock::now() - t0).count();
            t0 = Clock::now(); heap.createRandom(n); sumRandom += chrono::duration_cast<chrono::milliseconds>(Clock::now() - t0).count();
            heap.buildFromFile("Liczby.txt");
            t0 = Clock::now(); heap.extractMax(); sumExtract += chrono::duration_cast<chrono::milliseconds>(Clock::now() - t0).count();
        }
        out << "Heap\t" << n << "\t" << sumBuild / iterations << "\t" << sumRandom / iterations << "\t" << sumExtract / iterations << "\n";
        // Test lista
        ListQueue<int> list;
        long sumB2 = 0, sumR2 = 0, sumE2 = 0;
        for (int i = 0; i < iterations; i++) {
            auto t0 = Clock::now(); list.build_from_file("Liczby.txt"); sumB2 += chrono::duration_cast<chrono::milliseconds>(Clock::now() - t0).count();
            t0 = Clock::now(); list.generate_random(n, 0, 100); sumR2 += chrono::duration_cast<chrono::milliseconds>(Clock::now() - t0).count();
            list.build_from_file("Liczby.txt");
            t0 = Clock::now(); list.extract_max(); sumE2 += chrono::duration_cast<chrono::milliseconds>(Clock::now() - t0).count();
        }
        out << "List\t" << n << "\t" << sumB2 / iterations << "\t" << sumR2 / iterations << "\t" << sumE2 / iterations << "\n";
    }
    out.close();
    cout << "Wyniki zapisane w wyniki.txt" << endl;
}*/

void generateRandomFile(const string& filename, int count) {
    ofstream file(filename);
    mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> distElem(0, 1000000);
    uniform_int_distribution<int> distPrio(0, 100);
    for (int i = 0; i < count; i++) {
        file << distElem(rng) << " " << distPrio(rng) << "\n";
    }
    file.close();
}
