import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional

from tree import TreeNode


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def delNodes(self, root: Optional[TreeNode], to_delete: List[int]) -> List[TreeNode]:
        retVal = []

        if not root:
            return retVal

        toDeleteSet = set(to_delete)
        nodesQueue = deque([root])
        while nodesQueue:
            currentNode = nodesQueue.popleft()

            if currentNode.left:
                nodesQueue.append(currentNode.left)
                # Disconnect the left child if it needs to be deleted
                if currentNode.left.val in toDeleteSet:
                    currentNode.left = None

            if currentNode.right:
                nodesQueue.append(currentNode.right)
                # Disconnect the right child if it needs to be deleted
                if currentNode.right.val in toDeleteSet:
                    currentNode.right = None

            # If the current node needs to be deleted, add its non-null children to the forest
            if currentNode.val in toDeleteSet:
                if currentNode.left:
                    retVal.append(currentNode.left)
                if currentNode.right:
                    retVal.append(currentNode.right)

        # Ensure the root is added to the forest if it is not to be deleted
        if root.val not in toDeleteSet:
            retVal.append(root)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, to_delete in zip([[1, 2, 3, 4, 5, 6, 7], [1, 2, 4, None, 3]], [[3, 5], [3]]):
            # /* Example
            #  *  Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
            #  *  Output: [[1,2,null,4],[6],[7]]
            #  *
            #  *  Input: root = [1,2,4,null,3], to_delete = [3]
            #  *  Output: [[1,2,4]]
            #  */
            logging.info("Input: root = %s, to_delete = %s", root, to_delete)

            retVal = pSolution.delNodes(TreeNode().buildTree(root), to_delete)
            displayBuf = []
            for pTree in retVal:
                pTree = TreeNode().printLevelOrder(pTree)
                displayBuf.append(pTree)
            logging.info("Output: %s", displayBuf)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
