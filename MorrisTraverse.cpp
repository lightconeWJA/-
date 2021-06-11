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


// 一句话思路：
// 利用孩子节点空闲的指针，指向遍历孩子节点的“前驱节点”
// 通过指向“前驱节点”的指针来模拟栈递归的返回过程

void MorrisLDR(TreeNode* root) {
    TreeNode* cur = root;       // 当前遍历过程中访问的节点，初始化为root
    TreeNode* pre = nullptr;    // 遍历过程中 cur 之前的一个节点，用于构建线索

    while (cur != nullptr){
        // 存在左子树，需要考虑遍历完左子树后返回的问题
        // 即需要创建指向中序后驱节点的线索
        if (cur->left != nullptr) {
            
            // 寻找遍历左子树时最后一个访问到的节点
            pre = cur->left;
            while (pre->right != nullptr && pre->right != cur) {
                pre = pre->right;
            }
            
            // 线索为空，说明还没有设定过线索，进一步说明还未遍历
            // 设定线索，指向前驱节点，这里是cur指向的某个子树或者总树的根
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

// 前序遍历 DLR 与中序遍历 LDR 需要构建的线索实质上是一样的
// 唯一的不同是访问子树根节点的时机
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


// 手动实现 reverse 函数
// 思路参考反转链表
void reverse(TreeNode* from, TreeNode* to) {
    if (from == to) return;

    TreeNode* x = from;
    TreeNode* y = from->right;
    TreeNode* z = nullptr;

    while (true) {
        z = y->right;
        y->right = x;
        x = y;
        y = z;
        if (x == to) break;
    }
}

/*
 MorrisLRD 中需要进行倒序遍历的特殊情况
 比如有个这样的树：
       5
     /  \
    2     6
   / \   / \
  1   3  7  9

from = 5
to = 9
那么只需要处理“最右边一侧”的所有节点即可
即自底向上遍历这个子树：
       5
        \
          6
           \
            9
得到结果 {9, 6, 5}
*/
void reverseTraverse(TreeNode* from, TreeNode* to){
    reverse(from, to);

    TreeNode* node = to;
    while (true) {
        cout << to->val << endl;
        if (node = from) break;
        to = to->right;
    }

    reverse(to, from);
}

// 后序遍历需要额外的节点作为起始节点
// 
void MorrisLRD(TreeNode* root) {
    TreeNode* dummy = new TreeNode(-1);
    dummy->left = root;
    
    TreeNode* cur = dummy;
    TreeNode* pre = nullptr;

    while (cur != nullptr){
        // 左子树不为空时
        if (cur->left != nullptr) {
            // 找到左子树遍历过程中最后一个节点
            pre = cur->left;
            while (pre->right != nullptr && pre->right != cur) {
                pre = pre->right;
            }

            // 线索未设置情况
            if (pre->right == nullptr) {
                pre->right = cur;   //设置线索
                cur = cur->left;    //进入左子树
            }
            // 线索设置过了，进入遍历过程
            // 倒序输出从当前节点的左孩子到前驱节点
            else {
                reverseTraverse(cur->left, pre);
                pre->right = nullptr;
                cur = cur->right;
            }
        }

        // 左子树不存在，进入右子树
        // 或者是遍历到叶子节点，根据线索返回到子树的根
        else {
            cur = cur->right;
        }
    }

    return;
}
