/**
 * 6-13 邻接矩阵存储图的深度优先遍历
 */
/*
void DFS(MGraph Graph, Vertex V, void (*Visit)(Vertex)) {
    Vertex i = 0;
    Visit(V);
    Visited[V] = true;
    for (int i = 0; i < Graph->Nv; i++) {
        if (Graph->G[V][i] == 1 && !Visited[i]) {
            DFS(Graph, i, Visit);//进行递归
        }
    }
}
*/
/**
 * 6-14 邻接表存储图的广度优先遍历
 */
/*void BFS(LGraph Graph, Vertex S, void (*Visit)(Vertex)) {
    Visited[S] = true;//标记起始点
    Visit(S);
    int queue[1000], front = 0, rear = 0;
    queue[rear++] = S;//起始点入队列
    PtrToAdjVNode temp;//temp就代表当前点的邻接点的下标
    while (front < rear) {//队伍不为空
        temp = Graph->G[queue[front++]].FirstEdge;
        while (temp) {
            int p = temp->AdjV;//把temp中的下标提取出来
            if (!Visited[p]) {//如果p点没有被标记的话
                Visited[p] = true;
                Visit(p);
                queue[rear++] = p;//储存在队列中
            }
            temp = temp->Next;//指向下一个邻接点
        }
    }
}*/