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
    def maximumEnergy(self, energy: List[int], k: int) -> int:
        retVal = float('-inf')

        energySize = len(energy)
        for i in range(energySize - k, energySize):
            total = 0
            j = i
            while j >= 0:
                total += energy[j]
                retVal = max(retVal, total)
                j -= k

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for energy, k in [[[5, 2, -10, -5, 1], 3], [[-2, -3, -1], 2]]:
            # /* Example
            #  *  Input: energy = [5,2,-10,-5,1], k = 3
            #  *  Output: 3
            #  *
            #  *  Input: energy = [-2,-3,-1], k = 2
            #  *  Output: -1
            #  */
            logging.info("Input: energy = %s, k = %s", energy, k)

            retVal = pSolution.maximumEnergy(energy, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
