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
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        retVal = root

        if not retVal:
            return retVal

        bfsQueue = [retVal]

        level = 0
        while bfsQueue:
            currentLevelNodes = []
            bfsQueueSize = len(bfsQueue)
            for _ in range(bfsQueueSize):
                node = bfsQueue.pop(0)

                currentLevelNodes.append(node)
                if node.left:
                    bfsQueue.append(node.left)
                if node.right:
                    bfsQueue.append(node.right)

            if level % 2 == 1:
                left = 0
                right = len(currentLevelNodes) - 1
                while left < right:
                    tmp = currentLevelNodes[left].val
                    currentLevelNodes[left].val = currentLevelNodes[right].val
                    currentLevelNodes[right].val = tmp
                    left += 1
                    right -= 1

            level += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[2, 3, 5, 8, 13, 21, 34], [7, 13, 11], [0, 1, 2, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2]]:
            # /* Example
            #  *  Input: root = [2,3,5,8,13,21,34]
            #  *  Output: [2,5,3,8,13,21,34]
            #  *
            #  *  Input: root = [7,13,11]
            #  *  Output: [7,11,13]
            #  *
            #  *  Input: root = [0,1,2,0,0,0,0,1,1,1,1,2,2,2,2]
            #  *  Output: [0,2,1,0,0,0,0,2,2,2,2,1,1,1,1]
            #  */
            logging.info("Input: root = %s", root)

            root = TreeNode().buildTree(root)
            retVal = pSolution.reverseOddLevels(root)
            retVal = TreeNode().printLevelOrder(retVal)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
