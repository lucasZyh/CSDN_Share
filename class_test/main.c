#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Line 200 //ÿ������ַ���

typedef struct HTNode {
    int weight;//Ȩֵ
    int lchild, rchild, parent;//���Һ��Ӽ�˫�׽���������е�λ���±�
} HTNode, *HTree;//��������

typedef char **HuffmanCode;//����������

//�����ļ��е�·��
char *SourceFile = "../Source.txt";
char *CountFile = "../Count.txt";
char *HuffmanCodeFile = "../HuffmanCodeFile.txt";
char *ZipFile = "../Zip.txt";
char *UnZipFile = "../Unzip.txt";

int HexDataTimes[256] = {0};//�洢16�������ݳ��ִ���


void TransToHex(char ByteData[], int HexData[], int bytenum);//��ByteData�е�����ת����16�������ݴ洢��HexData��
void AddTimes(int HexDataTimes[], int HexData[]);//��HexData�е����ݳ��ִ����洢��HexDataTimes��
void ReadByte_WriteHex();//��ȡ�ļ������ֽ�����ת����16�������ݣ��洢��HexDataTimes[0~0xFF]��
void SelectMin(HTree HT, const int n, int *min1, int *min2);//ѡ����С������Ȩֵ
HTree CreateHTree(int *N);//������������
HuffmanCode HuffmanCoding(HTree HT, int n);//��������������
HuffmanCode CreateSearchList(HuffmanCode HC);//����������
void Compress(HuffmanCode SearchList);//ѹ���ļ�
void WriteHuffmanCode(HuffmanCode SearchList, char *Str01);//��Str01�е�01ת����16����д���ļ�
void TransWrite(char *Str01, int _01StrLen);//��Str01�е�01ת����16����д���ļ�
void _01StrCat(char *Str01, char *OriginCode, int strlen, HuffmanCode SearchList);//��OriginCode�е��ַ�ת����Str01�е�01
void Set_bit(char *a, int bit, int _01);//����bitλΪ_01
void BitToStr(char a, char *Each_Str);//��aת�����ַ����洢��Each_Str��
void TransWrite2(char *Str01, char SearchList[0xFF + 1][200], int bytenum);//��Str01�е�01ת����16����д���ļ�
void DeCompress();//��ѹ�ļ�
void TransWrite2(char *Str01, char SearchList[0xFF + 1][200], int bytenum);//��Str01�е�01ת����16����д���ļ�
void BitToStr(char a, char *Each_Str);//���ַ�aת�����ַ����洢��Each_Str��
int Compare(void);//�ļ����ݱȽϣ�Ĭ��ΪԴ�ļ��ͽ�ѹ�ļ��Ƚ�
int Check_File(char *filename);//����ļ��Ƿ����

