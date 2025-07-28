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
    def sortPeople(self, names: List[str], heights: List[int]) -> List[str]:
        retVal = []

        retVal = [name for _, name in sorted(
            zip(heights, names), reverse=True)]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for names, heights in zip([["Mary", "John", "Emma"], ["Alice", "Bob", "Bob"]],
                                  [[180, 165, 170], [155, 185, 150]]):
            # /* Example
            #  *  Input: names = ["Mary","John","Emma"], heights = [180,165,170]
            #  *  Output: ["Mary","Emma","John"]
            #  *
            #  *  Input: names = ["Alice","Bob","Bob"], heights = [155,185,150]
            #  *  Output: ["Bob","Alice","Bob"]
            #  */
            logging.info("Input: names = %s, heights = %s", names, heights)

            retVal = pSolution.sortPeople(names, heights)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
