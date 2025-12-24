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
    def minimumBoxes(self, apple: List[int], capacity: List[int]) -> int:
        retVal = 0

        capacity.sort(reverse=True)
        totalApples = sum(apple)
        while totalApples > 0:
            totalApples -= capacity[retVal]
            retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for apple, capacity in [[[1, 3, 2], [4, 3, 1, 5, 2]], [[5, 5, 5], [2, 4, 2, 7]]]:
            # /* Example
            #  *  Input: apple = [1,3,2], capacity = [4,3,1,5,2]
            #  *  Output: 2
            #  *
            #  *  Input: apple = [5,5,5], capacity = [2,4,2,7]
            #  *  Output: 4
            #  */
            logging.info("Input: apple = %s, capacity = %s", apple, capacity)

            retVal = pSolution.minimumBoxes(apple, capacity)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
