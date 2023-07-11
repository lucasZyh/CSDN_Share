#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Line 200 //每行最大字符数

typedef struct HTNode {
    int weight;//权值
    int lchild, rchild, parent;//左右孩子及双亲结点在数组中的位置下标
} HTNode, *HTree;//哈夫曼树

typedef char **HuffmanCode;//哈夫曼编码

//各个文件夹的路径
char *SourceFile = "../Source.txt";
char *CountFile = "../Count.txt";
char *HuffmanCodeFile = "../HuffmanCodeFile.txt";
char *ZipFile = "../Zip.txt";
char *UnZipFile = "../Unzip.txt";

int HexDataTimes[256] = {0};//存储16进制数据出现次数


void TransToHex(char ByteData[], int HexData[], int bytenum);//将ByteData中的数据转换成16进制数据存储到HexData中
void AddTimes(int HexDataTimes[], int HexData[]);//将HexData中的数据出现次数存储到HexDataTimes中
void ReadByte_WriteHex();//读取文件，将字节数据转换成16进制数据，存储到HexDataTimes[0~0xFF]中
void SelectMin(HTree HT, const int n, int *min1, int *min2);//选择最小的两个权值
HTree CreateHTree(int *N);//创建哈夫曼树
HuffmanCode HuffmanCoding(HTree HT, int n);//创建哈夫曼编码
HuffmanCode CreateSearchList(HuffmanCode HC);//创建搜索表
void Compress(HuffmanCode SearchList);//压缩文件
void WriteHuffmanCode(HuffmanCode SearchList, char *Str01);//将Str01中的01转换成16进制写入文件
void TransWrite(char *Str01, int _01StrLen);//将Str01中的01转换成16进制写入文件
void _01StrCat(char *Str01, char *OriginCode, int strlen, HuffmanCode SearchList);//将OriginCode中的字符转换成Str01中的01
void Set_bit(char *a, int bit, int _01);//设置bit位为_01
void BitToStr(char a, char *Each_Str);//将a转换成字符串存储到Each_Str中
void TransWrite2(char *Str01, char SearchList[0xFF + 1][200], int bytenum);//将Str01中的01转换成16进制写入文件
void DeCompress();//解压文件
void TransWrite2(char *Str01, char SearchList[0xFF + 1][200], int bytenum);//将Str01中的01转换成16进制写入文件
void BitToStr(char a, char *Each_Str);//将字符a转换成字符串存储到Each_Str中
int Compare(void);//文件内容比较，默认为源文件和解压文件比较
int Check_File(char *filename);//检查文件是否存在

