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
    def finalValueAfterOperations(self, operations: List[str]) -> int:
        retVal = 0

        for operation in operations:
            # operations[i] will be either "++X", "X++", "--X", or "X--"
            if operation == "++X" or operation == "X++":
                retVal += 1
            else:
                retVal -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for operations in [["--X", "X++", "X++"], ["++X", "++X", "X++"], ["X++", "++X", "--X", "X--"]]:
            # /* Example
            #  *  Input: operations = ["--X","X++","X++"]
            #  *  Output: 1
            #  *
            #  *  Input: operations = ["++X","++X","X++"]
            #  *  Output: 3
            #  *
            #  *  Input: operations = ["X++","++X","--X","X--"]
            #  *  Output: 0
            #  */
            logging.info("Input: operations = %s", operations)

            retVal = pSolution.finalValueAfterOperations(operations)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
