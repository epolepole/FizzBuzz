def max_len_chain_pairs(pairs):
    max_len = 1
    options = {}
    for pair in pairs:
        to_merge_vals = []
        for prev_value in options.keys():
            if pair[0] > prev_value:
                to_merge_vals.append(prev_value)
        if pair[1] not in options:
            options[pair[1]] = 1
        for to_merge in to_merge_vals:
            options[pair[1]] = max(options[pair[1]], options[to_merge] + 1)
        max_len = max(max_len, options[pair[1]])

    return max_len


def test_this():
    assert max_len_chain_pairs([[1, 2], [2, 3], [3, 4]]) == 2
    assert max_len_chain_pairs([[1, 2], [2, 3], [3, 30], [4, 5], [6, 7]]) == 3
    assert max_len_chain_pairs([[1, 2], [2, 3], [3, 30], [4, 5], [6, 7], [31, 32]]) == 4
    assert max_len_chain_pairs([[1, 2], [3, 6], [4, 6], [7, 8]]) == 3
    assert max_len_chain_pairs([[1, 2], [3, 30], [4, 5], [6, 7]]) == 3
