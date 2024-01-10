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


class Solution:
    def __init__(self):
        self.method = 1

    def answerQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        retVal = []

        if self.method == 1:
            print("Binary Search")

            nums.sort()
            prefixSum = list(accumulate(nums))
            for query in queries:
                iterator = bisect_right(prefixSum, query)
                retVal.append(iterator)

        elif self.method == 2:
            print("Sorting")

            nums.sort()
            for query in queries:
                count = 0
                for num in nums:
                    query -= num
                    if query < 0:
                        break
                    count += 1
                retVal.append(count)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, queries in zip([[4, 5, 2, 1], [2, 3, 4, 5]], [[3, 10, 21], [1]]):
            # /* Example
            #  *  Input: nums = [4,5,2,1], queries = [3,10,21]
            #  *  Output: [2,3,4]
            #  *
            #  *  Input: nums = [2,3,4,5], queries = [1]
            #  *  Output: [0]
            #  */
            logging.info("Input: nums = %s, queries = %s", nums, queries)

            retVal = pSolution.answerQueries(nums, queries)
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
