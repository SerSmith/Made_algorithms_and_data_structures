// Ребро неориентированного графа называется мостом, если удаление этого ребра из графа увеличивает число компонент связности.
// Дан неориентированный граф, требуется найти в нем все мосты.


#include <vector>
#include <iostream>
#include <stack>
#include<set>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;


// Структура для симуляции рекурсиии без рекурсии
struct call{
    explicit call() :now(0), parrent(0), num(0) {}
    explicit call(int a, int b, int i) :now(a), parrent(b), num(i) {}
    int now;
    int parrent;
    int num;
};


class Graph {
public:
    explicit Graph(int number_vertex,int number_edges) :already_was(number_vertex,false),edges(), vec(number_vertex),vertex_num(number_vertex) {}
    // Добавление ребра
    void add(int a, int b,int num);
    // Нахождение мостов
    void FindBridges();

    private:
    // Разметка графа начиная с олпределенной вершины
    void DFS(int zero_vertex);
    // количество вершин графа
    const int vertex_num; 
    // Граф
    vector<vector <int>> vec; 
    // Номера ребер
    multimap<pair<int,int>,int> edges;
    // Вектор мостов
    vector<int> bridges;
    // Были ли мы в вершине
    vector<bool> already_was;

};


void Graph::add(int a, int b,int num) {

    
    vec[a].push_back(b);
    vec[b].push_back(a);
    // Будем хранить сначала меньший узел, потом больший
    edges.insert({pair<int,int>(min(a,b),max(a,b)),num});

    int qwerty;
}




void Graph:: DFS(int zero_vertex) {

    int  in_time[vertex_num];
    int in_time_lowest[vertex_num];
    for (int i=0; i<vertex_num; i++){
        in_time[i]=0;
        in_time_lowest[i]=0;
    }
    stack<call> call_stack;
    int counter=0;
    call_stack.push(call(zero_vertex, -1, 0));

    do {
        call next_call=call_stack.top();
        call_stack.pop();

        int now_vertex = next_call.now;
        int parrent = next_call.parrent;
        int num=next_call.num;

        if (num== vec[now_vertex].size()) {
        int next=now_vertex;
        now_vertex=parrent;
        in_time_lowest[now_vertex] = min (in_time_lowest[now_vertex],in_time_lowest[next]);
                    if (in_time_lowest[next] > in_time[now_vertex]){
                        // Кратное ребро не может быть мостом
                        if (edges.count(pair<int,int>(min(now_vertex,next),max(now_vertex,next)))==1){
                             bridges.push_back(edges.find(pair<int,int>(min(now_vertex,next),max(now_vertex,next)))->second);    
                        }
                        

                    }
        continue; 
        } else if ((num == 0) and (!already_was[now_vertex])) {
                already_was[now_vertex]=true;
                in_time[now_vertex]=counter;
                in_time_lowest[now_vertex]=counter;
                counter+=1;
        }

         int next= vec[now_vertex][num];

        if (next == parrent) {
            call_stack.push( call(now_vertex, parrent,num + 1));
            continue;
            }
         
    if (already_was [next]){
                        in_time_lowest[now_vertex] = min (in_time_lowest[now_vertex],in_time[next]);
                   call_stack.push( call(now_vertex, parrent,num + 1));
                    } else {
                    call_stack.push( call(now_vertex, parrent,num + 1));
                     call_stack.push(call( next ,now_vertex,0));
                    }
                    
    
    } while (!call_stack.empty());
}


void Graph::FindBridges(){
    // Ищем мосты
    for (int i=0; i<vec.size();i++){
        if (!already_was[i]) DFS(i);
  }
//   Выводим результат
ofstream output("bridges.out");
  sort(bridges.begin(),bridges.end());
  output<<bridges.size()<<endl;
  for (int i=0; i<bridges.size(); i++){
    output<<bridges[i]<<" ";
}

}




int main() {

    int number_vertex=0;
    int number_edges=0;
    ifstream input("bridges.in");
    input >> number_vertex >>number_edges;
    Graph graph(number_vertex,number_edges);


    for (int i = 1; i <= number_edges; ++i) {
        int first=0;
        int second=0;
        input>> first >> second;
        graph.add(first-1, second-1,i);
    }

    graph.FindBridges();

    system("pause");
}






