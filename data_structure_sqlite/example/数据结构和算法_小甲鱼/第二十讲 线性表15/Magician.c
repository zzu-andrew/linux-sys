#include <stdio.h>
#include <stdlib.h>

#define  CardNumber 13

typedef struct node
{
    int data;
    struct node *next;
}sqlist, *linklist;

linklist CreateLinkList()
{
    linklist head = NULL;
    linklist s, r;
    int i;

    r = head;

    for(i=1; i <= CardNumber; i++)
    {
        s = (linklist)malloc(sizeof(sqlist));
        s->data = 0;

        if(head == NULL)
            head = s;
        else
            r->next = s;

        r = s;
    }

    r->next = head;

    return head;
}

// 发牌顺序计算
void Magician(linklist head)
{
    linklist p;
    int j;
    int Countnumber = 2;

    p = head;
    p->data = 1;  //第一张牌放1

    while(1)
    {
        for(j=0; j < Countnumber; j++)
        {
            p = p->next;
            if(p->data != 0)  //该位置有牌的话,则下一个位置
            {
                p->next;
                j--;
            }
        }

        if(p->data == 0)
        {
            p->data = Countnumber;
            Countnumber ++;

            if(Countnumber == 14)
                break;
        }
    }
}

// 销毁工作
void DestoryList(linklist* list)
j
}

int main()
{
    linklist p;
    int i;

    p = CreateLinkList();
    Magician(p);

    printf("按如下顺序排列：\n");
    for (i=0; i < CardNumber; i++)
    {
        printf("黑桃%d ", p->data);
        p = p->next;
    }

    DestoryList(&p);

    return 0;
}
