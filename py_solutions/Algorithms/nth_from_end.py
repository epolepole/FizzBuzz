# Use this class to create linked lists.
from array import array


class Node:
    def __init__(self, value, child=None):
        self.value = value
        self.child = child

    # The string representation of this node.
    # Will be used for testing.
    def __str__(self):
        return str(self.value)


def list_to_array(head):
    ar = array(0)
    while head is not None:
        ar.append(head.value)
        head = head.child
    return ar


# Implement your function below.
def nth_from_last(head, n):
    ar = array('I')
    while head is not None:
        ar.append(head.value)
        head = head.child
    if len(ar) == 0 or len(ar) < n:
        return None
    return ar[-n]


# NOTE: Feel free to use the following function for testing.
# It converts the given linked list into an easy-to-read string format.
# Example: 7 -> 6 -> 5 -> 4 -> 3 -> 2 -> 1 -> (None)
def linked_list_to_string(head):
    current = head
    str_list = []
    while current:
        str_list.append(str(current.value))
        current = current.child
    str_list.append('(None)')
    return ' -> '.join(str_list)


# head2 = 1 -> 2 -> 3 -> 4 -> (None)

def test_nth_from_last():
    # NOTE: The following input values will be used for testing your solution.
    current = Node(1)
    for i in range(2, 8):
        current = Node(i, current)
    head = current
    # head = 7 -> 6 -> 5 -> 4 -> 3 -> 2 -> 1 -> (None)

    current2 = Node(4)
    for i in range(3, 0, -1):
        current2 = Node(i, current2)
    head2 = current2

    assert nth_from_last(head, 1) == 1.
    assert nth_from_last(head, 5) == 5.
    assert nth_from_last(head2, 2) == 3.
    assert nth_from_last(head2, 4) == 1.
    assert nth_from_last(head2, 5) is None
    assert nth_from_last(None, 1) is None
