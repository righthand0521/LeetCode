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
    def findArray(self, pref: List[int]) -> List[int]:
        retVal = []

        retVal.append(pref[0])  # 1 <= pref.length <= 10^5
        prefSize = len(pref)
        for i in range(1, prefSize):
            retVal.append(pref[i-1] ^ pref[i])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for pref in [[5, 2, 0, 3, 1], [13]]:
            # /* Example
            #  *  Input: pref = [5,2,0,3,1]
            #  *  Output: [5,7,2,3,2]
            #  *
            #  *  Input: pref = [13]
            #  *  Output: [13]
            #  */
            logging.info("Input: pref = %s", pref)

            retVal = pSolution.findArray(pref)
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
