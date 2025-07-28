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
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        retVal = []

        if root == None:
            return retVal
        retVal.extend(self.inorderTraversal(root.left))
        retVal.append(root.val)
        retVal.extend(self.inorderTraversal(root.right))

        return retVal

    def findMode(self, root: Optional[TreeNode]) -> List[int]:
        retVal = []

        if root == None:
            return retVal
        record = Counter(self.inorderTraversal(root)).most_common()

        maxValue = record[0][1]
        retVal.append(record[0][0])
        record = record[1:]
        for key, value in record:
            if maxValue == value:
                retVal.append(key)
            else:
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, None, 2, 2], [0]]:
            # /* Example
            #  *  Input: root = [1,null,2,2]
            #  *  Output: [2]
            #  *
            #  *  Input: root = [0]
            #  *  Output: [0]
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.findMode(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
