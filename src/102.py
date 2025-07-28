import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

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
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        retVal = []

        if root == None:
            return retVal

        queue = deque([])
        queue.append(root)

        while queue:
            levelVal = []
            for _ in range(len(queue)):
                node = queue.popleft()
                levelVal.append(node.val)
                if node.left != None:
                    queue.append(node.left)
                if node.right != None:
                    queue.append(node.right)
            retVal.append(levelVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[3, 9, 20, None, None, 15, 7], [1], []]:
            # /* Example
            #  *  Input: root = [3,9,20,null,null,15,7]
            #  *  Output: [[3],[9,20],[15,7]]
            #  *
            #  *  Input: root = [1]
            #  *  Output: [[1]]
            #  *
            #  *  Input: root = []
            #  *  Output: []
            #  */
            logging.info("Input: root = %s", root)

            root = TreeNode().buildTree(root)
            retVal = pSolution.levelOrder(root)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
