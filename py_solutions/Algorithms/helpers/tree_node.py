class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


class TreeBuilder:
    def __init__(self, input_list: list):
        self.input_list = input_list

    def build(self):
        root = TreeNode(self.input_list[0])
        for item in self.input_list[1:]:
            inserted = False
            curr_node = root
            while not inserted:
                if item < curr_node.val:
                    if curr_node.left:
                        curr_node = curr_node.left
                    else:
                        curr_node.left = TreeNode(item)
                        inserted = True

                elif item > curr_node.val:
                    if curr_node.right:
                        curr_node = curr_node.right
                    else:
                        curr_node.right = TreeNode(item)
                        inserted = True
                else:
                    inserted = True
        return root
