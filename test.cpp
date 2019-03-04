#include <iostream>
#include <chrono>
#include <vector>
#include <assert.h>
#include <string.h>
#include <string>
#include <time.h>
#include <stdarg.h>
#include <iostream>   // std::cout
#include <functional> // std::ref
#include <thread>     // std::thread
#include <future>     // std::promise, std::future
using namespace std;
// typedef void (*pLineCallback)(int iCnt, const char *pcszContent);
typedef void(pLineCallback)(string strContent);

const int iCommitCnt = 100;
#define MAX 40000

typedef char DataType;
typedef struct stBiTree
{
    DataType data;
    struct stBiTree *lchild, *rchild; // 未定义就先使用
} stTreeNode, *p_TreeNode;

typedef struct tagDBFHead
{
    char Mark;
    unsigned char Year;
    unsigned char Month;
    unsigned char Day;
    // 4 + 4 = 8
    long RecCount;
    // 8
    unsigned short DataOffset;
    unsigned short RecSize;
    // 4 + 4 = 8
    char Reserved[20];
    // 8 + 8 + 4 + 4 = 24
} DBFHEAD, *LPDBFHEAD;
// sizeof(DBFHEAD) = 40

typedef struct stDBFHead
{
    char szMark[1]; // 版本信息
    char szYear[1];
    char szMonth[1];
    char szDay[1];
    char szRecCount[4];   // 4字节保存记录数
    char szDataOffset[2]; // 2字节保存文件头字节数
    char szRecSize[2];    // 2字节保存每行数据的长度
    char Reserved[20];
} stDbfHead;

string WString2String(const std::wstring &ws)
{
    std::string strLocale = setlocale(LC_ALL, "");
    const wchar_t *wchSrc = ws.c_str();
    size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
    char *chDest = new char[nDestSize];
    memset(chDest, 0, nDestSize);
    wcstombs(chDest, wchSrc, nDestSize);
    std::string strResult = chDest;
    delete[] chDest;
    setlocale(LC_ALL, strLocale.c_str());
    return strResult;
}

string GetMsgValue(string strOrig, string strKey, string strSplit)
{
    string strRetValue = "";
    int iStrOrigLen;
    int iStrKeyLen;
    size_t uiPosKeyBegin;
    size_t uiPosKeyEnd;
    size_t uiPosStrSplit;

    iStrOrigLen = strOrig.length();
    iStrKeyLen = strKey.length();
    uiPosKeyBegin = strOrig.find(strKey);

    if (uiPosKeyBegin != string::npos)
    {
        // 从key的位置开始,第一次出现 str_split 的位置
        uiPosStrSplit = strOrig.substr(uiPosKeyBegin).find(strSplit);
        if (uiPosStrSplit != string::npos)
        {
            uiPosKeyEnd = uiPosKeyBegin + uiPosStrSplit;
        }
        else
        {
            uiPosKeyEnd = iStrOrigLen;
        }
        int pos_begin = uiPosKeyBegin + iStrKeyLen + 1; // +1 跳过'='字符
        int value_len = uiPosKeyEnd - pos_begin;
        strRetValue = strOrig.substr(pos_begin, value_len);
        return strRetValue;
    }
    return strRetValue;
}

void SwapNeighbourCharacters(string str_swap)
{
    int i = 0;
    char tmp = {0};
    // string str_swap = "HuangJinJie";
    char *pData = (char *)str_swap.c_str();
    char *pCur = (char *)str_swap.c_str();

    // 1.
    while (*pCur != '\0' && i != str_swap.length() - 1)
    {
        tmp = *pCur;
        *(pData + i) = *(pCur + 1);
        *(pData + i + 1) = tmp;
        pCur = pData + i + 2;
        i += 2;
    }
    std::string strResult;
    strResult = pData;
    cout << strResult << endl;

    int len = str_swap.length();
    char chTmp[len];
    str_swap.copy(chTmp, len, 0);

    // 2.
    for (size_t i = 0; i < len - 1; i = i + 2)
    {
        tmp = chTmp[i];
        chTmp[i] = chTmp[i + 1];
        chTmp[i + 1] = tmp;
    }
    chTmp[len] = '\0';
    strResult = chTmp;

    cout << strResult << endl;
}

time_t GetCurrentTimeMs()
{
    time_t currTime;
    currTime = time(NULL);
    return currTime * 1000 + clock();
}

void ReadFile(const std::string &strFile, int iCommitCnt, pLineCallback pf)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    fp = fopen(strFile.c_str(), "r");
    assert(fp);

    while ((read = getline(&line, &len, fp)) != -1)
    {
        pf(line);
    }

    if (line)
    {
        free(line);
    }
}

