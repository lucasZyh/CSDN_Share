/**
 * 7-12 人以群分
 *  排序
 */

#include <stdio.h>
#include <stdlib.h>

int comfunc(const void *elem1, const void *elem2);

void sort_character(int *p, int n);

int main12() {
    int n, i;
    int a[100001];

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    qsort(a, n, sizeof(int), comfunc);
    sort_character(a, n);

    return 0;
}

int comfunc(const void *elem1, const void *elem2) {
    int *p1 = (int *) elem1;
    int *p2 = (int *) elem2;

    return *p1 - *p2;
}

void sort_character(int *p, int n) {
    int i, j, n1, n2, sum1, sum2, dif, dif1, dif2;

    sum1 = sum2 = 0;
    dif = dif1 = dif2 = 0;
    if (n % 2 == 0) {
        n1 = n2 = n / 2;
        for (i = 0; i < n1; i++)
            sum1 += p[i];
        for (i = n1; i < n; i++)
            sum2 += p[i];
        dif = abs(sum2 - sum1);
    } else {
        n1 = n2 = n / 2;
        for (i = 0; i < n1; i++)
            sum1 += p[i];
        for (i = n / 2 + 1; i < n; i++)
            sum2 += p[i];
        dif1 = abs(sum1 + p[n1] - sum2);
        dif2 = abs(sum2 + p[n2] - sum1);
        dif = (dif1 > dif2) ? dif1 : dif2;
        if (dif1 > dif2)
            n1++;
        else
            n2++;
    }
    printf("Outgoing #: %d\n", n2);
    printf("Introverted #: %d\n", n1);
    printf("Diff = %d\n", dif);

}
