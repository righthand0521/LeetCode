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
    def maxArea(self, height: List[int]) -> int:
        retVal = 0

        heightSize = len(height)

        left = 0
        right = heightSize - 1
        while left < right:
            leftValue = height[left]
            rightValue = height[right]
            minValue = min(leftValue, rightValue)
            retVal = max(retVal, minValue * (right - left))

            if leftValue > rightValue:
                right -= 1
            else:
                left += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for height in [[1, 8, 6, 2, 5, 4, 8, 3, 7], [1, 1]]:
            # /* Example
            #  *  Input: height = [1,8,6,2,5,4,8,3,7]
            #  *  Output: 49
            #  *
            #  *  Input: height = [1,1]
            #  *  utput: 1
            #  */
            logging.info("Input: height = %s", height)

            retVal = pSolution.maxArea(height)
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
