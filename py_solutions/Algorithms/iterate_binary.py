from random import randint


class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


class TreeHelper:

    @staticmethod
    def __step(node: Node, ordered_list: list):
        if node.left:
            TreeHelper.__step(node.left, ordered_list)
        ordered_list.append(node.val)
        if node.right:
            TreeHelper.__step(node.right, ordered_list)
        return

    @staticmethod
    def get_ordered_list(root: Node):
        ordered_list = list()
        TreeHelper.__step(root, ordered_list)
        return ordered_list

    @staticmethod
    def create_tree_from_list(input_list: list):
        root = Node(input_list[0])
        for item in input_list[1:]:
            inserted = False
            curr_node = root
            # print("Checking {}".format(item))
            while not inserted:
                if item < curr_node.val:
                    if curr_node.left:
                        curr_node = curr_node.left
                    else:
                        curr_node.left = Node(item)
                        inserted = True

                elif item > curr_node.val:
                    if curr_node.right:
                        curr_node = curr_node.right
                    else:
                        curr_node.right = Node(item)
                        inserted = True
                else:
                    inserted = True
        return root


def test_tree_helper():
    print("")
    random_list = list([randint(0, 200) for _ in range(50)])
    print("Random list: [ ", end=" ")
    for i in random_list:
        print(i, end=" ")
    print("]")
    root = TreeHelper.create_tree_from_list(random_list)
    ordered_list = TreeHelper.get_ordered_list(root)
    print("Ordered list: [ ", end=" ")
    for i in ordered_list:
        print(i, end=" ")
    print("]")


if __name__ == "__main__":
    test_tree_helper()
