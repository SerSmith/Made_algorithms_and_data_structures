// Дан невзвешенный неориентированный граф. Найдите цикл минимальной длины.


#include <iostream>
#include <vector>
#include <climits>
#include <set>
using namespace std;

int Prim(vector<vector<pair<int, int>>> &graph) {
    // Минимальные расстояния, по умолчанию большое число
    vector<int> min_dist(graph.size(), INT_MAX);
    // Были ли мы уже тут
    vector<char> already_was(graph.size(), 0);
    // Будем всегда начинать с первого узла
    min_dist[0] = 0;
    int out = 0;
    // Множество минимальных расстояний
    set<pair<int, int>> min_set;
    // Множество <минимальное расстояние, номер вершины>
    min_set.insert(pair<int, int>(0, 0));

    // Пока не наберем все вершины
    for(int i=0;i < graph.size();i++) {
        // воспользуемся тем, что set по умолчанию сортируется
        pair<int, int> vertex = *min_set.begin();
        min_set.erase(min_set.begin());
    // Если еще не были в этой вершине
        if (already_was[vertex.second] == false) {
            // мы нашли очередную вершину для добавления
            out += vertex.first;

            for (pair<int, int> j : graph[vertex.second]) {
            //    для ускорения, что бы не обращаться каждый раз к элементу вектора запишем его
                int min_dist_int=min_dist[j.first];

                if (already_was[j.first] == false) {

                    if (j.second < min_dist_int) {
                        // Если найденное расстояние до вершины меньше записанного -обновим
                        
                        min_set.erase(pair<int, int>(min_dist_int, j.first));
                        min_dist[j.first] = j.second;
                        min_set.insert(pair<int, int>(j.second, j.first));

                    }
                }
            }
            already_was[vertex.second] = true;
        }
    }
    return out;
}

int main() {
    int num_vertex=0;
    int num_edges=0;
    cin >> num_vertex >> num_edges;

    vector<vector<pair<int, int>>> graph(num_vertex);

    int start=0;
    int end=0;
    int weight=0;
    for (int i = 0; i < num_edges; ++i) {
        cin >> start >> end >> weight;
        graph[start-1].push_back(pair<int,int>(end-1, weight));
        graph[end-1].push_back(pair<int,int>(start-1, weight));
    }
    cout << Prim(graph);

    system("pause");
    return 0;
}
