def fibonacci_recursive(nums):
    if nums < 2:
        return nums
    return fibonacci_recursive(nums - 1) + fibonacci_recursive(nums - 2)


def fibonacci_generator(nums):
    R = [0, 1]
    for i in range(2, nums):
        R.append(R[i - 1] + R[i - 2])
    return R


def reverse_fibonacci_generator(nums):
    R = [0] * nums
    R[nums - 2] = 1
    for i in range(nums - 3, -1, -1):
        R[i] = R[i + 1] + R[i + 2]
    return R


def test():
    assert reverse_fibonacci_generator(7) == [8, 5, 3, 2, 1, 1, 0]
    assert fibonacci_recursive(0) == 0
    assert fibonacci_recursive(1) == 1
    assert fibonacci_recursive(2) == 1
    assert fibonacci_recursive(3) == 2
    assert fibonacci_recursive(4) == 3
    assert fibonacci_recursive(5) == 5
    assert fibonacci_recursive(6) == 8
    assert fibonacci_recursive(7) == 13
