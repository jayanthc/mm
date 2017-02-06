#include <stdio.h>
#include "mm.h"

/* valgrind -v --show-reachable=yes --leak-check=full --track-origins=yes */

int main(int argc, char* argv[])
{
    int* pi1 = NULL;
    int* pi2 = NULL;
    char* pc3 = NULL;
    float* pf4 = NULL;
    double* pd5 = NULL;
    int iRet = EXIT_SUCCESS;

    printf("**** Run 1 ****\n");

    iRet = mmInit(10);
    printf("iRet = %d\n", iRet);

    iRet = mmAlloc((void**) &pi1, 4, sizeof(int), 0);
    printf("iRet = %d\n", iRet);

    iRet = mmAlloc((void**) &pi2, 20, sizeof(int), 1);
    printf("iRet = %d\n", iRet);

    iRet = mmAlloc((void**) &pc3, 1, sizeof(char), 1);
    printf("iRet = %d\n", iRet);

    iRet = mmAlloc((void**) &pf4, 3, sizeof(float), 1);
    printf("iRet = %d\n", iRet);

    /* error */
    iRet = mmAlloc((void**) &pd5, 0, sizeof(double), 0);
    printf("iRet = %d\n", iRet);

    mmStat();

    mmClose();
    /* up to the user to NULL the local pointer */
    pi1 = NULL;
    pi2 = NULL;
    pc3 = NULL;
    pf4 = NULL;
    pd5 = NULL;

    printf("**** Run 2 ****\n");

    iRet = mmInit(2);
    printf("iRet = %d\n", iRet);

    iRet = mmAlloc((void**) &pi1, 2, sizeof(int), 0);
    printf("iRet = %d\n", iRet);

    iRet = mmAlloc((void**) &pd5, 3, sizeof(double), 0);
    printf("iRet = %d\n", iRet);

    mmStat();

    mmClose();
    /* up to the user to NULL the local pointer */
    pi1 = NULL;
    pd5 = NULL;

    printf("**** Run 3 ****\n");

    iRet = mmInit(2);
    printf("iRet = %d\n", iRet);

    iRet = mmAlloc((void**) &pi1, 2, sizeof(int), 0);
    printf("iRet = %d\n", iRet);

    iRet = mmAlloc((void**) &pf4, 3, sizeof(float), 1);
    printf("iRet = %d\n", iRet);

    /* error */
    iRet = mmAlloc((void**) &pd5, 3, sizeof(double), 0);
    printf("iRet = %d\n", iRet);

    mmStat();

    mmClose();
    /* up to the user to NULL the local pointer */
    pi1 = NULL;
    pd5 = NULL;

    return EXIT_SUCCESS;
}