int main() {
    //使用之前务必有一个Source.txt文件，其他文件没有会自动创建

    char f[256];
    char x[256];
    char s[256];
    int length, N;
    int n;
    HTree HT = NULL;
    HuffmanCode HC = NULL;
    HuffmanCode SearchList = NULL;
    //界面设置
    printf("***********欢迎使用哈夫曼编码压缩文件系统***********\n");
    printf("*-------------------请选择功能---------------------*\n");
    printf("* 1.压缩文件                                       *\n");
    printf("* 2.解压文件                                       *\n");
    printf("* 3.文件对比                                       *\n");
    printf("* 0.退出系统                                       *\n");
    printf("****************************************************\n");
    printf("请输入功能编号：");

    while (1) {
        scanf("%d", &n);
        printf("%d\n", n);
        while (1) {
            //选择功能1，压缩文件
            if(n == 1){
                printf("请输入要压缩的文件路径：");
                scanf("%s", f);
                printf("%s\n", f);
                if (Check_File(f)) {
                    //路径正确，文件存在，开始压缩
                    printf("开始压缩\n");
                    //初始化
                    HT = NULL;
                    HC = NULL;
                    SearchList = NULL;
                    SourceFile = f;
                    length=  N = 0;
                    for (int i = 0; i < 256; ++i)
                        HexDataTimes[i] = 0;

                    ReadByte_WriteHex();
                    HT = CreateHTree(&N);//创建哈夫曼树
                    HC = HuffmanCoding(HT, N);//创建哈夫曼编码
                    SearchList = CreateSearchList(HC);
                    Compress(SearchList);//压缩文件
                    DeCompress();//解压文件
                    Compare();//文件内容比较

                    printf("压缩成功,请输入其他命令\n");
                    printf("请输入功能编号：");
                } else {
                    //路径错误，文件不存在，重新输入
                    continue;
                }
            }
            //选择功能2，解压文件
            else if(n == 2){
                printf("请输入要解压的文件路径：");
                scanf("%s", x);
                printf("%s\n", x);

                if (Check_File(x)) {
                    //路径正确，文件存在，开始解压
                    printf("开始解压\n");
                    if (Check_File(HuffmanCodeFile) == 0) {
                        printf("解压失败，缺少对应码表，请进入功能1录入源文件信息\n");
                        printf("请输入功能编号：");
                        break;
                    } else {
                        ZipFile = x;

                        DeCompress();//解压文件
                        Compare();//文件内容比较
                    }
                    printf("解压完成,请输入其他命令\n");
                    printf("请输入功能编号：");
                } else {
                    //路径错误，文件不存在，重新输入
                    continue;
                }
            }
            //选择功能3，文件内容比较
            else if(n == 3)
            {
                printf("请输入要对比的两个文件的路径：\n");
                printf("文件1：");
                scanf("%s", f);
                if (Check_File(f)) {
                    SourceFile = f;
                    printf("\n文件2：");
                    scanf("%s", s);
                    if (Check_File(s)) {
                        UnZipFile = s;
                        Compare();//文件内容比较
                        printf("对比完成,请输入其他命令\n");
                        printf("请输入功能编号：");
                    } else {
                        //路径错误，文件不存在，重新输入
                        printf("\n");
                        continue;
                    }
                } else {
                    //路径错误，文件不存在，重新输入
                    printf("\n");
                    continue;
                }
            }
            //选择功能0，退出系统
            else if (n == 0)
            {
                exit(0);
            }
            //输入错误的功能编号，重新输入
            else{
                printf("输入错误，请重新输入\n");
                printf("请输入功能编号：");
            }
            break;
        }
    }
    return 0;
}

/**
 * @brief 检查文件是否存在
 * @param filename  文件路径
 * @return  0：文件不存在 1：文件存在
 */
int Check_File(char *filename) {
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("文件不存在,请输入正确的文件路径\n");
        return 0;
    } else {
        return 1;
    }
}

/*功能1*/
/**
 * @brief 读取文件，将字节数据转换成16进制数据，存储到HexDataTimes[0~0xFF]中
 */
void ReadByte_WriteHex() {
    int i, bytenum;
    FILE *file1 = fopen(SourceFile, "rb");// 以二进制只读方式打开源文件
    FILE *file2 = fopen(CountFile, "wb");// 以二进制写入方式打开计数文件

    if (file1 != NULL && file2 != NULL) {//确保文件打开成功
        //打开文件
        char ByteData[Line + 1] = {0};//存储原始字节数据
        int HexData[Line + 1] = {0};//以16进制存储字节值的
        for (; feof(file1) == 0;) {
            memset(HexData, -1, sizeof(HexData) / sizeof(int));//每次都重置为-1
            memset(ByteData, 0, sizeof(ByteData) / sizeof(char));//重置数组为0
            bytenum = fread(ByteData, sizeof(char), Line + 1, file1);//返回值为实际读取的字节数
            TransToHex(&ByteData[0], &HexData[0], bytenum);//将ByteData转换成16进制数存储
            AddTimes(&HexDataTimes[0], &HexData[0]);//将16进制字节值的出现次数存储到HexDataTime[0~255]全局变量中
        }
        for (i = 0; i <= 0xFF; ++i) {
            fprintf(file2, "%02X==%010d\n", i, HexDataTimes[i]);//以特定格式将频次数据写入文件
        }
        //关闭文件
        fclose(file1);
        fclose(file2);
    }
}

/**
 * @brief 将ByteData中的数据转换成16进制数据存储到HexData中
 * @param ByteData 存储字节数据
 * @param HexData  存储16进制数据
 * @param bytenum  字节数据的个数
 */
