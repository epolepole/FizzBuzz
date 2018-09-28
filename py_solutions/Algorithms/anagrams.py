from collections import defaultdict


def calc_anagrams(input_list):
    output_lists = list()
    keys = defaultdict(int)
    for key in input_list: #O(N)
        key = ''.join(sorted(key)) #(K*log(K))
        if key not in keys:  #O(1)
            keys[key] = len(keys)  #O(1)
            output_lists.append([key])  #O(1)
            continue
        output_lists[keys[key]].append(key)  #O(1)
    print(str(output_lists))
    return output_lists



def calc_anagrams_ok(input_list):
    output_lists = list()
    keys = defaultdict(int)
    for key in input_list: #O(N)
        key = ''.join(sorted(key)) #(K*log(K))
        if key not in keys:  #O(1)
            keys[key] = len(keys)  #O(1)
            output_lists.append([key])  #O(1)
            continue
        output_lists[keys[key]].append(key)  #O(1)
    print(str(output_lists))
    return output_lists


calc_anagrams(['abc', 'cba', 'abb', 'cdf', 'fdc'])
