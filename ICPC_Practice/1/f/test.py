def solve():
    n = int(input())
    m = int(input())

    arr = [0 for _ in range(n)]
    map = {}
    for i in range(n):
        arr[i] = int(input())
        if arr[i] in map:
            map[arr[i]] += 1
        else:
            map[arr[i]] = 1

    for i in range(m):
        ind = int(input())
        val = int(input())

        map[arr[ind]] -= 1
        if map[arr[ind]] == 0:
            map.pop(arr[ind])
        arr[ind] += val
        if arr[ind] in map:
            map[arr[ind]] += 1
        else:
            map[arr[ind]] = 1

        print(len(map))

t = int(input())
for i in range(t):
    solve()
