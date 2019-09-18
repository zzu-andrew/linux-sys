// 二叉树的二叉链表结点结构定义
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

// 递归查找二叉排序树 T 中是否存在 key
// 指针 f 指向 T 的双亲，其初始值调用值为 NULL
// 若查找成功，则指针 p 指向该数据元素结点，并返回 TRUE
// 否则指针 p 指向查找路径上访问的最后一个结点，并返回 FALSE
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
    if( !T )    // 查找不成功
    {
        *p = f;
        return FALSE;
    }
    else if( key == T->data )   // 查找成功
    {
        *p = T;
        return TRUE;
    }
    else if( key < T->data )
    {
        return SearchBST( T->lchild, key, T, p );   // 在左子树继续查找
    }
    else
    {
        return SearchBST( T->rchild, key, T, p );   // 在右子树继续查找
    }
}