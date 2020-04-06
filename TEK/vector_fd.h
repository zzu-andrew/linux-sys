 // Vector在C++ java中是一个容器，其实说白了就是一个动态数组
#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct{
    int *fd;
    int counter;
    int max_counter;
}VectorFD;


//创建动态数组
extern VectorFD* create_vector_fd(void); 

//销毁动态数组
extern void destroy_vector_fd(VectorFD *);

//获取某个动态数组
extern int get_fd(VectorFD *, int index);

//删除某个动态数组
extern void remove(VectorFD*, int fd);

//增加一个动态数组
extern void add_fd(VectorFD*, int fd);





#endif //VECTOR




