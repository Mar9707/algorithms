#include <iostream>
#include <vector>
#include <stack>
#include <queue>


class Graph {
    private:
    int size;
    std::vector<std::vector<int>> adjList;


    void dfsRec(int edge, std::vector<bool>& isVisited){
        isVisited[edge] = true;
        std::cout << edge << " ";

        for(int v : adjList[edge]){
            if(!isVisited[v]){
                dfsRec(v, isVisited);
            }
        }
    }


    void bfs (int edge, std::vector<bool>& isVisited){
        std::queue<int> que;

        que.push(edge);
        isVisited[edge] = true;

        while(!que.empty()){
            int current = que.front();
            que.pop();
            std::cout << current << " ";

            for(int v : adjList[current]){
                if(!isVisited[v]){
                    que.push(v);
                    isVisited[v] = true;
                }
            }
        }
    }


    public:
    Graph(int edge) : size{edge} {
        adjList.resize(size);
    }

    void dfsIter(int edge){
        if(edge >= size) {
            throw std::out_of_range("Error");
        }

        std::stack<int> st;
        std::vector<bool> isVisited (size, false);

        st.push(edge);
        isVisited[edge] = true;

        while (!st.empty()){
            int current = st.top();
            st.pop();

            std::cout << current << " ";

            for(int i = 0; i < adjList[current].size(); ++i){
                int v = adjList[current][i];
                if(!isVisited[v]){
                    st.push(v);
                    isVisited[v] = true;
                }
            }
        }
        std::cout << std::endl;
    }


    void dfsRecWrapper(int edge){
        if(edge >= size){
            throw std::out_of_range("Error");
        }

        std::vector<bool> isVisited (size, false);
        dfsRec(edge, isVisited);
        std::cout << std::endl;
    }


    void bfsWrapper (int edge){
        if(edge >= size){
            throw std::out_of_range("Error");
        }

        std::vector<bool> isVisited (size, false);
        bfs(edge, isVisited);
        std::cout << std::endl;
    }


    int componentCounterDFS(){
        int count = 0;
        std::vector<bool> isVisited (size, false);

        for(int i = 0; i < size; ++i){
            if(!isVisited[i]){
                dfsRec(i, isVisited);
                ++count;
            }
        }
        return count;
    }


    int componentCounterBFS(){
        int count = 0;
        std::vector<bool> isVisited(size, false);

        for(int i = 0; i < size; ++i){
            if(!isVisited[i]){
                bfs(i, isVisited);
                ++count;
            }
        }

        return count;
    }


    void addEdge(int a, int b){
        if (a >= size || b >= size){
            throw std::out_of_range("Error");
        }

        adjList[a].push_back(b);
        adjList[b].push_back(a); //for undirected graph
    }


    void addVerteedge(){
        ++size;
        adjList.resize(size);
    }

    void transpose(std::vector<std::vector<int>>& graph) {
    std::vector<std::vector<int>> newGraph(graph.size());

    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            newGraph[graph[i][j]].push_back(i);
        }
    }

    graph = newGraph;
}

bool dfsForShortestPath(const std::vector<std::vector<int>>& graph, int current, int dest, std::vector<int>& parents) {
    if (current == dest) return true;

    for (int i : graph[current]) {
        if (parents[i] == -1) {
            parents[i] = current;
            if (dfsForShortestPath(graph, i, dest, parents)) {
                return true;
            }
        }
    }
    return false;
}


std::vector<int> getShortestPathInUndirectedGraph(std::vector<std::vector<int>>& graph, int source, int dest) {
    std::vector<int> parents(graph.size(), -1);
    parents[source] = source;

    if (!dfsForShortestPath(graph, source, dest, parents)) {
        return std::vector<int>();
    }

    std::vector<int> path;
    for (int cur = dest; cur != source; cur = parents[cur]) {
        path.push_back(cur);
    }
    path.push_back(source);

        std::reverse(path.begin(), path.end());
    return path;
}


