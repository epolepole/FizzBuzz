def gen_matrix(n):
    m = [[0 for _ in range(n)] for _ in range(n)]
    count = 0
    for i in range(n):
        for j in range(n):
            count += 1
            m[i][j] = count
    return m


def gen_rotated_matrix(n):
    count = 0
    m90 = [[0 for _ in range(n)] for _ in range(n)]
    for j in reversed(range(n)):
        for i in range(n):
            count += 1
            m90[i][j] = count
    return m90


def rotate_90(m, size):
    z = size - 1
    for l in range(size // 2):
        for j in range(l, z - l):
            a1, b1 = l, j
            a2, b2 = b1, z - l
            a3, b3 = b2, z - j
            a4, b4 = b3, a1
            m[a1][b1], m[a2][b2], m[a3][b3], m[a4][b4] = m[a4][b4], m[a1][b1], m[a2][b2], m[a3][b3]

    return m


def test_rotate_size(n):
    a2 = gen_matrix(n)
    a2_rotated = gen_rotated_matrix(n)
    rotate_90(a2, n)
    assert a2 == a2_rotated


def test_rotate_array():
    print("")
    for n in range(10):
        test_rotate_size(n)
