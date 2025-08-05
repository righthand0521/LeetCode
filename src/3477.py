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
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        retVal = 0

        basketsSize = len(baskets)
        for fruit in fruits:
            unset = 1
            for i in range(basketsSize):
                if fruit <= baskets[i]:
                    baskets[i] = 0
                    unset = 0
                    break
            retVal += unset

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for fruits, baskets in [[[4, 2, 5], [3, 5, 4]], [[3, 6, 1], [6, 4, 7]]]:
            # /* Example
            #  *  Input: fruits = [4,2,5], baskets = [3,5,4]
            #  *  Output: 1
            #  *
            #  *  Input: fruits = [3,6,1], baskets = [6,4,7]
            #  *  Output: 0
            #  */
            logging.info("Input: fruits = %s, baskets = %s", fruits, baskets)

            retVal = pSolution.numOfUnplacedFruits(fruits, baskets)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
