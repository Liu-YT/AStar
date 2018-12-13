# A* 算法

## 介绍
使用 `A* 算法`解决八数码问题

## 使用

### 编译
```
g++ ./src/main.cpp ./src/astar.hpp -o a -std=c++11
```

### 运行
```
a.exe
```

## 启发式搜索
### 估价函数 `f(n) = g(n) + h(n)`
* `估价函数h1` 放错位置数目的数字的个数
* `估价函数h2` 所有数字当前位置以最短路径走到正确位置的步数之和

### 使用
* 默认使用`h1`
* 更换修改文件`.\src\astar.hpp`中`AStarSearch`函数
    ```cpp
    // h1
    node->priority = getValuationOfOne(node) + node->status;
    // h2
    node->priority = getValuationOfTwo(node) + node->status;
    ```

