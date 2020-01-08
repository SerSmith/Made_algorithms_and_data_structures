#include<iostream>

struct Point {
	int X;
	int Y;

	Point() : X(0), Y(0) {}
	Point(int x, int y) : X(x), Y(y) {}
};

// 1
// Переопределяем оператор меньше для сравнения объектов пользовательских типов
// Не удобно, так как на один тип можно определить только один оператор меньше
bool operator < (const Point& l, const Point& r) {
	return l.X < r.X;
}

// 2
// Пользовательская функция сравнения
// Не удобно, так как нельзя задать контекст сравнения
bool IsLessByX(const Point& l, const Point& r) {
	return l.X < r.X;
}

// 3
// Универсальная функция сравнения для тех типов, для которых определён оператор меньше
template<class T>
bool IsLessDefault(const T& l, const T& r) {
	return l < r;
}

// 4
// Пользовательский функтор. Позволяет перед передачей в функцию сравнения
// задать произвольный контекст в котором будет выполняться сравнение
class IsLessByPoint {
public:
	IsLessByPoint(const Point& _point) : point(_point) {}

	bool operator()(const Point& l, const Point& r)
	{
		return (l.X - point.X) * (l.X - point.X) + (l.Y - point.Y) * (l.Y - point.Y) <
			(r.X - point.X) * (r.X - point.X) + (r.Y - point.Y) * (r.Y - point.Y);
	}

private:
	Point point;
};

// 5
// Универсальный функтор для тех типов, для которых определён оператор меньше
template<class T>
class IsLessDefaultFunctor {
public:
	bool operator()(const T& l, const T& r)
	{
		return l < r;
	}
};

// Сортировка в диапазоне [l, r]
template<class T, class IsLess = IsLessDefaultFunctor<T> >
void Sort(T* arr, int l, int r, IsLess isLess = IsLess())
{
	for (int i = l; i < r; i++)
		for (int j = l; j < r; j++)
			if (isLess(arr[j + 1], arr[j]))
				std::swap(arr[j], arr[j + 1]);
}

int main()
{
	int arr1[4] = { 3, 2, 1, 4 };
	// Сортировка при помощи стандартного оператора меньше
	Sort(arr1, 0, 3);

	Point arr[4] = { Point(0, 0), Point(2, 4), Point(1, 2), Point(5, 4) };
	// Сортировка при помощи лямбда-функции
	Sort(arr, 0, 3, [](const Point& l, const Point& r) { return l.X + l.Y < r.X + r.Y; });
	// Сортировка при помощи функции сравнения
	Sort(arr, 0, 3, IsLessByX);
	// Сортировка при помощи функтора. Функтор передаётся как временный безымянный объект
	Sort(arr, 1, 3, IsLessByPoint(arr[0]));
	// Ещё одна сортировка при помощи функтора. Функтор создаётся заранее
	IsLessByPoint isLess(arr[0]);
	Sort(arr, 1, 3, isLess);

	for (int i = 0; i < 4; i++)
		std::cout << arr[i].X << ", " << arr[i].Y << " | ";
	return 0;
}
