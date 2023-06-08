/**
* 7-3 银行业务队列简单模拟
*/
#include <stdio.h>
const int MAX = 1010;

int main3() {

    int a[MAX], b[MAX], cnta, cntb;
    cnta = cntb = 0;
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int temp;
        scanf("%d", &temp);
        if (temp % 2) a[++cnta] = temp;
        else b[++cntb] = temp;
    }
    int flag = 0, x = 1, y = 1;
    while (x <= cnta || y <= cntb) {
        if (x <= cnta) {
            if (flag++) printf(" ");
            printf("%d", a[x++]);
        }
        if (x <= cnta) {
            if (flag++) printf(" ");
            printf("%d", a[x++]);
        }
        if (y <= cntb) {
            if (flag++) printf(" ");
            printf("%d", b[y++]);
        }
    }
    return 0;
}