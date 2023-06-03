
#include<stdio.h>
#include<stdlib.h>
typedef int SLDataType; //类型重命名，后续要存储其他类型时方便更改
#define N 20//数组定长设置为20

//采用静态顺序表
typedef struct SeqList
{
    SLDataType array[N];    //定长数组
    int size;               //有效数据个数
}SeqList;

SeqList* setA,*setB,*setC;  //全局变量

//创建集合
SeqList* createSet(){
    SeqList *set = (SeqList*)malloc(sizeof(SeqList));
    set->size = 0;
    return set;
}

//判断元素在集合中是否存在
int isExist(SeqList* set,int x){
    int i;
    for(i = 0; i <set->size;i++){
        if(set->array[i] == x){
            return 1;
        }
    }
    return 0;
}


//添加元素到集合
void addSet(SeqList* set,int x){
    set->array[set->size++] = x;
}

//求两个集合的并集
SeqList* unionSet(SeqList* setA,SeqList* setB){
    SeqList *setC = createSet();
    int i;
    for(i = 0; i < setA->size;i++){
        addSet(setC,setA->array[i]);
    }
    for(i = 0; i<setB->size;i++){
        if( ( isExist(setC,setB->array[i]) ) )
        {
            continue;
        }
        addSet(setC,setB->array[i]);
    }
    return setC;
}

//求两个集合的交集
SeqList* intersectSet(SeqList* setA,SeqList *setB){
    SeqList *setC = createSet();
    int i,j;
    for(i = 0; i <setA->size;i++){
        for(j = 0; j <setB->size;j++){
            if(setA->array[i] == setB->array[j]){
                addSet(setC,setA->array[i]);
                break;
            }
        }
    }
    return setC;
}

//求两个集合的差集
SeqList* differenceSet(SeqList* setA,SeqList* setB)
{
    SeqList* setC = createSet();
    int i,j;
    for(i = 0; i< setA->size;i++)
    {
        for(j=0;j<setB->size;j++){
            if(setA->array[i] == setB->array[j]){
                break;
            }
        }
        if(j == setB->size){
            addSet(setC,setA->array[i]);
        }
    }
    return setC;
}

//打印集合元素
void printSet(SeqList* set)
{
    printf("{");
    for(int i = 0; i < set->size;++i)
    {
        printf("%d",set->array[i]);
        if(i!= (set->size)-1)
        {
            printf(",");
        }
    }
    printf("}\n");
}

//销毁集合
void destorySet(SeqList *set){
    free(set->array);
    free(set);
}



//功能模块，调用相关函数
void create(){
    int n,m,i,x;
    printf("请输入集合A的元素个数:\n");
    scanf("%d",&n);
    setA = createSet();
    printf("请依次输入集合A的%d个元素\n",n);
    for(i = 0; i < n; i++){
        scanf("%d",&x);
        if(isExist(setA,x)){
            printf("数据存在重复，请您重新输入");
            --i;
            continue;
        }
        addSet(setA,x);
    }

    printf("请输入集合B的元素个数:\n");
    scanf("%d",&m);
    setB = createSet();
    printf("请依次输入集合B的%d个元素\n",m);
    for(i = 0; i < m; i++){
        scanf("%d",&x);
        if(isExist(setB,x)){
            printf("数据存在重复，请您重新输入");
            --i;
            continue;
        }
        addSet(setB,x);
    }
    printf("A集合的元素如下");
    printSet(setA);
    printf("B集合的元素如下");
    printSet(setB);
    return ;
}
void bingji(){
    setC = unionSet(setA,setB);
    printf("集合A和集合B的并集为：\n");
    printSet(setC);
}
void chaji(){
    int choice;
    printf("1.A-B\n2.B-A\n请选择(1-2)\n");
    scanf("%d",&choice);
    if(choice == 1){
        setC = differenceSet(setA,setB);
        printf("集合A和集合B的差集为：\n");
        printSet(setC);
        return;
    }
    setC = differenceSet(setB,setA);
    printf("集合B和集合A的差集为：\n");
    printSet(setC);
}
void jiaoji(){
    setC = intersectSet(setA,setB);
    printf("集合A和集合B的交集为:\n");
    printSet(setC);
}


//set主函数
int set_(){
    int choice;
    int loop = 1;
    printf("============欢迎来到集合模块===========\n");
    printf("===========请输入你的选择============\n");
    printf("1.写入集合\n2.求集合的并集\n3.求集合的差集\n4.求集合的交集\n5.返回上一级\n");
    do{
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            create();
            break;
        case 2:
            bingji();
            break;
        case 3:
            chaji();
            break;
        case 4:
            jiaoji();
            break;
        case 5:
            loop = 0;
            destorySet(setA);
            destorySet(setB);
            destorySet(setC);
            break;
        default:
            printf("你的输入有误，请重新输入");
        }
    printf("===========请输入你的选择============\n");
    printf("1.写入集合\n2.求集合的并集\n3.求集合的差集\n4.求集合的交集\n5.返回上一级\n");
    }while(loop);
    return 0;
}
