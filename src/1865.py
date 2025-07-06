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


class FindSumPairs:
    def __init__(self, nums1: List[int], nums2: List[int]):
        self.nums1 = nums1
        self.nums2 = nums2
        self.frequency = Counter(nums2)

    def add(self, index: int, val: int) -> None:
        _nums2 = self.nums2
        _frequency = self.frequency

        _frequency[_nums2[index]] -= 1
        _nums2[index] += val
        _frequency[_nums2[index]] += 1

    def count(self, tot: int) -> int:
        retVal = 0

        _nums1 = self.nums1
        _frequency = self.frequency
        for num in _nums1:
            value = tot - num
            if value in _frequency:
                retVal += _frequency[value]

        return retVal

# Your FindSumPairs object will be instantiated and called as such:
# obj = FindSumPairs(nums1, nums2)
# obj.add(index,val)
# param_2 = obj.count(tot)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip(
            [["FindSumPairs", "count", "add", "count", "count", "add", "add", "count"]],
            [[[[1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]], [7], [3, 2], [8], [4], [0, 1], [1, 1], [7]]]
        ):
            # /* Example
            #  *  Input
            #  *  ["FindSumPairs", "count", "add", "count", "count", "add", "add", "count"]
            #  *  [[[1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]], [7], [3, 2], [8], [4], [0, 1], [1, 1], [7]]
            #  *  Output
            #  *  [null, 8, null, 2, 1, null, null, 11]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "FindSumPairs":
                    obj = FindSumPairs(value[0], value[1])
                    displayStr.append(None)
                elif key == "add":
                    obj.add(value[0], value[1])
                    displayStr.append(None)
                elif key == "count":
                    retVal = obj.count(value[0])
                    displayStr.append(retVal)
            logging.info("Output")
            logging.info("%s", displayStr)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
