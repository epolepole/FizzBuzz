def get_contiguous_directions():
    cont_set = set()
    for i in range(-1, 2):
        for j in range(-1, 2):
            if i != 0 or j != 0:
                cont_set.add((i, j))
    return cont_set


def my_add(a, b):
    return tuple(map(sum, zip(a, b)))


def print_matrix(m):
    print("[")
    for line in m:
        print("\t[", end='')
        for pos in line:
            if pos < 0:
                print(pos, end=' ')
            else:
                print(" {}".format(pos), end=' ')
        print("]")
    print("]")


def mine_sweeper(mines, h, w):
    # mines_set = set([(mine[0], mine[1]) for mine in mines])
    board = [[0 for _ in range(w)] for _ in range(h)]
    cont_dir = get_contiguous_directions()

    for mine in mines:
        for cell_dir in cont_dir:
            i, j = my_add(cell_dir, (mine[0], mine[1]))
            board[mine[0]][mine[1]] = -1
            if h > i >= 0 <= j < w:
                if board[i][j] != -1:
                    board[i][j] += 1

    print(board)
    return board


def test_mine_sweeper():
    """
        y 0  1  2  3
      x
      0  -1 -1  1  0
      1   2  2  1  0
      2   0  0  0  0
    """
    print("")
    assert mine_sweeper([[0, 0], [0, 1]], 3, 4) == [
        [-1, -1, 1, 0],
        [2, 2, 1, 0],
        [0, 0, 0, 0]]
    assert mine_sweeper([[0, 0], [0, 1], [2, 1], [2, 2]], 3, 4) == [
        [-1, -1, 1, 0],
        [3, 4, 3, 1],
        [1, -1, -1, 1]]
