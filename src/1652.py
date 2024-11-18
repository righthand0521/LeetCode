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
    def decrypt(self, code: List[int], k: int) -> List[int]:
        retVal = []

        codeSize = len(code)
        retVal = [0] * codeSize
        if k == 0:
            return retVal

        start = 1
        end = k
        if k < 0:  # If k < 0, the starting point will be end of the array.
            start = codeSize - abs(k)
            end = codeSize - 1

        sum = 0
        for i in range(start, end + 1):
            sum += code[i]

        # Scan through the code array as i moving to the right, update the window sum.
        for i in range(codeSize):
            retVal[i] = sum
            sum -= code[start % codeSize]
            sum += code[(end + 1) % codeSize]
            start += 1
            end += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for code, k in zip([[5, 7, 1, 4], [1, 2, 3, 4], [2, 4, 9, 3]], [3, 0, -2]):
            # /* Example
            #  *  Input: code = [5,7,1,4], k = 3
            #  *  Output: [12,10,16,13]
            #  *
            #  *  Input: code = [1,2,3,4], k = 0
            #  *  Output: [0,0,0,0]
            #  *
            #  *  Input: code = [2,4,9,3], k = -2
            #  *  Output: [12,5,6,13]
            #  */
            logging.info("Input: code = %s, k = %s", code, k)

            retVal = pSolution.decrypt(code, k)
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
