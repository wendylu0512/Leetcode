//
//  mydp.h
//  Leetcode
//
//  Created by Wendi Lu on 11/2/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mydp_h
#define Leetcode_mydp_h



int minimumTotal(vector<vector<int> > &triangle) {//Triangle
    for(int i = (int)triangle.size() - 2; i >= 0; i--){
        for(int j = 0; j < i + 1; j++){
            triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
        }
    }
    return triangle[0][0];
}


int maxSubArray(int A[], int n) {//Maximum Subarray
    int result = INT_MIN, f = 0;
    for(int i = 0; i < n; i++){
        f = max(f + A[i], A[i]);
        result = max(result, f);
    }
    return result;
}


int maxProduct(int A[], int n) {//Maximum Product Subarray
    int result = INT_MIN;
    int fmax = 1, fmin = 1;
    for(int i = 0; i < n; i++){
        int temp = fmax;
        fmax = max(max(fmin * A[i], fmax * A[i]), A[i]);
        fmin = min(min(temp * A[i], fmin * A[i]), A[i]);
        result = max(result, fmax);
    }
    return result;
}


int minCut(string s) {//Palindrome Partitioning II
    const int n = (int)s.size();
    int f[n + 1];
    bool p[n][n];
    fill_n(&p[0][0], n * n, false);
    for(int i = 0; i <= n; i++)
        f[i] = i - 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            if(s[i] == s[j] && (i - j < 2 || p[j + 1][i - 1])){
                p[j][i] = true;
                f[i + 1] = min(f[i + 1], f[j] + 1);
            }
        }
    }
    return f[n];
}


int maximalRectangle(vector<vector<char> > &matrix) {//Maximal Rectangle
    if(matrix.size() == 0) return 0;
    const int m = (int)matrix.size();
    const int n = (int)matrix[0].size();
    vector<int> L(n, 0);
    vector<int> H(n, 0);
    vector<int> R(n, n);
    int result = 0;
    for(int i = 0; i < m; i++){
        int left = 0, right = n;
        for(int j = 0; j < n; j++){
            if(matrix[i][j] == '1'){
                H[j]++;
                L[j] = max(L[j], left);
            }else{
                left = j + 1;
                H[j] = 0;
                L[j] = 0;
                R[j] = n;
            }
        }
        for(int j = n - 1; j >= 0; j--){
            if(matrix[i][j] == '1'){
                R[j] = min(R[j], right);
                result = max(result, H[j] * (R[j] - L[j]));
            }else{
                right = j;
            }
        }
    }
    return result;
}


int maxProfit3(vector<int> &prices) {//Best Time to Buy and Sell Stock III
    if(prices.size() < 2) return 0;
    const int n = (int)prices.size();
    vector<int> f(n, 0);
    vector<int> g(n, 0);
    for(int i = 1, valley = prices[0]; i < n; i++){
        valley = min(valley, prices[i]);
        f[i] = max(f[i - 1], prices[i] - valley);
    }
    for(int i = n - 2, peak = prices[n - 1]; i >= 0; i--){
        peak = max(peak, prices[i]);
        g[i] = max(g[i + 1], peak - prices[i]);
    }
    int profit = 0;
    for(int i = 0; i < n; i++){
        profit = max(profit, f[i] + g[i]);
    }
    return profit;
}


bool isInterleave(string s1, string s2, string s3) {//Interleaving String
    if(s3.size() != s1.size() + s2.size())
        return false;
    vector<vector<bool> > f(s1.size() + 1, vector<bool>(s2.size() + 1, true));
    for(size_t i = 1; i <= s1.size(); i++){
        f[i][0] = f[i - 1][0] && s1[i - 1] == s3[i - 1];
    }
    for(size_t i = 1; i <= s2.size(); i++){
        f[0][i] = f[0][i - 1] && s2[i - 1] == s3[i - 1];
    }
    for(size_t i = 1; i <= s1.size(); i++){
        for(size_t j = 1; j <= s2.size(); j++){
            f[i][j] = (f[i - 1][j] && s1[i - 1] == s3[i + j - 1]) || (f[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
        }
    }
    return f[s1.size()][s2.size()];
}


bool isScramble(string s1, string s2) {//Scramble String
    const int n = (int)s1.size();
    if(n != s2.size()) return false;
    bool f[n + 1][n][n];
    fill_n(&f[0][0][0], (n + 1) * n * n, false);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            f[1][i][j] = s1[i] == s2[j];
    for(int k = 1; k <= n; k++){
        for(int i = 0; i + k <= n; i++){
            for(int j = 0; j + k <= n; j++){
                for(int m = 1; m < n; m++){
                    if((f[m][i][j] && f[k - m][i + m][j + m]) || (f[m][i][k - m + j] && f[k - m][i + m][j])){
                        f[k][i][j] = true;
                        break;
                    }
                }
            }
        }
    }
    return f[n][0][0];
}


int minPathSum(vector<vector<int> > &grid) {//Minimum Path Sum
    if(grid.size() == 0) return 0;
    const int m = (int)grid.size();
    const int n = (int)grid[0].size();
    for(int i = 1; i < m; i++)
        grid[i][0] += grid[i - 1][0];
    for(int j = 1; j < n; j++)
        grid[0][j] += grid[0][j - 1];
    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
        }
    }
    return grid[m - 1][n - 1];
}


