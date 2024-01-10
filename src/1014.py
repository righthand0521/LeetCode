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
    def maxScoreSightseeingPair(self, values: List[int]) -> int:
        retVal = 0

        # The score of a pair (i < j) of sightseeing spots is
        #  values[i] + values[j] + i - j = (values[i] + i) + (values[j] - j)
        maxScore = values[0] + 0
        valuesSize = len(values)
        for i in range(1, valuesSize):
            retVal = max(retVal, (maxScore + values[i] - i))
            maxScore = max(maxScore, values[i] + i)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for values in [[8, 1, 5, 2, 6], [1, 2]]:
            # /* Example
            #  *  Input: values = [8,1,5,2,6]
            #  *  Output: 11
            #  *
            #  *  Input: values = [1,2]
            #  *  Output: 2
            #  */
            logging.info("Input: values = %s", values)

            retVal = pSolution.maxScoreSightseeingPair(values)
            logging.info("Output: %s", retVal)

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
