/**
 * 7-11 QQ帐户的申请与登陆
 *  哈希表  分离链接法
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*账号与密码最大长度的定义
它们的最大长度需要比题目所给的大一位
这是因为还需要一个位置来储存'\0'来判断字符串的结尾*/
#define Max_Password_Len 17
#define Max_Account_Len 11
#define MaxTableSize 1000000

/*各种状态的定义
最好用正数表示成功的状态
用负数或0表示失败的状态
这样会让强迫症看了舒服一点*/
#define ERROR_WrongPW   -2
#define ERROR_Exist     -1
#define ERROR_NOTExist  0
#define New_OK          1
#define Login_OK        2

typedef char AccountType[Max_Account_Len];//账号类型定义
typedef char PasswordType[Max_Password_Len];//密码类型定义
typedef int Index;
typedef enum {
    New, Log
} Pattern;//两种模式，新建账号与登入账号

typedef struct {
    AccountType Account;
    PasswordType Password;
} ElemType;//数据类型的定义，每个对应一个用户，内含用户的账号和密码

//链表指针的定义
typedef struct LNode *PtrToLNode;
//链表结点的定义
typedef struct LNode {
    PtrToLNode Next;
    ElemType Data;
} LNode;
typedef PtrToLNode List;//链表的定义
typedef PtrToLNode Position;//哈希表中结点位置的定义

//哈希表的定义
typedef struct TblNode *HashTable;
typedef struct TblNode {
    int TableSize;//哈希表的大小
    List Heads;//储存各个列表头节点的数组
} TblNode;

int NextPrime(int N)//返回N的下一个素数
{
    int i, P;
    P = N % 2 ? N + 2 : N + 1;
    //P为N之后的第一个奇数
    while (P < MaxTableSize) {
        for (i = (int) sqrt(P); i > 2; i--)//因为只考虑奇数，所以i为2时就结束了
            if (P % i == 0)
                break;
        if (i == 2)
            break;//i为2说明P为素数
        else
            P += 2;//i!=2说明P不是素数，则P指向下一个奇数
    }
    return P;
}

int Hash(int Key, int TableSize) {//返回Key值相对应的哈希值，即其在哈希表中的储存下标
    return Key % TableSize;
}

HashTable CreateTable(int TableSize) {    //构造空的哈希表
    HashTable H;
    int i;
    H = (HashTable) malloc(sizeof(TblNode));
    H->TableSize = NextPrime(TableSize);
    H->Heads = (List) malloc(sizeof(LNode) * H->TableSize);
    for (i = 0; i < H->TableSize; i++) {
        H->Heads[i].Data.Account[0] = '\0';
        H->Heads[i].Data.Password[0] = '\0';
        H->Heads[i].Next = NULL;
    }
    return H;
}

Position Find(HashTable H, ElemType Key) {
    Position Pos;
    Index p;
    if (strlen(Key.Account) > 5) //账号大于5位时取最后5位
        p = Hash(atoi(Key.Account +
                      strlen(Key.Account) - 5), H->TableSize);
    else//账号不大于5位则等于它本身
        p = Hash(atoi(Key.Account), H->TableSize);
    Pos = H->Heads[p].Next;
    while (Pos && strcmp(Key.Account, Pos->Data.Account))
        Pos = Pos->Next;
    return Pos;//Pos指向用户数据的位置，没有注册就返回NULL
}

int NewOrLog(HashTable H, ElemType Key, Pattern P) {    //返回状态参数
    Position Pos, NewPos;
    Index p;
    Pos = Find(H, Key);
    switch (P) {
        case Log:
            if (Pos == NULL)
                return ERROR_NOTExist;//登陆时不存在账号
            else if (strcmp(Pos->Data.Password, Key.Password) ||
                     (strlen(Key.Password) > 16 || strlen(Key.Password) < 6))
                return ERROR_WrongPW; //密码错误或格式错误
            else
                return Login_OK;//账号和密码均正确，可以登录
        case New:
            if (Pos != NULL)
                return ERROR_Exist; //新建账号时发现已经存在这样的账号了
            else {
                NewPos = (Position) malloc(sizeof(LNode));
                strcpy(NewPos->Data.Account, Key.Account);
                strcpy(NewPos->Data.Password, Key.Password);
                if (strlen(Key.Account) > 5)
                    p = Hash(atoi(Key.Account +
                                  strlen(Key.Account) - 5), H->TableSize);
                else
                    p = Hash(atoi(Key.Account), H->TableSize);
                NewPos->Next = H->Heads[p].Next;
                H->Heads[p].Next = NewPos;
                return New_OK; //插入新值并返回插入成功
            }
    }
}

void DestroyTable(HashTable H) {    //销毁哈希表
    PtrToLNode p, q;
    int i;
    for (i = 0; i < H->TableSize; i++) {
        q = H->Heads[i].Next;
        while (q) {
            p = q->Next;
            free(q);
            q = p;
        }
    }
    free(H);
}

int main11(void) {
    int N, i;
    ElemType Key;
    char Input;
    Pattern P;
    HashTable H;
    scanf("%d", &N);
    H = CreateTable(2 * N);
    for (i = 0; i < N; i++) {
        scanf("\n%c %s %s", &Input, Key.Account, Key.Password);
        P = (Input == 'L') ? Log : New;
        switch (NewOrLog(H, Key, P)) {//最后根据不同返回值输出对应状态即可
            case ERROR_Exist:
                printf("ERROR: Exist\n");
                break;
            case ERROR_NOTExist:
                printf("ERROR: Not Exist\n");
                break;
            case ERROR_WrongPW:
                printf("ERROR: Wrong PW\n");
                break;
            case Login_OK:
                printf("Login: OK\n");
                break;
            case New_OK:
                printf("New: OK\n");
                break;
        }
    }
    DestroyTable(H);
    return 0;
}