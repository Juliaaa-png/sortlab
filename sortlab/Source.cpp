#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;


void QuickSort(int* mas, int size) {
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int cntr = mas[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while (mas[i] < cntr) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while (mas[j] > cntr) {
            j--;
        }
        //Меняем элементы местами
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0) {
        QuickSort(mas, j + 1);              //"Левый кусок"
    }
    if (i < size) {
        QuickSort(&mas[i], size - i);       //"Првый кусок"
    }
}


void maxHeapify(long i, int* A, int heapsize) {
    long largest;

    //Формируем 3 кучу - 3 потомка у каждого звена
    long l = 3 * i + 1;
    long m = 3 * i + 2;
    long r = 3 * i + 3;

    //Находим наибольшего по размеру потомка и записываем его индекс
    if (l < heapsize && A[l] > A[i])
        largest = l;
    else
        largest = i;

    if (m < heapsize && A[m] > A[largest])
        largest = m;

    if (r < heapsize && A[r] > A[largest])
        largest = r;

    //Если самый большой индекс не является родительским, то существует другое большее значение
    //Поэтому меняем местами это значение с родительским
    if (largest != i) {
        std::swap(A[i], A[largest]);
        maxHeapify(largest, A, heapsize);
    }
}

void buildMaxHeap(int* A, int heapsize) {
    long j;
    //Идем с последнего родителя к самому первому(корневому)
    for (j = heapsize / 3 - 1; j >= 0; --j)
        maxHeapify(j, A, heapsize);
}

void heapsort(int* A, int heapsize) {
    buildMaxHeap(A, heapsize);

    long i;
    for (i = heapsize - 1; i > 0; --i) {
        std::swap(A[0], A[i]);

        --heapsize;
        maxHeapify(0, A, heapsize);
    }
}

void save_mas(int* mas, int size, const char* file_name) {
    std::ofstream ofs(file_name);
    for (int i = 0; i < size; i++) {
        ofs << mas[i] << " ";
    }
    ofs.close();
}

int main() {

    clock_t begin, end;
    double time_elapsed;
    srand(time(NULL));

    std::ofstream ofs, ofs1;

    int size = 1;
    cout << "\nEnter size of mas for quicksort:";
    cin >> size;
    int* mas_q = new int[size];
    // Заполнение массива случайными числами
    for (int i = 0; i < size; i++)
        mas_q[i] = rand() % 1000;
    

    begin = clock();
    QuickSort(mas_q,size); 
    end = clock();

    time_elapsed = (double)(end - begin) / CLOCKS_PER_SEC;

    // Вывод элементов массива после сортировки и запись в файл
    if (size < 20) {
        for (int i = 0; i < size; i++)
            printf("%4d ", mas_q[i]);
        save_mas(mas_q, size, "res_q.txt");
        ofs.open("res_q.txt", ios::app);
        ofs << "\n" << " Time:" << time_elapsed << endl;
    }

    cout << "\n";
    cout << "Time of quicksort:" << time_elapsed;
    cout << "\n";
    
    std::ofstream t("time_q.txt");
    t << "\n" << " Time:" << time_elapsed << endl;
    t.close();


    clock_t begin1, end1;
    double time_elapsed1;
    int  heapsize = 1;
    cout << "\nEnter size of mas for heapsort:";
    cin >> heapsize;
    int* mas_h= new int[heapsize];
    srand(time(NULL));
    
    for (int i=0 ; i < heapsize; ++i) {
        mas_h[i] = rand() % 1000;
    }

    begin1 = clock();
    heapsort(mas_h,heapsize);
    end1 = clock();

    time_elapsed1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;

    if (heapsize < 20) {
        for (int i = 0; i < heapsize; ++i)
            printf("%4d ", mas_h[i]);
        save_mas(mas_h, heapsize, "res_h.txt");
        ofs1.open("res_h.txt", ios::app);
        ofs1 << "\n" << " Time:" << time_elapsed << endl;
    }

    cout << "\n";
    cout << "Time of heapsort:" << time_elapsed1;

    std::ofstream t1("time_h.txt");
    t1 << "\n" << " Time:" << time_elapsed1 << endl;
    t1.close();

    return 0;
}

