import queue


def get_contiguous_directions():
    cont_set = set()
    for i in range(-1, 2):
        for j in range(-1, 2):
            if i != 0 or j != 0:
                cont_set.add((i, j))
    return cont_set


dirs = get_contiguous_directions()


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

    # print(board)
    return board


def is_bounded(i, j, h, w):
    return 0 <= i < h and 0 <= j < w


# Implement your function below.
def click_a(field, h, w, i, j):
    if is_bounded(i, j, h, w) and field[i][j] == 0:
        field[i][j] = -2
        for x, y in dirs:
            click_a(field, h, w, i + x, j + y)
    return field


def click(field, h, w, i, j):
    to_check = queue.Queue()
    to_check.put((i, j))
    while not to_check.empty():
        a, b = to_check.get()
        if field[a][b] == 0:
            field[a][b] = -2
            for da, db in dirs:
                i, j = a + da, b + db
                if is_bounded(i, j, h, w):
                    to_check.put((i, j))
    return field


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

    field1 = [[0, 0, 0, 0, 0],
              [0, 1, 1, 1, 0],
              [0, 1, -1, 1, 0]]

    field1_opened = [[-2, -2, -2, -2, -2],
                     [-2, 1, 1, 1, -2],
                     [-2, 1, -1, 1, -2]]

    assert mine_sweeper([[2, 2]], 3, 5) == field1
    assert click(field1, 3, 5, 2, 2) == field1
    assert click(field1, 3, 5, 1, 4) == field1_opened
    assert click_a(field1, 3, 5, 2, 2) == field1
    assert click_a(field1, 3, 5, 1, 4) == field1_opened

    field2 = [[-1, 1, 0, 0],
              [1, 1, 0, 0],
              [0, 0, 1, 1],
              [0, 0, 1, -1]]

    field2_opened = [[-1, 1, -2, -2],
                     [1, 1, -2, -2],
                     [-2, -2, 1, 1],
                     [-2, -2, 1, -1]]

    assert mine_sweeper([[0, 0], [3, 3]], 4, 4) == field2
    assert click(field2, 4, 4, 0, 1) == field2
    assert click(field2, 4, 4, 1, 3) == field2_opened
    assert click_a(field2, 4, 4, 0, 1) == field2
    assert click_a(field2, 4, 4, 1, 3) == field2_opened
