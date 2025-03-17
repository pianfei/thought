/*
 * link.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Administrator
 */
#include "agi.h"
#include "link.h"

void* Malloc2(AgiMember* pDemo,u32 size)
{
    void *p = malloc(size);
    memset(p,0,size);
    return p;
}

void Free2(AgiMember* pDemo,void *p){
    free(p);
}

void* Realloc2(AgiMember* pDemo,void *p,u32 size,u32 old_size)
{
    void *pPre;
    pPre = p;
    p = Malloc2(pDemo,size);
    memcpy(p,pPre,old_size);
    memset(pPre,0,old_size);
    Free2(pDemo,pPre);
   // p = realloc(p,size);
    return p;
}

//不确定是固定还是动态分配
void* MallocX(AgiMember* pDemo,u32 size)
{
    void *p = malloc(size);
    memset(p,0,size);
    return p;
}

void* RawMalloc(u32 size)
{
    void *p = malloc(size);
    memset(p,0,size);
    return p;
}

void* Malloc1(AgiMember* pDemo,u32 size)
{
    void *p = malloc(size);
    memset(p,0,size);
    return p;

}

void Free1(AgiMember* pDemo,void *p){
    free(p);
}

