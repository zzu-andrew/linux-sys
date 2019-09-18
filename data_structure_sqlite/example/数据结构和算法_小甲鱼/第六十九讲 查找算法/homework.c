#include <stdio.h>

typedef struct student
{
    int id;
    char name[10];
    float score;
}Student;

float search(Student stu[], int n, int key)
{
    int i;
    
    for( i=0; i < n; i++ )
    {
        if( stu[i].id == key )
        {
            return i.score;
        }
    }
    
    return -1;
}

int main()
{
    Student stu[4] = {
        {1024, "小甲鱼", 100}, 
        {1026, "秋舞斜阳", 60}, 
        {1028, "黑夜", 100}, 
        {1030, "迷途", 60}
        };
    
    float score;
    
    score = search(stu, 4, 1024);
    printf("1024号童鞋的成绩是：%f", score);
    
    return 0;
}