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

class UnionFind {
 private:
    vector<int> parent;
    vector<int> rank;
    int count;

 public:
    UnionFind(vector<vector<char>>& grid) {
        count = 0;
        const int row = grid.size();
        const int col = grid[0].size();

        for(int r = 0; r < row; ++r) {
            for (int c = 0; c < col; ++c) {
                if (grid[r][c] == '1') {
                    parent.emplace_back(r * row + c);
                    ++count;
                } else {
                    parent.emplace_back(-1);
                }
                rank.emplace_back(0);
            }
        }
    }

    int find(int i) {
        if (parent[i] != i) parent[i] = find(parent[i]);
        return parent[i];
    }

    void unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x != root_y) {
            if (rank[root_x] < rank[root_y]) {
                swap(root_x, root_y);
            }
            parent[root_y] = root_x;
            if (rank[root_x] == rank[root_y]) rank[root_x] += 1;
            --count;
        }
    }

    int getCount() const {
        return count;
    };
};


class Solution {
 public:
    int numIslands(vector<vector<char>>& grid) {
        const int row = grid.size();
        const int col = grid[0].size();
        if (row == 0 || col == 0) return 0;

        UnionFind uf(grid);

        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < col; ++c) {
                if (grid[r][c] == '1') {
                    grid[r][c] == '0';
                    if (r - 1 >= 0 && grid[r-1][c] == '1') uf.unite(r * row + c, (r-1) * row + c);
                    if (r - 1 >= 0 && grid[r-1][c] == '1') uf.unite(r * row + c, (r+1) * row + c);
                    if (r - 1 >= 0 && grid[r-1][c] == '1') uf.unite(r * row + c, r * row + c - 1);
                    if (r - 1 >= 0 && grid[r-1][c] == '1') uf.unite(r * row + c, r * row + c + 1);
                }
            }
        }

        return uf.getCount();
    }
};