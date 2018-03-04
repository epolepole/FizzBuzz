

def reorder(letter_num_list: list):
    n = int(len(letter_num_list)/3)
    for i in range(0, n-1):
        letter_num_list.insert(i*3 + 1, letter_num_list.pop(2*i+n))
        letter_num_list.insert(i*3 + 2, letter_num_list.pop(i+2*n))
    return letter_num_list


def gen_list(n: int):
    a_list = []
    for i in range(1, n+1):
        a_list.append('a' + str(i))
    for i in range(1, n+1):
        a_list.append('b' + str(i))
    for i in range(1, n+1):
        a_list.append('c' + str(i))
    print("list generated: " + str(a_list))
    return a_list


for a_n in range(1, 10):
    print("n = " + str(a_n))
    the_list = gen_list(a_n)
    reorder(the_list)
