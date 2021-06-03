#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

string addSharp(const string& s){
    string res = "#";
    for (const char& ch : s) {
        res += ch;
        res += "#";
    }

    return res;
}

vector<int> Manacher(const string& s) {
    // 首先在字符串头尾以及每个字符中间插入 # 或者必然不会出现的一个字符
    // 这样解决会文中单字符中心或者多字符中心需要分开讨论的问题
    string addedsharp_s = addSharp(s);

    // 记录加上 # 的字符串的回文半径
    vector<int> radius(addedsharp_s.size(), 1);

    // 使用 p 逐个遍历加上 # 的字符串
    int p;
    // 最右回文右边界
    // 考虑所有 p 遍历过的回文中心所能达到的最右位置
    // 使用最右位置字符的索引表示。
    int right_edge = -1;

    // 最右回文边界的对称中心
    // 即 most_right_edge 所在的回文的中心位置索引
    int center = -1;

    // 对加上 # 的字符串进行遍历
    for (p = 0; p < addedsharp_s.size(); ++p) {
        // 目前遍历的位置超过了最右回文右边界
        // 采用普遍的中心扩展法
        if (p > right_edge) {
            center = p;
            right_edge = p;
            int r = 1;
            while (center - r >=0 && center + r < addedsharp_s.size()) {
                if (addedsharp_s[center - r] == addedsharp_s[center + r]) {
                    ++radius[p];
                    ++right_edge;
                    ++r;
                } else break;
            }
        } else { // 目前遍历位置在 right_edge 上或者在其左边
            // q 为 p 以 center 为对称中心的对称点
            int q = 2 * center - p;
            // q_left_edge 为以 q 为中心的回文左边界
            int q_left_edge = q - radius[q] + 1;
            // left_edge 就是以 center 为中心的左边界
            int left_edge = 2 * center - right_edge;

            // 如果 q_left_edge 在最右回文能够 “照顾” 到的范围内
            // 说明 p 和 q 中心的回文其实也是以 center 为中心的回文的一个真子集
            if (left_edge < q_left_edge) {
                radius[p] = radius[q];
            }
            // q_left_edge 比 left_edge 还要小
            // 那么[p, right_edge] 这部分就是以 p 为中心的回文的右半边 
            else if (left_edge > q_left_edge) {
                radius[p] = right_edge - p + 1;
            }
            // 最后一种情况，最少说明[p1, R] 肯定为回文，但或许还能扩展
            else {
                center = p;
                int r = right_edge - p;
                radius[p] = r + 1;
                r++;
                while (center - r >=0 && center + r < addedsharp_s.size()) {
                    if (addedsharp_s[center - r] == addedsharp_s[center + r]) {
                        ++radius[p];
                        ++right_edge;
                        ++r;
                    } else break;
                }
            }
        }
    }

    return radius;
}

int main(void) {
    string a = "acbbcbds";
    vector<int> res = Manacher(a);

    for (int& i : res) {
        cout << i << " ";
    }
    cout<<endl;
    
    return 0;
}