std::vector<int> bfsForShortestPath (const std::vector<std::vector<int>>& graph, int source, int dest){
    std::vector<int> parents(graph.size(), -1);
    std::queue<int> que;

    que.push(source);
    parents[source] = source;

    while(!que.empty()){
        int current = que.front();
        que.pop();

        if(current == dest) break;

        for(int i = 0; i < graph[current].size(); ++i){
            int n = graph[current][i];
            if(parents[n] == -1){
                parents[n] = current;
                que.push(n);
            }
        }
    }

    std::vector<int> path;
    for(int i = dest; i != source; i = parents[i]){
        path.push_back(i);
    }

    path.push_back(source);

    std::reverse(path.begin(), path.end());

    return path;
}


int bfsCountNodes (std::vector<std::vector<int>>& graph, int source, int level){
    std::queue<int> que;
    que.push(source);

    while(level && !que.empty()){
        int size = que.size();

        for(int i = 0; i < size; ++i){
            int current = que.front();
            que.pop();

            for(int j = 0; j < graph[current].size(); ++j){
                que.push(graph[current][j]);   
            }
        }

        --level;
    }
    return que.size();
}


int dfsCountNodes (std::vector<std::vector<int>>& graph, int source, int level){
    if(level == 0) return 1;

    int count = 0;
    for(int i = 0; i < graph[source].size(); ++i){
        count += dfsCountNodes(graph, graph[source][i], level - 1);
    }

    return count;
}


void helperAllPossiblePath (std::vector<std::vector<int>>& graph, int source, int target, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& paths){
    path.push_back(source);

    if(source == target){
        paths.push_back(path);
    } else {
        visited[source] = true;

        for(int i = 0; i < graph[source].size(); ++i){
            int current = graph[source][i];
            if(!visited[current]){
                vec = helperAllPossiblePath(graph, current, target, visited, path, paths);
            }
        }

        visited[source] = false;
    }

    path.pop_back();
}


std::vector<std::vector<int>> allPossiblePath(std::vector<std::vector<int>>& graph, int source, int target){
    std::vector<std::vector<int>> paths;
    std::vector<bool> visited (graph.size(), false);
    std::vector<int> path;

    helperAllPossiblePath(graph, source, target, visited, path, paths);

    return paths;
}


