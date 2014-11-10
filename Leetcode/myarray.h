//
//  myarray.h
//  Leetcode
//
//  Created by Wendi Lu on 10/22/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef __Leetcode__myarray__
#define __Leetcode__myarray__

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int findMin(vector<int> &num){//Find Minimum in Rotated Sorted Array
    if(num.size() == 1) return num[0];
    int first = 0, last = (int)num.size() - 1;
    while(first < last){
        const int mid = (first + last) / 2;
        if(first + 1 == last)
            return min(num[first], num[last]);
        if(num[first] < num[mid]){
            if(num[mid] > num[last]){
                first = mid + 1;
            }
            else{
                last = mid;
            }
        }else{
            last = mid;
        }
    }
    return num[first];
}


int findMin2(vector<int> &num){//Find Minimum in Rotated Sorted Array II
    if(num.size() == 1) return num[0];
    int first = 0, last = (int)num.size() - 1;
    while(first < last){
        const int mid = (first + last) / 2;
        if(first + 1 == last)
            return min(num[first], num[last]);
        if(num[first] < num[mid]){
            if(num[mid] > num[last])
                first = mid + 1;
            else
                last = mid;
        }
        else if(num[first] > num[mid]){
            last = mid;
        }
        else first++;
    }
    return num[first];
}


int removeDuplicates(int A[], int n){//Remove Duplicates from Sorted Array
    if(n == 0) return 0;
    int index = 0;
    for(int i = 1; i < n; ++i){
        if(A[index] != A[i])
            A[++index] = A[i];
    }
    return ++index;
}


int removeDuplicates2(int A[], int n){//Remove Duplicates from Sorted Array II
    if(n == 0) return 0;
    int count = 1, index = 0;
    for(int i = 1; i < n; ++i){
        if(A[index] != A[i]){
            A[++index] = A[i];
            count = 1;
        }else{
            if(count < 2){
                A[++index] = A[i];
                count++;
            }
        }
    }
    return ++index;
}


int search(int A[], int n, int target){//Search in Rotated Sorted Array
    int first = 0, last = n - 1;
    while(first <= last){
        const int mid = (first + last) / 2;
        if(target == A[mid]){
            return mid;
        }
        if(A[first] <= A[mid]){
            if(target >= A[first] && target < A[mid]){
                last = mid;
            }else{
                first = mid + 1;
            }
        }else{
            if(target > A[mid] && target <= A[last]){
                first = mid + 1;
            }else{
                last = mid;
            }
        }
    }
    return -1;
}


bool search2(int A[], int n, int target){//Search in Rotated Sorted Array II
    int first = 0, last = n - 1;
    while (first <= last) {
        const int mid = (first + last) / 2;
        if(target == A[mid]){
            return true;
        }
        if(A[first] < A[mid]){
            if(target >= A[first] && target <= A[mid]){
                last = mid;
            }else{
                first = mid + 1;
            }
        }else if(A[first] > A[mid]){
            if(target > A[mid] && target <= A[last]){
                first = mid + 1;
            }else{
                last = mid;
            }
        }else{
            first++;
        }
    }
    return false;
}


int findKth(int A[], int m, int B[], int n, int k);

double findMedianSortedArrays(int A[], int m, int B[], int n) {//Median of Two Sorted Arrays
    int total = m + n;
    if(total & 0x01){
        return findKth(A, m, B, n, total / 2 + 1);
    }else{
        return (findKth(A, m, B, n, total / 2) + findKth(A, m, B, n, total / 2 + 1)) / 2.0;
    }
}

int findKth(int A[], int m, int B[], int n, int k){
    if(m > n) return findKth(B, n, A, m, k);
    if(m == 0) return B[k - 1];
    if(k == 1) return min(A[0], B[0]);
    int ia = min(k / 2, m), ib = k - ia;
    if(A[ia - 1] < B[ib - 1]) return findKth(A + ia, m - ia, B, n, k - ia);
    else if (A[ia - 1] > B[ib - 1]) return findKth(A, m, B + ib, n - ib, k - ib);
    else return A[ia - 1];
}


int longestConsecutive(vector<int> &num) {//Longest Consecutive Sequence
    unordered_map<int, bool> used;
    for(auto i : num) used[i] = false;
    int longest = 0;
    for(auto i : num){
        if(used[i]) continue;
        int length = 1;
        for(int j = i + 1; used.find(j) != used.end(); ++j){
            used[j] = true;
            length++;
        }
        for(int j = i - 1; used.find(j) != used.end(); --j){
            used[j] = true;
            length++;
        }
        longest = max(longest, length);
    }
    return longest;
}


