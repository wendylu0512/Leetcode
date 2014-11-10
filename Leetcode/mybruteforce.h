//
//  mybruteforce.h
//  Leetcode
//
//  Created by Wendi Lu on 10/30/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mybruteforce_h
#define Leetcode_mybruteforce_h


vector<vector<int> > subsets(vector<int> &S) {//Subsets
    const int n = (int)S.size();
    vector<vector<int> > result;
    sort(S.begin(), S.end());
    for(int i = 0; i < 1 << n; i++){
        vector<int> row;
        for(int j = 0; j < n; j++){
            if(i & 1 << j) row.push_back(S[j]);
        }
        result.push_back(row);
    }
    return result;
}


vector<vector<int> > subsetsWithDup(vector<int> &S) {//Subsets II
    const int n = (int)S.size();
    vector<vector<int> > real_result;
    set<vector<int> > result;
    sort(S.begin(), S.end());
    for(int i = 0; i< 1 << n; i++){
        vector<int> row;
        for(int j = 0; j < n; j++){
            if(i & 1 << j) row.push_back(S[j]);
        }
        result.insert(row);
    }
    for(auto elem : result)
        real_result.push_back(elem);
    return real_result;
}


vector<vector<int> > permute(vector<int> &num) {//Permutations
    if(num.size() == 0) return vector<vector<int> >();
    vector<vector<int> > result;
    vector<int> copy = num;
    do{
        result.push_back(num);
        nextPermutation(num);
    }while(copy != num);
    return result;
}


void dfs(int n, int k, int start, int step, vector<vector<int> > &result, vector<int> &path);

vector<vector<int> > combine(int n, int k) {//Combinations
    vector<vector<int> > result;
    vector<int> path;
    dfs(n, k, 1, 0, result, path);
    return result;
}

void dfs(int n, int k, int start, int step, vector<vector<int> > &result, vector<int> &path){
    if(step == k){
        result.push_back(path);
        return;
    }
    for(int i = start; i <= n; i++){
        path.push_back(i);
        dfs(n, k, i + 1, step + 1, result, path);
        path.pop_back();
    }
}


void dfs(string digits, string &one, vector<string> &result, vector<string> &dict, int start);

vector<string> letterCombinations(string digits) {//Letter Combinations of a Phone Number
    vector<string> dict = {" ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> result;
    string one;
    dfs(digits, one, result, dict, 0);
    return result;
}

void dfs(string digits, string &one, vector<string> &result, vector<string> &dict, int start){
    if(start == digits.size()){
        result.push_back(one);
        return;
    }
    for(int j = 0; j < dict[digits[start] - '0'].size(); j++){
        one.push_back(dict[digits[start] - '0'][j]);
        dfs(digits, one, result, dict, start + 1);
        one.pop_back();
    }
}




#endif
