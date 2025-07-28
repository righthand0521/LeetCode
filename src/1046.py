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
    def lastStoneWeight(self, stones: List[int]) -> int:
        retVal = 0

        reverseStones = [-stone for stone in stones]
        heapify(reverseStones)
        while len(reverseStones) > 1 and reverseStones[0] != 0:
            heappush(reverseStones, heappop(
                reverseStones) - heappop(reverseStones))
        retVal = -reverseStones[0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for stones in [[2, 7, 4, 1, 8, 1], [1], [3, 7, 2], [2, 2]]:
            # /* Example
            #  *  Input: stones = [2,7,4,1,8,1]
            #  *  Output: 1
            #  *
            #  *  Input: stones = [1]
            #  *  Output: 1
            #  *
            #  *  Input: stones = [3,7,2]
            #  *  Output: 2
            #  *
            #  *  Input: stones = [2,2]
            #  *  Output: 0
            #  */
            logging.info("Input: stones = %s", stones)

            retVal = pSolution.lastStoneWeight(stones)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
