/**
 * 7-14 PAT排名汇总
 *  快速排序
 */
#include <stdio.h>
#include <string.h>

struct stu {
    char id[14];                //考号
    int score;                  //分数
    int kc;                     //考场
};
struct stu a[30000];

int bigger(const char *s1, const char *s2) {
    for (int i = 0; i < 13; i++)
        if (s1[i] > s2[i])
            return 1;
        else if (s1[i] < s2[i])
            return 0;
    return 1;
}

void qsort(int l, int r) {
    if (l >= r)
        return;

    int i = l;
    int j = r;

    struct stu t = a[l];
    while (i != j) {
        while (i < j && (a[j].score < t.score || a[j].score == t.score && bigger(a[j].id, t.id)))
            j--;
        while (i < j && (a[i].score > t.score || a[i].score == t.score && bigger(t.id, a[i].id)))
            i++;
        if (i < j) {
            struct stu s = a[i];
            a[i] = a[j];
            a[j] = s;
        }
    }
    a[l] = a[i];
    a[i] = t;

    qsort(l, i - 1);
    qsort(i + 1, r);

    return;
}

void Copy(int *b2, int *b1, int n) {
    for (int i = 1; i <= n; i++)
        b2[i] = b1[i];
}

int main14() {
    int n, j, i, top = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        int k;
        scanf("%d", &k);
        for (j = 0; j < k; j++) {
            char id[14];
            int score;
            scanf("%s %d", id, &score);
            a[top].score = score;
            a[top].kc = i;
            strcpy(a[top].id, id);
            top++;
        }
    }
    qsort(0, top - 1);

    int levall = 1, b1[n + 1], b2[n + 1], score = a[0].score;

    for (i = 1; i <= n; i++)
        b1[i] = 1, b2[i] = 1;
    printf("%d\n", top);
    printf("%s %d %d %d\n", a[0].id, 1, a[0].kc, 1);
    int llevall = 1;            //上一个总排名
    levall = 2;                   //总排名

    Copy(b2, b1, n);
    b1[a[0].kc]++;
    for (i = 1; i < top; i++) {
        if (a[i].score == a[i - 1].score) {
            printf("%s %d %d %d\n", a[i].id, llevall, a[i].kc, b2[a[i].kc]);
            levall++;
            b1[a[i].kc]++;
        } else {
            printf("%s %d %d %d\n", a[i].id, levall, a[i].kc, b1[a[i].kc]);
            llevall = levall;
            levall++;

            Copy(b2, b1, n);
            b1[a[i].kc]++;                    //考场的排名
        }
    }
    return 0;
}

