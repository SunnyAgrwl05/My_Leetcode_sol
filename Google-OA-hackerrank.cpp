#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
// code written by sunny
string getPattern(const string &s) {
    unordered_map<char, int> mp;
    string pattern;
    int idx = 0;
    for (char c : s) {
        if (mp.find(c) == mp.end()) {
            mp[c] = idx++;
        }
        pattern += to_string(mp[c]) + ",";
    }
    return pattern;
}

vector<int> solve(int N, int Q, vector<string> &S, vector<string> &K) {
    unordered_map<string, int> freq;
    for (int i = 0; i < N; i++) {
        string p = getPattern(S[i]);
        freq[p]++;
    }
    vector<int> ans(Q);
    for (int i = 0; i < Q; i++) {
        string p = getPattern(K[i]);
        ans[i] = freq.count(p) ? freq[p] : 0;
    }
    return ans;
}

int main() {
    int N = 4, Q = 1;
    vector<string> S = {"abaca", "efefe", "trtft", "rtrcr"};
    vector<string> K = {"hwhoh"};
    vector<int> result = solve(N, Q, S, K);
    for (int x : result) cout << x << " ";
    return 0;
}
