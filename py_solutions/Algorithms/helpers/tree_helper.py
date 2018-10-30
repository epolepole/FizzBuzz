from py_solutions.Algorithms.helpers.tree_node import TreeNode


class TreeToList:
    def __init__(self, root: TreeNode):
        self.root = root

    @staticmethod
    def __step(node: TreeNode, ordered_list: list):
        if node.left:
            TreeToList.__step(node.left, ordered_list)
        ordered_list.append(node.val)
        if node.right:
            TreeToList.__step(node.right, ordered_list)
        return

    def recursive(self):
        ordered_list = list()
        TreeToList.__step(self.root, ordered_list)
        return ordered_list

    def iterative(self):
        ordered_list = list()
        stack_of_nodes = [self.root]
        checked_nodes = set()
        while stack_of_nodes:
            last_node = stack_of_nodes[-1]

            """TreeNode checked already, means we are coming back from left sub tree. Adding it to result list and going for the right sub tree"""
            if last_node.val in checked_nodes:
                current = stack_of_nodes.pop()
                ordered_list.append(current.val)
                if current.right:
                    stack_of_nodes.append(current.right)
                continue

            """Leaf node. Adding it and continuing"""
            if last_node.left is None and last_node.right is None:
                current = stack_of_nodes.pop()
                ordered_list.append(current.val)
                continue

            """First time non leaf node. Adding it to checked and going to left sub tree"""
            checked_nodes.add(last_node.val)
            if last_node.left:
                stack_of_nodes.append(last_node.left)

        return ordered_list

    def generator(self):
        ordered_list = list()
        stack_of_nodes = [self.root]
        checked_nodes = set()
        while stack_of_nodes:
            last_node = stack_of_nodes[-1]

            """TreeNode checked already, means we are coming back from left sub tree. Adding it to result list and going for the right sub tree"""
            if last_node.val in checked_nodes:
                current = stack_of_nodes.pop()
                yield current.val
                if current.right:
                    stack_of_nodes.append(current.right)
                continue

            """Leaf node. Adding it and continuing"""
            if last_node.left is None and last_node.right is None:
                current = stack_of_nodes.pop()
                yield current.val
                continue

            """First time non leaf node. Adding it to checked and going to left sub tree"""
            checked_nodes.add(last_node.val)
            if last_node.left:
                stack_of_nodes.append(last_node.left)

        return ordered_list
