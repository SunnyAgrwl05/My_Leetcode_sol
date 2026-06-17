 class Solution {
    // code written by sunny
    string num;
    int n;
    
    long long cnt[17][2][2];
    bool cntVis[17][2][2];
    
    long long wav[17][10][11][2][2];
    bool wavVis[17][10][11][2][2];
    
    long long countNums(int pos, int tight, int started) {
        if (pos == n) return started ? 1 : 0;
        if (cntVis[pos][tight][started]) 
            return cnt[pos][tight][started];
        cntVis[pos][tight][started] = true;
        
        int lim = tight ? (num[pos] - '0') : 9;
        long long res = 0;
        for (int d = 0; d <= lim; d++) {
            res += countNums(pos+1, tight&&(d==lim), started||(d!=0));
        }
        return cnt[pos][tight][started] = res;
    }
    
    long long solve(int pos, int p1, int p2, int tight, int started) {
        if (pos == n) return 0;
        if (wavVis[pos][p1][p2][tight][started]) 
            return wav[pos][p1][p2][tight][started];
        wavVis[pos][p1][p2][tight][started] = true;
        
        int lim = tight ? (num[pos] - '0') : 9;
        long long res = 0;
        
        for (int d = 0; d <= lim; d++) {
            int ns = started || (d != 0);
            int nt = tight && (d == lim);
            
            long long completions = countNums(pos+1, nt, ns);
            
            long long contribution = 0;
            if (started && ns && p2 != 10) {
                if (p1 > p2 && p1 > d) contribution = completions;
                else if (p1 < p2 && p1 < d) contribution = completions;
            }
            
            int newP1 = ns ? d : 0;
            int newP2 = ns ? (started ? p1 : 10) : 10;
            
            res += contribution + solve(pos+1, newP1, newP2, nt, ns);
        }
        
        return wav[pos][p1][p2][tight][started] = res;
    }
    
    long long count(long long x) {
        if (x <= 0) return 0;
        num = to_string(x);
        n = num.size();
        memset(cntVis, 0, sizeof(cntVis));
        memset(wavVis, 0, sizeof(wavVis));
        return solve(0, 0, 10, 1, 0);
    }
    
public:
    long long totalWaviness(long long num1, long long num2) {
        return count(num2) - count(num1 - 1);
    }
};