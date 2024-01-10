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
    def average(self, salary: List[int]) -> float:
        retVal = 0

        # salary.sort()
        # retVal = sum(salary[1:-1]) / (len(salary) - 2)
        retVal = (sum(salary) - max(salary) - min(salary)) / (len(salary) - 2)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for salary in [[4000, 3000, 1000, 2000], [1000, 2000, 3000]]:
            # /* Example
            #  *  Input: salary = [4000,3000,1000,2000]
            #  *  Output: 2500.00000
            #  *
            #  *  Input: salary = [1000,2000,3000]
            #  *  Output: 2000.00000
            #  */
            logging.info("Input: salary = %s", salary)

            retVal = pSolution.average(salary)
            logging.info("Output: %.5f", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
