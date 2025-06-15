import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy


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
    def maxDiff(self, num: int) -> int:
        retVal = 0

        # Find a high position and replace it with 9.
        maxNum = str(num)
        for digit in maxNum:
            if digit != "9":
                maxNum = maxNum.replace(digit, "9")
                break

        # Replace the most significant bit with 1
        # Or find a high-order digit that is not equal to the highest digit and replace it with 0.
        minNum = str(num)
        for i, digit in enumerate(minNum):
            if i == 0:
                if digit != "1":
                    minNum = minNum.replace(digit, "1")
                    break
            else:
                if (digit != "0") and (digit != minNum[0]):
                    minNum = minNum.replace(digit, "0")
                    break

        retVal = int(maxNum) - int(minNum)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for num in [555, 9]:
            # /* Example
            #  *  Input: num = 555
            #  *  Output: 888
            #  *
            #  *  Input: num = 9
            #  *  Output: 8
            #  */
            logging.info("Input: num = %s", num)

            retVal = pSolution.maxDiff(num)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
