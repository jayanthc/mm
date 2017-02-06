/*
 * @file mm.h
 * A simple memory management library
 * 
 * @author Jayanth Chennamangalam
 * @date 2012.02.28
 */

#ifndef __MM_H__
#define __MM_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct tagmmList
{
    void* pvBuf;
    int iBufSize;
} MM_LIST;

int mmInit(int iMax);
int mmAlloc(void** ppvBuf, size_t iNum, size_t iSize, int iZero);
int mmFree(void** ppvBuf);
void mmClose(void);
void mmStat(void);

#endif  /* __MM_H__ */

