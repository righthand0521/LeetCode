from typing import List


# Definition for a Node.
class Node:
    def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next
        #
        self.retVal = []

    def buildTree(self, items: List[int | None]):
        if not items:
            return None

        index = iter(items)
        pRoot = Node(next(index))
        q = [pRoot]
        for node in q:
            val = next(index, None)
            if val is not None:
                node.left = Node(val)
                q.append(node.left)

            val = next(index, None)
            if val is not None:
                node.right = Node(val)
                q.append(node.right)

        return pRoot

    def treeHeight(self, root):
        retVal = 0

        if root is None:
            return retVal

        left = self.treeHeight(root.left)
        right = self.treeHeight(root.right)
        if left > right:
            retVal = left + 1
        else:
            retVal = right + 1

        return retVal

    def printCurrentLevel(self, root, level):
        if root is None:
            return

        if level == 1:
            self.retVal.append(root.val)
        elif level > 1:
            self.printCurrentLevel(root.left, level-1)
            self.printCurrentLevel(root.right, level-1)

    def printLevelOrder(self, root):
        height = self.treeHeight(root)
        for i in range(1, height+1):
            self.printCurrentLevel(root, i)

        return self.retVal

    def displayNodeTreeByNext(self, root):
        if root == None:
            return

        p = root
        while p != None:
            self.retVal.append(p.val)
            p = p.next
        self.retVal.append('#')

        self.displayNodeTreeByNext(root.left)

        return self.retVal
