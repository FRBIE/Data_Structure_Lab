#include<stdio.h>
#include<stdlib.h>
// 二叉树结点定义
typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
    int isThreaded;  // 用于中序线索化的标志位
} TreeNode;

// 创建二叉树B的函数
TreeNode* createBinaryTree(char* str, int* index) {
    char ch = str[*index];
    if (ch == ',' || ch == ')' || ch == '\0') {
        return NULL;
    }
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = ch;
    node->isThreaded = 0;
    node->left = NULL;
    node->right = NULL;
    (*index)++;
    if (str[*index] == '(') {
        (*index)++; // 跳过左括号
        node->left = createBinaryTree(str, index);
    }
    if (str[*index] == ',') {
        (*index)++; // 跳过逗号
        node->right = createBinaryTree(str, index);
    }
    if (str[*index] == ')') {
        (*index)++; // 跳过右括号
    }
    return node;
}



// 输出二叉树B中某结点的左右孩子结点的值
void printChildNodes(TreeNode* root, char ch) {
    if (root == NULL) {
        return;
    }
    if (root->data == ch) {
        if (root->left != NULL) {
            printf("左孩子结点的值为：%c\n", root->left->data);
        } else {
            printf("左孩子结点不存在\n");
        }
        if (root->right != NULL) {
            printf("右孩子结点的值为：%c\n", root->right->data);
        } else {
            printf("右孩子结点不存在\n");
        }
    }
    printChildNodes(root->left, ch);
    printChildNodes(root->right, ch);
}

// 计算二叉树B的高度
int getHeight(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// 用凹入表示法输出二叉树B
void printIndentedTree(TreeNode* root, int level) {
    if (root == NULL) {
        return;
    }
    int i;
    for (i = 0; i < level; i++) {
        printf("  ");  // 每一层缩进两个空格
    }
    printf("%c\n", root->data);
    printIndentedTree(root->left, level + 1);
    printIndentedTree(root->right, level + 1);
}

// 用括号表示法输出二叉树B
void printParenthesisTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%c", root->data);
    if (root->left != NULL || root->right != NULL) {
        printf("(");
        printParenthesisTree(root->left);
        printf(",");
        printParenthesisTree(root->right);
        printf(")");
    }
}

// 先序遍历并输出二叉树B，并将B的先序序列存储在数组A中
void preorderTraversal(TreeNode* root, char* A, int* index) {
    if (root == NULL) {
        return;
    }
    printf("%c ", root->data);
    A[(*index)++] = root->data;
    preorderTraversal(root->left, A, index);
    preorderTraversal(root->right, A, index);
}

// 中序遍历并输出二叉树B，并将B的中序序列存储在数组B中
void inorderTraversal(TreeNode* root, char* B, int* index) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left, B, index);
    printf("%c ", root->data);
    B[(*index)++] = root->data;
    inorderTraversal(root->right, B, index);
}

// 后序遍历并输出二叉树B
void postorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%c ", root->data);
}

// 释放二叉树B的内存
void freeBinaryTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeBinaryTree(root->left);
    freeBinaryTree(root->right);
    free(root);
}

// 根据先序序列数组A和中序序列数组B重新构造二叉树
TreeNode* buildTreeFromPreorderInorder(char* A, char* B, int start, int end) {
    static int preIndex = 0;
    if (start > end) {
        return NULL;
    }
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = A[preIndex++];
    node->isThreaded = 0;
    if (start == end) {
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    int inIndex;
    for (inIndex = start; inIndex <= end; inIndex++) {
        if (B[inIndex] == node->data) {
            break;
        }
    }
    node->left = buildTreeFromPreorderInorder(A, B, start, inIndex - 1);
    node->right = buildTreeFromPreorderInorder(A, B, inIndex + 1, end);
    return node;
}

// 中序线索化二叉树B的函数
void inorderThreading(TreeNode* root, TreeNode** prev) {
    if (root == NULL) {
        return;
    }
    inorderThreading(root->left, prev);
    if (root->left == NULL) {
        root->left = *prev;
        root->isThreaded = 1;
    }
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->isThreaded = 1;
    }
    *prev = root;
    inorderThreading(root->right, prev);
}

// 找到中序线索二叉树C的第一个结点
TreeNode* findFirstNode(TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->left != NULL && !root->isThreaded) {
        root = root->left;
    }
    return root;
}

// 非递归方式遍历输出中序线索二叉树C的中序序列
void inorderTraversalThreaded(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    TreeNode* current = findFirstNode(root);
    while (current != NULL) {
        printf("%c ", current->data);
        if (current->isThreaded) {
            current = current->right;
        } else {
            current = findFirstNode(current->right);
        }
    }
}


int main() {
    char str[] = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
    int index = 0;
    TreeNode* root = createBinaryTree(str, &index);
    printChildNodes(root, 'H');

    printf("\n二叉树B的高度：%d\n", getHeight(root));

    printf("\n用凹入表示法输出二叉树B：\n");
    printIndentedTree(root, 0);

    printf("\n用括号表示法输出二叉树B：\n");
    printParenthesisTree(root);
    printf("\n");

    printf("\n 先序遍历并输出二叉树B：\n");
    char preorderArray[100];
    int preorderIndex = 0;
    preorderTraversal(root, preorderArray, &preorderIndex);
    printf("\n");

    printf("\n中序遍历并输出二叉树B：\n");
    char inorderArray[100];
    int inorderIndex = 0;
    inorderTraversal(root, inorderArray, &inorderIndex);
    printf("\n");

    printf("\n 后序遍历并输出二叉树B：\n");
    postorderTraversal(root);
    printf("\n");

    printf("\n 释放二叉树B的内存\n");
    freeBinaryTree(root);

    char preorder[] = "ABDEHJKLMNCFGI";
    char inorder[] = "HJKLMNEDBACFGI";
    TreeNode* reconstructedTree = buildTreeFromPreorderInorder(preorder, inorder, 0, 14);

    printf("\n重新构造的二叉树B（先序遍历）：\n");
    preorderTraversal(reconstructedTree, preorderArray, &preorderIndex);
    printf("\n");

    printf("\n 对二叉树B进行中序线索化\n");
    TreeNode* prev = NULL;
    inorderThreading(reconstructedTree, &prev);

    printf("\n中序线索二叉树C的中序序列：\n");
    inorderTraversalThreaded(reconstructedTree);
    printf("\n");
    system("pause");
    return 0;
}