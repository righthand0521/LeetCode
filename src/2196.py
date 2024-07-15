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
    def createBinaryTree(self, descriptions: List[List[int]]) -> Optional[TreeNode]:
        retVal = None

        treeHashTable = defaultdict(TreeNode)
        childHashTable = defaultdict(int)
        for parent, child, isLeft in descriptions:
            if parent not in treeHashTable:
                treeHashTable[parent] = TreeNode(parent)

            if child not in treeHashTable:
                treeHashTable[child] = TreeNode(child)

            if isLeft == 1:
                treeHashTable[parent].left = treeHashTable[child]
            else:
                treeHashTable[parent].right = treeHashTable[child]

            childHashTable[child] += 1

        for key, value in treeHashTable.items():
            if key not in childHashTable:
                retVal = value
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for descriptions in [[[20, 15, 1], [20, 17, 0], [50, 20, 1], [50, 80, 0], [80, 19, 1]],
                             [[1, 2, 1], [2, 3, 0], [3, 4, 1]]]:
            # /* Example
            #  *  Input: descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
            #  *  Output: [50,20,80,15,17,19]
            #  *
            #  *  Input: descriptions = [[1,2,1],[2,3,0],[3,4,1]]
            #  *  Output: [1,2,null,null,3,4]
            #  */
            logging.info("Input: descriptions = %s", descriptions)

            retVal = pSolution.createBinaryTree(descriptions)
            retVal = TreeNode().printLevelOrder(retVal)
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
