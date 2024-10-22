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
    def kthLargestLevelSum(self, root: Optional[TreeNode], k: int) -> int:
        retVal = -1  # If there are fewer than k levels in the tree, return -1.

        traversal = []

        queue = deque([])
        queue.append(root)
        while queue:
            levelSum = 0

            queueSize = len(queue)
            for _ in range(queueSize):
                node = queue.popleft()
                levelSum += node.val
                if node.left != None:
                    queue.append(node.left)
                if node.right != None:
                    queue.append(node.right)

            traversal.append(levelSum)

        traversalSize = len(traversal)
        if k <= traversalSize:
            traversal.sort(reverse=True)
            retVal = traversal[k-1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, k in zip([[5, 8, 9, 2, 1, 3, 7, 4, 6], [1, 2, None, 3]], [2, 1]):
            # /* Example
            #  *  Input: root = [5,8,9,2,1,3,7,4,6], k = 2
            #  *  Output: 13
            #  *
            #  *  Input: root = [1,2,null,3], k = 1
            #  *  Output: 3
            #  */
            logging.info("Input: root = %s, k = %s", root, k)

            pRoot = TreeNode().buildTree(root)
            retVal = pSolution.kthLargestLevelSum(pRoot, k)
            logging.info("Output: %s", retVal)

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
