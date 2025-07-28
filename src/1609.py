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
    def isEvenOddTree(self, root: Optional[TreeNode]) -> bool:
        retVal = False

        level = 0
        bfsQueue = deque()
        bfsQueue.append(root)
        while bfsQueue:
            if level % 2 == 0:
                previous = float('-inf')
            else:
                previous = float('inf')

            bfsSize = len(bfsQueue)
            for _ in range(bfsSize):
                current = bfsQueue.popleft()
                value = current.val
                if level % 2 == 0:
                    if value % 2 == 0:
                        return retVal
                    elif value <= previous:
                        return retVal
                    previous = value
                else:
                    if value % 2 != 0:
                        return retVal
                    elif value >= previous:
                        return retVal
                    previous = value

                if current.left:
                    bfsQueue.append(current.left)
                if current.right:
                    bfsQueue.append(current.right)

            level += 1

        retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 10, 4, 3, None, 7, 9, 12, 8, 6, None, None, 2], [5, 4, 2, 3, 3, 7], [5, 9, 1, 3, 5, 7]]:
            # /* Example
            #  *  Input: root = [1,10,4,3,null,7,9,12,8,6,null,null,2]
            #  *  Output: true
            #  *
            #  *  Input: root = [5,4,2,3,3,7]
            #  *  Output: false
            #  *
            #  *  Input: root = [5,9,1,3,5,7]
            #  *  Output: false
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.isEvenOddTree(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
