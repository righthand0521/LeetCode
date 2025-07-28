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
    def successfulPairs(self, spells: List[int], potions: List[int], success: int) -> List[int]:
        retVal = []

        potions.sort()
        for spell in spells:
            divisor = (success + spell - 1) // spell
            iterator = bisect_left(potions, divisor)
            retVal.append(len(potions) - iterator)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for spells, potions, success in zip([[5, 1, 3], [3, 1, 2]], [[1, 2, 3, 4, 5], [8, 5, 8]], [7, 16]):
            # /* Example
            #  *  Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
            #  *  Output: [4,0,3]
            #  *
            #  *  Input: spells = [3,1,2], potions = [8,5,8], success = 16
            #  *  Output: [2,0,2]
            #  */
            logging.info(
                "Input: spells = %s, potions = %s, success = %d", spells, potions, success)

            retVal = pSolution.successfulPairs(spells, potions, success)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
