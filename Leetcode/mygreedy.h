//
//  mygreedy.h
//  Leetcode
//
//  Created by Wendi Lu on 11/2/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mygreedy_h
#define Leetcode_mygreedy_h



bool canJump(int A[], int n) {//Jump Game
    int farthest = 0;
    for(int i = 0; i <= farthest; i++){
        farthest = max(farthest, A[i] + i);
        if(farthest >= n - 1) return true;
    }
    return false;
}


int jump(int A[], int n) {// Jump Game II
    int step = 0;
    int left = 0;
    int right = 0;
    if(n == 1) return 0;
    while(left <= right){
        ++step;
        int old_right = right;
        for(int i = left; i <= old_right; i++){
            int new_right = i + A[i];
            if(new_right >= n - 1) return step;
            if(new_right > right) right = new_right;
        }
        left = old_right + 1;
    }
    return 0;
}


int maxProfit(vector<int> &prices) {//Best Time to Buy and Sell Stock
    if(prices.size() < 2) return 0;
    int valley = prices[0];
    int profit = 0;
    for(int i = 0; i < prices.size(); i++){
        profit = max(profit, prices[i] - valley);
        if(prices[i] < valley) valley = prices[i];
    }
    return profit;
}


int maxProfit2(vector<int> &prices) {//Best Time to Buy and Sell Stock II
    if(prices.size() < 2) return 0;
    int profit = 0;
    for(int i = 1; i < prices.size(); i++){
        if(prices[i] > prices[i - 1]) profit += prices[i] - prices[i - 1];
    }
    return profit;
}


int lengthOfLongestSubstring(string s) {//Longest Substring Without Repeating Characters
    int last[256];
    fill(last, last + 256, -1);
    int max_len = 0;
    int start = 0;
    for(int i = 0; i < s.size(); i++){
        if(last[s[i]] >= start){
            max_len = max(max_len, i - start);
            start = last[s[i]] + 1;
        }
        last[s[i]] = i;
    }
    return max(max_len, (int)s.size() - start);
}


int maxArea(vector<int> &height) {//Container With Most Water
    if(height.size() < 2) return 0;
    int max_area = 0;
    int start = 0, end = (int)height.size() - 1;
    while(start < end){
        max_area = max(max_area, min(height[start], height[end]) * (end - start));
        if(height[start] <= height[end])
            start++;
        else end--;
    }
    return max_area;
}

#endif