void TransToHex(char ByteData[], int HexData[], int bytenum) {
    for (int i = 0; i < bytenum; ++i) {
        HexData[i] = ByteData[i] & 0b11111111;
    }
}

/**
 * @brief 将HexData中的数据出现次数存储到HexDataTimes中
 * @param hexDataTimes 存储16进制数据出现次数
 * @param HexData    存储16进制数据
 */
void AddTimes(int hexDataTimes[], int HexData[]) {
    for (int i = 0; HexData[i] != -1 && i <= Line; i++)
        HexDataTimes[HexData[i]]++;//相同字符出现次数加1
}

/*功能2*/
/**
 * @brief       创建哈夫曼树
 * @param   N   哈夫曼树的叶子节点个数
 * @return      哈夫曼树
 */
HTree CreateHTree(int *N) {
    int i, n, m;
    int min1, min2;
    HTree HT;
    int weight[0xFF + 1], weight_Hex[0xFF + 1];
    for (i = 0, n = 0; i < 256; i++) {
        if (HexDataTimes[i] != 0) {
            weight[n] = HexDataTimes[i];//把非0权值提取出来
            weight_Hex[n] = i;        //保留对应非0权值的映射值
            ++n;
        }
    }
    *N = n;
    m = 2 * n - 1;//weight[0~n-1]存放了所有非0权值
    HT = (HTree) malloc((m + 1) * sizeof(HTNode));//分配编码空间舍去0单元不用
    for (i = 1; i <= n; i++) {
        HT[i].weight = weight[i];
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for (i = n + 1; i <= m; i++) {
        HT[i].weight = 0;
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for (i = n + 1; i <= m; ++i) {
        SelectMin(HT, i - 1, &min1, &min2);
        HT[min1].parent = i;
        HT[min2].parent = i;
        HT[i].lchild = min1;
        HT[i].rchild = min2;
        HT[i].weight = HT[min1].weight + HT[min2].weight;
    }
    return HT;
}

/**
 * @brief 获取哈夫曼编码
 * @param HT  哈夫曼树
 * @param n   哈夫曼树的叶子节点个数
 * @return    哈夫曼编码
 */
HuffmanCode HCHuffmanCoding(HTree HT, int n) {
    int start, parent, current;
    HuffmanCode HC;
    HC = (HuffmanCode) malloc((n + 1) * sizeof(char *));
    char *Each_Code = (char *) malloc(n * sizeof(char));
    Each_Code[n - 1] = '\0';

    for (int i = 1; i <= n; ++i) {
        start = n - 1;//从start开始时指向最后，即编码结束符位置
        current = i;
        parent = HT[i].parent;
        while (parent != 0) {
            --start;
            if (HT[parent].lchild == current)
                Each_Code[start] = '0';
            else
                Each_Code[start] = '1';
            current = parent;
            parent = HT[parent].parent;
        }
        HC[i] = (char *) malloc((n - start) * sizeof(char));
        strcpy(HC[i], &Each_Code[start]);
    }
    free(Each_Code);
    return HC;
}

/**
 * @brief 选择最小的两个权值
 * @param HT    哈夫曼树
 * @param n     哈夫曼树的叶子节点个数
 * @param min1  最小权值的下标
 * @param min2  次小权值的下标
 */
void SelectMin(HTree HT, const int n, int *min1, int *min2) {
    int i;
    int min_value1 = INT_MAX;//INT_MAX是C语言中定义的最大整数
    int min_value2 = INT_MAX;

    //找出最小权值
    for (i = 1; i <= n; i++) {
        if (HT[i].parent == 0 && HT[i].weight < min_value1) {//HT[i].parent==0是为了防止节点被重复选取
            min_value1 = HT[i].weight;//min_value1是最小权值
            *min1 = i;//min1是最小权值的下标
        }
    }
    //找出次小权值
    for (i = 1; i <= n; i++) {
        if (HT[i].parent == 0 && HT[i].weight < min_value2 && i != (*min1)) {//i!=(*min1)是为了防止min1和min2指向同一个节点
            min_value2 = HT[i].weight;//min_value2是次小权值
            *min2 = i;//min2是次小权值的下标
        }
    }
}

/*功能3 压缩*/

/**
 * @brief 根据编码查询表SearchList[0~0xFF]进行编码
 * @param SearchList  搜索表
 */
void Compress(HuffmanCode SearchList) {
    FILE *pfile = fopen(SourceFile, "rb");
    FILE *pfile1 = fopen(ZipFile, "wb");
    fclose(pfile1);
    char OriginCode[Line + 10] = {0}, Str01[20 * Line] = {0};

    for (; feof(pfile) == 0;) {
        memset(OriginCode, 0, strlen(OriginCode));
        fread(OriginCode, sizeof(char), Line, pfile);
        _01StrCat(&Str01[0], &OriginCode[0], strlen(OriginCode), SearchList);
        TransWrite(&Str01[0], strlen(Str01));//写入BitCode
    }
    fclose(pfile);
    WriteHuffmanCode(SearchList, Str01);
    //将编码查询表写入另一文件,同时将无法凑足8bit位的
    //编码以字符串形式写到该文件末尾
}

/**
 * @brief 创建搜索表
 * @param HC  哈夫曼编码  SearchList中有NULL，而HC只有[0]单元为空
 * @return  搜索表
 */
HuffmanCode CreateSearchList(HuffmanCode HC) {
    int i, j;
    HuffmanCode SearchList;

    SearchList = (HuffmanCode) calloc(0xFF + 1, sizeof(char *));
    for (i = 0; i <= 0xFF; ++i)
        SearchList[i] = NULL;
    for (i = 0, j = 1; i <= 0xFF; ++i) {
        if (HexDataTimes[i] != 0) {
            SearchList[i] = HC[j];
            ++j;
        }
    }
    return SearchList;
}

/**
 * @brief 将读取的字节值对应的哈夫曼编码逐个连接到Str01
 * @param Str01  二进制字符串
 * @param OriginCode  原始数据
 * @param strlen  原始数据长度
 * @param SearchList  搜索表
 */
void _01StrCat(char *Str01, char *OriginCode, int strlen, HuffmanCode SearchList) {
    int i;
    for (i = 0; i < strlen; ++i) {
        strcat(Str01, SearchList[OriginCode[i] & 0b11111111]);//将读取的字节值对应的哈夫曼编码逐个连接到_01Str
    }
}

/*按位运算设定bit位，稍大数值用强制类型转换(char)，否则部分编译器报错数值溢出*/
/**
 * @brief 设置bit位
 * @param a    字符串
 * @param bit  bit位
 * @param _01  0或1
 */
void Set_bit(char *a, int bit, int _01) {
    char bit_to_1[9] = {0, 0b1, 0b10, 0b100, 0b1000, 0b10000,
                        0b100000, 0b1000000, (char) 0b10000000};
    char bit_to_0[9] = {0, (char) 0b11111110, (char) 0b11111101, (char) 0b11111011, (char) 0b11110111,
                        (char) 0b11101111, (char) 0b11011111, (char) 0b10111111, (char) 0b01111111};
    if (_01 == 0) {
        *a &= bit_to_0[bit]; //表示要将bit位变为0，也即是将第bit位&0，其他位&1即可
    } else if (_01 == 1) {
        *a |= bit_to_1[bit];//表示要将bit位变为1，也即时将第bit位|1，其他位|0即可
    }
}

/**
 * @brief 将Str01(0101010000111……)字符数字数值存储到BitCode[]元素的bit位中
 * @param Str01      二进制字符串
 * @param _01StrLen  二进制字符串长度
 */
void TransWrite(char *Str01, int _01StrLen) {
    int i, last, bytenum;
    char BitCode[_01StrLen / 8 + 10];
    char temp[10];
    last = _01StrLen % 8;//将不足八位的截断
    _01StrLen -= last;
    for (i = 7, bytenum = 0; i < _01StrLen; i += 8) {
        Set_bit(&BitCode[bytenum], 1, Str01[i] - 48);
        Set_bit(&BitCode[bytenum], 2, Str01[i - 1] - 48);
        Set_bit(&BitCode[bytenum], 3, Str01[i - 2] - 48);
        Set_bit(&BitCode[bytenum], 4, Str01[i - 3] - 48);
        Set_bit(&BitCode[bytenum], 5, Str01[i - 4] - 48);
        Set_bit(&BitCode[bytenum], 6, Str01[i - 5] - 48);
        Set_bit(&BitCode[bytenum], 7, Str01[i - 6] - 48);
        Set_bit(&BitCode[bytenum], 8, Str01[i - 7] - 48);
        bytenum++;
    }
    BitCode[bytenum] = '\0';
    strcpy(temp, &Str01[_01StrLen]);
    strcpy(Str01, temp);//将截断未被写入的子字符串恢复到_01Str开头

    FILE *pfile = fopen(ZipFile, "ab");
    if (pfile != NULL) {
        fwrite(BitCode, sizeof(char), bytenum, pfile);
        fclose(pfile);
    } else {
        printf("文件打开失败！\n");
        fclose(pfile);
    }

}

/**
 * @brief 将哈夫曼编码表写到文件fHuffmanCode，格式为每行一个编码
 * @param SearchList  搜索表
 * @param Str01     二进制字符串
 */
void WriteHuffmanCode(HuffmanCode SearchList, char *Str01) {
    int i;
    FILE *pfile = fopen(HuffmanCodeFile, "wb");
    if (pfile != NULL) {
        for (i = 0; i <= 0xFF; ++i)
            fprintf(pfile, "%s\n", SearchList[i]);
        fprintf(pfile, "%s", Str01);//不足8bit位的，写到文件尾部
        fclose(pfile);
    } else {
        printf("文件打开失败！\n");
    }

}

/*功能四 解压*/
/**
 * @brief 解压文件
 */
void DeCompress() {
    int i;
    char surplus[12] = {0};//读取编码查询表文件末尾的不足8位字符串
    char SearchList[0xFF + 1][200];//这里以数组形式使用编码表
    FILE *pfile = fopen(HuffmanCodeFile, "rb");
    FILE *pfile1 = fopen(UnZipFile, "wb");//清空
    fclose(pfile1);
    if (pfile != NULL) {
        for (i = 0; i <= 0xFF; ++i) {
            fscanf(pfile, "%s", SearchList[i]);//读取编码查询表
        }
        fgets(surplus, 10, pfile);//最后一行就是不足8位的字符串，读取它
        fclose(pfile);
    }
    //编码查询表写入时有的为(null)，将其截断
    for (i = 0; i <= 0xFF; ++i)
        if (strcmp(SearchList[i], "(null)") == 0)
            SearchList[i][0] = '\0';

    pfile = fopen(ZipFile, "rb");
    char BitCode[Line + 10], Str01[8 * Line + 10] = {0}, EachStr[50];
    int bytenum;

    for (; feof(pfile) == 0;) {
        memset(BitCode, 0, strlen(BitCode));
        bytenum = fread(BitCode, sizeof(char), Line, pfile);
        //返回值为读取了的字节数
        for (i = 0; i < bytenum; ++i) {
            //BitCode转为字符串
            BitToStr(BitCode[i], EachStr);
            //将每个逆转得到的字符串连接到_01Str
            strcat(Str01, EachStr);
        }
        //将_01Str写入到解压文件
        TransWrite2(Str01, SearchList, bytenum);
    }
    fclose(pfile);
    //下面的代码作用：将不足8位的编码字符串连接到_01Str中，
    //按理将正好凑足8位。并将该(也是最后一个)字节写入解压文件
    strcat(Str01, surplus);

    pfile = fopen(UnZipFile, "ab");
    for (i = 0; i <= 0xFF; ++i) {
        if (SearchList[i][0] != '\0')
            if (strcmp(Str01, SearchList[i]) == 0) {
                char OneCode = i;
                printf("%c", OneCode);
                fwrite(&OneCode, sizeof(char), 1, pfile);
                break;
            }
    }
    fwrite("\n", sizeof(char), 1, pfile);
    fclose(pfile);
}

/**
 * 将_01Str中的01转换成16进制写入文件
 * @param a  Str01 01字符串
 * @param Each_Str  OriginCode 字符串
 */
void BitToStr(char a, char *Each_Str) {
    int bit[8] = {0b00000001, 0b00000010, 0b00000100,
                  0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000};
    Each_Str[0] = ((a & bit[7]) >> 7) + 48;
    Each_Str[1] = ((a & bit[6]) >> 6) + 48;
    Each_Str[2] = ((a & bit[5]) >> 5) + 48;
    Each_Str[3] = ((a & bit[4]) >> 4) + 48;
    Each_Str[4] = ((a & bit[3]) >> 3) + 48;
    Each_Str[5] = ((a & bit[2]) >> 2) + 48;
    Each_Str[6] = ((a & bit[1]) >> 1) + 48;
    Each_Str[7] = ((a & bit[0]) >> 0) + 48;
    Each_Str[8] = '\0';
}

/**
 * 将Str01中的01转换成16进制写入文件
 * @param Str01  Str01 01字符串
 * @param SearchList  OriginCode 字符串
 * @param bytenum  OriginCode 字符串长度
 */
void TransWrite2(char *Str01, char SearchList[0xFF + 1][200], int bytenum) {
    FILE *pfile = fopen(UnZipFile, "ab");

    int i = 0, times = 0, j, Bitnum = bytenum * 8, len = 0;
    char *p = NULL;
    //char temp[100];
    char OneCode;

    //循环遍历_01Str
    while (i <= Bitnum) {
        for (j = 0; j <= 0xFF; ++j)//遍历编码查询表
        {
            //如果编码串不为空
            if (SearchList[j][0] != '\0')
                //比较 编码串长度个字符
                if (strncmp(&Str01[i], SearchList[j], strlen(SearchList[j])) == 0) {        //如果_01Str[i]开始匹配成功，
                    len += strlen(SearchList[j]);//统计总共写入了的_01Str中的字符数
                    OneCode = j;//j的值即为该编码串对应的原字节值
                    //把字节值写入解压文件，完成一个字节的解压
                    printf("%c", OneCode);
                    fwrite(&OneCode, sizeof(char), 1, pfile);

                    times++;
                    i += strlen(SearchList[j]);
                    //执行到这里说明已经解压了编码串长度个字符，i要随之变动
                    break;
                }
        }
        if (j == 0xFF + 1)//说明遍历了编码查询表也没有匹配成功，继续从下一个字符匹配
            ++i;//所以加1
    }
    strcpy(Str01, &Str01[len]);//将未解压的子字符串安排到开头，下一次继续
    fclose(pfile);
}

/**
 * 文件内容比较，默认为源文件和解压文件比较
 * @return  1：两个文件完全相同 0：两个文件不相同
 */
int Compare(void) {
    FILE *fp, *fp1;
    int array1 = 1, row1 = 1, array2 = 1, row2 = 1;
    char ch1, ch2;
    //test与test1都是与当前程序在同一目录下的文件
    fp = fopen(SourceFile, "r");
    fp1 = fopen(UnZipFile, "r");
    while (!feof(fp) || !feof(fp1)) {
        ch1 = fgetc(fp);
        ch2 = fgetc(fp1);
        if (ch1 == '\n') {
            row1++;
            array1 = 1;
        }
        if (ch2 == '\n') {
            row2++;
            array2 = 1;
        }
        if (ch1 != ch2) {
            if (ch1 == EOF || ch2 == EOF) break;
            printf("第一次不相同的位置：\n");
            printf("test\t行号：%d 列号：%d\n", row1, array1);
            printf("test1\t行号：%d 列号：%d\n", row2, array2);
            printf("-----两个文件不相同！-----\n");
            break;
        } else {
            array1++;
            array2++;
        }
    }
    if (ch1 == EOF && ch2 != EOF) {
        printf("\n-----源文件文件内容被包含在解压文件中-----\n");
        fclose(fp);
        fclose(fp1);
        return 0;
    }

    if (ch2 == EOF && ch1 != EOF) {
        printf("\n-----解压文件内容被包含在源文件中-----\n");
        fclose(fp);
        fclose(fp1);
        return 0;
    }

    if (ch1 == EOF && ch2 == EOF) {
        printf("\n-----两个文件完全相同！-----\n");
        fclose(fp);
        fclose(fp1);
        return 1;
    }
    return 0;
}
