class Solution {
public: // code written by sunny
    int maximumLength(vector<int>& nums) {
        int n = nums.size();
        
        map<int, int> mp;
        for (int i = 0; i < n; i++) mp[nums[i]]++;
        
        int ans = 0;
        
        if (mp[1] % 2 == 1) ans = mp[1];
        else ans = mp[1] - 1;
        
        for (int i = 2; i * i <= 1e9; i++) {
            long long num = i;
            int cnt = 0;
            
            while (num <= 1e9) {
                if (mp.find(num) == mp.end()) break;
                if (mp[num] >= 2) cnt += 2, num *= num;
                else {
                    cnt++;
                    break;
                }
            }
            
            if (mp.find(num) == mp.end()) cnt--;
            ans = max(ans, cnt);
        }
        
        return ans;
    }
};