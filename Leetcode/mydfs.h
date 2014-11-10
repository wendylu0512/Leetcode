//
//  mydfs.h
//  Leetcode
//
//  Created by Wendi Lu on 11/1/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mydfs_h
#define Leetcode_mydfs_h



void dfs(vector<vector<string> > &result, vector<string> &path, string &s, int start);

bool isPalindrome(string &s, int start, int end);

vector<vector<string>> partition(string s) {//Palindrome Partitioning
    vector<vector<string> > result;
    vector<string> path;
    dfs(result, path, s, 0);
    return result;
}

void dfs(vector<vector<string> > &result, vector<string> &path, string &s, int start){
    if(start == s.size()){
        result.push_back(path);
        return;
    }
    for(int i = start; i < s.size(); i++){
        if(isPalindrome(s, start, i)){
            path.push_back(s.substr(start, i - start + 1));
            dfs(result, path, s, i + 1);
            path.pop_back();
        }
    }
}

bool isPalindrome(string &s, int start, int end){
    while(start <= end && s[start] == s[end]){
        start++;
        end--;
    }
    return start > end;
}


int dfs(int m, int n, vector<vector<int> > &f);

int getOrUpdate(int m, int n, vector<vector<int> > &f);

int uniquePaths(int m, int n) {//Unique Paths
    vector<vector<int> > f = vector<vector<int> >(m + 1, vector<int>(n + 1, 0));
    return dfs(m , n, f);
}

int dfs(int m, int n, vector<vector<int> > &f){
    if(m < 1 || n < 1) return 0;
    if(m == 1 && n == 1) return 1;
    return getOrUpdate(m , n - 1, f) + getOrUpdate(m - 1, n, f);
}

int getOrUpdate(int m, int n, vector<vector<int> > &f){
    if(f[m][n] > 0) return f[m][n];
    return f[m][n] = dfs(m , n, f);
}


int dfs(int m, int n, vector<vector<int> > &f, vector<vector<int> > &obstacleGrid);

int getOrUpdate(int m, int n, vector<vector<int> > &f, vector<vector<int> > &obstacleGrid);

int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {//Unique Paths II
    const int m = (int)obstacleGrid.size();
    const int n = (int)obstacleGrid[0].size();
    vector<vector<int> > f = vector<vector<int> >(m + 1, vector<int>(n + 1, 0));
    return dfs(m, n, f, obstacleGrid);
}

int dfs(int m, int n, vector<vector<int> > &f, vector<vector<int> > &obstacleGrid){
    if(m < 1 || n < 1) return 0;
    if(obstacleGrid[m - 1][n - 1] == 1) return 0;
    if(m == 1 && n == 1) return 1;
    return getOrUpdate(m - 1, n, f, obstacleGrid) + getOrUpdate(m, n - 1, f, obstacleGrid);
}

int getOrUpdate(int m, int n, vector<vector<int> > &f, vector<vector<int> > &obstacleGrid){
    if(f[m][n] > 0) return f[m][n];
    return f[m][n] = dfs(m, n, f, obstacleGrid);
}


void dfs(vector<int> &C, vector<vector<string> > &result, int row, vector<bool> &columns,
         vector<bool> &main_dialog, vector<bool> &anti_dialog);

vector<vector<string> > solveNQueens(int n) {//N-Queens 
    vector<bool> columns(n, 0);
    vector<bool> main_dialog(2 * n, 0);
    vector<bool> anti_dialog(2 * n, 0);
    vector<vector<string> > result;
    vector<int> C(n, 0);
    dfs(C, result, 0, columns, main_dialog, anti_dialog);
    return result;
}

void dfs(vector<int> &C, vector<vector<string> > &result, int row, vector<bool> &columns,
         vector<bool> &main_dialog, vector<bool> &anti_dialog){
    const int N = (int)C.size();
    if(row == N){
        vector<string> solution;
        for(int i = 0; i < N; i++){
            string s(N, '.');
            for(int j = 0; j < N; j++)
                if(C[i] == j) s[j] = 'Q';
            solution.push_back(s);
        }
        result.push_back(solution);
        return;
    }
    for(int i = 0; i < N; i++){
        bool ok = !columns[i] && !main_dialog[row + i] && !anti_dialog[N - i + row];
        if(!ok) continue;
        C[row] = i;
        columns[i] = main_dialog[row + i] = anti_dialog[N - i + row] = true;
        dfs(C, result, row + 1, columns, main_dialog, anti_dialog);
        C[row] = 0;
        columns[i] = main_dialog[row + i] = anti_dialog[N - i + row] = false;
    }
}


void dfs(vector<int> &C, int &result, vector<bool> &columns, vector<bool> &main, vector<bool> &anti, int row);

int totalNQueens(int n) {//N-Queens II
    vector<bool> columns(n, 0);
    vector<bool> main(2 * n, 0);
    vector<bool> anti(2 * n, 0);
    vector<int> C(n, 0);
    int result = 0;
    dfs(C, result, columns, main, anti, 0);
    return result;
}

void dfs(vector<int> &C, int &result, vector<bool> &columns, vector<bool> &main, vector<bool> &anti, int row){
    const int N = (int)C.size();
    if(N == row){
        result++;
        return;
    }
    for(int i = 0; i < N; i++){
        bool ok = !columns[i] && !main[row + i] && !anti[N - i + row];
        if(!ok) continue;
        C[row] = i;
        columns[i] = main[row + i] = anti[N - i + row] = true;
        dfs(C, result, columns, main, anti, row + 1);
        C[row] = 0;
        columns[i] = main[row + i] = anti[N - i + row] = false;
    }
}


