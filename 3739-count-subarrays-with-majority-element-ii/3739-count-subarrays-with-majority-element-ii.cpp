class Solution {
public: //code written by sunny
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size(); 
        vector<int> pre(n + 1);
        pre[0] = 0;
        for (int i = 0; i < n; i++) {
            pre[i+1] = pre[i] + (nums[i] == target ? 1 : -1);
        } 
        int offset = n;
        int sz = 2 * n + 2;
        vector<int> bit(sz + 1, 0);

        auto update = [&](int i) {
            for (i++; i <= sz; i += i & (-i))
                bit[i]++;
        };

        auto query = [&](int i) {
            int s = 0;
            for (i++; i > 0; i -= i & (-i))
                s += bit[i];
            return s;
        }; 
        long long ans = 0;
        for (int i = 0; i <= n; i++) {
            int v = pre[i] + offset;      
            if (v - 1 >= 0)
                ans += query(v - 1);       
            update(v);                       
        }

        return ans;
    }
};