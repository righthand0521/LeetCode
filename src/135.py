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
    def candy(self, ratings: List[int]) -> int:
        retVal = 0

        ratingsSize = len(ratings)

        left = [0] * ratingsSize
        for i in range(ratingsSize):
            if (i > 0) and (ratings[i] > ratings[i - 1]):
                left[i] = left[i - 1] + 1
            else:
                left[i] = 1

        right = 0
        for i in range(ratingsSize - 1, -1, -1):
            if (i < ratingsSize - 1) and (ratings[i] > ratings[i + 1]):
                right += 1
            else:
                right = 1

            retVal += max(left[i], right)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for ratings in [[1, 0, 2], [1, 2, 2]]:
            # /* Example
            #  *  Input: ratings = [1,0,2]
            #  *  Output: 5
            #  *
            #  *  Input: ratings = [1,2,2]
            #  *  Output: 4
            #  */
            logging.info("Input: ratings = %s", ratings)

            retVal = pSolution.candy(ratings)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
