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
    def longestWPI(self, hours: List[int]) -> int:
        retVal = 0

        hoursSize = len(hours)

        prefixSum = [0] * (hoursSize + 1)
        monotonicStack = [0]
        for idx, hour in enumerate(hours, 1):
            prefixSum[idx] = prefixSum[idx - 1] + (1 if hour > 8 else -1)
            if prefixSum[idx] < prefixSum[monotonicStack[-1]]:
                monotonicStack.append(idx)

        for i in range(hoursSize, 0, -1):
            while monotonicStack and prefixSum[i] > prefixSum[monotonicStack[-1]]:
                retVal = max(retVal, i - monotonicStack.pop())

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for hours in [[9, 9, 6, 0, 6, 6, 9], [6, 6, 6], [9, 9, 6, 9, 0, 6, 9, 6, 9], [6, 9, 6], [6, 9, 9]]:
            # /* Example
            #  *  Input: hours = [9,9,6,0,6,6,9]
            #  *  Output: 3
            #  *
            #  *  Input: hours = [6,6,6]
            #  *  Output: 0
            #  *
            #  *  Input: hours = [9,9,6,9,0,6,9,6,9]
            #  *  Output: 9
            #  *
            #  *  Input: hours = [6,9,6]
            #  *  Output: 1
            #  *
            #  *  Input: hours = [6,9,9]
            #  *  Output: 3
            #  */
            logging.info("Input: hours = %s", hours)

            retVal = pSolution.longestWPI(hours)
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
