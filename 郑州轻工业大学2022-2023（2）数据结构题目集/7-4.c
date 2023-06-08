/**
 * 7-4 顺序存储的二叉树的最近的公共祖先问题
 */
#include <stdio.h>

int find(int i, int j);

int main4() {
    int n, i, j, m;
    int a[1000];
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d %d", &i, &j);

    if (a[i] == 0)//查错
    {
        printf("ERROR: T[%d] is NULL\n", i);
        return 0;
    }
    if (a[j] == 0)//查错
    {
        printf("ERROR: T[%d] is NULL\n", j);
        return 0;
    }
    m = find(i, j);
    printf("%d %d", m, a[m]);
    return 0;
}
/**
 * 查找公共祖先,二分查找
 * @param i
 * @param j
 * @return
 */
int find(int i, int j) {
    if (i == j) {
        return i;
    } else if (i > j) {
        return find(i / 2, j);
    } else if (i < j) {
        return find(i, j / 2);
    }
}