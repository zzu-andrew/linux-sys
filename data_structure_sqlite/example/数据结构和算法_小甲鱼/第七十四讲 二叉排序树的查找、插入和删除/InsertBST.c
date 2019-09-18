// 当二叉排序树 T 中不存在关键字等于 key 的数据元素时，
// 插入 key 并返回 TRUE，否则返回 FALSE
Status InsertBST(BiTree *T, int key)
{
    BiTree p, s;
    if( !SearchBST(*T, key, NULL, &p) )
    {
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data = key;
        s->lchild = s->rchild = NULL;
        
        if( !p )       
        {
            *T = s;     // 插入 s 为新的根结点
        }
        else if( key < p->data )
        {
            p->lchild = s;  // 插入 s 为左孩子
        }
        else
        {
            p->rchild = s;  // 插入 s 为右孩子
        }
        return TRUE;
    }
    else
    {
        return FALSE;   // 树中已有关键字相同的结点，不再插入
    }
}