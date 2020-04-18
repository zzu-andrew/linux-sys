#include "c-base.h"



int main(int argc, char const *argv[])
{
    char szEnvName[2048] = "PATH";
    char *pEnvName = NULL;

    pEnvName = getenv(szEnvName);
    if(NULL != pEnvName)
    {
        printf("env = [%s]\n",
                 pEnvName);
    }
    return 0;
}


