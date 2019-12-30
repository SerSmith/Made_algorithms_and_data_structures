// Скрипт, сортирующий ччастично отсортированную последовательность
// 08.11

#include <assert.h>
#include <iostream>
#include <string.h>
using namespace std;




template <typename T>
bool compare_less(const T first, const T second)
{

if (first< second) {
return true;
} else {
return false;
}

}

template <typename T>
class seq {

public:

	seq(const int length_ , const int k_);
	~seq();
    seq<T>(const seq<T>&) = delete;
    seq<T>(const seq<T>&&) = delete;
    seq<T>& operator=(const seq&) = delete;
    seq<T>& operator=(seq&&) = delete;

// Выгрузка в исходящий поток k первых сохраненных элементов
void GetFirstK(const bool EndFlg);

// Добавдение нового элемента
void AddElement(const T add);

//Массив длины 2*k для хранения пока не отсортированных элементов 
T* array;
// Длина массива, в данной задаче всегда равна 2*k
int LengthMain;
// Размер окна, через которое начинаются числа больше или равные текущему
int k;
// Количество заполненных элементов в массиве
int NowLenght;
// Флаг -первые 4 элемента уже отсортированы
bool first_sorted;

};

template <typename T> 
seq<T>::seq(const int length_ , const int k_)
{
    LengthMain=length_;
    array=new T[LengthMain];
    k=k_;
    NowLenght=0;
    first_sorted=0;
}

template <typename T> 
seq<T>::~seq()
{
    delete [] array;
}

template <typename T> 
void Merge(const T* FirstArr, const int FirstQuant,const T* SecondArr,const int SecondQuant,T* out,bool (*compare)(const T, const T)  )
{
  
    int counter=0;
    int i=0;
    int j=0;

    while (i<FirstQuant or j<SecondQuant)
    {
        if ((i>=FirstQuant) or (j<SecondQuant and compare_less(SecondArr[j],FirstArr[i])) ) 
        {
            out[counter]=SecondArr[j];
            j++;
            counter++;
        } else {
                 out[counter]=FirstArr[i];
            i++;
            counter++;
        }
    }


}

template <typename T> 
void MergeSort( T * a, const int length,bool (*compare)(const T, const T) ) {
if( length <= 1 ) {
return;
}
int firstLen = length / 2;
int secondLen = length - firstLen;

MergeSort( a + firstLen, secondLen, compare );
int* c = new int[length];

Merge( a, firstLen, a + firstLen, secondLen, c, compare );

memcpy( a, c, sizeof( int ) * length );


delete[] c;
}



template <typename T> 
void seq<T>::GetFirstK(bool EndFlg)
{
    int LengthOut=-1;
    // Если это запуск не по достижению конца ппоследовательности, то выводим только первые k элементов, так как они точно меньше, чем всего последующие элементы
    if (EndFlg==0) LengthOut=k; else 
    {LengthOut=NowLenght;} 

    if (!EndFlg){  
        // Нам не надо отдельно отсортировать первые k элементов изначального массива, так как они уже отсортированы, кроме как при первой сортировке
        if (LengthMain!=NowLenght or first_sorted!=1) MergeSort( array, LengthMain/2,compare_less);
        MergeSort( array, LengthMain,compare_less );
         } else {
             MergeSort( array, NowLenght,compare_less ); 
         }
    first_sorted=1;



    for (int i=0; i<LengthOut; i++)
    {
        cout<<array[i]<<" ";
 
    } 
    
    memcpy( array, array+k, sizeof(int)*k );
    NowLenght=k;


}

template <typename T> 
void seq<T>::AddElement(T add)
{
    array[NowLenght]=add;
    NowLenght++;
}

int main()
{

  int num_numbers = 0;
  int window=0;

  cin >> num_numbers>>window;

    seq<int> PartialSeq(2*window,window);


    for (int i = 1; i < num_numbers+1; ++i) {
//удобнее отсчитывать элементы с 1, а не с 0, 
// что бы использовать целосчисленное деление на weindow
          int in=-1;
          cin>>in;
          PartialSeq.AddElement(in);
          if (i !=window and i%window==0 ) PartialSeq.GetFirstK(0);
  }
        PartialSeq.GetFirstK(1);



  system("pause");
  return 0;
}

	
	