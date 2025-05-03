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
    def numRabbits(self, answers: List[int]) -> int:
        retVal = 0

        hashTable = Counter(answers)
        retVal = sum((count + answer) // (answer + 1) * (answer + 1) for answer, count in hashTable.items())

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for answers in [[1, 1, 2], [10, 10, 10]]:
            # /* Example
            #  *  Input: answers = [1,1,2]
            #  *  Output: 5
            #  *
            #  *  Input: answers = [10,10,10]
            #  *  Output: 11
            #  */
            logging.info("Input: answers = %s", answers)

            retVal = pSolution.numRabbits(answers)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
