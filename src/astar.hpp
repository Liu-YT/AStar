#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

// 拓展结点数
int totalNode = 0;

// 定义一个结点
struct Node {
    int priority;               // 估价
    vector<int> order;          // 当前数码序列
    int blank;                  // 记录空格位置
    int status;                 // 层数
    Node* pre;                  // 父节点
    vector<Node*> child;        // 子结点

    Node(vector<int> &_order, Node *_pre, int _blank) {
        order = _order;
        pre = _pre;
        blank = _blank;
        status = 0;
    }

    friend bool operator<(Node a, Node b) {
        //重载小于号使得小的先出队列
        return a.priority > b.priority;
    }

    bool operator==(const Node &a) {
        return order == a.order;
    }

    Node operator=(const Node &a) {
        order = a.order;
        pre = a.pre;
        priority = a.priority;
        blank = a.blank;
    }
};

// 获得移动的路径
vector<Node *> movePath;

// 枚举移动方向
enum Direction {
    Left,
    Right,
    Up,
    Down
};

// set中cmp
struct cmp {
    bool operator()(const Node* a, const Node* b) const {
        return a->order < b->order;
    }
};

// close
set<Node*, cmp> close;

// priority queue中的cmp
struct cmp1 {
    bool operator()(const Node *a, const Node *b) const {
        return a->priority > b->priority;
    }
};

// open
priority_queue<Node*, vector<Node*>, cmp1 > open;

// 目标状态
vector<int> endOrder;

// 获取vector内某个元素的下标
int getIndex(vector<int>& v, int value) {
    for(int i = 0; i <= 8; ++i) {
        if(v[i] == value) {
            return i;
        }
    }
}

// 估价函数h1 放错位置数目的数字的个数
int getValuationOfOne(Node* n, int problem = 8) {
    int num = 0;
    for(int i = 0; i <= 8; ++i) {
        if(n->order[i] != endOrder[i])
            ++num;
    }
    if(num == 0)    return 0;
    return problem == 9 ? num : num-1;
}

// 估价函数h2 所有数字当前位置以最短路径走到正确位置的步数之和
int getValuationOfTwo(Node* n, int problem = 8) {
    int num = 0;
    for(int i = 0; i <= 8; ++i) {
        if (n->order[i] != endOrder[i] && n->order[i] != 0) {
            int index = getIndex(endOrder, n->order[i]);
            num += abs(i % 3 - index % 3) + abs(i / 3 - index / 3);
        }
        if (n->order[i] == 0 && problem == 9) {
            int index = getIndex(endOrder, n->order[i]);
            num += abs(i % 3 - index % 3) + abs(i / 3 - index / 3);
        }
    }
    return num;
}

// 估价函数挑选
int getValuation(Node* n, string choose = "h1", int problem = 8) {
    if(choose == "h1") 
        return getValuationOfOne(n, problem);
    else
        return getValuationOfTwo(n, problem);
}

// 移动
Node* move(Node* origin, Direction direction) {
    vector<int> order = origin->order;
    switch(direction) {
        case Left:
            order[origin->blank] = origin->order[origin->blank - 1];
            order[origin->blank - 1] = origin->order[origin->blank];
            break;
        case Right:
            order[origin->blank] = origin->order[origin->blank + 1];
            order[origin->blank + 1] = origin->order[origin->blank];
            break;
        case Up:
            order[origin->blank] = origin->order[origin->blank - 3];
            order[origin->blank - 3] = origin->order[origin->blank];
            break;
        case Down:
            order[origin->blank] = origin->order[origin->blank + 3];
            order[origin->blank + 3] = origin->order[origin->blank];
            break;
    }
    int blank = getIndex(order, 0);
    return new Node(order, origin, blank);
}

// 释放内存
void memoryFree(Node* root) {
    if(root) {
        for(int i = 0; i < root->child.size(); ++i) {
            memoryFree(root->child[i]);
        }
        delete root;
    }
}

// 递归获得移动
void getPath(Node* node) {
    if(node->pre) {
        movePath.push_back(node);
        getPath(node->pre);
    }
    else {
        cout << "[INFO] TotalNode: " << totalNode << endl; 
        cout << "f*(S0): " << movePath.size() << endl;
        cout << "----show path----" << endl;
        movePath.push_back(node);
        for(int i = movePath.size()-1; i >= 0; --i) {
            for(int j = 0; j <= 8; ++j) {
                cout << movePath[i]->order[j] << " ";
                if(j % 3 == 2)
                    cout << endl;
            }
            cout << "f(n): " << movePath[i]->priority << endl; 
            cout << endl;
        }
    }
}


// A* search
void AStarSearch(vector<int>& cur, vector<int>& target, string choose = "h1", int problem = 8) {
    endOrder = target;

    // 获取空格的位置
    int blank = getIndex(cur, 0);
    Node* start = new Node(cur, nullptr, blank);
    start->priority = getValuation(start, choose, problem);
    Node *now = start;
    open.push(start);
    while(!open.empty()) {
        now = open.top();

        // 输出一些有效信息
        cout << "[INFO] Open Table: Size: " << open.size() << " Node: ";
        for(int i = 0; i <= 8; ++i) cout << now->order[i] << " ";
        cout << "f(n): " << now->priority << endl;

        open.pop();
        if(now->order == endOrder)   break;
        close.insert(now);

        // left
        if(now->blank % 3 != 0) {
            Node* node = move(now, (Direction)0);
            if(!close.count(node)) {
                node->status = now->status + 1;
                node->priority = getValuation(node, choose, problem) + node->status;
                now->child.push_back(node);
                ++totalNode;
                open.push(node);
            }
        }

        // right
        if(now->blank % 3 != 2) {
            Node* node = move(now, (Direction)1);
            if (!close.count(node)) {
                node->status = now->status + 1;
                node->priority = getValuation(node, choose, problem) + node->status;
                now->child.push_back(node);
                ++totalNode;
                open.push(node);
            }
        }

        // up
        if(now->blank / 3 != 0) {
            Node* node = move(now, (Direction)2);
            if (!close.count(node)) {
                node->status = now->status + 1;
                node->priority = getValuation(node, choose, problem) + node->status;
                now->child.push_back(node);
                ++totalNode;
                open.push(node);
            }   
        }

        // down
        if(now->blank / 3 != 2) {
            Node* node = move(now, (Direction)3);
            if (!close.count(node)) {
                node->status = now->status + 1;
                node->priority = getValuation(node, choose, problem) + node->status;
                now->child.push_back(node);
                ++totalNode;
                open.push(node);
            }
        }
    }

    getPath(now);

    memoryFree(start);
}

/*
*   能否达到目标状态的判断方法
*   一个状态表示成一维的形式，求出除0之外所有数字的逆序数之和，也就是每个数字前面比它大的数字的个数的和，称为这个状态的逆序。该表示等价于某个数后面有比它小的数字的个数
*   若两个状态的逆序奇偶性 相同，则可相互到达，否则不可相互到达。
*   证明： https://blog.csdn.net/tiaotiaoyly/article/details/2008233
*/
// 计算序列的逆序数
int getReverse(vector<int>& order) {
    int num = 0;
    for(int i = 0; i < 8; ++i) {
        if(order[i] == 0)   continue;
        for(int j = i + 1; j <= 8; ++j) {
            if (order[j] == 0) continue;
            if(order[i] > order[j]) ++num;
        }
    }
    return num;
}

#endif