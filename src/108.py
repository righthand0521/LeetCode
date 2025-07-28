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
    def buildBSTbyPreorder(self, nums: List[int], left: int, right: int) -> Optional[TreeNode]:
        retVal = None

        if left > right:
            return retVal

        middle = (left + right + 1) // 2
        retVal = TreeNode(nums[middle])
        retVal.left = self.buildBSTbyPreorder(nums, left, middle - 1)
        retVal.right = self.buildBSTbyPreorder(nums, middle + 1, right)

        return retVal

    def sortedArrayToBST(self, nums: List[int]) -> Optional[TreeNode]:
        retVal = None

        retVal = self.buildBSTbyPreorder(nums, 0, len(nums) - 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[-10, -3, 0, 5, 9], [1, 3]]:
            # /* Example
            #  *  Input: nums = [-10,-3,0,5,9]
            #  *  Output: [0,-3,9,-10,null,5]
            #  *
            #  *  Input: nums = [1,3]
            #  *  Output: [3,1]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.sortedArrayToBST(nums)
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
