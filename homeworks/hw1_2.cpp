// Скрипт, вычисление операций для "сломанного компьютера"
// 06.11

#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;



class heap {
	// Класс куча
public:
	heap();
	~heap();

// Получить ответ нна задачу
int get_answer();

//Дорбавление элемента в кучу 
void add_element(int num);

private:

// Просеивание вниз
void SiftDown(int i);

// Просеивание вsth[]
void SiftUp(int i);


// Куча с данными
vector<int> vec;

};



heap::heap()
{
	vector<int> vec;

}

heap::~heap()
{

}

void heap::SiftDown(int i) {

if (i*2+1>=vec.size()) {
// Если потомков нет, то и делать нечего 

} else if (i*2+2==vec.size())
{
// Если потомок ровно 1
if (vec[i]>vec[2*i+1])
{
	swap(vec[i],vec[2*i+1]);
}

} else if (vec[i]>min(vec[2*i+1],vec[2*i+2]))
{
	// Если потомка 2
	int j=0;
	if (vec[2*i+1]<vec[2*i+2])
	 {
		 j=2*i+1;
		 }	else 
		 {
			 j=2*i+2                            ;
			 }
	swap(vec[i],vec[j]);
	SiftDown(j);
}
}




void heap::SiftUp(int i) {
  
  if (i==0) {
  }
  if (vec[i]<vec[(i-1)/2]) {

     swap(vec[i], vec[(i-1)/2]);
       
	   SiftUp((i-1)/2);
      }
}



void heap::add_element(int add)
{
	vec.push_back(add);
	SiftUp(vec.size()-1) ;
}

int heap::get_answer()
{
	int time=0;
	int second_smallest=0; //номер второго наименьшего элемента в куче
	int size_start=vec.size();

	for (int i=0; i<size_start-1;i++)
	{
		// второй наименьший элемент в куче может быть только потомком корня, посмотрим какой из них меньше
		// также уччтем кейс, когда второго потомкеа нет
		if (vec.size()<=2) second_smallest=1;  else if (vec[1]>vec[2]) second_smallest=2; else second_smallest=1;
		// новый элемент кучи
		int new_num=vec[0]+vec[second_smallest];
		time+=new_num;
		// Убираем первый элемент
		vec[0]=new_num;
		swap(vec[second_smallest],vec.back());
		vec.pop_back();
		SiftDown(second_smallest);
		SiftDown(0);
	}
	return time;
}

int main()
{

  int num_commands = 0;
  std::cin >> num_commands;
 	heap h;
  for (int i = 0; i < num_commands; ++i) {
	int number=-1;
	  cin>>number;
	h.add_element(number);
  }

cout<<h.get_answer();

  system("pause");
  return 0;
}

	
	