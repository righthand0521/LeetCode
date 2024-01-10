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
    def sortByBits(self, arr: List[int]) -> List[int]:
        retVal = []

        retVal = arr
        retVal.sort(key=lambda num: (num.bit_count(), num))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[0, 1, 2, 3, 4, 5, 6, 7, 8], [1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1]]:
            # /* Example
            #  *  Input: arr = [0,1,2,3,4,5,6,7,8]
            #  *  Output: [0,1,2,4,8,3,5,6,7]
            #  *
            #  *  Input: arr = [1024,512,256,128,64,32,16,8,4,2,1]
            #  *  Output: [1,2,4,8,16,32,64,128,256,512,1024]
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.sortByBits(arr)
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