void test()
{
    vector<string> vecInt{"a", "b", "c", "d"};
    printf("%s\n", vecInt[0].c_str());
    vecInt.erase(vecInt.begin());
    printf("%s\n", vecInt[0].c_str());

    /* code */
    int i = 5;
    int *p = &i;
    p++;
    cout << *p << endl;

    char a[10] = "abc", b[10] = "012", c[10] = "xyz";
    strcpy(a + 1, b + 2);
    puts(strcat(a, c + 1));

    char szTest[14] = "ä¸­å›½";
    // cout << "length" << szTest.length() << endl;
    cout << "length: " << sizeof(szTest) / sizeof(char) << endl;
    cout << "length: " << strlen(szTest) << endl;

    time_t nowMs = GetCurrentTimeMs();
    cout << "nowMs: " << nowMs << endl;

    /* c++11 */
    auto time_now = chrono::system_clock::now();
    auto duration_in_ms = chrono::duration_cast<chrono::milliseconds>(time_now.time_since_epoch());
    cout << "chrono: " << duration_in_ms.count() << endl;

    char szLBM[32 + 1];
    memset((void *)szLBM, 0x00, sizeof(szLBM));
    string strLbm = "L1100125";
    char *p_szLbm = (char *)strLbm.c_str();
    cout << atol(p_szLbm) << endl;

    char szCurrTime[64] = {0};
    // char *F_RUNTIME = "123123";
    string strNowTime = "2018-12-20-14.11.42.333333";
    char *F_RUNTIME = (char *)strNowTime.c_str();
    cout << F_RUNTIME + 11 << endl;
    strncpy(szCurrTime, F_RUNTIME + 11, sizeof(szCurrTime));
    szCurrTime[8] = '\0';
    cout << szCurrTime << endl;
}

void print(string line)
{
    printf("%s\n", line.c_str());
}

void SetMsgText(char *szMsgText, int p_iMsgCode, ...)
{
    char szErrorMsg[4096];
    va_list lpvlArgPtr;
    va_start(lpvlArgPtr, p_iMsgCode);
    vsnprintf(szErrorMsg, sizeof(szErrorMsg) - 1, szMsgText, lpvlArgPtr);
    va_end(lpvlArgPtr);
    cout << szErrorMsg << endl;
}

int test20190124()
{
    char chstr[] = "abcde";
    cout << chstr << endl;
    cout << *chstr << endl;
    cout << *chstr + 1 << endl;
    cout << *(chstr + 1) << endl;

    /*字符常量不可更改*/
    char *p = (char *)"qwertyuiop";
    // p[3] = 'b'; // error
    // *p = 'b'; // error
    // *p++; // success
    // p = "edf"; // success

    while (*p)
    {
        printf("%c ", *p);
        p++;
    }

    cout << p << endl;

    int iRetCode = 100199;
    char szMsgText[] = "没有查询到客户[%lld]征信信息";
    cout << &szMsgText << endl;
    // SetMsgText(szMsgText, iRetCode, 170005578);
    SetMsgText(szMsgText, iRetCode, "打");

    int iArray[4] = {1, 2, 3, 4};
    cout << sizeof(iArray) / sizeof(int) << endl;

    int timems = 1548232725;
    cout << timems % 100 << endl;

    SwapNeighbourCharacters("HuangJinJie");

    int array[] = {2, 4, 6, 8};
    // 用引用会改变array里的值
    for (auto &x : array)
    {
        x++;
    }
    for (auto x : array)
    {
        cout << x;
    }
    cout << endl;

    // ReadFile("./sql_0000.sql", iCommitCnt, print);
    return 0;
}

void setValue(std::future<int> &fut, int value)
{
    std::promise<int> prom;  // 生成一个 std::promise<int> 对象.
    fut = prom.get_future(); // 和 future 关联.
    prom.set_value(value);   // 设置共享状态的值, 此处和线程t保持同步.
}

void printValue(std::future<int> &fut)
{
    int x = fut.get();                   // 获取共享状态的值.
    std::cout << "value: " << x << '\n'; // 打印 value: 10.
}

int test_future()
{
    std::future<int> fut;
    std::thread set_thread(setValue, std::ref(fut), 10); // 将 future 交给另外一个线程t.
    std::thread print_thread(printValue, std::ref(fut)); // 将 future 交给另外一个线程t.

    set_thread.join();
    print_thread.join();
    return 0;
}

struct node
{
    char name[30];
} que[MAX];
/*
BKDRHash函数的解析链接：
http://blog.csdn.net/djinglan/article/details/8812934
*/
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131313; //也可以乘以31、131、1313、13131、131313..
    unsigned int hash = 0;
    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return hash % 32767; //最好对一个大的素数取余
}
int test_bkdr()
{
    int i = 0, n, t, j;
    char a[MAX][30];
    char temp[300];
    memset(a, 0, sizeof(a));

    cin >> n;
    for (i = 0; i < n; i++)
    {
        cin >> que[i].name;
        strcpy(a[BKDRHash(que[i].name)], que[i].name);
    }
    cout << "请输入要查找的字符串:";
    while (~scanf("%s", temp))
    {
        if (strcmp(a[BKDRHash(temp)], temp) == 0)
            cout << "yes" << endl;
        else
        {
            cout << "no" << endl;
            strcpy(a[BKDRHash(temp)], temp);
            strcpy(que[i++].name, temp);
        }
    }
    for (j = 0; j <= i; j++)
    {
        cout << que[j].name << endl; //含有的所有字符串
    }
    return 0;
}

