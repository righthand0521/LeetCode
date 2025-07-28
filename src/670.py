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
    def maximumSwap(self, num: int) -> int:
        retVal = 0

        numStr = list(str(num))
        numStrSize = len(numStr)
        maxDigitIndex = -1
        swapIdx1 = -1
        swapIdx2 = -1
        for i in range(numStrSize - 1, -1, -1):
            if maxDigitIndex == -1 or numStr[i] > numStr[maxDigitIndex]:
                maxDigitIndex = i
            elif numStr[i] < numStr[maxDigitIndex]:
                swapIdx1 = i
                swapIdx2 = maxDigitIndex

        if swapIdx1 != -1 and swapIdx2 != -1:
            numStr[swapIdx1], numStr[swapIdx2] = numStr[swapIdx2], numStr[swapIdx1]

        retVal = int("".join(numStr))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for num in [2736, 9973]:
            # /* Example
            #  *  Input: num = 2736
            #  *  Output: 7236
            #  *
            #  *  Input: num = 9973
            #  *  Output: 9973
            #  */
            logging.info("Input: num = %s", num)

            retVal = pSolution.maximumSwap(num)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
