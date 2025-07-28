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
    def trap(self, height: List[int]) -> int:
        retVal = 0

        heightSize = len(height)
        if heightSize == 0:
            return retVal

        leftMax = [0] * heightSize
        leftMax[0] = height[0]
        for i in range(1, heightSize):
            leftMax[i] = max(leftMax[i - 1], height[i])

        rightMax = [0] * heightSize
        rightMax[heightSize - 1] = height[heightSize - 1]
        for i in range(heightSize - 2, -1, -1):
            rightMax[i] = max(rightMax[i + 1], height[i])

        for i in range(heightSize):
            retVal += (min(leftMax[i], rightMax[i]) - height[i])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for height in [[0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1], [4, 2, 0, 3, 2, 5]]:
            # /* Example
            #  *  Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
            #  *  Output: 6
            #  *
            #  *  Input: height = [4,2,0,3,2,5]
            #  *  Output: 9
            #  */
            logging.info("Input: height = %s", height)

            retVal = pSolution.trap(height)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
