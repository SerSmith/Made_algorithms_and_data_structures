
// Скрипт, выдающий k-ый элемент в отсортированнном массиве
// 09.11

#include <iostream>
using namespace std;


template <typename T>
bool compare_more(const T first, const T second)
{

if (first> second) {
return true;
} else {
return false;
}

}

template <typename T>
int partition( T * array, const int PartSize, const int PivotIndex, bool (*compare)(const T, const T))
{



    // Меняем опорный элемент с последним
    swap(array[PartSize],array[PivotIndex]);
    //Начало отсчета
    int i=0;


    for (int j = 0; j < PartSize; j++) {
        // Поскольку мы передаем в качестве array адрес 
        // i-ого элемента, то считать можно начинать с 0


            if ((compare(array[PartSize],array[j]))  or (array[PartSize] == array[j]) ) {
                swap(array[i], array[j]);
                i++;
            }
        }



        // Меняем опорный элемент и элемент, на который указывает i
        swap(array[i], array[PartSize]);


        return i;
}

template <typename T>
T compute_k(T* array, int length, int k) {
    // Функция, возвращающая k-элемент в сортированном массиве

    int begin=0;
    int end=length;
    // В будущем нам понадобится знать значение начала 
    int last_begin=begin;
    do{


        begin+=partition(array+begin, end-begin-1, rand()%(end-begin),compare_more);

        // В будущем нам понадобится знать значение начала 
        last_begin=begin;

        if (begin<k ) /*Если мы слева от k-го элемента*/ begin++; else {
           //Если мы справа от k-го элемента
            end=begin;
            begin=0;
        }





    }
    // Если подобрали K элемент или отсортировали все, то можем останавливаться
     while( begin != end and last_begin !=k);




    return array[k];

}




int main() {
    // Количество элементов в последовательности
    int n=0;
    // Номер элемента, который наддоо вернуть 
    int k=0;
    std::cin >> n >> k;

    int* array=new int [n];

    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }

   cout << compute_k(array, n, k);

    system("pause");

    delete[] array;

    return 0;
} 