/**
 * 7-10 旅游规划
 *  最短路径  弗洛伊德算法
 */

#include<stdio.h>

#define MAXN 500
#define ERROR -1
#define Infinite 65534

int N, M, S, D;//城市的个数 高速公路的条数 出发地 目的地
int Dist[MAXN][MAXN], Cost[MAXN][MAXN];//距离与花费矩阵
int dist[MAXN], cost[MAXN], visit[MAXN];//最短距离与花费 标记数组

void Inicialization(void);

void FindTheWay(void);

int FindMinWay(void);

int main10() {
    scanf("%d %d %d %d", &N, &M, &S, &D);//城市的个数 高速公路的条数 出发地 目的地
    Inicialization();//初始化
    FindTheWay();
    printf("%d %d", dist[D], cost[D]);
    return 0;
}

void Inicialization(void) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            Dist[i][j] = Cost[i][j] = Infinite;//矩阵初始化为无限值

    int v1, v2, d, c;
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d %d", &v1, &v2, &d, &c);
        Dist[v1][v2] = Dist[v2][v1] = d;//输入距离路径
        Cost[v1][v2] = Cost[v2][v1] = c;//输入花费路径
    }

    for (int i = 0; i < N; i++)
        dist[i] = cost[i] = Infinite;//矩阵初始化为无限值
}

void FindTheWay(void) {
    dist[S] = cost[S] = 0;//出发地为0
    visit[S] = 1;//出发地访问标记
    int v;
    for (int i = 0; i < N; i++)//记录出发地直达的路径
        if (!visit[i] && Dist[S][i] < Infinite) //如果没访问 且有路径
        {
            dist[i] = Dist[S][i];
            cost[i] = Cost[S][i];
        }
    while (1) {
        v = FindMinWay();//找出最短出发地直达且未访问的城市
        if (v == ERROR) break;
        visit[v] = 1;//找出城市的访问标记

        for (int i = 0; i < N; i++)//循环每个城市
            if (!visit[i] && Dist[v][i] < Infinite)//如果未访问且有路径
                if ((dist[v] + Dist[v][i] < dist[i]) ||
                    (dist[v] + Dist[v][i] == dist[i] && cost[v] + Cost[v][i] < cost[i])) {//如果从先到该城市再到另一城市距离小于直接到另一城市
                    //或者从先到该城市再到另一城市距离等于直接到另一城市，且花费少
                    dist[i] = dist[v] + Dist[v][i];//更新最短路径
                    cost[i] = cost[v] + Cost[v][i];
                }
    }
}

int FindMinWay(void) {
    int min = Infinite;
    int temp;

    for (int i = 0; i < N; i++)//循环每个城市 找出最短的路径
        if (!visit[i] && dist[i] < min) {
            min = dist[i];
            temp = i;
        }
    if (min == Infinite) return ERROR;
    return temp;
}


