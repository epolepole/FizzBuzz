from collections import defaultdict


def split_stick(n, p):
    r = defaultdict(int)
    r[0] = 0
    for i in range(1, n + 1):
        for j in range(i):
            r[i] = max(r[i], r[j] + p[i - j])
    return r[n]


def test_this():
    p = [-1, 1, 1, 1, 1, 10, 4, 5, 1, 2, 4]
    n = len(p) - 1

    assert split_stick(n, p) == 20
