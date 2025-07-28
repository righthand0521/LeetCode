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
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        retVal = []

        temperaturesSize = len(temperatures)
        retVal = [0] * temperaturesSize

        stack = []
        for idx, temperature in enumerate(temperatures):
            while stack and temperature > temperatures[stack[-1]]:
                previousIdx = stack.pop()
                retVal[previousIdx] = idx - previousIdx
            stack.append(idx)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for temperatures in [[73, 74, 75, 71, 69, 72, 76, 73], [30, 40, 50, 60], [30, 60, 90]]:
            # /* Example
            #  *  Input: temperatures = [73,74,75,71,69,72,76,73]
            #  *  Output: [1,1,4,2,1,1,0,0]
            #  *
            #  *  Input: temperatures = [30,40,50,60]
            #  *  Output: [1,1,1,0]
            #  *
            #  *  Input: temperatures = [30,60,90]
            #  *  Output: [1,1,0]
            #  */
            logging.info("Input: temperatures = %s", temperatures)

            retVal = pSolution.dailyTemperatures(temperatures)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