auto testsum(int a, int b) -> decltype(a)
{
    int sum;
    sum = a + b;
    return sum;
}

int test2(int argc, char const *argv[])
{
    // test_bkdr();
    int ii = 010;
    cout << ii + 1 << endl;

    int a = 1, b = 2, c = 2, t;
    while (a < b < c)
    {
        t = a;
        a = b;
        b = t;
        c--;
    }
    printf("%d,%d,%d\n", a, b, c);
    int n[3][3], i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            n[i][j] = i + j;

    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            n[i + 1][j + 1] += n[i][j];

    printf("%d\n", n[i][j]);

    if (strcmp("20160301", "20090624") == 0)
    {
        cout << "same" << endl;
    }
    else
    {
        cout << "diff" << endl;
    }
    stDbfHead dbfHead;
    memset(&dbfHead, 0x00, sizeof(stDbfHead));
    cout << sizeof(dbfHead) << endl;
    dbfHead.szMark[0] = 0x03;
    string msg = "NAME:YEAR,TYPE:C,LEN:20";
    cout << GetMsgValue(msg, "NAME", ",") << endl;

    time_t now;
    time(&now);
    tm *tp = localtime(&now);

    short offset = 161;
    memcpy(&dbfHead.szDataOffset, &offset, 2);

    memmove(&dbfHead.szYear, &tp->tm_year, sizeof(dbfHead.szYear));
    memmove(&dbfHead.szMonth, &tp->tm_mon, sizeof(dbfHead.szMonth));
    memmove(&dbfHead.szDay, &tp->tm_mday, sizeof(dbfHead.szDay));

    // 存在char数组里的数怎么进行加减读取
    uint8_t uinta = 0x03;
    cout << uinta << uinta++ << endl;

    uint8_t iLen;
    char aaa[1];
    string x = "LEN:20000";
    string strTmp = GetMsgValue(x, "LEN", ",");
    int iTmp = atoi(GetMsgValue(x, "LEN", ",").c_str());
    memcpy(aaa, &iTmp, sizeof(aaa)); // 从string到char[]
    // memcpy(aaa, strTmp.c_str(), sizeof(aaa));
    memcpy(&iLen, aaa, 1); // 从char[]到int
    printf("%d\n", iLen);

    union DataUnion {
        char buf[4];
        uint32_t number;
    };

    auto iiTmp = atoi(strTmp.c_str());
    char aa[4];
    memcpy(aa, &iiTmp, sizeof(iiTmp));
    printf("iiTmp = %d\n", iiTmp);
    printf("iTmp=%d, %x\t%x\t%x\t%x\n", iiTmp, aa[0], aa[1], aa[2], aa[3]);

    wstring cc = L"wstring中文";
    string strcc = WString2String(cc);
    wcout << cc << endl;
    cout << strcc << endl;

    return 0;
}

void createTree(p_TreeNode &T)
{
    DataType data;
    cin >> data;
    if (data == '#')
    {
        T = NULL;
    }
    else
    {
        T = (p_TreeNode)malloc(sizeof(p_TreeNode));
        T->data = data;
        createTree(T->lchild);
        createTree(T->rchild);
    }
}

void PreVisit(p_TreeNode T)
{
    if (T != NULL)
    {
        if (T->data != '#')
        {
            printf("%c ", T->data);
        }
        PreVisit(T->lchild);
        PreVisit(T->rchild);
    }
}

void DestroyBinTree(p_TreeNode T)
{
    if (T == NULL)
        return;
    DestroyBinTree(T->lchild);
    DestroyBinTree(T->rchild);
    T->lchild = NULL;
    T->rchild = NULL;
    free(T);
}

int main(int argc, char *argv[])
{
    printf("         A         \n");
    printf("        / \\       \n");
    printf("       B   #       \n");
    printf("     /   \\        \n");
    printf("   C       D       \n");
    printf("  / \\    /   \\   \n");
    printf(" #   #  E     F    \n");
    printf("       / \\   / \\ \n");
    printf("      #   G #   #  \n");
    printf("         / \\      \n");
    printf("        #   #	   \n");

    printf("         e          \n");
    printf("       /   \\       \n");
    printf("     b       f      \n");
    printf("   /   \\    / \\   \n");
    printf("  a     d  #   g    \n");
    printf(" / \\   / \\    / \\\n");
    printf("#   # c   #  #   #  \n");
    printf("     / \\           \n");
    printf("    #   #			\n");

    /*
    p_TreeNode p_Tree;
    createTree(p_Tree);
    PreVisit(p_Tree);
    DestroyBinTree(p_Tree);
    */
    int a = 10;
    float b = static_cast<float> (a);
    int i;
    cout << b << endl;
}