std::vector<std::vector<int>> bfsAllPossiblePaths(const std::vector<std::vector<int>>& graph, int source, int target) {
    std::vector<std::vector<int>> paths;
    std::queue<std::vector<int>> que;

    que.push({source});

    while (!que.empty()) {
        std::vector<int> path = que.front();
        que.pop();

        int lastNode = path.back();

        if (lastNode == target) {
            paths.push_back(path);
        } else {
            for (int i = 0; i < graph[lastNode].size(); ++i) {
                int needgetNode = graph[lastNode][i];

                std::vector<int> newPath = path;
                newPath.push_back(needgetNode);

                que.push(newPath);
            }
        }
    }

    return paths;
}


    bool helperIsCyclic (std::vector<std::vector<int>>& graph, int start, std::vector<bool>& visited, int parent){
        visited[start] = true;
        
        for(int i = 0; i < graph[start].size(); ++i){
            int current = graph[start][i];
            if(current != parent){
                if(visited[current]){
                    return true;
                } else if(helperIsCyclic(graph, current, visited, start)){
                    return true;
                }
            } 
        }
        return false;
    }


    bool isCyclic(std::vector<std::vector<int>>& graph){ //for undirected graph
        std::vector<bool> visited (graph.size(), false);

        for(int i = 0; i < graph.size(); ++i){
            if(!visited[i]){
                if(helperIsCyclic(graph, i, visited, -1)){
                    return true;
                }
            }
        }
        return false;
    }


    bool helperIsCyclicDirectedGraph(std::vector<std::vector<int>>& graph, int start, std::vector<bool>& visited, std::vector<bool>& recursionStack){
        visited[start] = true;
        recursionStack[start] = true;

        for(int i = 0; i < graph[start].size(); ++i){
            int current = graph[start][i];
            if(!visited[current]){
                if(helperIsCyclicDirectedGraph(graph, current, visited, recursionStack)){
                    return true;
                }
            } else if(recursionStack[current]){
                    return true;
            }
        }
        recursionStack[start] = false;
        return false;
    }


    bool isCyclicDirectedGraph(std::vector<std::vector<int>>& graph){  //for directed graph
        std::vector<bool> visited (graph.size(), false);
        std::vector<bool> recursionStack (graph.size(), false);

        for(int i = 0; i < graph.size(); ++i){
            if(!visited[i]){
                if(helperIsCyclicDirectedGraph(graph, i, visited, recursionStack)){
                    return true;
                }
            }
        }
        return false;
    }


    void helperTopSort(std::vector<std::vector<int>>& graph, int start, std::vector<bool>& visited, std::deque<int>& deq){
        visited[start] = true;

        for(int i = 0; i < graph[start].size(); ++i){
            int current = graph[start][i];
            if(!visited[current]){
                helperTopSort(graph, current, visited, deq);
            }
        }
        deq.push_front(start);
    }


    std::deque<int> topSort (std::vector<std::vector<int>>& graph){
        std::vector<bool> visited (graph.size(), false);
        std::deque<int> vec;

        for(int i = 0; i < graph.size(); ++i){
            if (!visited[i]){
                helperTopSort(graph, i, visited, vec);
            }
        }

        return vec;
    }


    std::vector<int> topSortKahn (std::vector<std::vector<int>>& graph){
        std::vector<int> inDegree (graph.size(), 0);
        std::vector<int> result;
        std::queue<int> que;

        for(int i = 0; i < graph.size(); ++i){
            for(int j = 0; j < graph[i].size(); ++j){
                int current = graph[i][j];
                ++inDegree[current];
            }
        }

        for(int i = 0; i < graph.size(); ++i){
            if(inDegree[i] == 0){
                que.push(i);
            }
        }


        while(!que.empty()){
            int current = que.front();
            que.pop();
            result.push_back(current);

            for(int i = 0; i < graph[current].size(); ++i){
                int edge = graph[current][i];
                --inDegree[edge];
                if(inDegree[edge] == 0){
                    que.push(edge);
                }
            }

        }

        if(result.size() != graph.size()){
            throw std::runtime_error("Graph has a cycle.");
        }

        return result;
    }

    void helper1KosarajuSCC(std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::stack<int>& st, int start){
        visited[start] = true;

        for(int i = 0; i < graph[start].size(); ++i){
            int current = graph[start][i];
            if(!visited[current]){
                helper1KosarajuSCC(graph, visited, st, current);
            }
        }
        st.push(start);
    }


    void helper2KosarajuSCC(std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::vector<int>& scc, int start){
        visited[start] = true;
        scc.push_back(start);

        for(int i = 0; i < graph[start].size(); ++i){
            int current = graph[start][i];
            if(!visited[current]){
                helper2KosarajuSCC(graph, visited, scc, current);
            }
        }

    }


    std::vector<std::vector<int>> kosarajuSCC (std::vector<std::vector<int>>& graph){
        std::vector<bool> visited (graph.size(), false);
        std::stack<int> st;

        for(int i = 0; i < graph.size(); ++i){
            if(!visited[i]){
                helper1KosarajuSCC(graph, visited, st, i);
            }
        }


        std::vector<std::vector<int>> trans (graph.size());
        for(int i = 0; i < graph.size(); ++i){
            for(int j = 0; j < graph[i].size(); ++j){
                int current = graph[i][j];
                trans[current].push_back(i);
            }
        }


        std::vector<std::vector<int>> sccs;
        std::fill(visited.begin(), visited.end(), false);
        while(!st.empty()){
            int current = st.top();
            st.pop();

            if(!visited[current]){
                std::vector<int> scc;
                helper2KosarajuSCC(trans, visited, scc, current);
                sccs.push_back(scc);
            }
        }

        return sccs;
    }


    void helperTarjanSCC (std::vector<std::vector<int>>& graph, std::vector<int>& ids, std::vector<int>& low, std::vector<bool>& onStack, std::stack<int>& st, int& indeedge, int verteedge, std::vector<std::vector<int>>& sccs){
        ids[verteedge] = low[verteedge] = indeedge++;
        onStack[verteedge] = true;
        st.push(verteedge);

        for(int i = 0; i < graph[verteedge].size(); ++i){
            int current = graph[verteedge][i];
            if(ids[current] == -1){
                helperTarjanSCC(graph, ids, low, onStack, st, indeedge, current, sccs);
                low[verteedge] = std::min (low[verteedge], low[current]);
            } else if(onStack[current]){
                low[verteedge] = std::min(low[verteedge], ids[current]);
            }
        }

        if(ids[verteedge] == low[verteedge]){
            std::vector<int> scc;
            do {
                int current = st.top();
                st.pop();
                scc.push_back(current);
                onStack[current] = false;
            } while(current != verteedge);
            sccs.push_back(scc);
        }
    }


    std::vector<std::vector<int>> TarjanScc(std::vector<std::vector<int>>& graph){
        std::vector<int> ids (graph.size(), -1);
        std::vector<int> low (graph.size(), -1);
        std::vector<bool> onStack(graph.size(), false);
        std::stack<int> st;
        std::vector<std::vector<int>> sccs;
        int indeedge = 0;

        for(int i = 0; i < graph.size(); ++i){
            if(ids[i] == -1){
                helperTarjanSCC(graph, ids, low, onStack, st,indeedge, i, sccs);
            }
        }
        return sccs;
    }


    std::vector<int> dijkstra (int source, std::vector<std::vector<std::pair<int, int>>>& graph){
        int size = graph.size();
        std::vector<bool> visited (size, false);
        std::vector<int> distance(size, INT_MAX);

        distance[source] = 0;

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, greater<std::pair<int, int>>> pq;

        pq.push({0, source});

        while(!pq.empty()){
            int current = pq.top().second;
            pq.pop();

            if(visited[current]) continue;

            visited[current] = true;

            for(int i = 0; i < graph[current].size(); ++i){
                std::pair<int, int> edge = graph[current][i];
                if(!visited[edge.first] && distance[edge.first] > distance[current] + edge.second){
                    distance[edge.first] = distance[current] + edge.second;
                    pq.push({distance[edge.first], edge.first});
                }
            }
        }
        return distance;
    }


    bool bellmanFord (int source, std::vector<std::vector<std::pair<int,int>>>& graph){
        int size = graph.size();
        std::vector<int> distance (size, INT_MAX);

        distance[source] = 0;

        for(int i = 0; i < size - 1; ++i){
            for(int j = 0; j < size; ++j){
                for(int k = 0; k < graph[j].size(); ++k){
                    int vertex = graph[j][k].first;
                    int weight = graph[j][k].second;

                    if(distance[j] != INT_MAX && distance[j] + weight < distance[vertex]){
                        distance[vertex] = distance[j] + weight;
                    }
                }
            }
        }

        for(int i = 0; i < size; ++i){
            for(int j = 0; j < graph[i].size(); ++j){
                int vertex = graph[i][j].first;
                int weight = graph[i][j].second;

                if(distance[i] != INT_MAX && distance[i] + weight < distance[vertex]){
                    return false;
                }
            }
        }
        return true;
    }
};


