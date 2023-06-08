/**
 * 7-2 符号配对
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#define Maxsize 105
typedef struct StackRecord *Stack;
struct StackRecord {
    int top;
    char *array;
};

Stack creat();//创建空栈
int cheekEmpty(Stack s);//判断栈是否为空
void push(Stack s, char x);//添加新元素
void pop(Stack s);//删除
char top(Stack s);//取出

char a[100];
char str[200];

int main2() {
    int i, j = 0, flag = 0;
    char ch;
    Stack s = creat();

    while (gets(str)) {
        if (str[0] == '.' && !str[1])
            break;
        for( i=0; str[i]; i++){
            if(str[i]=='('||str[i]=='['||str[i]=='{'||str[i]==')'||str[i]=='}' ||str[i]==']')
                a[j++]=str[i];
            else if(str[i]=='/'&&str[i+1]=='*'){
                a[j++]='<';
                i++;
            }else if(str[i]=='*'&&str[i+1]=='/'){
                a[j++]='>';
                i++;
            }
        }
    }

    for (i = 0; i < j; i++) {
        if (a[i] == '(' || a[i] == '[' || a[i] == '{' || a[i] == '<') {
            push(s, a[i]);
        } else if (a[i] == ')') {
            if (s->top != -1 && top(s) == '(') {
                pop(s);
            } else {
                ch = a[i];
                flag = 1;
                break;
            }
        } else if (a[i] == ']') {
            if (s->top != -1 && top(s) == '[') pop(s);
            else {
                ch = a[i];
                flag = 1;
                break;
            }
        } else if (a[i] == '}') {
            if (s->top != -1 && top(s) == '{') pop(s);
            else {
                ch = a[i];
                flag = 1;
                break;
            }
        } else if (a[i] == '>') {
            if (s->top != -1 && top(s) == '<') pop(s);
            else {
                ch = a[i];
                flag = 1;
                break;
            }
        }
    }

    if (!flag && cheekEmpty(s)) {
        printf("YES\n");
    } else {
        printf("NO\n");
        if (!cheekEmpty(s)) {
            if (top(s) == '<') printf("/*-?\n");
            else printf("%c-?\n", top(s));
        } else {
            if (ch == '>') printf("?-*/\n");
            else printf("?-%c\n", ch);
        }
    }

    return 0;
}

/**
 * 创建新栈
 * @return
 */
Stack creat() {
    Stack s = (Stack) malloc(sizeof(struct StackRecord));
    s->top = -1;
    s->array = (char *) malloc(sizeof(char) * Maxsize);
    return s;
}

/**
 * 判断是否为空栈
 * @param s
 * @return
 */
int cheekEmpty(Stack s) {
    if (s->top == -1)
        return 1;
    else
        return 0;
}

/**
 *添加元素
 * @param s
 * @param x
 */
void push(Stack s, char x) {
    s->array[++(s->top)] = x;
}

/**
 *删除
 * @param s
 */
void pop(Stack s) {
    s->top--;
}

/**
 *取出
 * @param s
 */
char top(Stack s) {
    return s->array[s->top];
}