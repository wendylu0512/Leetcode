//
//  mystack.h
//  Leetcode
//
//  Created by Wendi Lu on 10/28/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mystack_h
#define Leetcode_mystack_h

#include <stack>


bool isValid(string s) {//Valid Parentheses
    string left = "({[";
    string right = ")}]";
    stack<char> mystack;
    for(auto c : s){
        if(left.find(c) != string::npos)
            mystack.push(c);
        else{
            if(mystack.empty() || mystack.top() != left[right.find(c)])
                return false;
            else mystack.pop();
        }
    }
    return mystack.empty();
}


int longestValidParentheses(string s) {//Longest Valid Parentheses
    stack<int> lefts;
    int max_len = 0;
    int last = -1;
    for(int i = 0; i < s.size(); ++i){
        if(s[i] == '(')
            lefts.push(i);
        else{
            if(lefts.empty()){
                last = i;
            }else{
                lefts.pop();
                if(lefts.empty()){
                    max_len = max(max_len, i - last);
                }else{
                    max_len = max(max_len, i - lefts.top());
                }
            }
        }
    }
    return max_len;
}


int largestRectangleArea(vector<int> &height) {//Largest Rectangle in Histogram
    stack<int> s;
    height.push_back(0);
    int result = 0;
    for(int i = 0; i < height.size();){
        if(s.empty() || height[i] > height[s.top()])
            s.push(i++);
        else{
            int temp = s.top();
            s.pop();
            result = max(result, height[temp] * (s.empty()? i : i - s.top() - 1));
        }
    }
    return result;
}


int evalRPN(vector<string> &tokens) {//Evaluate Reverse Polish Notation
    stack<int> s;
    for(auto t : tokens){
        if(t.size() != 1 || string("+-*/").find(t[0]) == string :: npos)
            s.push(stoi(t));
        else{
            int temp = s.top();
            s.pop();
            if(t == "+") s.top() += temp;
            else if(t == "-") s.top() -= temp;
            else if(t == "*") s.top() *= temp;
            else s.top() /= temp;
        }
    }
    return s.top();
}

#endif