int main() {
    // Создаем граф с 5 вершинами
    Graph g(5);

    // Добавляем ребра
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    std::cout << "DFS (рекурсивный) начиная с вершины 0: ";
    g.dfsRecWrapper(0); // DFS рекурсивно

    std::cout << "DFS (итеративный) начиная с вершины 0: ";
    g.dfsIter(0); // DFS итеративно
    std::cout << std::endl;

    std::cout << "BFS начиная с вершины 0: ";
    g.bfsWrapper(0); // BFS

    // Добавляем еще одну вершину
    g.addVerteedge();
    g.addEdge(5, 2); // Добавляем ребро к новой вершине

    std::cout << "DFS (рекурсивный) начиная с вершины 5: ";
    g.dfsRecWrapper(5); // DFS рекурсивно для новой вершины

    std::cout << "DFS (итеративный) начиная с вершины 5: ";
    g.dfsIter(5); // DFS итеративно для новой вершины
    std::cout << std::endl;

    std::cout << "BFS начиная с вершины 5: ";
    g.bfsWrapper(5); // BFS для новой вершины

    // Подсчет компонентов связности
    int componentsDFS = g.componentCounterDFS();
    std::cout << "Количество компонент связности (DFS): " << componentsDFS << std::endl;

    int componentsBFS = g.componentCounterBFS();
    std::cout << "Количество компонент связности (BFS): " << componentsBFS << std::endl;

    return 0;
}