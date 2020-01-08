// Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки ­– n. Время O(n + p), доп. память – O(p).
// Вариант 1. С помощью префикс-функции (алгоритм Кнута-Морриса-Пратта).


#include <vector>
#include <iostream>
#include <string>
using namespace std;

vector<int> Knut_morris_prat(const string templ,const string main_string){
  
    vector<int> out;
    vector<int> prefexes;
    // По началу заполним нашу префикс функцию нулями.
    prefexes.assign(templ.length(),0);

    int count=0;
        for (int i = 1; i < templ.length(); i++)
        {
        // Если мы не вначале подстроки и не совпадаем с символом то возьмеееммм значение префик функции из предыдущего символа
        while (count and templ[count] !=  templ[i]  )  count = prefexes[count - 1];
        if (templ[count] ==  templ[i] )  count++;
        prefexes[i] = count;
    }
    
    count=0;
        for (int i = 0; i < main_string.length(); i++)
        {
        while (count and templ[count] != main_string[i]  )  count = prefexes[count - 1];
        if (templ[count] == main_string[i] )  count++;
        if (count == templ.length() ) out.push_back(i-templ.length()+1);
    }


    return out;
}

int main(){
    string templ="";
    string main_string="";

    cin>>templ;
    cin>>main_string;
    vector<int> out=Knut_morris_prat(templ,main_string);
    
    for (int i = 0; i < out.size(); i++){
        cout<<out[i]<<" ";
    }

    system("pause");
    return 0;
}