int main() {
    //ʹ��֮ǰ�����һ��Source.txt�ļ��������ļ�û�л��Զ�����

    char f[256];
    char x[256];
    char s[256];
    int length, N;
    int n;
    HTree HT = NULL;
    HuffmanCode HC = NULL;
    HuffmanCode SearchList = NULL;
    //��������
    printf("***********��ӭʹ�ù���������ѹ���ļ�ϵͳ***********\n");
    printf("*-------------------��ѡ����---------------------*\n");
    printf("* 1.ѹ���ļ�                                       *\n");
    printf("* 2.��ѹ�ļ�                                       *\n");
    printf("* 3.�ļ��Ա�                                       *\n");
    printf("* 0.�˳�ϵͳ                                       *\n");
    printf("****************************************************\n");
    printf("�����빦�ܱ�ţ�");

    while (1) {
        scanf("%d", &n);
        printf("%d\n", n);
        while (1) {
            //ѡ����1��ѹ���ļ�
            if(n == 1){
                printf("������Ҫѹ�����ļ�·����");
                scanf("%s", f);
                printf("%s\n", f);
                if (Check_File(f)) {
                    //·����ȷ���ļ����ڣ���ʼѹ��
                    printf("��ʼѹ��\n");
                    //��ʼ��
                    HT = NULL;
                    HC = NULL;
                    SearchList = NULL;
                    SourceFile = f;
                    length=  N = 0;
                    for (int i = 0; i < 256; ++i)
                        HexDataTimes[i] = 0;

                    ReadByte_WriteHex();
                    HT = CreateHTree(&N);//������������
                    HC = HuffmanCoding(HT, N);//��������������
                    SearchList = CreateSearchList(HC);
                    Compress(SearchList);//ѹ���ļ�
                    DeCompress();//��ѹ�ļ�
                    Compare();//�ļ����ݱȽ�

                    printf("ѹ���ɹ�,��������������\n");
                    printf("�����빦�ܱ�ţ�");
                } else {
                    //·�������ļ������ڣ���������
                    continue;
                }
            }
            //ѡ����2����ѹ�ļ�
            else if(n == 2){
                printf("������Ҫ��ѹ���ļ�·����");
                scanf("%s", x);
                printf("%s\n", x);

                if (Check_File(x)) {
                    //·����ȷ���ļ����ڣ���ʼ��ѹ
                    printf("��ʼ��ѹ\n");
                    if (Check_File(HuffmanCodeFile) == 0) {
                        printf("��ѹʧ�ܣ�ȱ�ٶ�Ӧ�������빦��1¼��Դ�ļ���Ϣ\n");
                        printf("�����빦�ܱ�ţ�");
                        break;
                    } else {
                        ZipFile = x;

                        DeCompress();//��ѹ�ļ�
                        Compare();//�ļ����ݱȽ�
                    }
                    printf("��ѹ���,��������������\n");
                    printf("�����빦�ܱ�ţ�");
                } else {
                    //·�������ļ������ڣ���������
                    continue;
                }
            }
            //ѡ����3���ļ����ݱȽ�
            else if(n == 3)
            {
                printf("������Ҫ�Աȵ������ļ���·����\n");
                printf("�ļ�1��");
                scanf("%s", f);
                if (Check_File(f)) {
                    SourceFile = f;
                    printf("\n�ļ�2��");
                    scanf("%s", s);
                    if (Check_File(s)) {
                        UnZipFile = s;
                        Compare();//�ļ����ݱȽ�
                        printf("�Ա����,��������������\n");
                        printf("�����빦�ܱ�ţ�");
                    } else {
                        //·�������ļ������ڣ���������
                        printf("\n");
                        continue;
                    }
                } else {
                    //·�������ļ������ڣ���������
                    printf("\n");
                    continue;
                }
            }
            //ѡ����0���˳�ϵͳ
            else if (n == 0)
            {
                exit(0);
            }
            //�������Ĺ��ܱ�ţ���������
            else{
                printf("�����������������\n");
                printf("�����빦�ܱ�ţ�");
            }
            break;
        }
    }
    return 0;
}

/**
 * @brief ����ļ��Ƿ����
 * @param filename  �ļ�·��
 * @return  0���ļ������� 1���ļ�����
 */
int Check_File(char *filename) {
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("�ļ�������,��������ȷ���ļ�·��\n");
        return 0;
    } else {
        return 1;
    }
}

/*����1*/
/**
 * @brief ��ȡ�ļ������ֽ�����ת����16�������ݣ��洢��HexDataTimes[0~0xFF]��
 */
void ReadByte_WriteHex() {
    int i, bytenum;
    FILE *file1 = fopen(SourceFile, "rb");// �Զ�����ֻ����ʽ��Դ�ļ�
    FILE *file2 = fopen(CountFile, "wb");// �Զ�����д�뷽ʽ�򿪼����ļ�

    if (file1 != NULL && file2 != NULL) {//ȷ���ļ��򿪳ɹ�
        //���ļ�
        char ByteData[Line + 1] = {0};//�洢ԭʼ�ֽ�����
        int HexData[Line + 1] = {0};//��16���ƴ洢�ֽ�ֵ��
        for (; feof(file1) == 0;) {
            memset(HexData, -1, sizeof(HexData) / sizeof(int));//ÿ�ζ�����Ϊ-1
            memset(ByteData, 0, sizeof(ByteData) / sizeof(char));//��������Ϊ0
            bytenum = fread(ByteData, sizeof(char), Line + 1, file1);//����ֵΪʵ�ʶ�ȡ���ֽ���
            TransToHex(&ByteData[0], &HexData[0], bytenum);//��ByteDataת����16�������洢
            AddTimes(&HexDataTimes[0], &HexData[0]);//��16�����ֽ�ֵ�ĳ��ִ����洢��HexDataTime[0~255]ȫ�ֱ�����
        }
        for (i = 0; i <= 0xFF; ++i) {
            fprintf(file2, "%02X==%010d\n", i, HexDataTimes[i]);//���ض���ʽ��Ƶ������д���ļ�
        }
        //�ر��ļ�
        fclose(file1);
        fclose(file2);
    }
}

