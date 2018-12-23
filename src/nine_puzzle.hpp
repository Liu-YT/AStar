#ifndef NINE_PUZZLE_HPP
#define NINE_PUZZLE_HPP

#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include "astar.hpp"
using namespace std;

// 枚举移动方向
enum Direction9 {
    middle,
    clockwise
};

// 移动
Node* moveNine(Node* origin, Direction9 direction) {
    vector<int> order = origin->order;
    switch(direction) {
        case middle:
            order[3] = origin->order[4];
            order[4] = origin->order[5];
            order[5] = origin->order[3];
            break;
        case clockwise:
            order[0] = origin->order[1];
            order[1] = origin->order[2];
            order[2] = origin->order[5];
            order[5] = origin->order[8];
            order[8] = origin->order[7];
            order[7] = origin->order[6];
            order[6] = origin->order[3];
            order[3] = origin->order[0];
            break;
    }
    int blank = getIndex(order, 0);
    return new Node(order, origin, blank);
}

// A* search
void AStarSearchForNine(vector<int>& cur, vector<int>& target, string choose = "h1") {
    endOrder = target;

    // 获取空格的位置
    int blank = getIndex(cur, 0);
    Node* start = new Node(cur, nullptr, blank);
    Node *now = start;
    open.push(start);
    while(!open.empty()) {
        now = open.top();

        // 输出一些有效信息
        cout << "[INFO] Open Table: Size: " << open.size() << " Node: ";
        for(int i = 0; i <= 8; ++i) cout << now->order[i] << " ";
        cout << endl;

        open.pop();
        if(now->order == endOrder)   break;
        close.insert(now);

        // middle
        Node* node = moveNine(now, (Direction9)0);
        if(!close.count(node)) {
            node->status = now->status + 1;
            node->priority = getValuation(node, choose) + node->status;
            now->child.push_back(node);
            ++totalNode;
            open.push(node);
        }

        // clockwise 
        node = moveNine(now, (Direction9)1);
        if (!close.count(node)) {
            node->status = now->status + 1;
            node->priority = getValuation(node, choose) + node->status;
            now->child.push_back(node);
            ++totalNode;
            open.push(node);
        }
    }

    getPath(now);

    memoryFree(start);
}

#endif