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
    def multiply(self, num1: str, num2: str) -> str:
        retVal = ""

        if (num1 == "0") or (num2 == "0"):
            retVal = "0"
            return retVal

        num1Size = len(num1)
        num2Size = len(num2)
        returnSize = num1Size + num2Size
        returnBuf = [0] * returnSize
        for i in range(num1Size - 1, -1, -1):
            multiplicand = int(num1[i])
            for j in range(num2Size - 1, -1, -1):
                multiplier = int(num2[j])
                product = multiplicand * multiplier
                returnBuf[i + j + 1] = int(returnBuf[i + j + 1]) + product
                carry = int(returnBuf[i + j + 1]) // 10
                returnBuf[i + j + 1] = int(int(returnBuf[i + j + 1]) % 10)
                returnBuf[i + j] = int(returnBuf[i + j]) + carry

        if returnBuf[0] != 0:
            retVal += str(returnBuf[0])
        for i in returnBuf[1:]:
            retVal += str(i)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for num1, num2 in [["2", "3"], ["123", "456"]]:
            # /* Example
            #  *  Input: num1 = "2", num2 = "3"
            #  *  Output: "6"
            #  *
            #  *  Input: num1 = "123", num2 = "456"
            #  *  Output: "56088"
            #  */
            logging.info("Input: num1 = \"%s\", num2 = \"%s\"", num1, num2)

            retVal = pSolution.multiply(num1, num2)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
