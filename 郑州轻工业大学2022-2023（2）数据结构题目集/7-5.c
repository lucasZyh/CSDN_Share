/**
 * 7-5 修理牧场
 */
#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef struct HuffmanTreeNode {
    ElemType data;  //哈夫曼树中节点的权值
    struct HuffmanTreeNode *left;
    struct HuffmanTreeNode *right;
} HuffmanTreeNode, *HuffmanTree;

HuffmanTree createHuffmanTree(ElemType arr[], int N) {
    HuffmanTree treeArr[N];
    HuffmanTree tree, pRoot = NULL;

    for (int i = 0; i < N; i++) {  //初始化结构体指针数组,数组中每一个元素为一个结构体指针类型
        tree = (HuffmanTree) malloc(sizeof(HuffmanTreeNode));
        tree->data = arr[i];
        tree->left = tree->right = NULL;
        treeArr[i] = tree;
    }

    for (int i = 1; i < N; i++) {  //进行 n-1 次循环建立哈夫曼树

        //k1为当前数组中第一个非空树的索引，k2为第二个非空树的索引
        int k1 = -1, k2 = 0;
        for (int j = 0; j < N; j++) {
            if (treeArr[j] != NULL && k1 == -1) {
                k1 = j;
                continue;
            }
            if (treeArr[j] != NULL) {
                k2 = j;
                break;
            }
        }
        //循环遍历当前数组，找出最小值索引k1,和次小值索引k2
        for (int j = k2; j < N; j++) {
            if (treeArr[j] != NULL) {
                if (treeArr[j]->data < treeArr[k1]->data) {//最小
                    k2 = k1;
                    k1 = j;
                } else if (treeArr[j]->data < treeArr[k2]->data) {//次小
                    k2 = j;
                }
            }
        }
        //由最小权值树和次最小权值树建立一棵新树,pRoot指向树根结点
        pRoot = (HuffmanTree) malloc(sizeof(HuffmanTreeNode));
        pRoot->data = treeArr[k1]->data + treeArr[k2]->data;
        pRoot->left = treeArr[k1];
        pRoot->right = treeArr[k2];

        treeArr[k1] = pRoot; //将新生成的数加入到数组中k1的位置
        treeArr[k2] = NULL; //k2位置为空
    }

    return pRoot;
}

ElemType calculateWeightLength(HuffmanTree ptrTree, int len) {
    if (ptrTree == NULL) { //空树返回0
        return 0;
    } else {
        if (ptrTree->left == NULL && ptrTree->right == NULL) { //访问到叶子节点
            return ptrTree->data * len;
        } else {
            return calculateWeightLength(ptrTree->left, len + 1) + calculateWeightLength(ptrTree->right, len + 1); //向下递归计算
        }
    }
}

int main5() {
    ElemType arr[10001];
    int i = 0, N;
    scanf("%d", &N);

    while (i < N)
        scanf("%d", &arr[i++]);

    HuffmanTree pRoot = createHuffmanTree(arr, N);  //返回指向哈夫曼树根节点的指针

    printf("%d", calculateWeightLength(pRoot, 0));

    return 0;
}