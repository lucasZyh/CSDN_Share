/**
 * 7-1 一元多项式的乘法与加法运算
 */
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct LNode *List;

struct LNode {
    ElementType coe;//系数
    ElementType exp;//指数
    List Next;//下一个节点
};

void Insert(List L, ElementType coe, ElementType exp);//插入
List Multi(List p1, List p2);//乘法
List Plus(List p1, List p2);//加法
int compare(List p1, List p2);//比较系数大小

int main1() {
    List p1, p2;
    List p;
    int num1, num2, coe, exp;
    int i;
    p1 = (List) malloc(sizeof(struct LNode));
    p2 = (List) malloc(sizeof(struct LNode));
    p1->Next = NULL;
    p2->Next = NULL;

    scanf("%d", &num1);
    for (i = 0; i < num1; i++) {
        scanf("%d %d", &coe, &exp);
        Insert(p1, coe, exp);
    }
    scanf("%d", &num2);
    for (i = 0; i < num2; i++) {
        scanf("%d %d", &coe, &exp);
        Insert(p2, coe, exp);
    }
    //乘法运算
    p = Multi(p1->Next, p2->Next);
    while (p) {
        if (p->Next != NULL) {
            printf("%d %d ", p->coe, p->exp);//非最后一个节点,不换行打印,后接空格
        } else {
            printf("%d %d\n", p->coe, p->exp);//最后一个节点,换行打印
        }
        p = p->Next;
    }
    //加法运算
    p = Plus(p1->Next, p2->Next);
    if (p) {
        while (p) {
            if (p->Next != NULL) {
                printf("%d %d ", p->coe, p->exp);
            } else {
                printf("%d %d\n", p->coe, p->exp);
            }
            p = p->Next;
        }
    } else {//防止出现p1,p2抵消为零的情况
        printf("0 0\n");
    }
    return 0;
}

/**
 * 向链表中添加元素
 * @param L 需要添加的链表
 * @param coefficient 系数
 * @param exponent 指数
 */
void Insert(List L, ElementType coe, ElementType exp) {
    List s, p;
    p = L;

    while (p->Next)//找到最后一个节点
        p = p->Next;

    s = (List) malloc(sizeof(struct LNode));
    s->Next = NULL;
    s->coe = coe;
    s->exp = exp;

    p->Next = s;
}

/**
 * 两个多项式相乘
 * @param p1 代表多项式1的链表
 * @param p2 代表多项式2的链表
 * @return p 相乘后生成的新链表
 */
List Multi(List p1, List p2) {
    List p, p1a, p2a, s;
    int flag = 1;
    p = (List) malloc(sizeof(struct LNode));
    p->Next = NULL;
    p1a = p1;

    while (p1a) {
        p2a = p2;//确保p1多项式中的每一项可以与p2多项式中的每一项分别相乘
        s = (List) malloc(sizeof(struct LNode));
        s->Next = NULL;

        while (p2a) {//与p2多项式中的每一项分别相乘
            Insert(s, p1a->coe * p2a->coe, p1a->exp + p2a->exp);
            p2a = p2a->Next;
        }
        s = s->Next;

        if (flag == 1) {
            p = p->Next;
            /*
             * 如果是p1第一项与p2每一项相乘,那么先将链表p向后移一位,将头结点屏蔽
             * 因为默认初始化的P1头结点有默认的exp = 0,coe = 0,这两个数据是多余的
             * 如果不后移,那么头结点默认的数值0将会一直尾随整个乘法运算,导致最后的结果后面多两个0 0
             */
            flag = 0;

        }
        p = Plus(p, s);//相加,确保同类项合并
        p1a = p1a->Next;
        free(s);
    }

    return p;
}

/**
 * 比较两多项式指数大小
 * @param p1 代表多项式1的链表
 * @param p2 代表多项式2的链表
 * @return 返回值为0时表示两指数相同,可以进行加法运算
 */
int compare(List p1, List p2) {
    if (p1->exp > p2->exp)
        return 1;//p1指数大
    else if (p1->exp < p2->exp)
        return -1;//p1指数小
    else
        return 0;//指数相同
}

/**
 * 两个多项式相加
 * @param p1 代表多项式1的链表
 * @param p2 代表多项式2的链表
 * @return p 相加后生成的新链表
 */
List Plus(List p1, List p2) {
    List p, p1a, p2a;
    int temp;
    p = (List) malloc(sizeof(struct LNode));
    p->Next = NULL;
    p1a = p1;
    p2a = p2;

    while (p1a && p2a) {
        temp = compare(p1a, p2a);
        //判断指数大小,同指数才可以运算
        switch (temp) {
            case 1:
                //当前p1a的指数大,将当前p1a的数据放入新链表
                Insert(p, p1a->coe, p1a->exp);
                p1a = p1a->Next;//p1a向后移动,p2a不改变
                break;
            case -1:
                //当前p2a的指数大,将当前p2a的数据放入新链表
                Insert(p, p2a->coe, p2a->exp);
                p2a = p2a->Next;//p2a向后移动,p1a不改变
                break;
            case 0:
                //指数相同,进行运算
                if ((p1a->coe + p2a->coe) == 0) {
                    //系数为0,数据不放入新链表,直接将p1a和p2a后移
                    p1a = p1a->Next;
                    p2a = p2a->Next;
                } else {
                    //数据放入新链表,p1a和p2a后移
                    Insert(p, p1a->coe + p2a->coe, p2a->exp);
                    p1a = p1a->Next;
                    p2a = p2a->Next;
                }
                break;
            default:
                break;
        }
    }
    while (p1a) {
        //p1a的项数多,将剩余项放入链表
        Insert(p, p1a->coe, p1a->exp);
        p1a = p1a->Next;
    }
    while (p2a) {
        //p2a的项数多,将剩余项放入链表
        Insert(p, p2a->coe, p2a->exp);
        p2a = p2a->Next;
    }
    p = p->Next;
    return p;
}