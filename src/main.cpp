#include "astar.hpp"

int main(int argc, char const *argv[])
{
    vector<int> cur;
    vector<int> target;
    cout << "Use 0 for spaces" << endl;
    cout << "Enter the current eight puzzle status:" << endl;
    int num;
    for(int i = 0; i <= 8; ++i) {
        cin >> num;
        cur.push_back(num);
    }
    cout << "Enter the target eight digital status:" << endl;
    for(int i = 0; i <= 8; ++i) {
        cin >> num;
        target.push_back(num);
    }
    AStarSearch(cur, target);
    return 0;
}

