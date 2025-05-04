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
    def numEquivDominoPairs(self, dominoes: List[List[int]]) -> int:
        retVal = 0

        hashTable = [0] * 100  # dominoes[i].length == 2, 1 <= dominoes[i][j] <= 9
        for x, y in dominoes:
            if x > y:
                index = x * 10 + y
            else:
                index = y * 10 + x
            retVal += hashTable[index]
            hashTable[index] += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for dominoes in [[[1, 2], [2, 1], [3, 4], [5, 6]], [[1, 2], [1, 2], [1, 1], [1, 2], [2, 2]]]:
            # /* Example
            #  *  Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
            #  *  Output: 1
            #  *
            #  *  Input: dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
            #  *  Output: 3
            #  */
            logging.info("Input: dominoes = %s", dominoes)

            retVal = pSolution.numEquivDominoPairs(dominoes)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
