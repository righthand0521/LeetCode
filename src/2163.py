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


class Solution:
    def minimumDifference(self, nums: List[int]) -> int:
        retVal = 0

        n = len(nums) // 3

        # max heap
        total = sum(nums[:n])
        part1 = [0] * (n + 1)
        part1[0] = total
        maxHeap = [-x for x in nums[:n]]
        heapify(maxHeap)
        for i in range(n, n * 2):
            total += nums[i]
            heappush(maxHeap, -nums[i])
            total -= -heappop(maxHeap)
            part1[i - (n - 1)] = total

        # min heap
        part2 = sum(nums[n * 2:])
        minHeap = nums[n * 2:]
        heapify(minHeap)
        retVal = part1[n] - part2
        for i in range(n * 2 - 1, n - 1, -1):
            part2 += nums[i]
            heappush(minHeap, nums[i])
            part2 -= heappop(minHeap)
            retVal = min(retVal, part1[i - n] - part2)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[3, 1, 2], [7, 9, 5, 8, 1, 3]]:
            # /* Example
            #  *  Input: nums = [3,1,2]
            #  *  Output: -1
            #  *
            #  *  Input: nums = [7,9,5,8,1,3]
            #  *  Output: 1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.minimumDifference(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
