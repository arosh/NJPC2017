#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

def check(N, M, K, a, cnt, flag_rev):
    if cnt == K:
        if flag_rev:
            a = [[a[i][j] for i in xrange(N)] for j in xrange(M)]
        for l in a:
            #print　*l
            print " ".join(map(str, l))
        sys.exit()

def main():
    N, M, K = map(int, raw_input().split())
    flag_rev = False
    if N > M:
        N, M = M, N
        flag_rev = True

    a = [[i * M + j + 1 for j in xrange(M)] for i in xrange(N)]
    cnt = 0
    check(N, M, K, a, cnt, flag_rev)
    for i in xrange(N):
        for k in xrange(M-1, 0, -1):
            for j in xrange(k):
                a[i][j], a[i][j + 1] = a[i][j + 1], a[i][j]
                cnt += 1
                check(N, M, K, a, cnt, flag_rev)

    a = [[i * M + j + 1 for j in xrange(M-1, -1, -1)] for i in xrange(N-1, -1, -1)]
    cnt = N * M * (M-1)/2 + M * N * (N-1)/2;
    check(N, M, K, a, cnt, flag_rev)
    for i in xrange(N):
        for k in xrange(M-1, 0, -1):
            for j in xrange(k):
                a[i][j], a[i][j + 1] = a[i][j + 1], a[i][j]
                cnt -= 1
                check(N, M, K, a, cnt, flag_rev)

    # print(-1)

if __name__ == '__main__':
    main()
