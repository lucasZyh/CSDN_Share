/**
 * 7-7 畅通工程之最低成本建设问题
 * 最小生成树，Kruskal算法
 */

#include <stdio.h>
#include <stdlib.h>

struct path {
    int a, b, c;
} p[3000];
int f[1001], n, m;

void init() {
    for (int i = 1; i <= n; i++) f[i] = i;
}

int getf(int k) {
    if (f[k] == k) return f[k];
    return f[k] = getf(f[k]);
}

int cmp(const void *a, const void *b) {
    return ((struct path *) a)->c - ((struct path *) b)->c;
}

int main7() {
    scanf("%d%d", &n, &m);
    init();
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].c);
    }
    qsort(p, m, sizeof(p[0]), cmp);
    int c = 0, ans = 0;
    for (int i = 0; i < m; i++) {
        if (getf(p[i].a) != getf(p[i].b)) {
            ans += p[i].c;
            c++;
            f[getf(p[i].a)] = getf(p[i].b);
        }
    }
    if (c < n - 1) printf("Impossible\n");
    else printf("%d\n", ans);
    return 0;
}
