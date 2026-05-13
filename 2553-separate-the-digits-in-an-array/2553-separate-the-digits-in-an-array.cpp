class Solution {
public: // code written by sunny
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> answer;

        for (int num : nums) {
            string s = to_string(num);

            for (char ch : s) {
                answer.push_back(ch - '0');
            }
        }

        return answer;
    }
};