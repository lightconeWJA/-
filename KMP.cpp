#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;


// 构造“部分匹配表”
// 核心思想为“自己与自己匹配”
// “部分匹配值”就是“前缀”和“后缀”的最长的共有元素的长度
// 计算以每个字符为结尾的子字符串的“部分匹配值”
vector<int> nextConstruction(const string& pattern) {
    const int len = pattern.size();
    vector<int> next(len, 0);   //部分匹配表

    // pattern 的前 k 个字符(前缀)与 j 前面的 k 个字符(后缀)相同
    int j = 0;
    int k = -1;

    next[0] = -1;
    while (j < len) {
        // next[1] = 0
        // 或者出现 pattern[j] == pattern[k] 的情况
        // 之前已经有 [0, k-1] 与 [j-k, j-1] 这两段相同（长度为k的相同前后缀）
        // 又加上 pattern[j] == pattern[k]
        // 因此 [0, k] 与 [j-k, j] 两端相同，得到了 next[j + 1] = k + 1，
        if (k == -1 || pattern[j] == pattern[k]) next[++j] = ++k;
        // pattern[j] != pattern[k] 情况
        // 试图找到更小字串进行匹配
        // 因为之前已经知道了一定长度的前后缀是相同的
        // 定义前缀为A，后缀为B，那么 A 与 B 的后缀相同
        // 先要找 A 的前缀与 B 的后缀相同的最大长度，就是找 next[k]
        else k = next[k];
    }

    return std::move(next);
}

int main(void) {
    string s = "";

    return 0;
}
