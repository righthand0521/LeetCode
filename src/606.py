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
    def tree2str(self, root: Optional[TreeNode]) -> str:
        retVal = ""

        if root == None:
            return retVal

        retVal += str(root.val)

        if root.left != None:
            retVal += "(" + self.tree2str(root.left) + ")"

        if root.right != None:
            if root.left == None:
                retVal += "()"
            retVal += "(" + self.tree2str(root.right) + ")"

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 2, 3, 4], [1, 2, 3, None, 4]]:
            # /* Example
            #  *  Input: root = [1,2,3,4]
            #  *  Output: "1(2(4))(3)"
            #  *
            #  *  Input: root = [1,2,3,null,4]
            #  *  Output: "1(2()(4))(3)"
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.tree2str(TreeNode().buildTree(root))
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