int minDistance(string word1, string word2) {//Edit Distance
    const int m = (int)word1.size();
    const int n = (int)word2.size();
    int f[m + 1][n + 1];
    for(int i = 0; i <= m; i++)
        f[i][0] = i;
    for(int j = 0; j <= n; j++)
        f[0][j] = j;
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            if(word1[i - 1] == word2[j - 1]){
                f[i][j] = f[i - 1][j - 1];
            }else{
                f[i][j] = min(min(f[i][j - 1], f[i - 1][j]), f[i - 1][j - 1]) + 1;
            }
    return f[m][n];
}


int numDecodings(string s) {//Decode Ways
    if(s.empty() || s[0] == '0') return 0;
    int prev = 0, cur = 1;
    for(int i = 1; i <= s.size(); i++){
        if(s[i - 1] == '0') cur = 0;
        if(!(s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6')))
            prev = 0;
        int temp = cur;
        cur = temp + prev;
        prev = temp;
    }
    return cur;
}


int numDistinct(string S, string T) {//Distinct Subsequences
    int f[S.size() + 1][T.size() + 1];
    for(int i = 0; i <= S.size(); i++)
        f[i][0] = 1;
    for(int j = 1; j <= T.size(); j++)
        f[0][j] = 0;
    for(int i = 1; i <= S.size(); i++)
        for(int j = 1; j <= T.size(); j++){
            if(S[i - 1] == T[j - 1])
                f[i][j] = f[i - 1][j - 1] + f[i - 1][j];
            else f[i][j] = f[i - 1][j];
        }
    return f[S.size()][T.size()];
}


bool wordBreak(string s, unordered_set<string> &dict) {//Word Break
    vector<bool> f(s.size() + 1, false);
    f[0] = true;
    for(int i = 1; i <= s.size(); i++){
        for(int j = 0; j < i; j++){
            if(f[j] && dict.find(s.substr(j, i - j)) != dict.end()){
                f[i] = true;
                break;
            }
        }
    }
    return f[s.size()];
}


void gen_path(vector<string> &result, vector<string> &path, string &s, vector<vector<bool> > &p, int cur);

vector<string> wordBreak2(string s, unordered_set<string> &dict) {
    vector<bool> f(s.size() + 1, false);
    vector<vector<bool> > p(s.size() + 1, vector<bool>(s.size() + 1, false));
    f[0] = true;
    for(int i = 1; i <= s.size(); i++)
        for(int j = 0; j < i; j++)
            if(f[j] && dict.find(s.substr(j, i - j)) != dict.end()){
                f[i] = true;
                p[i][j] = true;//[j, i) is one of dict
            }
    vector<string> result;
    vector<string> path;
    gen_path(result, path, s, p, (int)s.size());
    return result;
}

void gen_path(vector<string> &result, vector<string> &path, string &s, vector<vector<bool> > &p, int cur){
    if(cur == 0){
        string temp;
        for(auto it = path.crbegin(); it != path.crend(); ++it){
            temp += *it + " ";
        }
        temp.erase(temp.end() - 1);
        result.push_back(temp);
    }
    for(int i = 0; i < s.size(); i++){
        if(p[cur][i]){
            path.push_back(s.substr(i, cur - i));
            gen_path(result, path, s, p, i);
            path.pop_back();
        }
    }
}





#endif
