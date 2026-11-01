class Solution {
public: // code written by sunny
    int minMoves(vector<int>& nums) {
        int mini = *min_element(nums.begin(), nums.end());
        int sum = 0;
        for (int num: nums){
            sum += num - mini;
        
        }
        return sum;
    }
};










// class Solution {
// public:
//     int minMoves(vector<int>& nums) {
//         int mini = *min_element(nums.begin(), nums.end());
//         int sum = 0;

//         for (int num : nums) {
//             sum += num - mini;
//         }

//         return sum;
//     }
// };