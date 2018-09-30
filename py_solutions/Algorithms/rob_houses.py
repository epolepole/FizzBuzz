def reduce_list(a, i):
    left = a[:i - 1] if i > 2 else ()
    right = a[i + 2:] if i < len(a) - 1 else ()
    return left + right


# Recursive solution with memo
def rob_rec(a, memo):
    mx = 0
    if a in memo:
        return memo[a]
    for i in range(len(a)):
        mx = max(mx, a[i] + rob_rec(reduce_list(a, i), memo))
    memo[a] = mx
    return mx


# Iterative solution
def rob_it(a):
    mx = [a[0]]
    for i in range(1, len(a)):
        max_val = max(mx[i - 1], a[i] + mx[i - 2])
        mx.append(max_val)
    return mx[len(a) - 1]


def test_this():
    assert rob_rec(tuple([1, 2, 3, 4, 5]), {}) == 9
    assert rob_it([1, 2, 3, 4, 5]) == 9
