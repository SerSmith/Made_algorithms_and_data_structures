// Дан невзвешенный неориентированный граф. Найдите цикл минимальной длины.


#include <vector>
#include <iostream>
#include <queue>
#include<set>
using namespace std;


class Graph {
public:
    explicit Graph(int number_vertex) : vec(number_vertex), vertexes(),vertex_num(number_vertex) {}
    // Добавление ребра
    void add(int a, int b);
    // Нахождение минимального цикла
    int minCycle();

    private:
    // Разметка графа начиная с олпределенной вершины
    int BFS(int zero_vertex);
    // количество вершин графа
    int vertex_num; 
    // Граф
    vector<vector <int>> vec; 
    // Множество вершин графа
    set<int> vertexes;
};


void Graph::add(int a, int b) {
    vertexes.insert(a);
    vertexes.insert(b);
    
    vec[a].push_back(b);
    vec[b].push_back(a);
}

int Graph:: BFS(int zero_vertex) {
   
    vector<bool> already_was;
    vector<int> depth;
    vector<int> parent;

    already_was.assign(vertex_num, false);
    depth.assign(vertex_num, 0);
    parent.assign(vertex_num, -1);
   
    queue<int> already_added; 
   
    already_added.push(zero_vertex); 
    already_was[zero_vertex] = true;

    while (!already_added.empty()) { 
        int now_vertex = already_added.front();
        already_added.pop();

        vector<int> step; 

        for (int i : vec[now_vertex]) {
            step.push_back(i);
            }
        
    

        for (int i : step) { 
            if (!already_was[i]) {
                already_added.push(i); 
                already_was[i] = true;
                depth[i] = depth[now_vertex] + 1;
                parent[i] = now_vertex;
            }
            else if (i != parent[now_vertex]) { 
                return depth[now_vertex] + depth[i] + 1; 
            }
        }
    }
    return vertex_num + 1;
}

int Graph:: minCycle() {
  

    int minCycle = vertex_num + 1;
    for (set<int>::iterator i = vertexes.begin(); i != vertexes.end(); i++) { 
        minCycle = min(BFS(*i), minCycle);
    }

    if (minCycle==vertex_num + 1){
        // Если цикла нет возвращаем -1
        return -1;
    } else {
        return minCycle;
    }
   ;
}

int main() {
    int number_vertex=0;
    int number_edges=0;

    cin >> number_vertex >>number_edges;
    Graph graph(number_vertex);


    for (int i = 0; i < number_edges; ++i) {
        int first=0;
        int second=0;
        cin >> first >> second;
        graph.add(first, second);
    }

    cout << graph.minCycle();
    system("pause");
}





