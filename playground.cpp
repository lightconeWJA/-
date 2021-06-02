#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <string>
#include <sstream>
#include <cstring>
#include <set>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class UnionFind{
 private:
    vector<int> parent;

 public:
    UnionFind(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int var) {
        if (parent[var] != var){
            parent[var] = find(parent[var]);
        }
        return parent[var];
    }

    void unit(int varx, int vary) {
        parent[find(varx)] = find(vary);
    }

    int countRoot() {
        set<int> parent_set;

        for (int i = 0; i < parent.size(); i++) find(i);
        for (int i = 0; i < parent.size(); i++) parent_set.emplace(parent[i]);

        return parent_set.size();
    }
};


 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


class Solution {
 public:
    void MorrisLDR(TreeNode* node) {
        TreeNode* cur = node;
        TreeNode* pre = nullptr;

        while (node != nullptr) {
            if (node->left == nullptr) {
                cout<<node->val<<endl;
                node = node->right;
            } else {
                node = node->left;
                while (node->right) node = node->right;
            }
        }   
        
        return;
    }
};
