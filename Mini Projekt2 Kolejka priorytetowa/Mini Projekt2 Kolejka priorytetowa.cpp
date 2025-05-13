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
void testAllStructures();
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
        case 3: testAllStructures(); break;
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

void testAllStructures() {
    const int tab[] = { 20000, 40000, 60000, 80000, 100000, 120000, 140000 };
    const int iterations = 100;

    std::mt19937_64 rng(static_cast<unsigned long>(std::time(nullptr)));
    std::ofstream out("wyniki.txt");
    out << "Struktura\tRozmiar\tinsert(ns)\textractMax(ns)\tfindMax(ns)\tmodifyKey(ns)\tgetSize(ns)\n";

    for (int n : tab) {
        std::uniform_int_distribution<int> distVal(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        std::uniform_int_distribution<int> distPrio(0, 2 * n);

        // Generuj dane testowe
        generateRandomFile("Liczby.txt", n);

        // Wczytaj dane do wektora (przydatne do modyfikacji)
        std::vector<std::pair<int, int>> fileData;
        {
            std::ifstream fin("Liczby.txt");
            int v, p;
            while (fin >> v >> p)
                fileData.push_back(std::make_pair(v, p));
        }
        std::uniform_int_distribution<size_t> distIndex(0, fileData.size() - 1);

        // Przygotuj dane testowe
        std::vector<std::pair<int, int>> insertData(iterations);
        std::vector<int> restorePrio(iterations);
        std::vector<std::pair<int, int>> modifyData(iterations);

        for (int i = 0; i < iterations; ++i) {
            insertData[i] = std::make_pair(distVal(rng), distPrio(rng));
            restorePrio[i] = distPrio(rng);
            std::pair<int, int> valPair = fileData[distIndex(rng)];
            modifyData[i] = std::make_pair(valPair.first, distPrio(rng));
        }

        long long sumInsH = 0, sumExtH = 0, sumFindH = 0, sumModH = 0, sumSzH = 0;
        long long sumInsL = 0, sumExtL = 0, sumFindL = 0, sumModL = 0, sumSzL = 0;

        // === HEAP ===
        for (int i = 0; i < iterations; ++i) {
            HeapPrioQueue<int> heap(0, 2 * n);

            // insert
            heap.buildFromFile("Liczby.txt");
            int v = insertData[i].first;
            int p = insertData[i].second;
            auto t0 = Clock::now();
            heap.insert(v, p);
            sumInsH += std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - t0).count();

            // extract
            heap.buildFromFile("Liczby.txt");
            t0 = Clock::now();
            int x = heap.extractMax();
            sumExtH += std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - t0).count();
            heap.insert(x, restorePrio[i]);

            // find max
            heap.buildFromFile("Liczby.txt");
            t0 = Clock::now();
            heap.findMax();
            sumFindH += std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - t0).count();

            // modify key
            heap.buildFromFile("Liczby.txt");
            int mv = modifyData[i].first;
            int newp = modifyData[i].second;
            t0 = Clock::now();
            heap.modifyKey(mv, newp);
            sumModH += std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - t0).count();

            // get size
            heap.buildFromFile("Liczby.txt");
            t0 = Clock::now();
            heap.returnSize();
            sumSzH += std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - t0).count();
        }

        // === LIST ===
        for (int i = 0; i < iterations; ++i) {
            ListQueue<int> list;

            // insert
            list.build_from_file("Liczby.txt");
            int v = insertData[i].first;
            int p = insertData[i].second;
            auto t0 = Clock::now();
            list.insert(v, p);
            sumInsL += std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - t0).count();

            // extract
            list.build_from_file("Liczby.txt");
            t0 = Clock::now();
            int x = list.extract_max();
            sumExtL += std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - t0).count();
            list.insert(x, restorePrio[i]);

            // find max
            list.build_from_file("Liczby.txt");
            t0 = Clock::now();
            list.find_max();
            sumFindL += std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - t0).count();

            // modify key
            list.build_from_file("Liczby.txt");
            int mv = modifyData[i].first;
            int newp = modifyData[i].second;
            t0 = Clock::now();
            list.modify_key(mv, newp);
            sumModL += std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - t0).count();

            // get size
            list.build_from_file("Liczby.txt");
            t0 = Clock::now();
            list.get_size();
            sumSzL += std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - t0).count();
        }

        // 5. Wyniki
        double div = static_cast<double>(iterations);
        std::cout << "\nRozmiar: " << n << "\n"
            << "Heap: insert=" << sumInsH / div
            << "ns, extract=" << sumExtH / div
            << "ns, find=" << sumFindH / div
            << "ns, modify=" << sumModH / div
            << "ns, size=" << sumSzH / div << "ns\n";

        std::cout << "List: insert=" << sumInsL / div
            << "ns, extract=" << sumExtL / div
            << "ns, find=" << sumFindL / div
            << "ns, modify=" << sumModL / div
            << "ns, size=" << sumSzL / div << "ns\n";

        // 6. Zapis do pliku
        out << "Heap\t" << n << "\t" << sumInsH / div << "\t" << sumExtH / div
            << "\t" << sumFindH / div << "\t" << sumModH / div << "\t" << sumSzH / div << "\n";
        out << "List\t" << n << "\t" << sumInsL / div << "\t" << sumExtL / div
            << "\t" << sumFindL / div << "\t" << sumModL / div << "\t" << sumSzL / div << "\n";
    }

    out.close();
    std::cout << "\nWyniki zapisane w wyniki.txt\n";
}



void generateRandomFile(const string& filename, int count) {
    ofstream file(filename);
    mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> distElem(0, 1000000);
    uniform_int_distribution<int> distPrio(0, count*2);
    for (int i = 0; i < count; i++) {
        file << distElem(rng) << " " << distPrio(rng) << "\n";
    }
    file.close();
}
