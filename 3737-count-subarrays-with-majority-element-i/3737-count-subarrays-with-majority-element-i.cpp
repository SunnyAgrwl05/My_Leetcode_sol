class Solution {
public: // code written by sunny
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = i; j < n; j++) {
                if (nums[j] == target) count++;
                int len = j - i + 1;
                // majority condition: count > len/2
                // float avoid karne ke liye: 2*count > len
                if (2 * count > len) ans++;
            }
        }

        return ans;
    }
};