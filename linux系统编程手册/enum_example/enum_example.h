

/**
 * @brief  宏定义实现枚举型的扩展
 * ＠　　　　该头文件仅用于扩展对应文件宏定义
 */

#define EXAM1_SIZE 1

ENUM_(EXAM1,EXAM1_SIZE,sizeof(int),"this is a enum example")

#define EXAM2_SIZE 2
ENUM_(EXAM2,EXAM1_SIZE,sizeof(int),"this is a enum example")

#define EXAM3_SIZE 30
ENUM_(EXAM3,EXAM3_SIZE,sizeof(int),"this is a enum example")