vector<int> twoSum(vector<int> &numbers, int target) {//Two Sum
    vector<int> result;
    unordered_map<int, int> index;
    for(int i = 0; i < numbers.size(); ++i){
        index[numbers[i]] = i + 1;
    }
    for(int i = 0; i < numbers.size(); ++i){
        auto it = index.find(target - numbers[i]);
        if (it != index.end() && index[target - numbers[i]] > i + 1) {
            result.push_back(i + 1);
            result.push_back(index[target - numbers[i]]);
            break;
        }
    }
    return result;
}


vector<vector<int> > threeSum(vector<int> &num) {//3Sum
    vector<vector<int> > result;
    if(num.size() < 3) return result;
    sort(num.begin(), num.end());
    const int target = 0;
    
    for(auto a = num.begin(); a < num.end() - 2;){
        auto b = next(a);
        auto c = prev(num.end());
        while (b < c) {
            if(*a + *b + *c < target){
                b++;
            }else if(*a + *b + *c > target){
                c--;
            }else {
                result.push_back({*a, *b, *c});
                do{b++;}while(b < c && *b == *(b - 1));
                do{c--;}while(b < c && *c == *(c + 1));
            }
        }
        do{a++;}while(a < num.end() - 2 && *a == *(a - 1));
    }
    return result;
}


int threeSumClosest(vector<int> &num, int target) {//3Sum Closest
    int result = 0;
    if(num.size() < 3) return result;
    int min_gap = INT_MAX;
    sort(num.begin(), num.end());
    for(int i = 0; i < num.size() - 2; ++i){
        int l = i + 1, r = (int)num.size() - 1;
        while(l < r){
            int sum = num[i] + num[l] + num[r];
            int gap = abs(sum - target);
            if(gap < min_gap){
                min_gap = gap;
                result = sum;
            }
            if(sum < target) l++;
            else r--;
        }
    }
    return result;
}


vector<vector<int> > fourSum(vector<int> &num, int target) {//4Sum
    vector<vector<int> > result;
    if(num.size() < 4) return result;
    sort(num.begin(), num.end());
    for(int i = 0; i < num.size() - 3;){
        for(int j = i + 1; j < num.size() - 2;){
            int l = j + 1;
            int r = (int)num.size() - 1;
            while(l < r){
                if(num[i] + num[j] + num[l] + num[r] < target)
                    l++;
                else if(num[i] + num[j] + num[l] + num[r] > target)
                    r--;
                else {
                    vector<int> four(4);
                    four[0] = num[i];
                    four[1] = num[j];
                    four[2] = num[l];
                    four[3] = num[r];
                    result.push_back(four);
                    do{l++;}while(l < r && num[l - 1] == num[l]);
                    do{r--;}while(l < r && num[r + 1] == num[r]);
                }
            }
            do{j++;}while(j < num.size() - 2 && num[j - 1] == num[j]);
        }
        do{i++;}while(i < num.size() - 3 && num[i - 1] == num[i]);
    }
    return result;
}


int removeElement(int A[], int n, int elem) {// Remove Element
    if(n == 0) return 0;
    int index = 0;
    for(int i = 0; i< n; ++i){
        if(A[i] != elem){
            A[index++] = A[i];
        }
    }
    return index;
}


void nextPermutation(vector<int> &num) {//Next Permutation
    auto it = num.end() - 1;
    for(; it != num.begin(); --it){
        if(*it > *(it - 1))
            break;
    }
    if(it != num.begin()){
        auto jt = num.rbegin();
        for(; jt != num.rend(); ++jt)
            if(*jt > *(it - 1)) break;
        swap(*(it - 1), *jt);
    }
    sort(it, num.end());
}

int factorial(int n);
string getPermutation(int n, int k) {// Permutation Sequence
    string s;
    for(int i = 1; i <= n; ++i)
        s += i + '0';
    string result;
    int base = factorial(n - 1);
    k--;
    for(int i = n - 1; i > 0; k %= base, base /= i, --i){
        auto a = next(s.begin(), k / base);
        result.push_back(*a);
        s.erase(a);
    }
    result.push_back(s[0]);
    return result;
}

int factorial(int n){
    int product = 1;
    for(int i = 1; i <= n; i++)
        product *= i;
    return product;
}

bool check(char c, bool used[]);

bool isValidSudoku(vector<vector<char> > &board) {// Valid Sudoku
    bool used[9];
    for(int i = 0; i < 9; i++){
        fill(used, used + 9, false);
        for(int j = 0; j < 9; j++){
            if(!check(board[i][j], used))
                return false;
        }
        fill(used, used + 9, false);
        for(int j = 0; j < 9; j++)
            if(!check(board[j][i], used))
                return false;
    }
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            fill(used, used + 9, false);
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    if(!check(board[r * 3 + i][3 * c + j], used))
                        return false;
                }
            }
        }
    }
    return true;
}

