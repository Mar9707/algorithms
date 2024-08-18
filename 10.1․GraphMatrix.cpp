#include <iostream>
#include <vector>
#include <stack>
#include <queue>


class Graph {
    private:
    int size;
    std::vector<std::vector<int>> adjMatrix;

    void dfsRec(int x, std::vector<bool>& isVisited){
        isVisited[x] = true;
        std::cout << x << " ";

        for(int i = 0; i < size; ++i){
            if(adjMatrix[x][i] && !isVisited[i]){
                dfsRec(i, isVisited);
            }
        }
    }


     void bfs(int u, std::vector<bool>& visited) {
        std::queue<int> queue;

        queue.push(u);
        visited[u] = true;

        while (!queue.empty()) {
            int x = queue.front();
            queue.pop();
            std::cout << x << " ";

            for (int v = 0; v < size; ++v) {
                if (adjMatrix[x][v] != 0 && !visited[v]) {
                    queue.push(v);
                    visited[v] = true;
                }
            }
        }
    }



    public:
    Graph (int x) : size{x} {
        adjMatrix.resize(size, std::vector<int>(size, 0));
    }


    void dfsIter (int x){
         if (x >= size) {
            throw std::out_of_range("Invalid vertex index");
        }

        std::vector<bool> isVisited (size, false);
        std::stack<int> st;
        st.push(x);
        isVisited[x] = true;

        while(!st.empty()){
            int tmp = st.top();
            st.pop();
            std::cout << tmp << " ";

            for(int i = 0; i < size; ++i){
                if(adjMatrix[tmp][i] && !isVisited[i]){
                    isVisited[i] = true;
                    st.push(i);
                }
            }
        }
    }


    void dfsRecWrapper (int x){
        if(x >= size){
            throw std::out_of_range("Error");
        }

        std::vector<bool> isVisited (size, false);
        dfsRec(x, isVisited);
        std::cout << std::endl;
    }


    void bfsWrapper(int u) {
        if (u >= size) {
            throw std::out_of_range("Invalid vertex index");
        }
        std::vector<bool> visited(size, false);
        bfs(u, visited);
        std::cout << std::endl;
    }


    int componentCounterDFS(){ // extra case for dfs
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


    int componentCounterBFS() { //extra case for bfs
        int count = 0;
        std::vector<bool> isVisited (size, false);

        for(int i = 0; i < size; ++i){
            if(!isVisited[i]){
                bfs(i, isVisited);
                ++count;
            }
        }
        return count;
    }


    void addEdge (int u, int v){
        if(u >= size || v >= size){
            throw std::out_of_range("Error");
        }

        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // for undirected graph
    }


    void addVertex (){
        ++size;

        for(auto& row : adjMatrix){
            row.push_back(0);
        }

        adjMatrix.push_back(std::vector<int>(size, 0));
    }


    int getShortestPath (int source, int dest){ //for undirected graph, count of levels 
        if(source >= size || dest >= size){
            throw std::out_of_range("Error");
        }

        return getShortestPat
    }

    void transpose(std::vector<std::vector<int>>& graph) {
    std::vector<std::vector<int>> newGraph(graph.size(), std::vector<int>(graph.size(), 0));

    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            if (graph[i][j]) {
                newGraph[j][i] = 1;
            }
        }
    }

    graph = newGraph;
}

bool dfsForShortestPath(const std::vector<std::vector<int>>& graph, int current, int dest, std::vector<int>& parents) {
    if (current == dest) return true;

    for (int i = 0; i < graph.size(); ++i) {
        if (graph[current][i] && parents[i] == -1) {
            parents[i] = current;
            if (dfsForShortestPath(graph, i, dest, parents)) {
                return true;
            }
        }
    }
    return false;
}

std::vector<int> getShortestPathInUndirectedGraph(const std::vector<std::vector<int>>& graph, int source, int dest) {
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
            int tmp = que.front();
            que.pop();

            if(tmp == dest){
                break;
            }

            for(int i = 0; i < graph.size(); ++i){
                if(graph[tmp][i] && parents[i] == -1){
                    parents[i] = tmp;
                    que.push(i);
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


    int bfsCountNodes(std::vector<std::vector<int>>& graph, int source, int level){
        std::queue<int> que;
        que.push(source);

        while(!que.empty() && level){
            int size = que.size();

            for(int i = 0; i < size; ++i){
                int tmp = que.front();
                que.pop();

                for(int j = 0; j < graph.size(); ++j){
                    if(graph[tmp][j]){
                        que.push(j);
                    }
                }
            }
            --level;
        }
        return que.size();
    }


    int dfsCountNodes (std::vector<std::vector<int>>& graph, int source, int level){
        if(level == 0) return 1;

        int count = 0;

        for(int i = 0; i < graph.size(); ++i){
            if(graph[source][i]){
                count += dfsCountNodes(graph, i, level - 1);
            }
        }

        return count;
    }


    void helperAllPossiblePath (std::vector<std::vector<int>>& graph, int source, int target, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& paths){
        path.push_back(source);

        if(source == target){
            paths.push_back(path);
        } else {
            visited[source] = true;

            for(int i = 0; i < graph.size(); ++i){
                if(graph[source][i]){
                    if(!visited[i]){
                        helperAllPossiblePath(graph, i, target, visited, path, paths);
                    }
                }
            }
            visited[source] = false;
        }
        path.pop_back();
    }

    std::vector<std::vector<int>> allPossiblePath(std::vector<std::vector<int>>& graph, int source, int target){
        std::vector<std::vector<int>> paths;
        std::vector<int> path;
        std::vector<bool> visited (graph.size(), false);

        helperAllPossiblePath(graph, source, target, visited, path, paths);

        return paths;
    }


    std::vector<std::vector<int>> bfsAllPossiblePaths(std::vector<std::vector<int>>& graph, int source, int target){
        std::vector<std::vector<int>> paths;
        std::queue<std::vector<int>> que;

        que.push({source});

        while(!que.empty()){
            std::vector<int> path = que.front();
            que.pop();

            int lastNode = path.back();

            if(lastNode == target){
                paths.push_back(path);
            } else {
                for(int i = 0; i < graph.size(); ++i){
                    if(graph[lastNode][i]){
                        std::vector<int> newPath = path;
                        newPath.push_back(i);

                        que.push(newPath);

                    }
                }
            }
        }   

        return paths;
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
    g.addVertex();
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