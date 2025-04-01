//dikstra
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto& edge : times) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> minTime(n + 1, INT_MAX);
        minTime[k] = 0;
        pq.push({0, k});

        while (!pq.empty()) {
            int currentTime = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            for (auto& neighbor : adj[currentNode]) {
                int newTime = currentTime + neighbor.second;
                if (newTime < minTime[neighbor.first]) {
                    minTime[neighbor.first] = newTime;
                    pq.push({newTime, neighbor.first});
                }
            }
        }

        int maxTime = *max_element(minTime.begin() + 1, minTime.end());
        return (maxTime == INT_MAX) ? -1 : maxTime;
    }
};

int main() {
    Solution sol;
    
    vector<vector<int>> times = {
        {1, 2, 4},
        {1, 3, 2},
        {2, 4, 2},
        {3, 4, 1}
    };
    int n = 4;
    int k = 1;

    cout << sol.networkDelayTime(times, n, k) << endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> dijkstra(int n, vector<vector<int>>& relations, int src) {
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto& edge : relations) {
            adj[edge[0]].push_back({edge[1], edge[2]});
            adj[edge[1]].push_back({edge[0], edge[2]});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> minDist(n + 1, INT_MAX);
        minDist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (currentDist > minDist[currentNode]) continue;

            for (auto& neighbor : adj[currentNode]) {
                int newDist = currentDist + neighbor.second;
                if (newDist < minDist[neighbor.first]) {
                    minDist[neighbor.first] = newDist;
                    pq.push({newDist, neighbor.first});
                }
            }
        }
        return minDist;
    }
};

int main() {
    Solution sol;
    
    vector<vector<int>> relations = {
        {1, 2, 1},
        {1, 3, 4},
        {2, 3, 2},
        {2, 4, 5},
        {3, 4, 1}
    };
    int n = 4;
    int src = 1;
    
    vector<int> shortestPaths = sol.dijkstra(n, relations, src);
    
    cout << "Shortest relationship paths from person " << src << ":\n";
    for (int i = 1; i <= n; i++) {
        cout << "To person " << i << " -> ";
        if (shortestPaths[i] == INT_MAX) cout << "No connection";
        else cout << shortestPaths[i];
        cout << endl;
    }
    
    return 0;
}

//prims
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    int minimumSpanningTree(int n, vector<vector<int>>& relations) {
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto& edge : relations) {
            adj[edge[0]].push_back({edge[1], edge[2]});
            adj[edge[1]].push_back({edge[0], edge[2]});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<bool> inMST(n + 1, false);
        pq.push({0, 1}); // Start from person 1
        int totalWeight = 0;

        while (!pq.empty()) {
            int weight = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (inMST[node]) continue;
            inMST[node] = true;
            totalWeight += weight;

            for (auto& neighbor : adj[node]) {
                if (!inMST[neighbor.first]) {
                    pq.push({neighbor.second, neighbor.first});
                }
            }
        }
        return totalWeight;
    }
};

int main() {
    Solution sol;
    
    vector<vector<int>> relations = {
        {1, 2, 1},
        {1, 3, 4},
        {2, 3, 2},
        {2, 4, 5},
        {3, 4, 1}
    };
    int n = 4;

    cout << "Total relationship strength (MST weight): " << sol.minimumSpanningTree(n, relations) << endl;
    return 0;
}

//bellmanford


#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> bellmanFord(int n, vector<vector<int>>& relations, int src) {
        vector<int> minDist(n + 1, INT_MAX);
        minDist[src] = 0;

        for (int i = 1; i < n; i++) {
            for (auto& edge : relations) {
                int u = edge[0], v = edge[1], weight = edge[2];
                if (minDist[u] != INT_MAX && minDist[u] + weight < minDist[v]) {
                    minDist[v] = minDist[u] + weight;
                }
            }
        }

        for (auto& edge : relations) {
            int u = edge[0], v = edge[1], weight = edge[2];
            if (minDist[u] != INT_MAX && minDist[u] + weight < minDist[v]) {
                cout << "Negative weight cycle detected!\n";
                return {};
            }
        }

        return minDist;
    }
};

int main() {
    Solution sol;
    
    vector<vector<int>> relations = {
        {1, 2, 1},
        {1, 3, 4},
        {2, 3, 2},
        {2, 4, 5},
        {3, 4, 1}
    };
    int n = 4;
    int src = 1;
    
    vector<int> shortestPaths = sol.bellmanFord(n, relations, src);
    
    if (!shortestPaths.empty()) {
        cout << "Shortest relationship paths from person " << src << ":\n";
        for (int i = 1; i <= n; i++) {
            cout << "To person " << i << " -> ";
            if (shortestPaths[i] == INT_MAX) cout << "No connection";
            else cout << shortestPaths[i];
            cout << endl;
        }
    }
    
    return 0;
}


//Floyd-Warshall

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    vector<vector<int>> floydWarshall(int n, vector<vector<int>>& relations) {
        vector<vector<int>> dist(n + 1, vector<int>(n + 1, INT_MAX));
        
        for (int i = 1; i <= n; i++) {
            dist[i][i] = 0;
        }
        
        for (auto& edge : relations) {
            int u = edge[0], v = edge[1], weight = edge[2];
            dist[u][v] = weight;
            dist[v][u] = weight;
        }
        
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                        dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        
        return dist;
    }
};

int main() {
    Solution sol;
    
    vector<vector<int>> relations = {
        {1, 2, 1},
        {1, 3, 4},
        {2, 3, 2},
        {2, 4, 5},
        {3, 4, 1}
    };
    int n = 4;
    
    vector<vector<int>> shortestPaths = sol.floydWarshall(n, relations);
    
    cout << "Shortest relationship paths between all people:\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (shortestPaths[i][j] == INT_MAX) cout << "INF ";
            else cout << shortestPaths[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