bool check(char c, bool used[]){
    if(c == '.') return true;
    if(used[c - '1']) return false;
    else{
        used[c - '1'] = true;
        return true;
    }
}


int trap(int A[], int n) {//Trapping Rain Water
    int max = 0;
    for(int i = 0; i < n; i++)
        if(A[i] > A[max]) max = i;
    int water = 0;
    for(int i = 0, peak = 0; i < max; ++i){
        if(A[i] > peak) peak = A[i];
        else water += peak - A[i];
    }
    for(int i = n - 1, peak = 0; i > max; --i){
        if(A[i] > peak) peak = A[i];
        else water += peak - A[i];
    }
    return water;
}


void rotate(vector<vector<int> > &matrix) {//Rotate Image
    const int n = (int)matrix.size();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n - 1 - i; j++)
            swap(matrix[i][j], matrix[n - 1 - j][n - 1 - i]);
    for(int i = 0; i < n / 2; i++)
        for(int j = 0; j < n; j ++)
            swap(matrix[i][j], matrix[n - i - 1][j]);
}


vector<int> plusOne(vector<int> &digits) {//Plus One
    int carry = 1;
    for(auto it = digits.rbegin(); it != digits.rend(); ++it){
        if(*it + carry >= 10){
            carry = 1;
            *it = 0;
        }else{
            *it += carry;
            carry = 0;
        }
    }
    if(carry) digits.insert(digits.begin(), 1);
    return digits;
}


int climbStairs(int n) {//Climbing Stairs
    if(n < 3) return n;
    int prev = 1, cur = 2;
    for(int i = 0; i < n - 2; i++){
        int temp = cur;
        cur += prev;
        prev = temp;
    }
    return cur;
}


vector<int> grayCode(int n) {//Gray Code
    vector<int> base = {0, 1};
    if(n == 0) return vector<int>{0};
    if(n == 1) return base;
    for(int i = 1; i < n; i++){
        vector<int> copy = base;
        reverse(copy.begin(), copy.end());
        for(auto num : copy){
            num |= 1 << i;
            base.push_back(num);
        }
    }
    return base;
}


void setZeroes(vector<vector<int> > &matrix) {//Set Matrix Zeroes
    const int m = (int)matrix.size();
    const int n = (int)matrix[0].size();
    bool row = false, col = false;
    for(int i = 0; i < m; i++)
        if(matrix[i][0] == 0){
            col = true;
            break;
        }
    for(int j = 0; j < n; j++)
        if(matrix[0][j] == 0){
            row = true;
            break;
        }
    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            if(matrix[i][j] == 0){
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            if(matrix[i][0] == 0 || matrix[0][j] == 0)
                matrix[i][j] = 0;
        }
    }
    if(row){
        for(int i = 0; i < n; i++)
            matrix[0][i] = 0;
    }
    if(col){
        for(int i = 0; i < m; i++)
            matrix[i][0] = 0;
    }
}


int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {//Gas Station
    int total = 0;
    int j = -1;
    for(int i = 0, sum = 0; i < gas.size(); i++){
        sum += gas[i] - cost[i];
        total += gas[i] - cost[i];
        if(sum < 0){
            j = i;
            sum = 0;
        }
    }
    if(total < 0) return -1;
    else return j + 1;
}


int candy(vector<int> &ratings) {//Candy
    const int n = (int)ratings.size();
    vector<int> candy(n, 1);
    for(int i = 1; i < ratings.size(); ++i){
        if(ratings[i] > ratings[i - 1])
            candy[i] = max(candy[i], candy[i - 1] + 1);
    }
    for(int i = (int)ratings.size() - 2; i >= 0; --i){
        if(ratings[i] > ratings[i + 1])
            candy[i] = max(candy[i], candy[i + 1] + 1);
    }
    
    int sum = 0;
    for(auto i : candy)
        sum += i;
    return sum;
}


int singleNumber(int A[], int n) {//Single Number
    int result = 0;
    for(int i = 0; i < n; i++){
        result ^= A[i];
    }
    return result;
}


int singleNumber2(int A[], int n) {//Single NUmber II
    int one = 0, two = 0;
    for(int i = 0; i < n; i++){
        one = (one ^ A[i]) & ~two;
        two = (two ^ A[i]) & ~one;
    }
    return one;
}















#endif /* defined(__Leetcode__myarray__) */
