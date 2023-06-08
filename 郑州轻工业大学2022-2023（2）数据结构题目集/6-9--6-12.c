
/**
 * 6-10 二叉树的遍历
 * @param BT
 */
/*void InorderTraversal(BinTree BT) {//中序遍历
    if (BT) {
        InorderTraversal(BT->Left);
        printf(" %c", BT->Data);
        InorderTraversal(BT->Right);
    }
}

void PreorderTraversal(BinTree BT) {//先序遍历
    if (BT) {
        printf(" %c", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

void PostorderTraversal(BinTree BT) {//后序遍历
    if (BT) {
        PostorderTraversal(BT->Left);
        PostorderTraversal(BT->Right);
        printf(" %c", BT->Data);
    }
}

void LevelorderTraversal(BinTree BT) {
    BinTree B[100];//结构体数组
    BinTree T;
    int i = 0, j = 0;
    if (!BT)return;//树为空，返回
    if (BT)//不为空
    {
        B[i++] = BT;//根节点入队
        while (i != j)//队列不空
        {
            T = B[j++];//出队
            printf(" %c", T->Data);
            if (T->Left) B[i++] = T->Left;
            if (T->Right) B[i++] = T->Right;
        }
    }
}*/
/**
 * 6-11 二叉树的非递归遍历
 * @param BT
 */
/*void InorderTraversal( BinTree BT ){//中序遍历
    BinTree T=BT;
    Stack S =CreateStack();
    while(T||!IsEmpty(S)){
        while(T!=NULL){
            Push(S,T);
            T=T->Left;
        }
        T=Pop(S);
        printf(" %c",T->Data);
        T=T->Right;
    }
}
void PreorderTraversal( BinTree BT ){//先序遍历
    BinTree T=BT;
    Stack S =CreateStack();
    while(T||!IsEmpty(S)){
        while(T!=NULL){
            Push(S,T);
            printf(" %c",T->Data);
            T=T->Left;
        }
        T=Pop(S);
        T=T->Right;
    }
}
void PostorderTraversal( BinTree BT ){//后序遍历
    BinTree T=BT;
    Stack S =CreateStack();
    while(T||!IsEmpty(S)){
        while(T!=NULL){
            T->flag=0;
            Push(S,T);
            T=T->Left;
        }
        T=Peek(S);
        if(T->flag==0){
            T->flag++;
            T=T->Right;
        }
        else{
            T=Pop(S);
            printf(" %c",T->Data);
            T=NULL;
        }
    }
}*/
/**
 * 6-12 求二叉树高度
 * @param BT
 * @return
 */
/*int GetHeight(BinTree BT) {
    int lNum, rNum, Height;
    if (BT) {
        lNum = GetHeight(BT->Left);
        rNum = GetHeight(BT->Right);
        if (lNum > rNum)
            Height = lNum;
        else
            Height = rNum;
        return Height + 1;
    } else {
        return 0;
    }
}*/