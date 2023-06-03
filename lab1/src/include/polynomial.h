
//定义多项式的项的结构
typedef struct Term
{
    int coef;//系数
    int expon;//指数
    struct Term* next;
}Term;
Term* poly1 ;
    Term* poly2;
    Term* sum ;
    Term* diff ;
    Term* prod;
//函数声明

//创建多项式
Term* createPolynomial();
//按照指数降序排列多项式
void sortPolynomial(Term* poly);
//合并多项式中的相同指数项
void simplifyPolynomial(Term* poly);
//打印多项式
void printPolynomial(Term* poly);
//多项式相加
Term* addPolynomials(Term* poly1,Term* poly2);
//多项式相减
Term* subtractPolynomials(Term* poly1,Term* poly2);
//多项式相乘
Term* multiplyPolynomials(Term* poly1,Term* poly2);
//销毁多项式
void destroyPolynomial(Term* poly);
// 合并多项式中的相同指数项
void simplifyPolynomial(Term* polynomial);

//函数的实现

// 创建多项式
Term* createPolynomial() {
    Term* head = NULL;  // 多项式头节点
    Term* tail = NULL;  // 多项式尾节点
    int coef, expon;  // 系数和指数

    printf("请输入多项式的系数和指数（以0 0表示输入结束）\n");
    
    while (1) {
        scanf("%d %d", &coef, &expon);
        if (coef == 0 && expon == 0)
            break;  // 输入0 0表示结束创建多项式

        // 创建新的项节点
        Term* newNode = (Term*)malloc(sizeof(Term));
        newNode->coef = coef;
        newNode->expon = expon;
        newNode->next = NULL;

        if (head == NULL) {
            // 多项式为空，设置头节点和尾节点为新节点
            head = newNode;
            tail = newNode;
        } else {
            // 多项式非空，尾插法添加新节点
            tail->next = newNode;
            tail = newNode;
        }
    }

    // 按指数降序排列多项式
    sortPolynomial(head);

    return head;
}
// 按指数降序排列多项式
void sortPolynomial(Term* poly) {
    int swapped;       // 用于标记是否发生交换
    Term* ptr1;        // 当前节点指针
    Term* lptr = NULL; // 上一轮排序的最后一个节点指针

    // 检查链表是否为空
    if (poly == NULL)
        return;

    do {
        swapped = 0; // 初始化标记为未发生交换
        ptr1 = poly; // 从多项式的头节点开始遍历

        while (ptr1->next != lptr) {
            if (ptr1->expon < ptr1->next->expon) {
                // 如果当前节点的指数小于下一个节点的指数，进行交换
                int tempcoef = ptr1->coef;
                int tempExp = ptr1->expon;

                // 交换节点的系数和指数
                ptr1->coef = ptr1->next->coef;
                ptr1->expon = ptr1->next->expon;
                ptr1->next->coef = tempcoef;
                ptr1->next->expon = tempExp;

                swapped = 1; // 标记已发生交换
            }
            ptr1 = ptr1->next; // 移动到下一个节点
        }

        lptr = ptr1; // 当前轮排序的最后一个节点为当前节点

    } while (swapped); // 如果发生交换，则继续下一轮排序

    // 多项式已按指数降序排列完成
}
// 打印多项式
void printPolynomial(Term* poly) {
    if (poly == NULL) {
        printf("多项式为空\n");
        return;
    }

    while (poly != NULL) {
        // 打印正负号
        if (poly->coef >= 0)
            printf("+");
        else
            printf("-");

        // 打印系数
        int abscoef = abs(poly->coef);
        if (abscoef != 1 || poly->expon == 0)
            printf("%d", abscoef);

        // 打印指数
        if (poly->expon > 0)
            printf("x^%d ", poly->expon);
        else if (poly->expon == 0)
            printf(" ");

        poly = poly->next;
    }

    printf("\n");
}

