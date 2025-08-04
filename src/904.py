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
    def totalFruit(self, fruits: List[int]) -> int:
        retVal = 0

        fruitsSize = len(fruits)

        # /* Example
        #  *          +--------------------------------------------+-----------------------------+
        #  *          | 3 | 3 | 3 | 1 | 2 | 1 | 1 | 2 | 3 | 3 | 4  |                             |
        #  *          +--------------------------------------------+-------------------------+---+
        #  *    tail  | 0 > 1 > 2 > 3 > 4                          | size: 1 > 1 > 1 > 2 > 3 |   |
        #  *    head  | 0                                          |  max: 1 > 2 > 3 > 4     | 4 |
        #  *          +--------------------------------------------+-------------------------+---|
        #  *    tail  |                 4                          | size: 3 > 3 > 3 > 2     |   |
        #  *    head  | 0 > 1 > 2 > 3                              |  max: 4 > 2             | 4 |
        #  *          +--------------------------------------------+-------------------------+---+
        #  *    tail  |                 4 > 5 > 6 > 7 > 8          | size: 2 > 2 > 2 > 2 > 3 |   |
        #  *    head  |             3                              |  max: 2 > 3 > 4 > 5     | 5 |
        #  *          +--------------------------------------------+-------------------------+---+
        #  *    tail  |                                 8          | size: 3 > 3 > 3 > 3 > 2 |   |
        #  *    head  |             3 > 4 > 5 > 6 > 7              |  max: 5 > 2             | 5 |
        #  *          +--------------------------------------------+-------------------------+---+
        #  *    tail  |                                 8 > 9 > 10 | size: 2 > 2 > 3         |   |
        #  *    head  |                             7              |  max: 2 > 3             | 5 |
        #  *          +--------------------------------------------+-------------------------+---+
        #  *    tail  |                                         10 | size: 3 > 2             |   |
        #  *    head  |                             7 > 8          |  max: 3 > 3             | 5 |
        #  *          +--------------------------------------------+-------------------------+---+
        #  */
        frequency = Counter()
        head = 0
        tail = 0
        while (tail < fruitsSize):
            frequency[fruits[tail]] += 1
            frequencySize = len(frequency)
            while frequencySize > 2:
                frequency[fruits[head]] -= 1
                if frequency[fruits[head]] == 0:
                    del frequency[fruits[head]]
                frequencySize = len(frequency)
                head += 1

            retVal = max(retVal, tail - head + 1)

            tail += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for fruits in [[1, 2, 1], [0, 1, 2, 2], [1, 2, 3, 2, 2], [3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4]]:
            # /* Example
            #  *  Input: fruits = [1,2,1]
            #  *  Output: 3
            #  *
            #  *  Input: fruits = [0,1,2,2]
            #  *  Output: 3
            #  *
            #  *  Input: fruits = [1,2,3,2,2]
            #  *  Output: 4
            #  *
            #  *  Input: fruits = [3,3,3,1,2,1,1,2,3,3,4]
            #  *  Output: 5
            #  */
            logging.info("Input: fruits = %s", fruits)

            retVal = pSolution.totalFruit(fruits)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
