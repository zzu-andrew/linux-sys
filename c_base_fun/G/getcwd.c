#include "c-base.h"


int main(int argc, char const *argv[])
{
    char pathName[128];
    char *pName = NULL;
    memset(pathName, 0, sizeof(pathName));
    
    pName = getcwd(pathName, sizeof(pathName));
    printf("pathName = [%s] pName = [%s]\n", pathName, pName);
    
    if(pathName == pName)
    {
        printf("pathName == pName\n");
    }
    return 0;
}
