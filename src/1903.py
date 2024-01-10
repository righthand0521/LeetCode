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
    def largestOddNumber(self, num: str) -> str:
        retVal = ""

        numSize = len(num)
        for i in range(numSize-1, -1, -1):
            if int(num[i]) % 2 == 0:
                continue
            retVal = num[:i+1]
            break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for num in ["52", "4206", "35427"]:
            # /* Example
            #  *  Input: num = "52"
            #  *  Output: "5"
            #  *
            #  *  Input: num = "4206"
            #  *  Output: ""
            #  *
            #  *  Input: num = "35427"
            #  *  Output: "35427"
            #  */
            logging.info("Input: num = \"%s\"", num)

            retVal = pSolution.largestOddNumber(num)
            logging.info("Output: \"%s\"", retVal)

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
