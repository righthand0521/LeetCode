import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


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
    # Return min number of swaps
    # if one could make all elements in tops or bottoms equal to x
    # else return -1.
    def check(self, tops: List[int], bottoms: List[int], x: int) -> int:
        retVal = -1

        # how many rotations should be done
        # to have all elements in tops equal to x and to have all elements in bottoms equal to x
        rotationsTops = 0
        rotationsBottoms = 0
        topsSize = len(tops)
        for i in range(topsSize):
            if (tops[i] != x) and (bottoms[i] != x):  # rotations coudn't be done
                return retVal

            if tops[i] != x:  # tops[i] != x and bottoms[i] == x
                rotationsTops += 1
            elif bottoms[i] != x:  # tops[i] == x and bottoms[i] != x
                rotationsBottoms += 1

        # min number of rotations to have all elements equal to x in tops or bottoms
        retVal = min(rotationsTops, rotationsBottoms)

        return retVal

    def minDominoRotations(self, tops: List[int], bottoms: List[int]) -> int:
        retVal = 0

        rotations = self.check(tops, bottoms, tops[0])
        # If one could make all elements in tops or bottoms equal to tops[0]
        if (rotations != -1) or (tops[0] == bottoms[0]):
            retVal = rotations
        else:   # If one could make all elements in tops or bottoms equal to bottoms[0]
            retVal = self.check(tops, bottoms, bottoms[0])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for tops, bottoms in zip([[2, 1, 2, 4, 2, 2], [3, 5, 1, 2, 3]], [[5, 2, 6, 2, 3, 2], [3, 6, 3, 3, 4]]):
            # /* Example
            #  *  Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
            #  *  Output: 2
            #  *
            #  *  Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
            #  *  Output: -1
            #  */
            logging.info("Input: tops = %s, bottoms = %s", tops, bottoms)

            retVal = pSolution.minDominoRotations(tops, bottoms)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
