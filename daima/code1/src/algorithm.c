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

typedef struct {
    int row, col;
} Pair;

typedef struct {
    Pair rc;
    int iterationTimes;
} AnsStru;

// 计算位置加上v后的新位置
Pair rcAdd(Pair rc, int v, int c) {
    rc.row += v / c;
    v %= c;
    rc.col += v;
    if (rc.col >= c) {
        rc.col %= c;
        rc.row += 1;
    }
    return rc;
}

// 计算第p列起始位置
Pair pthStart(long p, long r, long c) {
    Pair ret;
    //如果p=2，也就是做为第3列被收起了，前面收了2列,假设是7行3列，那么前面收了14个数字
    //重排后，收到的那一列的起始位置位于第14号位置（从0开始数起）
    //即第14/3=4行，第14%3=2列
    ret.row = (r * p) / c;
    ret.col = (r * p) % c;
    return ret;
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

void Cardiology1(int r, int c) {
    AnsStru* stablePos = (AnsStru*)malloc(sizeof(AnsStru) * c);
    if (!stablePos) {
        log_a("Memory allocation failed\n");
        return;
    }

    for (long p = 0; p < c; ++p) {
        Pair start = {0, 0}, end = {r - 1, c - 1};
        int iterationTime = 0;
        Pair pStart = pthStart(p, r, c);
        while (1) {
            Pair oS = start, oE = end;

            // 更新start和end (范围收缩)
            start = rcAdd(pStart, start.row, c);
            end = rcAdd(pStart, end.row, c);

            if (oS.row == start.row && oS.col == start.col &&
                oE.row == end.row && oE.col == end.col) {
                break;
            }
            iterationTime++;
        }
        if (start.row == end.row && start.col == end.col) {
            stablePos[p].rc = start;
        } else {
            stablePos[p].rc.row = -1;
            stablePos[p].rc.col = -1;
        }
        stablePos[p].iterationTimes = iterationTime;
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
        log_a("No stable position found.");
    }

    free(stablePos);
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

