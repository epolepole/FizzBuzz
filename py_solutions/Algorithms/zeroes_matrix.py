def propagate_zeroes(input_matrtix):
    n = len(input_matrtix)
    m = len(input_matrtix[0])

    col_zeroes = set()
    col_no_zeroes = set()
    row_zeroes = set()
    row_no_zeroes = set()

    for i in range(n):
        for j in range(m):
            if input_matrtix[i][j] == 0:
                col_zeroes.add(i)
                row_zeroes.add(j)
                continue

            if i in col_zeroes:
                input_matrtix[i][j] = 0
            elif i not in col_no_zeroes:
                zero_found = False
                for jj in range(j + 1, m):
                    if input_matrtix[i][jj] == 0:
                        input_matrtix[i][j] = 0
                        zero_found = True
                        break
                if zero_found:
                    col_zeroes.add(i)
                else:
                    col_no_zeroes.add(i)

            if j in row_zeroes:
                input_matrtix[i][j] = 0
            elif j not in row_no_zeroes:
                zero_found = False
                for ii in range(i + 1, n):
                    if input_matrtix[ii][j] == 0:
                        input_matrtix[i][j] = 0
                        zero_found = True
                        break
                if zero_found:
                    row_zeroes.add(j)
                else:
                    row_no_zeroes.add(j)

    return input_matrtix


def test_fill_zero():
    matrix = [
        [1, 2, 3, 4, 0],
        [6, 0, 8, 9, 10],
        [11, 12, 13, 14, 15],
        [16, 0, 18, 19, 20],
        [21, 22, 23, 24, 25]
    ]

    expected = [
        [0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0],
        [11, 0, 13, 14, 0],
        [0, 0, 0, 0, 0],
        [21, 0, 23, 24, 0]
    ]
    zeroes_matrix = propagate_zeroes(matrix)
    print(str(zeroes_matrix))
    print(zeroes_matrix == expected)


if __name__ == '__main__':
    test_fill_zero()

# if input_matrtix[i][j] == 0:
#     col_zeroes.add(i)
#     row_zeroes.add(j)
# else:
#     if i in col_zeroes:
#         input_matrtix[i][j] = 0
#     else:
#         for ii in range(i+1, m):
#             if input_matrtix[ii][j] == 0:
#                 col_zeroes.add(ii)
#                 row_zeroes.add(j)
#                 input_matrtix[i][j] = 0
#
#     if j in row_zeroes:
#         input_matrtix[i][j] = 0
#     else:
#         for jj in range(j+1, m):
#             if input_matrtix[i][jj] == 0:
#                 col_zeroes.add(i)
#                 row_zeroes.add(jj)
#                 input_matrtix[i][j] = 0
