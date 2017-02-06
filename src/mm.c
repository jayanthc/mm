/*
 * @file mm.c
 * A simple memory management library
 * 
 * @author Jayanth Chennamangalam
 * @date 2012.02.28
 */

#include "mm.h"

MM_LIST* g_pstmmList = NULL;
int g_iMax = 0;
int g_iFreeIdx = 0;

/*
 * int mmInit(int iMax)
 */
int mmInit(int iMax)
{
    /* create an array of MM_LISTs */
    g_pstmmList = (MM_LIST*) calloc((size_t) iMax, sizeof(MM_LIST));
    if (NULL == g_pstmmList)
    {
        (void) fprintf(stderr,
                       "ERROR: Memory allocation failed! %s\n",
                       strerror(errno));
        return EXIT_FAILURE;
    }

    /* save the maximum number of buffers possible */
    g_iMax = iMax;

    return EXIT_SUCCESS;
}

/* TODO: in addition to zeroing, add an option to fill with linearly
         stepped data */
/*
 * int mmAlloc(void** ppvBuf, size_t iNum, size_t iSize, int iZero)
 */
int mmAlloc(void** ppvBuf, size_t iNum, size_t iSize, int iZero)
{
    /* validate with g_iMax */
    if (g_iFreeIdx == g_iMax)
    {
        (void) fprintf(stderr,
                       "ERROR: Allocation request limit reached! "
                       "No more buffers will be allocated!\n");
        /* TODO: return a different error code */
        return EXIT_FAILURE;
    }

    /* input validation */
    if (*ppvBuf != NULL)
    {
        (void) fprintf(stderr,
                       "WARNING: Buffer is not NULL! "
                       "Possible reuse of non-freed pointer!\n");
        /* force to be NULL for later error-checking */
        *ppvBuf = NULL;
    }
    if ((iNum * iSize) == 0)
    {
        (void) fprintf(stderr,
                       "ERROR: Request for zero bytes!\n");
        return EXIT_FAILURE;
    }

    if (!iZero) /* malloc() */
    {
        *ppvBuf = malloc(iNum * iSize);
    }
    else        /* calloc() */
    {
        *ppvBuf = calloc(iNum, iSize);
    }
    if (NULL == *ppvBuf)
    {
        (void) fprintf(stderr,
                       "ERROR: Memory allocation failed! %s\n",
                       strerror(errno));
        return EXIT_FAILURE;
    }

    /* if successful, store info in the global MM_LIST list and update the
       free index */
    g_pstmmList[g_iFreeIdx].pvBuf = *ppvBuf;
    g_pstmmList[g_iFreeIdx].iBufSize = iNum * iSize;
    ++g_iFreeIdx;

    return EXIT_SUCCESS;
}

/* TODO: implement this - reshuffle array (make it a linked list?) */
int mmFree(void** ppvBuf)
{
    (void) fprintf(stderr,
                   "ERROR: This function is not yet implemented!\n");

    return EXIT_SUCCESS;
}

void mmClose()
{
    int i = 0;

    /* clean everything */
    for (i = 0; i < g_iFreeIdx; ++i)
    {
        free(g_pstmmList[i].pvBuf);
        g_pstmmList[i].pvBuf = NULL;
        g_pstmmList[i].iBufSize = 0;
    }
    /* reset the free index */
    g_iFreeIdx = 0;

    /* free the MM_LIST list */
    free(g_pstmmList);

    return;
}

void mmStat()
{
    int i = 0;
    int iTotalSize = 0;

    for (i = 0; i < g_iFreeIdx; ++i)
    {
        (void) printf("mmStat: %d:  %d\n",
                      i,
                      g_pstmmList[i].iBufSize);
        iTotalSize += g_pstmmList[i].iBufSize;
    }
    (void) printf("mmStat: %d bytes allocated in %d buffers. "
                  "%d buffers remaining.\n",
                  iTotalSize,
                  g_iFreeIdx,
                  g_iMax - g_iFreeIdx);

    return;
}

