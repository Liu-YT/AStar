#include "astar.hpp"

int main(int argc, char const *argv[]) {

    // 校验输入
    int a[9] = {0};
    int b[9] = {0};

    vector<int> cur;
    vector<int> target;
    cout << "Note:" << endl;
    cout << "  1. Use 0 replace spaces" << endl; 
    cout << "  2. Input range is 0-8" << endl;
    cout << "Enter the current eight puzzle status:" << endl;
    int num;
    for(int i = 0; i <= 8; ++i) {
        cin >> num;
        if(num > 8) {
            cout << "[ERROR] Input range is 0-8" << endl;
            return 0;
        }
        a[num]++;
        cur.push_back(num);
    }
    cout << "Enter the target eight digital status:" << endl;
    for(int i = 0; i <= 8; ++i) {
        cin >> num;
        if (num > 8) {
            cout << "[ERROR] Input range is 0-8" << endl;
            return 0;
        }
        b[num]++;
        target.push_back(num);
    }

    // 校验数字是否为0~8，并且只出现一次
    for(int i = 0; i <= 8; ++i) {
        if(a[i] == b[i] && a[i] == 1)
            continue;
        else {
            cout << "[ERROR] Input " << i << " more than one time" << endl;
            return 0;
        }
    }

    // 求取两个序列的逆序数，判断奇偶性是否一致
    if ((getReverse(cur) % 2) != (getReverse(target) % 2)) 
        cout << endl << "No solution" << endl;
    else
        AStarSearch(cur, target);

        
    return 0;
}

