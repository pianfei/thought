/*
 * algorithm.c
 *
 *  Created on: Mar 16, 2025
 *      Author: Administrator
 */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "algorithm.h"
#include "link.h"

typedef struct {
    int row, col;
    u8 *pData;
    u8 k;
} Pair;

typedef struct {
    Pair rc;
    int iterationTimes;
} AnsStru;

// 计算位置加上v后的新位置
void rcAdd(Pair *pIn, Pair *pOut, int c) {
    int v;
    v = pOut->row;
    pOut->row = pIn->row;
    pOut->col = pIn->col;

    pOut->row += v/c;//为什么这里加了，每数c个相当于把这张牌往下移动一行
    v %= c;
    pOut->col += v;
    if (pOut->col>=c) {
        pOut->col %= c;
        pOut->row += 1;//这里还要+1，这里加的是v取整后剩下的，看剩下的是不是能填充满这张牌所在行的右边空位
    }

}

// 计算第p列起始位置
void pthStart(Pair *pStart,long p, long r, long c) {
    //如果p=2，也就是做为第3列被收起了，前面收了2列,假设是7行3列，那么前面收了14个数字
    //重排后，收到的那一列的起始位置位于第14号位置（从0开始数起）
    //即第14/3=4行，第14%3=2列
    pStart->row = (r * p) / c;
    pStart->col = (r * p) % c;
    pStart->k = p;
}

// 计算距离中心点位置的曼哈顿距离
long calDist(Pair rc, long r, long c) {
    long mr = r / 2, mc = c / 2;
    long minr = labs(rc.row - mr);
    long minc = labs(rc.col - mc);
    if (r % 2 == 0 && labs(rc.row - (mr - 1)) < minr)
        minr = labs(rc.row - (mr - 1));
    if (c % 2 == 0 && labs(rc.col - (mc - 1)) < minc)
        minc = labs(rc.col - (mc - 1));
    return minr + minc;
}

void Cardiology1(int r, int c)
{
    AnsStru* stablePos;
    Pair first = {0, 0};
    Pair endst = {r - 1, c - 1};
    Pair start = {0, 0};
    int j,i;
    int iterationTime = 0;
    u8 aBuf[21];

    stablePos = (AnsStru*)RawMalloc(sizeof(AnsStru) * c);
    for(i=0;i<r*c;i++)
    {
        aBuf[i] = i;
    }

    for(j=0;j<c;j++)
    {
        iterationTime = 0;

        pthStart(&start,j, r, c);

        //第一个数字
        first.col = 0;
        first.row = 0;
        endst.row = r-1;//最后一个数字
        endst.col = c-1;
      //  log_a("restart:%d %d",start.row,start.col);

        while (1) {
            Pair oS = first, oE = endst;

            rcAdd(&start, &first, c);
            rcAdd(&start, &endst, c);
//            if(j==2){
//                if(iterationTime==0){
//                    for(i=0;i<first.row*c+first.col;i++)
//                    {
//                        log_b("%d ",aBuf[i]);
//                        if(i%c==c-1){
//                            log_a("");
//                        }
//                    }
//                }
//                log_a("start:%d %d",first.row,first.col);
//                log_a("end:%d %d",endst.row,endst.col);
//            }

            if (oS.row == first.row && oS.col == first.col &&
                oE.row == endst.row && oE.col == endst.col) {
                break;//这个循环一定会结束吗？
            }
            iterationTime++;
        }
        if (first.row == endst.row && first.col == endst.col) {
            stablePos[j].rc = first;
        } else {
            stablePos[j].rc.row = -1;
            stablePos[j].rc.col = -1;
        }
        stablePos[j].iterationTimes = iterationTime;
    }

    int ans = -1;
    long minDist = LONG_MAX;

    for (long i = 0; i < c; ++i) {
        Pair pi = stablePos[i].rc;
        if (pi.row != -1 && pi.col != -1) {
            long dist = calDist(pi, r, c);
            if (dist < minDist || (dist == minDist && i < ans)) {
                minDist = dist;
                ans = i;
            }
        }
    }

    if (ans != -1) {
        log_a("%d %d %d %d",
            ans + 1,
            stablePos[ans].rc.row + 1,
            stablePos[ans].rc.col + 1,
            stablePos[ans].iterationTimes);
    } else {
        log_a("No stable position found.");//c=1的时候会进这里
    }

    RawFree(stablePos);
}



#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

int Cardiology2(int R, int C) {
        // ret = {距离, p, i, j, 迭代次数s}
        int ret[5] = {100000, 0, 0, 0, 0};

        for (int64_t p = 0; p < C; p++) {
            int64_t i = -1, j = -1, s1 = -1, s2 = 0;
            int64_t x = 0, y = 0;

            // 第一次迭代，从(0,0)开始
            do {
                j = x;
                i = y;
                x = (y + p * R) % C;
                y = (y + p * R) / C;
                s1++;
            } while (x != j || y != i);

            if ((i > 0 && j == 0) || (i < R - 1 && j == C - 1))
                continue;

            x = C - 1;
            y = R - 1;
            s2 = 0;

            // 第二次迭代，从(R-1,C-1)开始
            while (x != j || y != i) {
                x = (y + p * R) % C;
                y = (y + p * R) / C;
                s2++;
            }

            int64_t d = MIN(llabs((C - 1) / 2 - j), llabs(C / 2 - j)) +
                        MIN(llabs((R - 1) / 2 - i), llabs(R / 2 - i));

            int64_t cur[5] = {d, p + 1, i + 1, j + 1, MAX(s1, s2)};

            // 比较cur和ret，cur<ret则更新ret
            int is_smaller = 0;
            for (int idx = 0; idx < 5; idx++) {
                if (cur[idx] < ret[idx]) {
                    is_smaller = 1;
                    break;
                } else if (cur[idx] > ret[idx]) {
                    is_smaller = 0;
                    break;
                }
            }
            if (is_smaller)
                for (int idx = 0; idx < 5; idx++)
                    ret[idx] = cur[idx];
        }
        log_a("%d %d %d %d",ret[1], ret[2], ret[3], ret[4]);

    return 0;
}

