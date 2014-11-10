//
//  mysearch.h
//  Leetcode
//
//  Created by Wendi Lu on 10/30/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mysearch_h
#define Leetcode_mysearch_h




template<typename ForwardIterator, typename T>
ForwardIterator mylower_bound(ForwardIterator first, ForwardIterator last, T value);

template<typename ForwardIterator, typename T>
ForwardIterator myupper_bound(ForwardIterator first, ForwardIterator last, T value);

vector<int> searchRange(int A[], int n, int target) {//Search for a Range
    int l = (int)distance(A, mylower_bound(A, A + n, target));
    int u = (int)distance(A, prev(myupper_bound(A, A + n, target)));
    if(A[l] != target)
        return vector<int>{-1, -1};
    else return vector<int>{l, u};
}

template<typename ForwardIterator, typename T>
ForwardIterator mylower_bound(ForwardIterator first, ForwardIterator last, T value){
    while(first != last){
        auto mid = first + distance(first, last) / 2;
        if(value > *mid) first = mid + 1;
        else last = mid;
    }
    return first;
}
template<typename ForwardIterator, typename T>
ForwardIterator myupper_bound(ForwardIterator first, ForwardIterator last, T value){
    while(first != last){
        auto mid = first + distance(first, last) / 2;
        if(value >= *mid) first = mid + 1;
        else last = mid;
    }
    return first;
}


int searchInsert(int A[], int n, int target) {//Search Insert Position
    int first = 0, last = n;
    while(first != last){
        int mid = (first + last) / 2;
        if(target > A[mid]) first = mid + 1;
        else last = mid;
    }
    return first;
}


bool searchMatrix(vector<vector<int> > &matrix, int target) {//Search a 2D Matrix
    if(matrix.size() == 0) return false;
    const size_t m = matrix.size();
    const size_t n = matrix[0].size();
    int first = 0, last = (int)(m * n);
    while(first != last){
        int mid = (first + last) / 2;
        int value = matrix[mid / n][mid % n];
        if(value == target)
            return true;
        else if(value < target)
            first = mid + 1;
        else last = mid;
    }
    return false;
}

#endif
