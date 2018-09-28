def one_changed(a, b):
    edits = 0
    for i in range(len(a)):
        if a[i] != b[i]:
            edits += 1
            if edits > 1:
                return False
    return True


def one_removed(a, b):
    removed = 0
    for i in range(len(b)):
        if a[i] != b[i - removed]:
            removed += 1
            if removed > 1:
                return False
    return True


def one_edit_array(a, b):
    if len(a) == len(b):
        return one_changed(a, b)
    elif len(a) - len(b) == 1:
        return one_removed(a, b)
    elif len(b) - len(a) == 1:
        return one_removed(b, a)
    return False


def test_all():
    assert one_edit_array("abc", "acc") is True
    assert one_edit_array("abc", "acd") is False
    assert one_edit_array("abc", "ac") is True
    assert one_edit_array("abcd", "aed") is False
    assert one_edit_array("ac", "abc") is True
    assert one_edit_array("aed", "abcd") is False
