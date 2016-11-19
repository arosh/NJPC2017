#!/usr/bin/env
# -*- coding: utf-8 -*-

import sys

def check():
    global a
    if cnt == K:
        if flag_rev:
            a = [[a[i][j] for i in range(N)] for j in range(M)]
        for l in a:
            # print(*l)
            print *l
        sys.exit()

N, M, K = map(int, input().split())
flag_rev = False
if N > M:
    N, M = M, N
    flag_rev = True

a = [[i * M + j + 1 for j in range(M)] for i in range(N)]
cnt = 0
check()
for i in range(N):
    for k in range(1, M)[::-1]:
        for j in range(k):
            a[i][j], a[i][j + 1] = a[i][j + 1], a[i][j]
            cnt += 1
            check()

a = [[i * M + j + 1 for j in range(M)[::-1]] for i in range(N)[::-1]]
cnt = N * M * (M-1)//2 + M * N * (N-1)//2;
check()
for i in range(N):
    for k in range(1, M)[::-1]:
        for j in range(k):
            a[i][j], a[i][j + 1] = a[i][j + 1], a[i][j]
            cnt -= 1
            check()

# print(-1)
