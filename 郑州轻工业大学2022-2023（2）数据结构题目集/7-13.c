/**
 * 7-13 寻找大富翁
 *  堆排序和选择排序
 */

#include <stdio.h>   //堆排序；  注意:此算法中，下标从1开始

#define max 1000010
int num[max];

void sift(int *num, int low, int high)  //将下标为low位置上的点调到适当位置
{
    int i, j, temp;
    i = low;
    j = 2 * i;   //num[j]是num[i]的左孩子结点；
    temp = num[i];  //待调整的结点
    while (j <= high) {
        if (j < high && num[j] < num[j + 1])   //如果右孩子比较大，则把j指向右孩子，j变为2*i+1；
            ++j;
        if (temp < num[j]) {
            num[i] = num[j];    //将num[j]调整到双亲结点的位置上；
            i = j;   //修改i和j的值，以便继续向下调整；
            j = i * 2;
        } else break;     //调整结束；
    }
    num[i] = temp;   //被调整的结点放入最终位置
}

int main13() {
    int n, m, i, temp, count = 0;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%d", &num[i]);
    if (n < m) m = n;   //注意，有一个测试点是n小于m的情况，这时，只用排前n个;
    for (i = n / 2; i >= 1; i--)  //所有结点建立初始堆
        sift(num, i, n);
    for (i = n; i >= 2; i--)   //进行n-1次循环，完成堆排序
    {
        /*以下3句换出了根节点中的关键字，将其放入最终位置*/
        temp = num[1];
        num[1] = num[i];
        num[i] = temp;
        count++;
        if (count == 1)
            printf("%d", num[i]);
        else
            printf(" %d", num[i]);
        if (count == m) break;  //打印前m个；
        sift(num, 1, i - 1);    //减少了1个关键字的无序序列，继续调整。
    }
    if (m == n) printf(" %d", num[1]);  //当n<m的特殊情况下，上面只打印了n~2，还有最后一个下标为1的没有打印，故再打印一个。
    return 0;
}