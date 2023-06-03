#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#define MaxSize 100

// 迷宫定义
int mg[6][6] = {
    {1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1}
};

// 栈的定义
typedef struct {
    int i;  // 当前方块的行号
    int j;  // 当前方块的列号
    int di; // di是下一相邻可走方位的方位号
} Box;  // 方块类型

typedef struct {
    Box data[MaxSize];
    int top;  // 栈顶指针
} StType;  // 顺序栈类型

// 初始化栈
void InitStack(StType *st) {
    st->top = -1;
}

// 判断栈是否为空
bool StackEmpty(StType *st) {
    return st->top == -1;
}

// 入栈
void Push(StType *st, Box e) {
    st->top++;
    st->data[st->top] = e;
}

// 出栈
void Pop(StType *st, Box *e) {
    *e = st->data[st->top];
    st->top--;
}

// 获取栈顶元素
void GetTop(StType *st, Box *e) {
    *e = st->data[st->top];
}

// 销毁栈
void DestroyStack(StType *st) {
    st->top = -1;
}

// 输出迷宫中所有从入口到出口的路径
void dispaths(Box path[], int k) {
    printf("迷宫中所有从入口到出口的路径如下：\n");
    for (int i = k - 1; i >= 0; i--) {
        printf("\t(%d, %d)\n", path[i].i, path[i].j);
    }
}

// 求解最短路径并输出第一条最短路径及其长度
void disminpath(Box path[], int k) {
    printf("最短路径如下：\n");
    for (int i = k - 1; i >= 0; i--) {
        printf("\t(%d, %d)\n", path[i].i, path[i].j);
    }
    printf("最短路径长度为：%d\n", k);
}

// 求解迷宫路径问题
bool mgpath(int xi, int yi, int xe, int ye) {
    Box path[MaxSize], e;
    int i, j, di, il, jl, k;
    bool find;
    StType st;  // 定义栈st
    InitStack(&st);  // 初始化栈顶指针
    e.i = xi;
    e.j = yi;
    e.di = -1;  // 设置e为入口
    Push(&st, e);  // 方块e进栈
    mg[xi][yi] = -1;  // 将入口的迷官值置为-1，避免重复走到该方块

    while (!StackEmpty(&st)) {  // 栈不空时循环
        GetTop(&st, &e);  // 取栈顶方块e
        i = e.i;
        j = e.j;
        di = e.di;

        if (i == xe && j == ye) {  // 找到了出口，输出该路径
            printf("找到一条迷宫路径！\n");
            k = 0;
            while (!StackEmpty(&st)) {
                Pop(&st, &e);  // 出栈方块e
                path[k++] = e;  // 将e添加到path数组中
            }
            dispaths(path, k);  // 输出迷宫中所有路径
            disminpath(path, k);  // 输出最短路径及长度
            DestroyStack(&st);  // 销毁栈
            return true;  // 输出一条迷宫路径后返回true
        }

        find = false;

        while (di < 4 && !find) {  // 找方块(i, j)的下一个相邻可走方块
            di++;
            switch (di) {
                case 0:
                    il = i - 1;
                    jl = j;
                    break;
                case 1:
                    il = i;
                    jl = j + 1;
                    break;
                case 2:
                    il = i + 1;
                    jl = j;
                    break;
                case 3:
                    il = i;
                    jl = j - 1;
                    break;
            }

            if (mg[il][jl] == 0) {
                find = true;  // 找到一个相邻可走方块，设置find为真
            }
        }

        if (find) {  // 找到了一个相邻可走方块(il, jl)
            st.data[st.top].di = di;  // 修改原栈顶元素的di值
            e.i = il;
            e.j = jl;
            e.di = -1;
            Push(&st, e);  // 相邻可走方块e进栈
            mg[il][jl] = -1;  // 将(il, jl)迷官值置为-1，避免重复走到该方块
        } else {  // 没有路径可走，则退栈
            Pop(&st, &e);  // 将栈顶方块退栈
            mg[e.i][e.j] = 0;  // 让退栈方块的位置变为其他路径可走方块
        }
    }

    printf("该迷宫问题没有解！\n");
    DestroyStack(&st);  // 销毁栈
    return false;  // 没有找到迷宫路径，返回false
}

int main() {
    int xi = 1, yi = 1;  // 入口坐标
    int xe = 4, ye = 4;  // 出口坐标

    if (mgpath(xi, yi, xe, ye)) {
        printf("成功找到迷宫路径！\n");
    } else {
        printf("没有找到迷宫路径！\n");
    }
    system("pause");
    return 0;
}
