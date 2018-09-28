import time



def count_count_1_bits(num: int):
    return bin(num).count('1')


def sum_count_1_bits(num: int):


def count_1_bits(num: int):
    count = 1
    while num > 1:
        if num % 2 == 1:
            count += 1
        num = int(num / 2)
    return count


print("109840000: " + str(count_1_bits(10984005)))
print("109840000: " + str(count_count_1_bits(10984005)))
print("109840000: " + str(sum_count_1_bits(10984005)))


def test_bin_count(repetitions, method, param):
    start = time.time()
    for i in range(repetitions):
        method(param)
    end = time.time()
    print("Rep: " + str(repetitions) + ", total time: " + str((start-end)) + ", time per rep: " + str((start-end)/repetitions))


test_bin_count(100000, count_1_bits, 10984005)
test_bin_count(100000, count_count_1_bits, 10984005)
test_bin_count(100000, sum_count_1_bits, 10984005)
