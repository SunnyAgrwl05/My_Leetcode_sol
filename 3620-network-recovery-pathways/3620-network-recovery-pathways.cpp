class Solution {
public: // code written by sunny
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size(), m = edges.size();
        vector<vector<int>> adjIdx(n);
        vector<int> indeg(n, 0);
        for (int i = 0; i < m; i++) {
            adjIdx[edges[i][0]].push_back(i);
            indeg[edges[i][1]]++;
        }

        // topo sort (Kahn's)
        vector<int> topo; topo.reserve(n);
        vector<int> indeg2 = indeg;
        queue<int> q;
        for (int i = 0; i < n; i++) if (indeg2[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            topo.push_back(u);
            for (int idx : adjIdx[u]) {
                int v = edges[idx][1];
                if (--indeg2[v] == 0) q.push(v);
            }
        }

        vector<int> costs;
        costs.reserve(m);
        for (auto &e : edges) costs.push_back(e[2]);
        sort(costs.begin(), costs.end());
        costs.erase(unique(costs.begin(), costs.end()), costs.end());

        const long long INF = LLONG_MAX / 2;

        auto check = [&](long long T) -> bool {
            vector<long long> dist(n, INF);
            dist[0] = 0;
            for (int u : topo) {
                if (dist[u] >= INF || !online[u]) continue;
                for (int idx : adjIdx[u]) {
                    int v = edges[idx][1];
                    long long c = edges[idx][2];
                    if (c < T || !online[v]) continue;
                    if (dist[u] + c < dist[v]) dist[v] = dist[u] + c;
                }
            }
            return dist[n - 1] <= k;
        };

        int lo = 0, hi = (int)costs.size() - 1, ans = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (check(costs[mid])) { ans = costs[mid]; lo = mid + 1; }
            else hi = mid - 1;
        }
        return ans;
    }
};