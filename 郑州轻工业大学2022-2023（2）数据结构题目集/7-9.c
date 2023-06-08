/**
 * 7-9 哈利·波特的考试
 *  最短路径     迪杰斯特拉算法
 */

#include<stdio.h>
#include<string.h>

#define maxInt 2147483647

typedef struct {
    int arcs[102][102];
    int vexnum, arcnum;
} MGraph;

int final[102];//final[w]=1表示求得顶点v0至vw的最短路径
int D[102];  //记录v0到vi的当前最短路径长度
int P[102]; //记录v0到vi的当前最短路径vi的前驱

int i, u, j, m, v, min, w, k, a, b, c, min1 = 999999, max = -991111, p = 0;

void Dijkstra(MGraph G, int v0) {
    for (v = 0; v < G.vexnum; v++)    //初始化数据
    {
        final[v] = 0;            //全部顶点初始化为未知最短路径状态
        D[v] = G.arcs[v0][v];// 将与v0点有连线的顶点加上权值
        P[v] = -1;                //初始化路径数组P为-1
    }

    D[v0] = 0;  //v0至v0路径为0
    final[v0] = 1;    // v0至v0不需要求路径
    // 开始主循环，每次求得v0到某个v顶点的最短路径
    for (v = 1; v < G.vexnum; v++) {
        min = maxInt;    // 当前所知离v0顶点的最近距离
        for (w = 0; w < G.vexnum; w++) // 寻找离v0最近的顶点
        {
            if (!final[w] && D[w] < min) {
                k = w;
                min = D[w];    // w顶点离v0顶点更近
            }
        }
        final[k] = 1;    // 将目前找到的最近的顶点置为1
        for (w = 0; w < G.vexnum; w++) // 修正当前最短路径及距离
        {
            // 如果经过v顶点的路径比现在这条路径的长度短的话
            if (!final[w] && (min + G.arcs[k][w] < D[w])) { // 说明找到了更短的路径，修改D[w]和P[w]
                D[w] = min + G.arcs[k][w];  // 修改当前路径长度
                P[w] = k;
            }
        }
    }
}

int main9() {
    MGraph G;
    memset(final, 0, sizeof(final));
    memset(D, 0x3f3f3f3f, sizeof(D));
    memset(G.arcs, 0x3f3f3f3f, sizeof(G.arcs));   //邻接矩阵一定要初始化
    scanf("%d %d", &G.vexnum, &m);
    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        G.arcs[a - 1][b - 1] = c;
        G.arcs[b - 1][a - 1] = c;
    }
    for (u = 0; u < G.vexnum; u++) {
        max = -9999999;
        Dijkstra(G, u);
        for (j = 0; j < G.vexnum; j++) {
            if (D[j] > max)
                max = D[j];
        }
        if (max < min1) {
            min1 = max;
            p = u + 1;
        }

    }
    if (p == 0)
        printf("0");
    else
        printf("%d %d\n", p, min1);
    return 0;
}

