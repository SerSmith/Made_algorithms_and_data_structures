#include<iostream>

struct Point {
	int X;
	int Y;

	Point() : X(0), Y(0) {}
	Point(int x, int y) : X(x), Y(y) {}
};

// 1
// �������������� �������� ������ ��� ��������� �������� ���������������� �����
// �� ������, ��� ��� �� ���� ��� ����� ���������� ������ ���� �������� ������
bool operator < (const Point& l, const Point& r) {
	return l.X < r.X;
}

// 2
// ���������������� ������� ���������
// �� ������, ��� ��� ������ ������ �������� ���������
bool IsLessByX(const Point& l, const Point& r) {
	return l.X < r.X;
}

// 3
// ������������� ������� ��������� ��� ��� �����, ��� ������� �������� �������� ������
template<class T>
bool IsLessDefault(const T& l, const T& r) {
	return l < r;
}

// 4
// ���������������� �������. ��������� ����� ��������� � ������� ���������
// ������ ������������ �������� � ������� ����� ����������� ���������
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
// ������������� ������� ��� ��� �����, ��� ������� �������� �������� ������
template<class T>
class IsLessDefaultFunctor {
public:
	bool operator()(const T& l, const T& r)
	{
		return l < r;
	}
};

// ���������� � ��������� [l, r]
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
	// ���������� ��� ������ ������������ ��������� ������
	Sort(arr1, 0, 3);

	Point arr[4] = { Point(0, 0), Point(2, 4), Point(1, 2), Point(5, 4) };
	// ���������� ��� ������ ������-�������
	Sort(arr, 0, 3, [](const Point& l, const Point& r) { return l.X + l.Y < r.X + r.Y; });
	// ���������� ��� ������ ������� ���������
	Sort(arr, 0, 3, IsLessByX);
	// ���������� ��� ������ ��������. ������� ��������� ��� ��������� ���������� ������
	Sort(arr, 1, 3, IsLessByPoint(arr[0]));
	// ��� ���� ���������� ��� ������ ��������. ������� �������� �������
	IsLessByPoint isLess(arr[0]);
	Sort(arr, 1, 3, isLess);

	for (int i = 0; i < 4; i++)
		std::cout << arr[i].X << ", " << arr[i].Y << " | ";
	return 0;
}
