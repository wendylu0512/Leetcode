//
//  mtbsf.h
//  Leetcode
//
//  Created by Wendi Lu on 10/30/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mtbsf_h
#define Leetcode_mtbsf_h



int ladderLength(string start, string end, unordered_set<string> &dict) {//Word Ladder
    queue<string> current, next;
    unordered_set<string> visited;
    int level = 0;
    bool found = false;
    auto state_is_target = [&](const string &s){return s == end;};
    auto state_extend = [&](const string &s){
        vector<string> result;
        for(size_t i = 0; i < s.size(); i++){
            string new_word(s);
            for(char c = 'a'; c <= 'z'; c++){
                if(c == new_word[i]) continue;
                swap(c, new_word[i]);
                if((dict.count(new_word) > 0 || new_word == end) && !visited.count(new_word)){
                    result.push_back(new_word);
                    visited.insert(new_word);
                }
                swap(c, new_word[i]);
            }
        }
        return result;
    };
    current.push(start);
    while(!current.empty() && !found){
        ++level;
        while(!current.empty() && !found){
            const string str = current.front();
            current.pop();
            const auto new_states = state_extend(str);
            for(const auto state : new_states){
                next.push(state);
                if(state_is_target(state)){
                    found = true;
                    break;
                }
            }
        }
        swap(next, current);
    }
    if(found) return level + 1;
    else return 0;
}


void gen_path(unordered_map<string, vector<string> > &father, vector<string> &path, string start, string word, vector<vector<string> > &result);

vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {//Word Ladder II
    unordered_set<string> current, next;
    vector<vector<string> > result;
    unordered_map<string, vector<string> > father;
    unordered_set<string> visited;
    bool found = false;
    auto state_extend = [&](const string &s){
        unordered_set<string> thisresult;
        for(int i = 0; i < s.size(); i++){
            string new_word(s);
            for(char c = 'a'; c <= 'z'; c++){
                if(new_word[i] == c) continue;
                swap(c, new_word[i]);
                if((dict.count(new_word) > 0 && !visited.count(new_word)) || new_word == end){
                    thisresult.insert(new_word);
                }
                swap(c, new_word[i]);
            }
        }
        return thisresult;
    };
    current.insert(start);
    while(!current.empty() && !found){
        for(auto i : current)
            visited.insert(i);
        for(const auto word : current){
            const auto new_states = state_extend(word);
            for(const auto state : new_states){
                if(state == end) found = true;
                next.insert(state);
                father[state].push_back(word);
            }
        }
        current.clear();
        swap(current, next);
    }
    if(found){
        vector<string> path;
        gen_path(father, path, start, end, result);
    }
    return result;
}

void gen_path(unordered_map<string, vector<string> > &father, vector<string> &path, string start, string word, vector<vector<string> > &result){
    path.push_back(word);
    if(word == start){
        result.push_back(path);
        reverse(result.back().begin(), result.back().end());
    }else{
        for(auto f: father[word]){
            gen_path(father, path, start, f, result);
        }
    }
    path.pop_back();
}


void bfs(vector<vector<char> > &board, int i, int j);

void solve(vector<vector<char>> &board) {//Surrounded Regions
    if(board.empty()) return;
    const int m = (int)board.size();
    const int n = (int)board[0].size();
    for(int i = 0; i < n; i++){
        bfs(board, 0, i);
        bfs(board, m - 1, i);
    }
    for(int j = 0; j < m; j++){
        bfs(board, j, 0);
        bfs(board, j , n - 1);
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(board[i][j] == 'O')
                board[i][j] = 'X';
            else if(board[i][j] == '+')
                board[i][j] = 'O';
        }
    }
}

void bfs(vector<vector<char> > &board, int i, int j){
    typedef pair<int, int> state_t;
    queue<state_t> q;
    const int m = (int)board.size();
    const int n = (int)board[0].size();
    auto is_valid = [&](state_t &state){
        int x = state.first;
        int y = state.second;
        if(x < 0 || y < 0 || x >= m || y >= n || board[x][y] != 'O') return false;
        return true;
    };
    auto state_extend = [&](const state_t &state){
        vector<state_t> result;
        int x = state.first;
        int y = state.second;
        state_t new_states[4] = {{x, y + 1}, {x + 1, y}, {x- 1, y}, {x, y - 1}};
        for(int k = 0; k < 4; k++){
            if(is_valid(new_states[k])){
                (board[new_states[k].first][new_states[k].second]) = '+';
                result.push_back(new_states[k]);
            }
        }
        return result;
    };
    state_t start = {i, j};
    if(is_valid(start)){
        board[i][j] = '+';
        q.push(start);
    }
    while(!q.empty()){
        state_t state = q.front();
        q.pop();
        auto new_states = state_extend(state);
        for(auto s : new_states){
            q.push(s);
        }
    }
}



#endif
