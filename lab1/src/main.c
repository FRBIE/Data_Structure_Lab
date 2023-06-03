#include"include/set.h"
#include"include/polynomial.h"
int main(){
    int loop = 1;
    int choice = 0;
    do{
    printf("\n============欢迎来到lab1============\n");
    printf("1.集合\n2.多项式\n3.退出\n");
    printf("请选择(1-3)\n");
    scanf("%d",&choice);
        switch (choice)
        {
        case 1:
           set_();
            break;
        case 2:
            polynomial();
            break;
        case 3:
            loop = 0;
        default:
            printf("你的输入有误，请重新输入\n");
        }
    }while (loop);
    return 0;
}