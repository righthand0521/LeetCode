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
    def widthOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        retVal = 1

        level = [[root, 1]]
        while level:
            retVal = max(retVal, level[-1][1] - level[0][1] + 1)

            tmp = []
            for node, index in level:
                if node.left:
                    tmp.append([node.left, index * 2])
                if node.right:
                    tmp.append([node.right, index * 2 + 1])
            level = tmp

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 3, 2, 5, 3, None, 9], [1, 3, 2, 5, None, None, 9, 6, None, 7], [1, 3, 2, 5]]:
            # /* Example
            #  *  Input: root = [1,3,2,5,3,null,9]
            #  *  Output: 4
            #  *
            #  *  Input: root = [1,3,2,5,null,null,9,6,null,7]
            #  *  Output: 7
            #  *
            #  *  Input: root = [1,3,2,5]
            #  *  Output: 2
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.widthOfBinaryTree(TreeNode().buildTree(root))
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
