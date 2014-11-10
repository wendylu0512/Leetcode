//
//  mylinklist.h
//  Leetcode
//
//  Created by Wendi Lu on 10/23/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mylinklist_h
#define Leetcode_mylinklist_h

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};




ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {//Add Two Numbers
    ListNode dummy(-1);
    ListNode *prev = &dummy;
    int carry = 0;
    for(ListNode * p1 = l1, * p2 = l2; p1 != nullptr || p2 != nullptr;){
        int val1 = p1 == nullptr? 0 : p1->val;
        int val2 = p2 == nullptr? 0 : p2->val;
        int value = val1 + val2 + carry;
        if(value >= 10) {value -= 10; carry = 1;}
        else {carry = 0;}
        prev->next = new ListNode(value);
        prev = prev->next;
        p1 = p1 == nullptr? nullptr : p1->next;
        p2 = p2 == nullptr? nullptr : p2->next;
    }
    if(carry) prev->next = new ListNode(carry);
    return dummy.next;
}


ListNode *reverseBetween(ListNode *head, int m, int n) {//Reverse Linked List II
    ListNode dummy(-1);
    dummy.next = head;
    ListNode *prev = &dummy, *pn = &dummy, *pm = &dummy;
    while(m - 1){prev = prev->next; m--;}
    while(n){pn = pn->next; n--;}
    pm = prev->next;
    while(pm != pn){
        prev->next = pm->next;
        pm->next = pn->next;
        pn->next = pm;
        pm = prev->next;
    }
    return dummy.next;
}


ListNode *partition(ListNode *head, int x) {//Partition List
    ListNode dummy(-1);
    dummy.next = head;
    ListNode *prev = &dummy, *cur = dummy.next, *head2 = &dummy;
    while(cur != nullptr){
        if(cur->val < x && cur != head2->next){
            prev->next = cur->next;
            cur->next = head2->next;
            head2->next = cur;
            cur = prev->next;
            head2 = head2->next;
        }
        else{
            if(cur->val < x) head2 = head2->next;
            cur = cur->next;
            prev = prev->next;
        }
    }
    return dummy.next;
}


ListNode *deleteDuplicates(ListNode *head) {//Remove Duplicates from Sorted List
    if(!head || !head->next) return head;
    ListNode *prev = head, *cur = head->next;
    while(cur){
        if(cur->val == prev->val){
            prev->next = cur->next;
            ListNode * temp = cur;
            cur = cur->next;
            delete temp;
        }
        else{
            prev = prev->next;
            cur = cur->next;
        }
    }
    return head;
}


ListNode *deleteDuplicates2(ListNode *head) {//Remove Duplicates from Sorted List II
    if(!head || !head->next) return head;
    ListNode dummy(-1);
    dummy.next = head;
    ListNode *prev = &dummy, *cur = dummy.next;
    int value = 0;
    bool same = false;
    while(cur){
        if(!same){
            if(cur->next && cur->next->val == cur->val){
                value = cur->val;
                same = true;
                cur = cur->next;
            }else if(!cur->next){
                break;
            }else{
                prev = prev->next;
                cur = cur->next;
            }
        }else{
            if(cur->val == value){
                cur = cur->next;
                if(cur == nullptr)
                    prev->next = cur;
            }else{
                same = false;
                prev->next = cur;
            }
        }
    }
    return dummy.next;
}


ListNode *rotateRight(ListNode *head, int k) {//Rotate List
    if(!head || !head->next || k == 0) return head;
    ListNode dummy1(-1);
    ListNode dummy2(-1);
    dummy1.next = head;
    ListNode * p = head;
    int length = 0;
    while(p){length++; p = p->next;}
    k %= length;
    p = &dummy1;
    while(length - k){p = p->next; length--;}
    dummy2.next = p->next;
    p->next = nullptr;
    p = &dummy2;
    while(k){p = p->next; k--;}
    p->next = dummy1.next;
    return dummy2.next;
}


ListNode *removeNthFromEnd(ListNode *head, int n) {//Remove Nth Node From End of List
    ListNode dummy(-1);
    dummy.next = head;
    ListNode * first = dummy.next, *cur = dummy.next, *prev = &dummy;
    while(first){
        if(n == 0){
            prev = prev->next;
            cur = cur->next;
            first = first->next;
        }else{
            n--;
            first = first->next;
        }
    }
    prev->next = cur->next;
    delete cur;
    return dummy.next;
}


ListNode *swapPairs(ListNode *head) {//Swap Nodes in Pairs
    if(!head || !head->next) return head;
    ListNode dummy(-1);
    dummy.next = head;
    ListNode *prev = &dummy, *cur = head->next;
    while(cur){
        prev->next->next = cur->next;
        cur->next = prev->next;
        prev->next = cur;
        prev = prev->next->next;
        if(prev->next)
            cur = prev->next->next;
        else break;
    }
    return dummy.next;
}


RandomListNode *copyRandomList(RandomListNode *head) {//Copy List with Random Pointer
    for(RandomListNode *cur = head; cur != nullptr;){//copy every node with member label and next
        RandomListNode *node = new RandomListNode(cur->label);
        node->next = cur->next;
        cur->next = node;
        cur = node->next;
    }
    for(RandomListNode *cur = head; cur != nullptr;){//copy member random for each node
        if(cur->random)
            cur->next->random = cur->random->next;
        cur = cur->next->next;
    }
    RandomListNode dummy(-1);
    for(RandomListNode *cur = head, *new_cur = &dummy; cur;){
        new_cur->next = cur->next;
        new_cur = new_cur->next;
        cur->next = cur->next->next;
        cur = cur->next;
    }
    return dummy.next;
}


bool hasCycle(ListNode *head) {//Linked List Cycle
    ListNode *slow = head, *fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) return true;
    }
    return false;
}


ListNode *detectCycle(ListNode *head) {//Linked List Cycle II
    ListNode * slow = head, *fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            ListNode *slow2 = head;
            while(slow2 != slow){
                slow = slow->next;
                slow2 = slow2->next;
            }
            return slow2;
        }
    }
    return nullptr;
}


void reorderList(ListNode *head) {//Reorder List
    if(!head || !head->next) return;
    ListNode *slow = head, *fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode *head2 = slow->next;
    slow->next = nullptr;
    ListNode *prev = head2;//reverse
    if(head2 && head2->next){
        ListNode *cur = head2->next, *next = cur->next;
        while(cur){
            cur->next = prev;
            prev = cur;
            cur = next;
            next = next == nullptr? nullptr : next->next;
        }
        head2->next = nullptr;
    }
    ListNode *p = head, *q = prev;//merge
    while(p){
        if(!q) break;
        ListNode *temp = q->next;
        q->next = p->next;
        p->next = q;
        p = q->next;
        q = temp;
    }
}












#endif