void dfs(string &s, vector<string> &result, string ip, int start, int step);

vector<string> restoreIpAddresses(string s) {//Restore IP Addresses
    vector<string> result;
    string ip;
    dfs(s, result, ip, 0, 0);
    return result;
}

void dfs(string &s, vector<string> &result, string ip, int start, int step){
    if(start == s.size() && step == 4){
        ip.pop_back();
        result.push_back(ip);
        return;
    }
    if(s.size() - start > (4 - step) * 3) return;
    if(s.size() -start < (4 - step)) return;
    int num = 0;
    for(int i = start; i < start + 3; i++){
        num = num * 10 + s[i] - '0';
        if(num < 256){
            ip += s[i];
            dfs(s, result, ip + '.', i + 1, step + 1);
        }
        if(num == 0) break;
    }
}


void dfs(vector<int> &candidates, int target, vector<int> &path, vector<vector<int> > &result, int sum);

vector<vector<int> > combinationSum(vector<int> &candidates, int target) {//Combination Sum
    sort(candidates.begin(), candidates.end());
    vector<vector<int> > result;
    vector<int> path;
    dfs(candidates, target, path, result, 0);
    return result;
}

void dfs(vector<int> &candidates, int gap, vector<int> &path, vector<vector<int> > &result, int start){
    if(gap == 0){
        result.push_back(path);
        return;
    }
    if(gap < 0) return;
    for(int i = start; i < candidates.size(); i++){
        path.push_back(candidates[i]);
        dfs(candidates, gap - candidates[i], path, result, i);
        path.pop_back();
    }
}


void dfs1(vector<int> &num, int gap, vector<int> &path, vector<vector<int> > &result, int start);

vector<vector<int> > combinationSum2(vector<int> &num, int target) {//Combination Sum II
    sort(num.begin(), num.end());
    vector<vector<int> > result;
    vector<int> path;
    dfs1(num, target, path, result, 0);
    return result;
}

void dfs1(vector<int> &num, int gap, vector<int> &path, vector<vector<int> > &result, int start){
    if(gap == 0){
        result.push_back(path);
        return;
    }
    if(gap < 0) return;
    int previous = -1;
    for(int i = start; i < num.size(); i++){
        if(previous == num[i]) continue;
        previous = num[i];
        path.push_back(num[i]);
        dfs1(num, gap - num[i], path, result, i + 1);
        path.pop_back();
    }
}


void dfs(int n, string s, int left, int right, vector<string> &result);

vector<string> generateParenthesis(int n) {//Generate Parentheses
    vector<string> result;
    if(n == 0) return result;
    dfs(n, "", 0, 0, result);
    return result;
}

void dfs(int n, string s, int left, int right, vector<string> &result){
    if(left == n){
        result.push_back(s.append(n - right, ')'));
        return;
    }
    dfs(n, s + '(', left + 1, right, result);
    if(left > right) dfs(n, s + ')', left, right + 1, result);
}


bool mysolveSudoku(vector<vector<char> > &board);

bool isValid(vector<vector<char> > &board, int x, int y);

void solveSudoku(vector<vector<char> > &board){//Sudoku Solver
    mysolveSudoku(board);
}

bool mysolveSudoku(vector<vector<char> > &board) {
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == '.'){
                for(char k = '1'; k <= '9'; k++){
                    board[i][j] = k;
                    if(isValid(board, i, j) && mysolveSudoku(board))
                        return true;
                    board[i][j] = '.';
                }
                return false;
            }
        }
    }
    return true;
}

bool isValid(vector<vector<char> > &board, int x, int y){
    for(int i = 0; i < 9; i++)
        if(board[i][y] == board[x][y] && i != x)
            return false;
    for(int j = 0; j < 9; j++)
        if(board[x][j] == board[x][y] && j != y)
            return false;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[x / 3 * 3 + i][y / 3 * 3 + j] == board[x][y] && (x != x / 3 * 3 + i || y != y / 3 * 3 + j))
                return false;
    return true;
}


bool dfs(vector<vector<char> > &board, string word, int start, int x, int y, vector<vector<bool> > &visited);

bool exist(vector<vector<char> > &board, string word) {//Word Search
    const int m = (int)board.size();
    const int n = (int)board[0].size();
    vector<vector<bool> > visited = vector<vector<bool> >(m, vector<bool>(n, false));
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            if(dfs(board, word, 0, i, j, visited))
                return true;
    return false;
}

bool dfs(vector<vector<char> > &board, string word, int start, int x, int y, vector<vector<bool> > &visited){
    if(start == word.size()){
        return true;
    }
    if(x < 0 || y < 0 || x >= board.size() || y >= board[0].size()) return false;
    if(visited[x][y]) return false;
    if(word[start] != board[x][y]) return false;
    visited[x][y] = true;
    bool ret = dfs(board, word, start + 1, x, y + 1, visited) || dfs(board, word, start + 1, x, y - 1, visited) ||
    dfs(board, word, start + 1, x - 1, y, visited) || dfs(board, word, start + 1, x + 1, y, visited);
    visited[x][y] = false;
    return ret;
}
#endif
