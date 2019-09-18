#include <stdio.h>
#include <stdlib.h>
#define MAX_NODE_NUM 100
#define TRUE 1U
#define FALSE 0U

typedef struct NodeType
{
    int id;
    int cipher;
    struct NodeType *next;
} NodeType;

/* 创建单向循环链表 */
static void CreaList(NodeType **, const int);
/* 运行"约瑟夫环"问题 */
static void StatGame(NodeType **, int);
/* 打印循环链表 */
static void PrntList(const NodeType *);
/* 得到一个结点 */
static NodeType *GetNode(const int, const int);
/* 测试链表是否为空, 空为TRUE，非空为FALSE */
static unsigned EmptyList(const NodeType *);

int main(void)
{
    int n, m;
    NodeType *pHead = NULL;
    while (1)
    {
        printf("请输入人数n（最多%d个）: ", MAX_NODE_NUM);
        scanf("%d", &n);
        printf("和初始密码m: ");
        scanf("%d", &m);
        if (n > MAX_NODE_NUM)
        {
            printf("人数太多，请重新输入！\n");
            continue;
        }
        else
            break;
    }
    CreaList(&pHead, n);
    printf("\n------------ 循环链表原始打印 -------------\n");
    PrntList(pHead);
    printf("\n-------------删除出队情况打印 -------------\n");
    StatGame(&pHead, m);
}

static void CreaList(NodeType **ppHead, const int n)
{
    int i, iCipher;
    NodeType *pNew, *pCur;
    for (i = 1; i <= n; i++)
    {
        printf("输入第%d个人的密码: ", i);
        scanf("%d", &iCipher);
        pNew = GetNode(i, iCipher);
        if (*ppHead == NULL)
        {
            *ppHead = pCur = pNew;
            pCur->next = *ppHead;
        }
        else
        {
            pNew->next = pCur->next;
            pCur->next = pNew;
            pCur = pNew;
        }
    }
    printf("完成单向循环链表的创建!\n");
}

static void StatGame(NodeType **ppHead, int iCipher)
{
    int iCounter, iFlag = 1;
    NodeType *pPrv, *pCur, *pDel;
    pPrv = pCur = *ppHead;
    /* 将pPrv初始为指向尾结点，为删除作好准备 */
    while (pPrv->next != *ppHead)
        pPrv = pPrv->next;
    while (iFlag)
    {
        for (iCounter = 1; iCounter < iCipher; iCounter++)
        {
            pPrv = pCur;
            pCur = pCur->next;
        }
        if (pPrv == pCur)
            iFlag = 0;
        pDel = pCur; /* 删除pCur指向的结点，即有人出列 */
        pPrv->next = pCur->next;
        pCur = pCur->next;
        iCipher = pDel->cipher;
        printf("第%d个人出列, 密码: %d\n", pDel->id, pDel->cipher);
        free(pDel);
    }
    *ppHead = NULL;
    getchar();
}

static void PrntList(const NodeType *pHead)
{
    const NodeType *pCur = pHead;
    if (EmptyList(pHead))
        return;
    do
    {
        printf("第%d个人, 密码: %d\n", pCur->id, pCur->cipher);
        pCur = pCur->next;
    }
    while (pCur != pHead);
    getchar();
}

static NodeType *GetNode(const int iId, const int iCipher)
{
    NodeType *pNew;
    pNew = (NodeType *)malloc(sizeof(NodeType));
    if(!pNew)
    {
        printf("Error, the memory is not enough!\n");
        exit(-1);
    }
    pNew->id = iId;
    pNew->cipher = iCipher;
    pNew->next = NULL;
    return pNew;
}

static unsigned EmptyList(const NodeType *pHead)
{
    if(!pHead)
    {
        printf("The list is empty!\n");
        return TRUE;
    }
    return FALSE;
}

