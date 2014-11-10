//
//  mysort.h
//  Leetcode
//
//  Created by Wendi Lu on 10/29/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mysort_h
#define Leetcode_mysort_h


void merge(int A[], int m, int B[], int n) {//Merge Sorted Array
    int a = m - 1;
    int b = n - 1;
    int i = m + n - 1;
    for(; i >= 0 && a >= 0 && b >= 0; i--){
        if(B[b] > A[a])
            A[i] = B[b--];
        else A[i] = A[a--];
    }
    while(b >= 0){
        A[i--] = B[b--];
    }
}


ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {//Merge Two Sorted Lists
    ListNode dummy(-1);
    dummy.next = l1;
    ListNode *prev = &dummy, *cur = l2;
    while(prev->next && cur){
        if(cur->val < prev->next->val){
            ListNode *temp = cur->next;
            cur->next = prev->next;
            prev->next = cur;
            cur = temp;
            prev = prev->next;
        }
        else{
            prev = prev->next;
        }
    }
    if(cur) prev->next = cur;
    return dummy.next;
}


template<typename InputIterator>
ListNode *mergeKLists(InputIterator first, InputIterator last);

ListNode *mergeKLists(vector<ListNode *> &lists) {//Merge k Sorted Lists
    return mergeKLists(lists.begin(), lists.end());
}

template<typename InputIterator>
ListNode *mergeKLists(InputIterator first, InputIterator last){
    const int k = (int) distance(first, last);
    if(k == 0) return nullptr;
    if(k == 1) return *first;
    if(k == 2) return mergeTwoLists(*first, *(next(first)));
    auto mid = first + k / 2;
    ListNode *first_half = mergeKLists(first, mid);
    ListNode *second_half = mergeKLists(mid, last);
    return mergeTwoLists(first_half, second_half);
}


ListNode *insertionSortList(ListNode *head) {//Insertion Sort List
    ListNode dummy(INT_MIN);
    dummy.next = head;
    ListNode *prev = &dummy, *cur = head;
    for(; cur; prev = prev->next, cur = cur->next){
        ListNode *pos = &dummy;
        while(pos != prev){
            if(pos->val <= cur->val && cur->val < pos->next->val){
                prev->next = cur->next;
                cur->next = pos->next;
                pos->next = cur;
                cur = prev;
                prev = &dummy;
                while(prev->next != cur){prev = prev->next;}
                break;
            }
            pos = pos->next;
        }
    }
    return dummy.next;
}


ListNode *sortList(ListNode *head) {//Sort List
    if(!head || !head->next) return head;
    ListNode *fast = head, *slow = head;
    while(fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = nullptr;
    ListNode *l1 = sortList(head);
    ListNode *l2 = sortList(fast);
    return mergeTwoLists(l1, l2);
}


int firstMissingPositive(int A[], int n) {//First Missing Positive
    for(int i = 0; i< n; i++){
        while(A[i] != i + 1){
            if(A[i] <= 0 || A[i] > n || A[i] == A[A[i] - 1])
                break;
            swap(A[i], A[A[i] - 1]);
        }
    }
    for(int i = 0; i < n; ++i){
        if(A[i] != i + 1)
            return i + 1;
    }
    return n + 1;
}


void sortColors(int A[], int n) {//Sort Colors
    int red = 0, blue = n - 1;
    for(int i = 0; i < blue + 1;){
        if(A[i] == 0)
            swap(A[i++], A[red++]);
        else if(A[i] == 2)
            swap(A[i], A[blue--]);
        else i++;
    }
}

#endif
