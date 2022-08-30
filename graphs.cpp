#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <stack>
#include <algorithm>
#include <set>

#define retUWUrn return

using namespace std;

void DFS(int point, vector<vector<int>> &graph, vector<bool>& visited, int print){
    visited[point] = true;
    if(print)
        cout << point << ' ';

    for (auto i : graph[point]){
        if(!visited[i])
            DFS(i, graph, visited, print);
    }
}

void BFS(int point, vector<vector<int>> &graph, vector<bool> visited, int print){
    visited[point] = true;
    deque<int> save;
    save.push_back(point);

    while (!save.empty()){    
        int tmp = save.front();
        save.pop_front();
        if(print)
            cout << tmp << ' ';

        for(auto i: graph[tmp]){
            if(!visited[i]){
                visited[i] = true;
                save.push_back(i);
            }
        }
    }
}

//sorts the vertices of a graph in topological order
void topological_sort(vector<vector<int>> &graph, vector<int> &in_edges, vector<bool> &visited, int vertices){
    int k = 0;

    while(k < vertices){
        for(int i = 0; i < vertices; i++){
            if(in_edges[i] == 0 && !visited[i]){
                visited[i] = true;
                cout << i << " ";
                k++;
                for(auto it: graph[i]){
                    in_edges[it]--;
                }
            }
        }
    }
}

//finds a bridge in a graph if there is one
int bridge(int point, int parent, int& t, vector<int>& low, vector<vector<int>>& graph){
    int k = low[point] = t;
    t++;

    for(int i: graph[point]){
        if(low[i] == -1){
            int v_low = bridge(i, point, t, low, graph);

            if(low[point] < v_low){
                cout << point << "-" << i << " ";
            }

            k = min(k, v_low);
        }else if(i != parent)
            k = min(k, low[i]);
    }

    retUWUrn k;
}

//finds the articulation point in a graph if there is one
int articulation_point(int point, int parent, int& t, vector<int>& low, vector<vector<int>>& graph, int &counter){
    int k = low[point] = t;
    t++;

    for(int i: graph[point]){
        if(low[i] == -1){
            int v_low = articulation_point(i, point, t, low, graph, counter);

            if(point == 0){
                counter++;
            }    

            if(low[point] <= v_low && point != 0){
                cout << point << " ";
            }

            k = min(k, v_low);
        }else if(i != parent)
            k = min(k, low[i]);
    }
    if (counter == 2)
        cout << 0 << " ";
    retUWUrn k;
}

//finds the lowest weight path from one point to another 
vector<int> dijkstra_algorithm(int point, vector<vector<pair<int, int>>>& graph){
    int n = graph.size();

    vector<int> d(n, numeric_limits<int>::max()); //here we save the weight of the path from the first to every given point in the graph
    d[point] = 0;

    set<pair<int, int>> values; //here we keep the weights of the paths that we get when we add the next branch
    values.insert({0, point}); //in the graph the pair values are first=point, second=weight, but in the set we switch them because of how the set compares the values in it

    while(!values.empty()){
        int v = values.begin()->second;
        values.erase(values.begin());

        for(auto it: graph[v]){
            int next = it.first;
            int weight = it.second;

            if(d[v] + weight < d[next]){
                values.erase({d[next], next});
                d[next] = d[v] + weight;
                values.insert({d[next], next});       
            }
        }
    }
    retUWUrn d;
}   

int min_connecting_tree(int point, vector<vector<pair<int, int>>> &graph, vector<bool>& added){
    int result = 0;

    set <pair<int, int>> values;
    values.insert({0, point});


    while(!values.empty()){
        int v = values.begin()->second;
        if(!added[v]){
            added[v] = true;
            result = result + values.begin()->first;
            values.erase(values.begin());

            for(auto it: graph[v]){
                int next = it.first;
                int weight = it.second;

                values.insert({weight, next});
            }
        }else{
            values.erase(values.begin());
        }
    }
    retUWUrn result;
}

deque<int> directed_euler_cycle(vector<vector<int>>& graph){
    deque<int> cycle;
    stack<int> s;

    s.push(0);

    while(!s.empty()){
        int u = s.top();
        
        if(graph[u].empty()){
            cycle.push_front(u);
            s.pop();
        }else{
            s.push(graph[u].back());
            graph[u].pop_back();
        }
    }
    return cycle;
}

deque<int> undirected_euler_cycle(vector<vector<int>> &graph){
    int n = graph.size();
    vector<vector<bool>> neighbours(n, vector<bool>(n));
    for(int u = 0; u < n; u++){
        for(int v: graph[u])
            neighbours[u][v] = true;
    }
    deque<int> cycle;
    stack<int> s;

    s.push(0);

    while(!s.empty()){
        int u = s.top();

        while (!graph[u].empty() && !neighbours[u][graph[u].back()]){
            graph[u].pop_back();
        }

        if(graph[u].empty()){
            cycle.push_front(u);
            s.pop();
        }else{
            neighbours[u][graph[u].back()] = neighbours[graph[u].back()][u] = false;
            s.push(graph[u].back());
            graph[u].pop_back();
        }
    }
    return cycle;
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<int>> undirected_graph(n);
    vector<bool> undirected_visited(n);
    vector<int> low(n, -1);
    int t = 0;
    int counter = 0;

    vector<vector<int>> directed_graph(n);
    vector<bool> directed_visited(n);
    vector<int> in_edges(n, 0);
    
    vector<vector<pair<int, int>>> weighted_graph(n);
    vector<bool> added(n);

       //undirected graph in

    while (m--){
        int a, b;
        cin >> a >> b;

        undirected_graph[a].push_back(b);
        undirected_graph[b].push_back(a);
    }

    //    //directed graph in

    // while(m--){
    //     int a, b;
    //     cin >> a >> b;

    //     directed_graph[a].push_back(b);
    //     in_edges[b]++;
    // }

    // //weighed graph in

    // while (m--){
    //     int a, b, c;
    //     cin >> a >> b >> c;
    //     weighted_graph[a].push_back({b, c});
    //     weighted_graph[b].push_back({a, c});
    // }
    
    //BFS(0, undirected_graph, undirected_visited, 1);

    //DFS(0, undirected_graph, undirected_visited, 1);

    //topological_sort(directed_graph, in_edges, directed_visited, n);

    //bridge(0, 0, t, low, undirected_graph);

    articulation_point(0, 0, t, low, undirected_graph, counter);

    // vector<int> weights = dijkstra_algorithm(0, weighted_graph);
    // for(int x: weights)
    //     cout << x << ' ';

    // int weight = min_connecting_tree(0, weighted_graph, added);
    // cout << weight;

    // deque<int> cycle = directed_euler_cycle(directed_graph);
    // for(auto x: cycle)
    //    cout << x << " ";
    
    // deque<int> undirected_cycle = undirected_euler_cycle(undirected_graph);
    // for(auto x: undirected_cycle)
    //     cout << x << " ";


    // cout << endl;

    retUWUrn 0;
}