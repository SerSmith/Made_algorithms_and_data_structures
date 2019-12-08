/* Задание 8
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.

1_2. Для разрешения коллизий используйте двойное хеширование.


 Дата 26.11*/

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class HashTable {
public:
  explicit HashTable();
  ~HashTable();
  HashTable(const HashTable&) = delete;
  HashTable(HashTable&&) = delete;
  HashTable& operator=(const HashTable&) = delete;
  HashTable& operator=(HashTable&&) = delete;
// Проверка имеется ли объект вхэш таблице 
  bool Has(string data);
// Добавление объекта в Хэш таблицу
  bool Add(string data);
// Удаление объекта из хэш таблицы  
  bool Remove(string data);
private:
    // Увеличение размера таблицы 
    void reHash();
    vector<string> table;
    // Вектор статустов удаляли или не
    vector<int> deleted;
    // Хэщ функция, реализованная по схеме горнера, может запускаться в режиме 1 и 
    // 2(для разных реализаций)
    int Hash_gorner(int mode, string data);
    // Размер таблицы
    int size;
    // Размер по умолчанию
    int initial_size=8;
    // Количество элементов
    int elements;
    // Множитель для схемы Горнера хэш функции 1
    const int mod1 = 255;
    // Множитель для схемы Горнера хэш функции 2
    const int mod2 = 127;

};

HashTable::HashTable() {
    elements = 0;
    table.assign(initial_size,"");
    deleted.assign(initial_size,0);
    size = initial_size;
}

 HashTable::~HashTable(){
 }

int HashTable::Hash_gorner(int mode, string data) {
    int result = 0;
    int mod_now=0;
    if (mode==1) {
        mod_now=mod1;
    } else {
        mod_now=mod2;
    }

    for (int i = 0; i < data.size(); ++i) {
        result = (result * mod_now % size + data[i]) % size;
    }
    if (mode==1) {
    return result % size;
    } else {
        // Гарантируем нечетность
    return (2*result+1) % size;
    }
}




bool HashTable::Add(string data) {
// Если объект уже имеется возвращаем ошибку
    if (Has(data))
        return false;

    int first_Hash = Hash_gorner(1,data);
    int second_Hash = Hash_gorner(2,data);
    
    for (int i = 0; i < size; ++i) {
        if (deleted[first_Hash] == 0 || deleted[first_Hash] == 1) {
            table[first_Hash] = data;
            deleted[first_Hash] = -1;
         // Если таблица недостаточно большая расширимся
         if (size <= (elements++) * 4/3) {
            reHash();
        }

            return true;
        }
        first_Hash = (first_Hash + second_Hash) % size;
    }
    return false;
}

bool HashTable::Remove(string data) {

    int first_Hash = Hash_gorner(1,data);
    int second_Hash = Hash_gorner(2,data);
    
    if (!Has(data))
        return false;

    for (int i = 0; i < size; ++i) {

        if (deleted[first_Hash] != 0) {

            if ((table[first_Hash] == data) && (deleted[first_Hash] == -1)) {
                deleted[first_Hash] = 1;
                // elements=elements-1;
                return true;
            }
            else if ((table[first_Hash] == data) && (deleted[first_Hash] == 1)) {
                return false;
            }
        }
        first_Hash = (first_Hash + second_Hash) % size;
    }
    return false;
}

bool HashTable::Has(string data) {

    int first_Hash = Hash_gorner(1,data);
    int second_Hash = Hash_gorner(2,data);
    
    for (int i = 0; i < size; ++i) {
    
        if (deleted[first_Hash] != 0) {
    
            if (table[first_Hash] == data && deleted[first_Hash] == -1)
    
                return true;
    
            else if (deleted[first_Hash] == 1 && table[first_Hash] == data)
    
                return false;
        }
        else
            return false;
        first_Hash = (first_Hash + second_Hash) % size;
    }
    return false;
}

void HashTable::reHash() {
    size = 2*size;

    vector<string> old_table=table;
    vector<int> old_deleted=deleted;
    table.assign(size,"");
    deleted.assign(size,0);

    for (int i = 0; i < old_table.size(); ++i) {
        if (old_deleted[i] == -1) {
           Add(old_table[i]);
        }

    }

}



int main() {
    HashTable table;
    char command;
    while (cin >> command) {
        string input, in_string;
        cin >> in_string;
        if (command == '+') {
            if (table.Add(in_string)) {
                cout << "OK" << endl;
            }
            else {
                cout << "FAIL" << endl;
            }
        }
        else if (command == '-') {
            if (table.Remove(in_string)) {
                cout << "OK" << endl;
            }
            else {
                cout << "FAIL" << endl;
            }
        }
        else if (command == '?') {
            if (table.Has(in_string)) {
                cout << "OK" << endl;
            }
            else {
                cout << "FAIL" << endl;
            }
        }
    }
    return 0;
}