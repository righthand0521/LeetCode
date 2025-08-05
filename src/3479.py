import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class SegmentTree:
    def __init__(self, baskets: List[int]):
        self.n = len(baskets)
        size = 2 << (self.n - 1).bit_length()
        self.segmentTree = [0] * size
        self._build(baskets, 1, 0, self.n - 1)

    def _maintain(self, o: int):
        self.segmentTree[o] = max(self.segmentTree[o * 2], self.segmentTree[o * 2 + 1])

    def _build(self, baskets: List[int], o: int, left: int, right: int):
        if left == right:
            self.segmentTree[o] = baskets[left]
            return

        middle = (left + right) // 2
        self._build(baskets, o * 2, left, middle)
        self._build(baskets, o * 2 + 1, middle + 1, right)
        self._maintain(o)

    def find_first_and_update(self, o: int, left: int, right: int, fruit: int) -> int:
        retVal = -1

        if self.segmentTree[o] < fruit:
            return retVal

        if left == right:
            self.segmentTree[o] = -1
            retVal = left
            return retVal

        middle = (left + right) // 2
        i = self.find_first_and_update(o * 2, left, middle, fruit)
        if i == -1:
            i = self.find_first_and_update(o * 2 + 1, middle + 1, right, fruit)
        self._maintain(o)
        retVal = i

        return retVal


class Solution:
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        retVal = 0

        basketsSize = len(baskets)
        if basketsSize == 0:
            retVal = len(fruits)
            return retVal

        tree = SegmentTree(baskets)
        for fruit in fruits:
            if tree.find_first_and_update(1, 0, basketsSize - 1, fruit) == -1:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for fruits, baskets in [[[4, 2, 5], [3, 5, 4]], [[3, 6, 1], [6, 4, 7]]]:
            # /* Example
            #  *  Input: fruits = [4,2,5], baskets = [3,5,4]
            #  *  Output: 1
            #  *
            #  *  Input: fruits = [3,6,1], baskets = [6,4,7]
            #  *  Output: 0
            #  */
            logging.info("Input: fruits = %s, baskets = %s", fruits, baskets)

            retVal = pSolution.numOfUnplacedFruits(fruits, baskets)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
