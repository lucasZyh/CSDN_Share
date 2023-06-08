/**
 * 6-1 线性表元素的区间删除
 * @param L
 * @param minD
 * @param maxD
 * @return
 */
/*
List Delete(List L, ElementType minD, ElementType maxD) {
    int i, p = 0;
    for (i = 0; i <= L->Last; i++) {
        if (L->Data[i] <= minD || L->Data[i] >= maxD) {
            L->Data[p++] = L->Data[i];
        }
    }
    L->Last = p - 1;
    return L;
}
*/

/**
 * 6-2 有序表的插入
 * @param L
 * @param x
 */
/*void ListInsertSort(SqList *L, DataType x) {
    int i;
    int temp = 0;

    for (i = 0; L->items[i] < x; i++) {
        temp++;
    }

    for (i = L->length - 1; i >= temp; i--) {
        L->items[i + 1] = L->items[i];
    }
    L->items[temp] = x;
    L->length++;
}*/

/*void ListInsertSort(SqList *L, DataType x) {
    int i;
    int temp = 1;

    for (i = 0; L->items[i] < x; i++) {
        temp++;
    }

    ListInsert(L, temp, x);
}*/

/**
 *6-3 合并两个有序数组
 * @param a
 * @param m
 * @param b
 * @param n
 * @param c
 */
/*void merge(int *a, int m, int *b, int n, int *c) {
    int i, j, k;
    while (i < m && j < n) {
        if (a[i] < b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    }
    while (i < m) {
        c[k++] = a[i++];
    }
    while (j < n) {
        c[k++] = b[j++];
    }
}*/

/**
 * 6-4 顺序表操作集
 * @return
 */
// 创建并返回一个空的线性表
/*
List MakeEmpty() {
    List list;
    list = (List) malloc(sizeof(struct LNode));
    list->Last = -1;
    return list;
}
//回线性表中X的位置。若找不到则返回ERROR
Position Find(List L, ElementType X) {
    int i;
    for (i = 0; i < MAXSIZE; i++) {
        if (L->Data[i] == X)
            return i;
    }
    return ERROR;
}
//将X插入在位置P并返回true。若空间已满，则打印“FULL”并返回false；如果参数P指向非法位置，则打印“ILLEGAL POSITION”并返回false；
bool Insert(List L, ElementType X, Position P) {
    int i;

    if (L->Last == MAXSIZE - 1) {
        printf("FULL");
        return false;
    }

    if (P < 0 || P > L->Last + 1) {
        printf("ILLEGAL POSITION");
        return false;
    }

    for (i = L->Last; i >= P; i--) {
        L->Data[i + 1] = L->Data[i];
    }
    L->Data[P] = X;
    L->Last++;
    return true;

}
//将位置P的元素删除并返回true。若参数P指向非法位置，则打印“POSITION P EMPTY”（其中P是参数值）并返回false
bool Delete(List L, Position P) {
    int i;

    if (P < 0 || P > L->Last) {
        printf("POSITION %d EMPTY", P);
        return false;
    }

    for (i = P; i < L->Last; i++) {
        L->Data[i] = L->Data[i + 1];
    }
    L->Last--;

    return true;
}
*/
/**
 *6-5 递增的整数序列链表的插入
 * @param L
 * @param X
 * @return
 */
/*List Insert(List L, ElementType X) {
    List p, s;
    p = L;
    s = (List) malloc(sizeof(struct Node));
    s->Data = X;

    while (p->Next && p->Next->Data < X) {
        p = p->Next;
    }
    s->Next = p->Next;
    p->Next = s;

    return L;
}*/
/**
 * 6-6 删除单链表偶数节点
 * @return
 */
//从标准输入读入一系列正整数，按照读入顺序建立单链表。当读到?1时表示输入结束，函数应返回指向单链表头结点的指针
/*
struct ListNode *createlist() {
    int m;
    struct ListNode *p, *s, *l;
    p = (struct ListNode *) malloc(sizeof(struct ListNode));

    scanf("%d", &m);
    if (m == -1)
        return NULL;
    p->data = m;
    p->next = NULL;
    s = p;

    while (1) {
        scanf("%d", &m);
        if (m == -1)
            break;
        l = (struct ListNode *) malloc(sizeof(struct ListNode));
        l->data = m;
        l->next = NULL;
        s->next = l;
        s = l;
    }
    return p;

}
//将单链表head中偶数值的结点删除，返回结果链表的头指针
struct ListNode *deleteeven(struct ListNode *head) {
    struct ListNode *p = NULL, *s = NULL;

    while (head && head->data % 2 == 0) {
        p = head;
        head = head->next;
        free(p);
    }
    if (head == NULL)
        return NULL;
    s = head;
    while (s->next) {
        if (s->next->data % 2 == 0)
            s->next = s->next->next;
        else
            s = s->next;
    }
    return head;
}
*/
/**
 * 6-7 逆序数据建立链表
 * @return
 */
/*
struct ListNode *createlist() {
    int m;
    struct ListNode *head, *p;
    head = (struct ListNode *) malloc(sizeof(struct ListNode));
    head->next = NULL;

    while (1) {
        scanf("%d", &m);
        if (m == -1)
            break;
        p = (struct ListNode *) malloc(sizeof(struct ListNode));
        p->next = head->next;
        p->data = m;
        head->next = p;
    }
    return head->next;
}
*/

/**
 * 6-8 求链表的倒数第m个元素
 * @param L
 * @param m
 * @return
 */
/*ElementType Find(List L, int m) {
    int i;
    PtrToNode p, s;
    p = s = L;

    for (i = 0; i < m; i++) {
        p = p->Next;
        if (!p)
            return ERROR;
    }
    while (p) {
        s = s->Next;
        p = p->Next;
    }

    return s->Data;
}*/

/**
 *6-9 两个有序链表序列的合并
 * @param L1
 * @param L2
 * @return
 */
/*List Merge(List L1, List L2) {
    List pa, pb, pc;
    pa = L1->Next;
    pb = L2->Next;
    List L = (List) malloc(sizeof(List));
    pc = L;

    while (pa && pb) {
        if (pa->Data > pb->Data) {
            pc->Next = pb;
            pb = pb->Next;
        } else {
            pc->Next = pa;
            pa = pa->Next;
        }
        pc = pc->Next;
    }

    if (pa)
        pc->Next = pa;
    if (pb)
        pc->Next = pb;
    L1->Next = NULL;
    L2->Next = NULL;

    return L;
}*/
