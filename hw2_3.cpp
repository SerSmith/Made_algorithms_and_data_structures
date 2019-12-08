// Скрипт, сортирующий ччастично отсортированную последовательность
// 08.11

#include <assert.h>
#include <iostream>
#include <string.h>
using namespace std;



class seq {

public:
	seq(int length_,int k_);
	~seq();

// Выгрузка в исходящий поток k первых сохраненных элементов
void GetFirstK(bool EndFlg);

// Добавдение нового элемента
void AddElement(int add);


private:

// Сортировка слиянием
void MergeSort( int* a, int length ) ;

// Функция слияния двух массивов
void Merge(int* FirstArr, int FirstQuant,int* SecondArr, int SecondQuant,int* out);


//Массив длины 2*k для хранения пока не отсортированных элементов 
int* array;
// Длина массива, в данной задаче всегда равна 2*k
int LengthMain;
// Размер окна, через которое начинаются числа больше или равные текущему
int k;
// Количество заполненных элементов в массиве
int NowLenght;
// Флаг -первые 4 элемента уже отсортированы
bool first_sorted;

};

seq::seq(int length_,int k_)
{
    LengthMain=length_;
    array=new int[LengthMain];
    k=k_;
    NowLenght=0;
    first_sorted=0;
}

seq::~seq()
{
    delete [] array;
}

void seq::MergeSort( int* a, int length  ) {
if( length <= 1 ) {
return;
}
int firstLen = length / 2;
int secondLen = length - firstLen;
// Нам не надо отдельно отсортировать первые k элементов изначального массива, так как они уже отсортированы, кроме как при первой сортировке
if (length!=NowLenght or first_sorted!=1) MergeSort( a, firstLen );
MergeSort( a + firstLen, secondLen );
int* c = new int[length];

Merge( a, firstLen, a + firstLen, secondLen, c );

memcpy( a, c, sizeof( int ) * length );


delete[] c;
}

void seq::Merge(int* FirstArr, int FirstQuant,int* SecondArr, int SecondQuant, int* out )
{
  
    int counter=0;
    int i=0;
    int j=0;

    while (i<FirstQuant or j<SecondQuant)
    {
        if ((i>=FirstQuant) or (j<SecondQuant and FirstArr[i]>SecondArr[j])) 
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

void seq::GetFirstK(bool EndFlg)
{
    int LengthOut=-1;
    // Если это запуск не по достижению конца ппоследовательности, то выводим только первые k элементов, так как они точно меньше, чем всего последующие элементы
    if (EndFlg==0) LengthOut=k; else 
    {LengthOut=NowLenght;} 

    if (!EndFlg)  MergeSort( array, LengthMain ); else MergeSort( array, NowLenght ); 
    first_sorted=1;



    for (int i=0; i<LengthOut; i++)
    {
        cout<<array[i]<<" ";
 
    } 
    
    memcpy( array, array+k, sizeof(int)*k );
    NowLenght=k;


}

void seq::AddElement(int add)
{
    array[NowLenght]=add;
    NowLenght++;
}

int main()
{

  int num_numbers = 0;
  int window=0;

  std::cin >> num_numbers>>window;

    seq PartialSeq(2*window,window);


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

	
	