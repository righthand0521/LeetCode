from typing import List


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        #
        self.val = val
        self.left = left
        self.right = right
        #
        self.retVal = []

    def buildTree(self, items: List[int | None]):
        if not items:
            return None

        index = iter(items)
        pRoot = TreeNode(next(index))
        q = [pRoot]
        for node in q:
            val = next(index, None)
            if val is not None:
                node.left = TreeNode(val)
                q.append(node.left)

            val = next(index, None)
            if val is not None:
                node.right = TreeNode(val)
                q.append(node.right)

        return pRoot

    def getSubTree(self, root, val):
        retVal = None

        if root is None:
            return retVal

        if root.val == val:
            retVal = root
            return retVal

        retVal = self.getSubTree(root.left, val)
        if retVal is not None:
            return retVal

        retVal = self.getSubTree(root.right, val)
        if retVal is not None:
            return retVal

        return retVal

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
