class Solution {
public: // code written by sunny
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> comp(n);
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            comp[i] = comp[i-1] + (nums[i] - nums[i-1] > maxDiff ? 1 : 0);
        }
        
        vector<bool> answer;
        answer.reserve(queries.size());
        for (auto& q : queries) {
            int u = q[0], v = q[1];
            answer.push_back(comp[u] == comp[v]);
        }
        return answer;
    }
};