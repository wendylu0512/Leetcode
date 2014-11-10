//
//  mytree.h
//  Leetcode
//
//  Created by Wendi Lu on 10/28/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mytree_h
#define Leetcode_mytree_h

#include <queue>


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};



vector<int> preorderTraversal(TreeNode *root) {//Binary Tree Preorder Traversal
    vector<int> result;
    TreeNode *p = root;
    stack<TreeNode *> s;
    if(p != nullptr) s.push(p);
    while(!s.empty()){
        p = s.top();
        s.pop();
        result.push_back(p->val);
        if(p->right) s.push(p->right);
        if(p->left) s.push(p->left);
    }
    return result;
}


vector<int> inorderTraversal(TreeNode *root) {//Binary Tree Inorder Traversal
    vector<int> result;
    stack<TreeNode *> s;
    TreeNode *p = root;
    while(!s.empty() || p != nullptr){
        if(p != nullptr){
            s.push(p);
            p = p->left;
        }else{
            p = s.top();
            result.push_back(p->val);
            s.pop();
            p = p->right;
        }
    }
    return result;
}


vector<int> postorderTraversal(TreeNode *root) {//Binary Tree Postorder Traversal
    vector<int> result;
    stack<TreeNode *> s;
    TreeNode *p = root, *q;
    do{
        while(p){s.push(p); p = p->left;}
        q = nullptr;
        while(!s.empty()){
            p = s.top();
            s.pop();
            if(p->right == q){
                result.push_back(p->val);
                q = p;
            }else{
                s.push(p);
                p = p->right;
                break;
            }
        }
    }while(!s.empty());
    return result;
}


vector<vector<int> > levelOrder(TreeNode *root) {//Binary Tree Level Order Traversal
    vector<vector<int> > result;
    queue<TreeNode*> current, next;
    TreeNode *p = root;
    if(!p) return result;
    current.push(p);
    while(!current.empty()){
        vector<int> row;
        while(!current.empty()){
            p = current.front();
            current.pop();
            row.push_back(p->val);
            if(p->left) next.push(p->left);
            if(p->right) next.push(p->right);
        }
        result.push_back(row);
        swap(current, next);
    }
    return result;
}


vector<vector<int> > levelOrderBottom(TreeNode *root) {//Binary Tree Level Order Traversal II
    vector<vector<int> > result;
    queue<TreeNode*> current, next;
    TreeNode *p = root;
    if(!p) return result;
    current.push(p);
    while(!current.empty()){
        vector<int> row;
        while(!current.empty()){
            p = current.front();
            current.pop();
            row.push_back(p->val);
            if(p->left) next.push(p->left);
            if(p->right) next.push(p->right);
        }
        result.push_back(row);
        swap(current, next);
    }
    reverse(result.begin(), result.end());
    return result;
}


vector<vector<int> > zigzagLevelOrder(TreeNode *root) {//Binary Tree Zigzag Level Order Traversal
    vector<vector<int> > result;
    if(!root) return result;
    queue<TreeNode *> current, next;
    TreeNode *p = root;
    current.push(p);
    while(!current.empty()){
        vector<int> row;
        while(!current.empty()){
            p = current.front();
            current.pop();
            row.push_back(p->val);
            if(p->left) next.push(p->left);
            if(p->right) next.push(p->right);
        }
        result.push_back(row);
        if(!(result.size() & 0x01)) reverse(result[result.size() - 1].begin(), result[result.size() - 1].end());
        swap(current, next);
    }
    return result;
}


void detect(TreeNode *&one, TreeNode *&two, TreeNode *prev, TreeNode *cur);

void recoverTree(TreeNode *root) {//Recover Binary Search Tree
    TreeNode *one = nullptr, *two = nullptr;
    TreeNode *prev = nullptr, *cur = root;
    while(cur != nullptr){
        if(cur->left == nullptr){
            detect(one, two, prev, cur);
            prev = cur;
            cur = cur->right;
        }else{
            TreeNode *node = cur->left;
            while(node->right != nullptr && node->right != cur)
                node = node->right;
            if(node->right == nullptr){
                node->right = cur;
                cur = cur->left;
            }else{
                detect(one, two, prev, cur);
                prev = cur;
                node->right = nullptr;
                cur = cur->right;
            }
        }
    }
    swap(one->val, two->val);
}

void detect(TreeNode *&one, TreeNode *&two, TreeNode *prev, TreeNode *cur){
    if(prev != nullptr && prev->val > cur->val){
        if(one == nullptr)
            one = prev;
        two = cur;
    }
}


bool isSameTree(TreeNode *p, TreeNode *q) {//Same Tree
    stack<TreeNode *> s;
    s.push(p);
    s.push(q);
    while(!s.empty()){
        p = s.top();
        s.pop();
        q = s.top();
        s.pop();
        if(!p && !q) continue;
        if(!q || !p) return false;
        if(p->val != q->val) return false;
        s.push(p->left);
        s.push(q->left);
        s.push(p->right);
        s.push(q->right);
    }
    return true;
}


