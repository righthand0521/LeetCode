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
    def maxScore(self, nums1: List[int], nums2: List[int], k: int) -> int:
        retVal = 0

        pairs = [(num1, num2) for num1, num2 in zip(nums1, nums2)]
        pairs.sort(key=lambda x: -x[1])

        topKNums1 = [x[0] for x in pairs[:k]]
        sumOfTopKNums1 = sum(topKNums1)
        heapify(topKNums1)

        retVal = sumOfTopKNums1 * pairs[k - 1][1]
        nums1Size = len(nums1)
        for i in range(k, nums1Size):
            sumOfTopKNums1 -= heappop(topKNums1)
            sumOfTopKNums1 += pairs[i][0]
            heappush(topKNums1, pairs[i][0])
            retVal = max(retVal, sumOfTopKNums1 * pairs[i][1])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2, k in zip([[1, 3, 3, 2], [4, 2, 3, 1, 1]], [[2, 1, 3, 4], [7, 5, 10, 9, 6]], [3, 1]):
            # /* Example
            #  *  Input: nums1 = [1,3,3,2], nums2 = [2,1,3,4], k = 3
            #  *  Output: 12
            #  *
            #  *  Input: nums1 = [4,2,3,1,1], nums2 = [7,5,10,9,6], k = 1
            #  *  Output: 30
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s, k = %s", nums1, nums2, k)

            retVal = pSolution.maxScore(nums1, nums2, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