/**
 * @brief ��ByteData�е�����ת����16�������ݴ洢��HexData��
 * @param ByteData �洢�ֽ�����
 * @param HexData  �洢16��������
 * @param bytenum  �ֽ����ݵĸ���
 */
void TransToHex(char ByteData[], int HexData[], int bytenum) {
    for (int i = 0; i < bytenum; ++i) {
        HexData[i] = ByteData[i] & 0b11111111;
    }
}

/**
 * @brief ��HexData�е����ݳ��ִ����洢��HexDataTimes��
 * @param hexDataTimes �洢16�������ݳ��ִ���
 * @param HexData    �洢16��������
 */
void AddTimes(int hexDataTimes[], int HexData[]) {
    for (int i = 0; HexData[i] != -1 && i <= Line; i++)
        HexDataTimes[HexData[i]]++;//��ͬ�ַ����ִ�����1
}

/*����2*/
/**
 * @brief       ������������
 * @param   N   ����������Ҷ�ӽڵ����
 * @return      ��������
 */
HTree CreateHTree(int *N) {
    int i, n, m;
    int min1, min2;
    HTree HT;
    int weight[0xFF + 1], weight_Hex[0xFF + 1];
    for (i = 0, n = 0; i < 256; i++) {
        if (HexDataTimes[i] != 0) {
            weight[n] = HexDataTimes[i];//�ѷ�0Ȩֵ��ȡ����
            weight_Hex[n] = i;        //������Ӧ��0Ȩֵ��ӳ��ֵ
            ++n;
        }
    }
    *N = n;
    m = 2 * n - 1;//weight[0~n-1]��������з�0Ȩֵ
    HT = (HTree) malloc((m + 1) * sizeof(HTNode));//�������ռ���ȥ0��Ԫ����
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
 * @brief ��ȡ����������
 * @param HT  ��������
 * @param n   ����������Ҷ�ӽڵ����
 * @return    ����������
 */
HuffmanCode HCHuffmanCoding(HTree HT, int n) {
    int start, parent, current;
    HuffmanCode HC;
    HC = (HuffmanCode) malloc((n + 1) * sizeof(char *));
    char *Each_Code = (char *) malloc(n * sizeof(char));
    Each_Code[n - 1] = '\0';

    for (int i = 1; i <= n; ++i) {
        start = n - 1;//��start��ʼʱָ����󣬼����������λ��
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
 * @brief ѡ����С������Ȩֵ
 * @param HT    ��������
 * @param n     ����������Ҷ�ӽڵ����
 * @param min1  ��СȨֵ���±�
 * @param min2  ��СȨֵ���±�
 */
void SelectMin(HTree HT, const int n, int *min1, int *min2) {
    int i;
    int min_value1 = INT_MAX;//INT_MAX��C�����ж�����������
    int min_value2 = INT_MAX;

    //�ҳ���СȨֵ
    for (i = 1; i <= n; i++) {
        if (HT[i].parent == 0 && HT[i].weight < min_value1) {//HT[i].parent==0��Ϊ�˷�ֹ�ڵ㱻�ظ�ѡȡ
            min_value1 = HT[i].weight;//min_value1����СȨֵ
            *min1 = i;//min1����СȨֵ���±�
        }
    }
    //�ҳ���СȨֵ
    for (i = 1; i <= n; i++) {
        if (HT[i].parent == 0 && HT[i].weight < min_value2 && i != (*min1)) {//i!=(*min1)��Ϊ�˷�ֹmin1��min2ָ��ͬһ���ڵ�
            min_value2 = HT[i].weight;//min_value2�Ǵ�СȨֵ
            *min2 = i;//min2�Ǵ�СȨֵ���±�
        }
    }
}

/*����3 ѹ��*/

/**
 * @brief ���ݱ����ѯ��SearchList[0~0xFF]���б���
 * @param SearchList  ������
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
        TransWrite(&Str01[0], strlen(Str01));//д��BitCode
    }
    fclose(pfile);
    WriteHuffmanCode(SearchList, Str01);
    //�������ѯ��д����һ�ļ�,ͬʱ���޷�����8bitλ��
    //�������ַ�����ʽд�����ļ�ĩβ
}

/**
 * @brief ����������
 * @param HC  ����������  SearchList����NULL����HCֻ��[0]��ԪΪ��
 * @return  ������
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
 * @brief ����ȡ���ֽ�ֵ��Ӧ�Ĺ���������������ӵ�Str01
 * @param Str01  �������ַ���
 * @param OriginCode  ԭʼ����
 * @param strlen  ԭʼ���ݳ���
 * @param SearchList  ������
 */
void _01StrCat(char *Str01, char *OriginCode, int strlen, HuffmanCode SearchList) {
    int i;
    for (i = 0; i < strlen; ++i) {
        strcat(Str01, SearchList[OriginCode[i] & 0b11111111]);//����ȡ���ֽ�ֵ��Ӧ�Ĺ���������������ӵ�_01Str
    }
}

/*��λ�����趨bitλ���Դ���ֵ��ǿ������ת��(char)�����򲿷ֱ�����������ֵ���*/
/**
 * @brief ����bitλ
 * @param a    �ַ���
 * @param bit  bitλ
 * @param _01  0��1
 */
void Set_bit(char *a, int bit, int _01) {
    char bit_to_1[9] = {0, 0b1, 0b10, 0b100, 0b1000, 0b10000,
                        0b100000, 0b1000000, (char) 0b10000000};
    char bit_to_0[9] = {0, (char) 0b11111110, (char) 0b11111101, (char) 0b11111011, (char) 0b11110111,
                        (char) 0b11101111, (char) 0b11011111, (char) 0b10111111, (char) 0b01111111};
    if (_01 == 0) {
        *a &= bit_to_0[bit]; //��ʾҪ��bitλ��Ϊ0��Ҳ���ǽ���bitλ&0������λ&1����
    } else if (_01 == 1) {
        *a |= bit_to_1[bit];//��ʾҪ��bitλ��Ϊ1��Ҳ��ʱ����bitλ|1������λ|0����
    }
}

/**
 * @brief ��Str01(0101010000111����)�ַ�������ֵ�洢��BitCode[]Ԫ�ص�bitλ��
 * @param Str01      �������ַ���
 * @param _01StrLen  �������ַ�������
 */
void TransWrite(char *Str01, int _01StrLen) {
    int i, last, bytenum;
    char BitCode[_01StrLen / 8 + 10];
    char temp[10];
    last = _01StrLen % 8;//�������λ�Ľض�
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
    strcpy(Str01, temp);//���ض�δ��д������ַ����ָ���_01Str��ͷ

    FILE *pfile = fopen(ZipFile, "ab");
    if (pfile != NULL) {
        fwrite(BitCode, sizeof(char), bytenum, pfile);
        fclose(pfile);
    } else {
        printf("�ļ���ʧ�ܣ�\n");
        fclose(pfile);
    }

}

/**
 * @brief �������������д���ļ�fHuffmanCode����ʽΪÿ��һ������
 * @param SearchList  ������
 * @param Str01     �������ַ���
 */
void WriteHuffmanCode(HuffmanCode SearchList, char *Str01) {
    int i;
    FILE *pfile = fopen(HuffmanCodeFile, "wb");
    if (pfile != NULL) {
        for (i = 0; i <= 0xFF; ++i)
            fprintf(pfile, "%s\n", SearchList[i]);
        fprintf(pfile, "%s", Str01);//����8bitλ�ģ�д���ļ�β��
        fclose(pfile);
    } else {
        printf("�ļ���ʧ�ܣ�\n");
    }

}

/*������ ��ѹ*/
/**
 * @brief ��ѹ�ļ�
 */
void DeCompress() {
    int i;
    char surplus[12] = {0};//��ȡ�����ѯ���ļ�ĩβ�Ĳ���8λ�ַ���
    char SearchList[0xFF + 1][200];//������������ʽʹ�ñ����
    FILE *pfile = fopen(HuffmanCodeFile, "rb");
    FILE *pfile1 = fopen(UnZipFile, "wb");//���
    fclose(pfile1);
    if (pfile != NULL) {
        for (i = 0; i <= 0xFF; ++i) {
            fscanf(pfile, "%s", SearchList[i]);//��ȡ�����ѯ��
        }
        fgets(surplus, 10, pfile);//���һ�о��ǲ���8λ���ַ�������ȡ��
        fclose(pfile);
    }
    //�����ѯ��д��ʱ�е�Ϊ(null)������ض�
    for (i = 0; i <= 0xFF; ++i)
        if (strcmp(SearchList[i], "(null)") == 0)
            SearchList[i][0] = '\0';

    pfile = fopen(ZipFile, "rb");
    char BitCode[Line + 10], Str01[8 * Line + 10] = {0}, EachStr[50];
    int bytenum;

    for (; feof(pfile) == 0;) {
        memset(BitCode, 0, strlen(BitCode));
        bytenum = fread(BitCode, sizeof(char), Line, pfile);
        //����ֵΪ��ȡ�˵��ֽ���
        for (i = 0; i < bytenum; ++i) {
            //BitCodeתΪ�ַ���
            BitToStr(BitCode[i], EachStr);
            //��ÿ����ת�õ����ַ������ӵ�_01Str
            strcat(Str01, EachStr);
        }
        //��_01Strд�뵽��ѹ�ļ�
        TransWrite2(Str01, SearchList, bytenum);
    }
    fclose(pfile);
    //����Ĵ������ã�������8λ�ı����ַ������ӵ�_01Str�У�
    //�������ô���8λ��������(Ҳ�����һ��)�ֽ�д���ѹ�ļ�
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
 * ��_01Str�е�01ת����16����д���ļ�
 * @param a  Str01 01�ַ���
 * @param Each_Str  OriginCode �ַ���
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
 * ��Str01�е�01ת����16����д���ļ�
 * @param Str01  Str01 01�ַ���
 * @param SearchList  OriginCode �ַ���
 * @param bytenum  OriginCode �ַ�������
 */
void TransWrite2(char *Str01, char SearchList[0xFF + 1][200], int bytenum) {
    FILE *pfile = fopen(UnZipFile, "ab");

    int i = 0, times = 0, j, Bitnum = bytenum * 8, len = 0;
    char *p = NULL;
    //char temp[100];
    char OneCode;

    //ѭ������_01Str
    while (i <= Bitnum) {
        for (j = 0; j <= 0xFF; ++j)//���������ѯ��
        {
            //������봮��Ϊ��
            if (SearchList[j][0] != '\0')
                //�Ƚ� ���봮���ȸ��ַ�
                if (strncmp(&Str01[i], SearchList[j], strlen(SearchList[j])) == 0) {        //���_01Str[i]��ʼƥ��ɹ���
                    len += strlen(SearchList[j]);//ͳ���ܹ�д���˵�_01Str�е��ַ���
                    OneCode = j;//j��ֵ��Ϊ�ñ��봮��Ӧ��ԭ�ֽ�ֵ
                    //���ֽ�ֵд���ѹ�ļ������һ���ֽڵĽ�ѹ
                    printf("%c", OneCode);
                    fwrite(&OneCode, sizeof(char), 1, pfile);

                    times++;
                    i += strlen(SearchList[j]);
                    //ִ�е�����˵���Ѿ���ѹ�˱��봮���ȸ��ַ���iҪ��֮�䶯
                    break;
                }
        }
        if (j == 0xFF + 1)//˵�������˱����ѯ��Ҳû��ƥ��ɹ�����������һ���ַ�ƥ��
            ++i;//���Լ�1
    }
    strcpy(Str01, &Str01[len]);//��δ��ѹ�����ַ������ŵ���ͷ����һ�μ���
    fclose(pfile);
}

/**
 * �ļ����ݱȽϣ�Ĭ��ΪԴ�ļ��ͽ�ѹ�ļ��Ƚ�
 * @return  1�������ļ���ȫ��ͬ 0�������ļ�����ͬ
 */
int Compare(void) {
    FILE *fp, *fp1;
    int array1 = 1, row1 = 1, array2 = 1, row2 = 1;
    char ch1, ch2;
    //test��test1�����뵱ǰ������ͬһĿ¼�µ��ļ�
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
            printf("��һ�β���ͬ��λ�ã�\n");
            printf("test\t�кţ�%d �кţ�%d\n", row1, array1);
            printf("test1\t�кţ�%d �кţ�%d\n", row2, array2);
            printf("-----�����ļ�����ͬ��-----\n");
            break;
        } else {
            array1++;
            array2++;
        }
    }
    if (ch1 == EOF && ch2 != EOF) {
        printf("\n-----Դ�ļ��ļ����ݱ������ڽ�ѹ�ļ���-----\n");
        fclose(fp);
        fclose(fp1);
        return 0;
    }

    if (ch2 == EOF && ch1 != EOF) {
        printf("\n-----��ѹ�ļ����ݱ�������Դ�ļ���-----\n");
        fclose(fp);
        fclose(fp1);
        return 0;
    }

    if (ch1 == EOF && ch2 == EOF) {
        printf("\n-----�����ļ���ȫ��ͬ��-----\n");
        fclose(fp);
        fclose(fp1);
        return 1;
    }
    return 0;
}
