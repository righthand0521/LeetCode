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
    def largestCombination(self, candidates: List[int]) -> int:
        retVal = 0

        # 1 <= candidates[i] <= 10^7 < 2^24
        for i in range(24):
            maxCount = 0
            for candidate in candidates:
                if (candidate & (1 << i)) != 0:
                    maxCount += 1
            retVal = max(retVal, maxCount)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for candidates in [[16, 17, 71, 62, 12, 24, 14], [8, 8]]:
            # /* Example
            #  *  Input: candidates = [16,17,71,62,12,24,14]
            #  *  Output: 4
            #  *
            #  *  Input: candidates = [8,8]
            #  *  Output: 2
            #  */
            logging.info("Input: candidates = %s", candidates)

            retVal = pSolution.largestCombination(candidates)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
