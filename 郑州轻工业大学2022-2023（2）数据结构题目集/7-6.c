/**
 * 7-6 公路村村通
 * 最小生成树，普利姆算法
 */

#include <stdio.h>
#include <stdlib.h>

int fa[1005];

typedef struct {
    int l;
    int r;
    int weight;
} Node;

Node p[3005];
int n, m, sum, cnt;

int cmp(const void *a, const void *b) {
    Node *p1 = (Node *) a;
    Node *p2 = (Node *) b;
    return p1->weight - p2->weight;
}

int Find(int x) {
    return (x == fa[x]) ? (x) : (fa[x] = Find(fa[x]));
}

void Union(int x, int y) {
    fa[Find(x)] = Find(y);
}

int main6() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 0; i < m; i++)
        scanf("%d %d %d", &p[i].l, &p[i].r, &p[i].weight);
    qsort(p, m, sizeof(Node), cmp);
    for (int i = 0; i < m; i++) {
        if (Find(p[i].l) != Find(p[i].r)) {
            sum += p[i].weight;
            Union(p[i].l, p[i].r);
            cnt++;
        }
        if (cnt == n - 1)
            break;
    }
    if (cnt == n - 1)
        printf("%d\n", sum);
    else
        printf("-1\n");
    return 0;
}