bool isSymmetric(TreeNode *root) {//Symmetric Tree
    if(!root) return true;
    TreeNode *p, *q;
    stack<TreeNode *> s;
    s.push(root->left);
    s.push(root->right);
    while(!s.empty()){
        p = s.top();
        s.pop();
        q = s.top();
        s.pop();
        if(!p && !q) continue;
        if(!p || !q) return false;
        if(p->val != q->val) return false;
        s.push(p->left);
        s.push(q->right);
        s.push(p->right);
        s.push(q->left);
    }
    return true;
}



int getHeight(TreeNode *root);

bool isBalanced(TreeNode *root) {//Balanced Binary Tree
    if(!root) return true;
    int left = getHeight(root->left);
    int right = getHeight(root->right);
    if(abs(left - right) > 1) return false;
    else return isBalanced(root->left) && isBalanced(root->right);
}

int getHeight(TreeNode *root){
    if(!root) return 0;
    if(!root->left && !root->right) return 1;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}


void flatten(TreeNode *root) {//Flatten Binary Tree to Linked List
    TreeNode *p =root;
    while(p){
        if(p->left){
            TreeNode *temp = p->right;
            TreeNode *node = p->left;
            while(node->right != nullptr) node = node->right;
            node->right = temp;
            p->right = p->left;
            p->left = nullptr;
        }
        p = p->right;
    }
}


void connect(TreeLinkNode *root) {//Populating Next Right Pointers in Each Node II
    if(!root) return;
    TreeLinkNode dummy(-1);
    TreeLinkNode *prev = &dummy, *cur = root;
    for(; cur; cur = cur->next){
        if(cur->left){
            prev->next = cur->left;
            prev = prev->next;
        }
        if(cur->right){
            prev->next = cur->right;
            prev = prev->next;
        }
    }
    connect(dummy.next);
}


TreeNode *buildTree(vector<int>::iterator prebegin, vector<int>::iterator preend,
                    vector<int>::iterator inbegin, vector<int>::iterator inend);

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {//Construct Binary Tree from Preorder and
//Inorder Traversal
    return buildTree(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
}

TreeNode *buildTree(vector<int>::iterator prebegin, vector<int>::iterator preend,
                    vector<int>::iterator inbegin, vector<int>::iterator inend){
    if(prebegin == preend || inbegin == inend) return nullptr;
    TreeNode *root = new TreeNode(*prebegin);
    auto it = find(inbegin, inend, *prebegin);
    auto far = distance(inbegin, it);
    root->left = buildTree(next(prebegin), next(prebegin, far + 1), inbegin, it);
    root->right = buildTree(next(prebegin, far + 1), preend, next(it), inend);
    return root;
}


template<typename InputIterator>
TreeNode *buildTree2(InputIterator inbegin, InputIterator inend, InputIterator posbegin, InputIterator posend);

TreeNode *buildTree2(vector<int> &inorder, vector<int> &postorder) {//Construct Binary Tree from Inorder and
//Postorder Traversal
    return buildTree(inorder.begin(), inorder.end(), postorder.begin(), postorder.end());
}

template<typename InputIterator>
TreeNode *buildTree2(InputIterator inbegin, InputIterator inend, InputIterator posbegin, InputIterator posend){
    if(inbegin == inend || posbegin == posend) return nullptr;
    TreeNode *root = new TreeNode(*(prev(posend)));
    InputIterator it = find(inbegin, inend, root->val);
    auto far = distance(inbegin, it);
    root->left = buildTree2(inbegin, it, posbegin, next(posbegin, far));
    root->right = buildTree2(next(it), inend, next(posbegin, far), prev(posend));
    return root;
}


int numTrees(int n) {//Unique Binary Search Trees
    int f[n + 1];
    fill(f, f + n + 1, 0);
    f[0] = 1;
    f[1] = 1;
    for(int k = 2; k < n + 1; k++){
        for(int i = 0; i < k; i++){
            f[k] += f[i] * f[k - 1 - i];
        }
    }
    return f[n];
}


vector<TreeNode *> generate(int start, int end);

vector<TreeNode *> generateTrees(int n) {//Unique Binary Search Trees II
    return generate(1, n);
}

vector<TreeNode *> generate(int start, int end){
    vector<TreeNode *> result;
    if(start > end){
        result.push_back(nullptr);
        return result;
    }
    for(int i = start; i <= end; i++){
        vector<TreeNode *> left = generate(start, i - 1);
        vector<TreeNode *> right = generate(i + 1, end);
        for(auto lefty : left){
            for(auto righty : right){
                TreeNode *root = new TreeNode(i);
                root->left = lefty;
                root->right = righty;
                result.push_back(root);
            }
        }
    }
    return result;
}


bool isValidBST(TreeNode *root, int cur_min, int cur_max);

bool isValidBST(TreeNode *root) {//Validate Binary Search Tree
    return isValidBST(root, INT_MIN, INT_MAX);
}

bool isValidBST(TreeNode *root, int cur_min, int cur_max){
    if(!root) return true;
    return root->val > cur_min && root->val < cur_max && isValidBST(root->left, cur_min, root->val) &&
    isValidBST(root->right, root->val, cur_max);
}


template<typename InputIterator>
TreeNode *sortedArrayToBST(InputIterator first, InputIterator last);

TreeNode *sortedArrayToBST(vector<int> &num) {//Convert Sorted Array to Binary Search Tree
    return sortedArrayToBST(num.begin(), num.end());
}

template<typename InputIterator>
TreeNode *sortedArrayToBST(InputIterator first, InputIterator last){
    int length = (int)distance(first, last);
    if(length <= 0) return nullptr;
    auto mid = first + length / 2;
    TreeNode *root = new TreeNode(*mid);
    root->left = sortedArrayToBST(first, mid);
    root->right = sortedArrayToBST(mid + 1, last);
    return root;
}


TreeNode* sortedListToBST(ListNode* &list, int start, int end);

TreeNode *sortedListToBST(ListNode *head) {//Convert Sorted List to Binary Search Tree
    int len = 0;
    ListNode *p = head;
    while(p){p = p->next; len++;}
    return sortedListToBST(head, 0, len - 1);
}

TreeNode* sortedListToBST(ListNode* &list, int start, int end){
    if(start > end) return nullptr;
    int mid = start - (start - end) / 2;
    TreeNode *left = sortedListToBST(list, start, mid - 1);
    TreeNode *parent = new TreeNode(list->val);
    parent->left = left;
    list = list->next;
    parent->right = sortedListToBST(list, mid + 1, end);
    return parent;
}


int minDepth(TreeNode *root) {//Minimum Depth of Binary Tree
    if(!root) return 0;
    if(!root->left && root->right) return minDepth(root->right) + 1;
    else if(root->left && !root->right) return minDepth(root->left) + 1;
    return min(minDepth(root->left), minDepth(root->right)) + 1;
}


int maxDepth(TreeNode *root) {//Maximum Depth of Binary Tree
    if(!root) return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}


bool hasPathSum(TreeNode *root, int sum) {//Path Sum
    if(!root) return false;
    if(!root->left && !root->right) return sum == root->val;
    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum -root->val);
}


