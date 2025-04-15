import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class FenwickTree:
    def __init__(self, size: int) -> None:
        self.tree = [0] * (size + 1)

    def update(self, index: int, delta: int) -> None:
        index += 1
        treeSize = len(self.tree)
        while index <= treeSize - 1:
            self.tree[index] += delta
            index += (index & -index)

    def query(self, index: int) -> int:
        retVal = 0

        index += 1
        while index > 0:
            retVal += self.tree[index]
            index -= (index & -index)

        return retVal


class Solution:
    def goodTriplets(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = 0

        nums1Size = len(nums1)

        pos2 = [0] * nums1Size
        for i, num2 in enumerate(nums2):
            pos2[num2] = i

        reversedIndexMapping = [0] * nums1Size
        for i, num1 in enumerate(nums1):
            reversedIndexMapping[pos2[num1]] = i

        tree = FenwickTree(nums1Size)

        for value in range(nums1Size):
            pos = reversedIndexMapping[value]
            left = tree.query(pos)
            tree.update(pos, 1)
            right = (nums1Size - 1 - pos) - (value - left)
            retVal += (left * right)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2 in zip([[2, 0, 1, 3], [4, 0, 1, 3, 2]], [[0, 1, 2, 3], [4, 1, 0, 2, 3]]):
            # /* Example
            #  *  Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
            #  *  Output: 1
            #  *
            #  *  Input: nums1 = [4,0,1,3,2], nums2 = [4,1,0,2,3]
            #  *  Output: 4
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s", nums1, nums2)

            retVal = pSolution.goodTriplets(nums1, nums2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
