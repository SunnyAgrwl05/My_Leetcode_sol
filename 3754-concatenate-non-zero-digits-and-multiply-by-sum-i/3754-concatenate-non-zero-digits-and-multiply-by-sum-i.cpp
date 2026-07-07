class Solution {
public: // code written by sunny
    long long sumAndMultiply(int n) {
        if (n == 0) return 0;
        
        string digits = to_string(n);
        long long x = 0;
        long long sum = 0;
        
        for (char c : digits) {
            int d = c - '0';
            if (d != 0) {
                x = x * 10 + d;
                sum += d;
            }
        }
        
        return x * sum;
    }
};