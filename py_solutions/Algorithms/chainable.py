from collections import deque


def followed(a, b):
    return a % 100 == b // 100


def chainable(set_of_nums, A, B):
    to_check = deque([A])

    while len(to_check) != 0:
        check = to_check.pop()
        set_of_nums.discard(check)
        if followed(check, B):
            return True
        for num in set_of_nums:
            if followed(check, num):
                to_check.append(num)

    return False


'''take A, iterate through set, find all 
that follows A
'''


def test():
    assert chainable({8363, 6388, 8183, 5364, 8353, 8365, 9380}, A=8183, B=6388) is True  # 8183 -> 8363 -> 6388
    assert chainable({8364, 6388, 8183, 5364, 8353, 8365, 9380}, A=8183, B=6388) is False  # 8183 -> 8364 -> X, 8183 -> 8353 -> 5364 -> X
    assert chainable({8364, 6388, 8183, 5364, 8353, 8365, 9380, 6483}, A=8183,
                     B=6388) is False  # 8183 -> 8364 -> X, 8183 -> 8353 -> 5364 -> 6483 -> 8364...


'''
Given a set of four digit numbers, and two numbers A and B which are in the set, 
indicate if A and B are chainable. 

Any numbers X and Y are chainable if the last two digits of X are the first two digits of Y, 
with any number of chainable numbers in between. 

For example, given the set {8363, 6388, 8183, 5364, 8353, 8365, 9380}, A=8183, B=6388, yes, A… 
'''
