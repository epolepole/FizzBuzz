def stock_buy_naive(p):
    n = len(p)
    mx = 0
    for i in range(n):
        for j in range(i + 1, n):
            mx = max(mx, p[j] - p[i])
    return mx


def stock_buy(prices):
    mx = 0
    mn = float('inf')
    for price in prices:
        mn = min(mn, price)
        mx = max(mx, price - mn)
    return mx


def test():
    assert stock_buy_naive([7, 1, 5, 3, 6, 4]) == 5
    assert stock_buy_naive([6, 4, 7, 1, 6, 5]) == 5
    assert stock_buy([7, 1, 5, 3, 6, 4]) == 5
    assert stock_buy([6, 4, 7, 1, 6, 5]) == 5
