

def get_max(num):
    if num == 7 or num == 9:
        return 4
    return 3

num_let_dic = {
    2: 'abc',
    3: 'def',
    4: 'ghi',
    5: 'jkl',
    6: 'mno',
    7: 'pqrs',
    8: 'tuv',
    9: 'wxyz',
}

def get_let(num, idx):
    print("\t\t\tnum: " + str(num) + ", idx: " + str(idx))
    return num_let_dic[num][idx]


def get_array(nums: str):
    nums_list = []
    for num in nums:
        nums_list.append(int(num))
    print("\tNums list: " + str(nums_list))
    return nums_list


def get_str_combinations(input_nums: str):
    nums_l = get_array(input_nums)
    combinations = set()
    print(str(get_comb(nums_l, [0]*len(nums_l), 0, '')))


def get_comb(nums_l, idx, pos, comb):
    print("\t\tidx: " + str(idx) + ", pos: " + str(pos))
    while idx[pos] < get_max(nums_l[pos]):
        comb += get_let(nums_l[pos], idx[pos])
        if pos < len(nums_l) - 1:
            get_comb(nums_l, idx, pos+1, comb)
        else:
            print("combination: " + comb)
        comb = ''
        idx[pos] += 1
    return


i_nums = "23"
get_str_combinations(i_nums)