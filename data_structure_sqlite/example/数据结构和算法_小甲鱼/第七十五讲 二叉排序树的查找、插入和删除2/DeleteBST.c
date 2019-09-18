Status DeleteBST(BiTree *T, int key)
{
    if( !*T )
    {
        return FALSE;
    }
    else
    {
        if( key == (*T)->data )
        {
            return Delete(T);
        }
        else if( key < (*T)->data )
        {
            return DeleteBST(&(*T)->lchild, key);
        }
        else
        {
            return DeleteBST(&(*T)->rchild, key);
        }
    }
}

Status Delete(BiTree *p)
{
    BiTree q, s;
    
    if( (*p)->rchild == NULL )
    {
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    else if( (*p)->lchild == NULL )
    {
        q = *p;
        *p = (*p)->rchild;
        free(q);
    }
    else
    {
        q = *p;
        s = (*p)->lchild;
        
        while( s->rchild )
        {
            q = s;
            s = s->rchild;
        }
        
        (*p)->data = s->data;
        
        if( q != *p )
        {
            q->rchild = s->lchild;
        }
        else
        {
            q->lchild = s->lchild;
        }
        
        free(s);
    }
    
    return TRUE;
}