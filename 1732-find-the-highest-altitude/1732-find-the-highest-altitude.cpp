class Solution {
public: // code written by sunny
    int largestAltitude(vector<int>& gain) {
        int curr = 0, maxAlt = 0;
        
        for (int g : gain) {
            curr += g;
            maxAlt = max(maxAlt, curr);
        }
        
        return maxAlt;
    }
};