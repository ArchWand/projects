import math

def solve():
    l, r, k = [int(n) for n in input().split()]

    sum = 0
    s = int(math.sqrt(k))
    for d in range(1, s+1):
        if k % d != 0: continue
        n = k / d
        if d != 1 and n % d == 0 or n * d != k: continue;

        a = int((int(r/n*d) - l + d-l%d)/d)
        if a > 0: sum += a

    print(sum)

t = int(input())
for _ in range(t):
    solve()
