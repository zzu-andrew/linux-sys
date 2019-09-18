//实现对order序(阶)的B-TREE结构基本操作的封装。  
//查找：search，插入：insert，删除：remove。  
//创建：create，销毁：destory，打印：print。  
#ifndef BTREE_H  
#define BTREE_H  
  
#ifdef __cplusplus  
extern "C" {  
#endif  
  
////* 定义m序(阶)B 树的最小度数BTree_D=ceil(m)*/  
/// 在这里定义每个节点中关键字的最大数目为:2 * BTree_D - 1，即序(阶)：2 * BTree_D.  
#define BTree_D        2  
#define ORDER        (BTree_D * 2) //定义为4阶B-tree,2-3-4树。最简单为3阶B-tree,2-3树。  
//#define ORDER        (BTree_T * 2-1)  //最简单为3阶B-tree,2-3树。  
  
    typedef int KeyType;  
    typedef struct BTNode{  
        int keynum;                        /// 结点中关键字的个数，keynum <= BTree_N  
        KeyType key[ORDER-1];                /// 关键字向量为key[0..keynum - 1]  
        struct BTNode* child[ORDER];        /// 孩子指针向量为child[0..keynum]  
        bool isLeaf;                    /// 是否是叶子节点的标志  
    }BTNode;  
      
    typedef BTNode* BTree;  ///定义BTree  
      
    ///给定数据集data,创建BTree。  
    void BTree_create(BTree* tree, const KeyType* data, int length);  
  
    ///销毁BTree，释放内存空间。  
    void BTree_destroy(BTree* tree);  
      
    ///在BTree中插入关键字key。  
    void BTree_insert(BTree* tree, KeyType key);  
  
    ///在BTree中移除关键字key。  
    void BTree_remove(BTree* tree, KeyType key);  
  
    ///深度遍历BTree打印各层结点信息。  
    void BTree_print(const BTree tree, int layer=1);  
      
    /// 在BTree中查找关键字 key，  
    /// 成功时返回找到的节点的地址及 key 在其中的位置 *pos  
    /// 失败时返回 NULL 及查找失败时扫描到的节点位置 *pos  
    BTNode* BTree_search(const BTree tree, int key, int* pos);  
      
#ifdef __cplusplus  
}  
#endif  
  
#endif