// 相加多项式
Term* addPolynomials(Term* poly1, Term* poly2) {
    Term* result = NULL;
    Term* tail = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        // 指数相同的项，系数相加
        if (poly1->expon == poly2->expon) {
            int sumcoef = poly1->coef + poly2->coef;

            // 系数不为0才添加到结果多项式中
            if (sumcoef != 0) {
                Term* newNode = (Term*)malloc(sizeof(Term));
                newNode->coef = sumcoef;
                newNode->expon = poly1->expon;
                newNode->next = NULL;

                if (result == NULL) {
                    result = newNode;
                    tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
            }

            poly1 = poly1->next;
            poly2 = poly2->next;
        }
        // poly1的指数大于poly2的指数
        else if (poly1->expon > poly2->expon) {
            Term* newNode = (Term*)malloc(sizeof(Term));
            newNode->coef = poly1->coef;
            newNode->expon = poly1->expon;
            newNode->next = NULL;

            if (result == NULL) {
                result = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }

            poly1 = poly1->next;
        }
        // poly1的指数小于poly2的指数
        else {
            Term* newNode = (Term*)malloc(sizeof(Term));
            newNode->coef = poly2->coef;
            newNode->expon = poly2->expon;
            newNode->next = NULL;

            if (result == NULL) {
                result = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }

            poly2 = poly2->next;
        }
    }

    // 将剩余的项添加到结果多项式中
    while (poly1 != NULL) {
        Term* newNode = (Term*)malloc(sizeof(Term));
        newNode->coef = poly1->coef;
        newNode->expon = poly1->expon;
        newNode->next = NULL;

        if (result == NULL) {
            result = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

                poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        Term* newNode = (Term*)malloc(sizeof(Term));
        newNode->coef = poly2->coef;
        newNode->expon = poly2->expon;
        newNode->next = NULL;

        if (result == NULL) {
            result = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        poly2 = poly2->next;
    }

    return result;
}

// 相减多项式
Term* subtractPolynomials(Term* poly1, Term* poly2) {
    // 多项式相减相当于将 poly2 的系数取相反数，然后与 poly1 相加
    Term* negPoly2 = poly2;
    while (negPoly2 != NULL) {
        negPoly2->coef = -(negPoly2->coef);
        negPoly2 = negPoly2->next;
    }

    // 调用 addPolynomials 函数进行相加
    Term* result = addPolynomials(poly1, poly2);

    // 恢复 poly2 的系数
    negPoly2 = poly2;
    while (negPoly2 != NULL) {
        negPoly2->coef = -(negPoly2->coef);
        negPoly2 = negPoly2->next;
    }

    return result;
}

// 相乘多项式
Term* multiplyPolynomials(Term* poly1, Term* poly2) {
    Term* result = NULL;

    // 遍历 poly1 中的每一项
    while (poly1 != NULL) {
        Term* temp = poly2;
        Term* tempResult = NULL;
        Term* tail = NULL;

        // 将 poly1 的当前项与 poly2 的每一项相乘
        while (temp != NULL) {
            int coef = poly1->coef * temp->coef;
            int exp = poly1->expon + temp->expon;

            // 创建新的节点
            Term* newNode = (Term*)malloc(sizeof(Term));
            newNode->coef = coef;
            newNode->expon = exp;
            newNode->next = NULL;

            if (tempResult == NULL) {
                tempResult = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }

            temp = temp->next;
        }

        // 将 tempResult 和 result 相加
        result = addPolynomials(result, tempResult);

        poly1 = poly1->next;
    }

    return result;
}
// 销毁多项式
void destroyPolynomial(Term* polynomial) {
    Term* current = polynomial;
    while (current != NULL) {
        Term* temp = current;
        current = current->next;
        free(temp);
    }
}

// 合并多项式中的相同指数项
void simplifyPolynomial(Term* polynomial) {
    if (polynomial == NULL) {
        return;
    }

    Term* current = polynomial;
    while (current->next != NULL) {
        if (current->expon == current->next->expon) {
            // 合并相同指数项的系数
            current->coef += current->next->coef;

            // 删除下一个节点
            Term* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}



//polynomial主函数
int polynomial(){
    int choice;
    int loop = 1;
    printf("============欢迎来到多项式模块===========\n");
    printf("===========请输入你的选择============\n");
    printf("1.构造多项式\n2.多项式相加\n3.多项式相减\n4.多项式相乘\n5.返回上一级\n");
    do{
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("请输入多项式1：");
            poly1 = createPolynomial();
            simplifyPolynomial(poly1); // 合并相同指数项
            printPolynomial(poly1);

            printf("请输入多项式2：");
            poly2 = createPolynomial();
            simplifyPolynomial(poly2); // 合并相同指数项
            printPolynomial(poly2);
            break;
        case 2:
            printf("多项式1 + 多项式2：");
            sum = addPolynomials(poly1, poly2);
            simplifyPolynomial(sum); // 合并相同指数项
            printPolynomial(sum);
            break;
        case 3:
            printf("多项式1 - 多项式2：");
            diff = subtractPolynomials(poly1, poly2);
            simplifyPolynomial(diff); // 合并相同指数项
            printPolynomial(diff);
            break;
        case 4:
            printf("多项式1 * 多项式2：");
            prod = multiplyPolynomials(poly1, poly2);
            simplifyPolynomial(prod); // 合并相同指数项
            printPolynomial(prod);
            break;
        case 5:
            loop = 0;
            destroyPolynomial(poly1);
            destroyPolynomial(poly2);
            destroyPolynomial(sum);
            destroyPolynomial(diff);
            destroyPolynomial(prod);
            break;
        default:
            printf("你的输入有误，请重新输入");
        }
    printf("===========请输入你的选择============\n");
    printf("1.构造多项式\n2.多项式相加\n3.多项式相减\n4.多项式相乘\n5.返回上一级\n");
    }while(loop);
    return 0;
}
