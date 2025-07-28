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
    def averageOfLevels(self, root: Optional[TreeNode]) -> List[float]:
        retVal = []

        if root == None:
            return retVal

        queue = deque([])
        queue.append(root)
        while queue:
            levelVal = []
            queueSize = len(queue)
            for _ in range(queueSize):
                node = queue.popleft()
                levelVal.append(node.val)
                if node.left != None:
                    queue.append(node.left)
                if node.right != None:
                    queue.append(node.right)

            levelValSize = len(levelVal)
            average = sum(levelVal) / levelValSize
            retVal.append(average)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[3, 9, 20, None, None, 15, 7], [3, 9, 20, 15, 7]]:
            # /* Example
            #  *  Input: root = [3,9,20,null,null,15,7]
            #  *  Output: [3.00000,14.50000,11.00000]
            #  *
            #  *  Input: root = [3,9,20,15,7]
            #  *  Output: [3.00000,14.50000,11.00000]
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.averageOfLevels(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
