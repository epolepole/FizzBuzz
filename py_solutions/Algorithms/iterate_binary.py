from random import randint

from py_solutions.Algorithms.helpers.tree_helper import TreeToList
from py_solutions.Algorithms.helpers.tree_node import TreeBuilder


def test_tree_helper():
    random_list = list([randint(0, 200) for _ in range(50)])
    sorted_random_list = sorted(set(random_list))
    root = TreeBuilder(random_list).build()
    tree_lister = TreeToList(root)
    assert tree_lister.recursive() == sorted_random_list
    assert tree_lister.iterative() == sorted_random_list
    assert list(tree_lister.generator()) == sorted_random_list


if __name__ == "__main__":
    test_tree_helper()
