#include <cstdio>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

void MorrisLDR(TreeNode* root) {
    TreeNode* cur = root;       // 当前遍历树的根
    TreeNode* pre = nullptr;    // 遍历过程中访问 cur 之前的一个节点，用于构建线索

    while (cur != nullptr){
        // 存在左子树，需要考虑遍历完左子树后返回的问题
        // 即创建指向中序后驱节点的线索
        if (cur->left != nullptr) {
            
            // 寻找遍历左子树时最后一个访问到的节点
            pre = cur->left;
            while (pre->right != nullptr && pre->right != cur) {
                pre = pre->right;
            }
            
            // 线索为空，说明还没有设定过线索，进一步说明还未遍历
            // 设定线索，指向前驱节点
            // cur进入左子树
            if (pre->right == nullptr) {
                pre->right = cur;
                cur = cur->left;
            }
            // 线索不为空且指向 cur，说明之前设定过且也遍历过
            // 删除线索，恢复树结构
            // cur 进入右子树 
            else {
                pre->right = nullptr;
                cout << cur->val << endl;
                cur = cur->right;
            }
        }

        // 左子树为空，访问当前节点值
        // 之后直接遍历右子树，无需考虑创建后驱线索 
        else {
            cout << cur->val << endl;
            cur = cur->right;
        }
    }

    return;
}

void MorrisDLR(TreeNode* root) {
    TreeNode* cur = root;
    TreeNode* pre = nullptr;

    while (cur != nullptr){
        if (cur->left != nullptr) {
            
            pre = cur->left;
            while (pre->right != nullptr && pre->right != cur) {
                pre = pre->right;
            }

            if (pre->right == nullptr) {
                pre->right = cur;

                // 与 LDR的唯一一处不同
                // 因为是前序，所以在遍历左子树前先输出根节点的值
                cout << cur->val << endl;
                
                cur = cur->left;
            }
            else {
                pre->right = nullptr;
                cur = cur->right;
            }
        }

        else {
            cout << cur->val << endl;
            cur = cur->right;
        }
    }

    return ;
}

void MorrisLRD(TreeNode* root) {
    TreeNode* dummy = new TreeNode(-1);
    dummy->left = root;
    TreeNode* cur = dummy;
    TreeNode* pre = nullptr;

    return;
}