void dfs(TreeNode *root, int sum, vector<vector<int> > &result, vector<int> &path);

vector<vector<int> > pathSum(TreeNode *root, int sum) {//Path Sum II
    vector<vector<int> > result;
    vector<int> path;
    dfs(root, sum, result, path);
    return result;
}

void dfs(TreeNode *root, int sum, vector<vector<int> > &result, vector<int> &path){
    if(!root) return;
    if(!root->left && !root->right){
        if(sum == root->val){
            path.push_back(root->val);
            result.push_back(path);
            path.pop_back();
            return;
        }
    }
    path.push_back(root->val);
    dfs(root->left, sum - root->val, result, path);
    dfs(root->right, sum - root->val, result, path);
    path.pop_back();
}


int dfs(TreeNode *root, int &max_sum);

int maxPathSum(TreeNode *root) {//Binary Tree Maximum Path Sum
    int max_sum = INT_MIN;
    dfs(root, max_sum);
    return max_sum;
}

int dfs(TreeNode *root, int &max_sum){
    if(!root) return 0;
    int l = dfs(root->left, max_sum);
    int r = dfs(root->right, max_sum);
    int sum = root->val;
    if(l > 0) sum += l;
    if(r > 0) sum += r;
    max_sum = max(max_sum, sum);
    return max(l, r) > 0? max(l, r) + root->val : root->val;
}


void connect1(TreeLinkNode *root) {//Populating Next Right Pointers in Each Node
    if(!root) return;
    TreeLinkNode *prev = nullptr, *next = nullptr, *cur = root;
    for(; cur; cur = next){
        next = nullptr;
        prev = nullptr;
        for(; cur; cur = cur->next){
            if(!next) next = cur->left ? cur->left : cur->right;
            if(cur->left){
                if(prev) prev->next = cur->left;
                prev = cur->left;
            }
            if(cur->right){
                if(prev) prev->next = cur->right;
                prev = cur->right;
            }
        }
    }
}


void dfs(TreeNode *root, int &allsum, int &sum);

int sumNumbers(TreeNode *root) {//Sum Root to Leaf Numbers
    int allsum = 0;
    int sum = 0;
    dfs(root, allsum, sum);
    return allsum;
}

void dfs(TreeNode *root, int &allsum, int &sum){
    if(!root) return;
    sum = 10 * sum + root->val;
    if(!root->left && !root->right) {
        allsum += sum;
    }
    dfs(root->left, allsum, sum);
    dfs(root->right, allsum, sum);
    sum /= 10;
}


#endif
