import random


class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.height = 1


class AVLTree:
    def __init__(self):
        self.root = None

    def insert(self, value):
        self.root = self._insert(self.root, value)

    def _insert(self, node, value):
        if not node:
            return Node(value)

        if value < node.value:
            node.left = self._insert(node.left, value)
        else:
            node.right = self._insert(node.right, value)

        node.height = 1 + max(self._height(node.left),
                              self._height(node.right))

        return self._balance(node)

    def _height(self, node):
        return node.height if node else 0

    def _balance(self, node):
        # left heavy
        if self._bf(node) > 1:
            if self._bf(node.right) < 0:
                node.right = self._rotate_right(node.right)
            return self._rotate_left(node)

        # right heavy
        if self._bf(node) < -1:
            if self._bf(node.left) > 0:
                node.left = self._rotate_left(node.left)
            return self._rotate_right(node)
        return node

    # balance factor
    def _bf(self, node):
        return self._height(node.right) - self._height(node.left)

    def _rotate_right(self, node):
        left = node.left
        node.left = left.right
        left.right = node
        node.height = 1 + max(self._height(node.left),
                              self._height(node.right))
        left.height = 1 + max(self._height(left.left),
                              self._height(left.right))
        return left

    def _rotate_left(self, node):
        right = node.right
        node.right = right.left
        right.left = node
        node.height = 1 + max(self._height(node.left),
                              self._height(node.right))
        right.height = 1 + max(self._height(right.left),
                               self._height(right.right))
        return right

    # tralversal
    def inorder(self):
        ret = []

        def _inorder(node):
            if not node:
                return
            _inorder(node.left)
            ret.append(node.value)
            _inorder(node.right)

        _inorder(self.root)
        return ret

    def __str__(self):
        return str(self.inorder())

    def __list__(self):
        return self.inorder()

    def __tuple__(self):
        return tuple(self.inorder())


def __main__():
    tree = AVLTree()
    data = random.sample(range(100), 10)
    for i, d in enumerate(data):
        tree.insert(d)
        print(f'{i + 1}: {d}')
        print(tree)
        print()


if __name__ == '__main__':
    __main__()
