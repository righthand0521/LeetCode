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
    def __init__(self) -> None:
        # integer range [-2^31, 2^31 - 1]
        self.INT_MAX = 2 ** 31 - 1
        self.INT_MIN = -2 ** 31

    def myAtoi(self, s: str) -> int:
        retVal = 0

        signStatus = False
        numberStatus = False
        isMinus = False
        sum = 0
        for c in s:
            if (c == '+') or (c == '-') or (c == ' '):
                if (signStatus == True) or (numberStatus == True):
                    break
                isMinus = True if (c == '-') else False
                signStatus = False if (c == ' ') else True
            elif (48 <= ord(c) <= 57):
                numberStatus = True
                sum = (10 * sum) + (ord(c) - 48)
                if sum > self.INT_MAX:
                    break
            else:
                break

        if isMinus == True:
            sum = -(sum)

        '''
        5. If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1],
        then clamp the integer so that it remains in the range.
        Specifically, integers less than -2^31 should be clamped to -2^31,
        and integers greater than 2^31 - 1 should be clamped to 2^31 - 1.
        '''
        if sum > self.INT_MAX:
            retVal = self.INT_MAX
        elif sum < self.INT_MIN:
            retVal = self.INT_MIN
        else:
            retVal = sum

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in [
            "42",
            "   -42", "4193 with words",
            "words and 987", "+-12",
            "20000000000000000000",
            "  0000000000012345678",
            "00000-42a1234",
            "  +  413",
            "-91283472332"
        ]:
            # /* Example
            #  *  Input: s = "42"
            #  *  Output: 42
            #  *
            #  *  Input: s = "   -42"
            #  *  Output: -42
            #  *
            #  *  Input: s = "4193 with words"
            #  *  Output: 4193
            #  *
            #  *  Input: s = "words and 987"
            #  *  Output: 0
            #  *
            #  *  Input: s = "+-12"
            #  *  Output: 0
            #  *
            #  *  Input: s = "20000000000000000000"
            #  *  Output: 2147483647
            #  *
            #  *  Input: s = "  0000000000012345678"
            #  *  Output: 12345678
            #  *
            #  *  Input: s = "00000-42a1234"
            #  *  Output: 0
            #  *
            #  *  Input: s = "  +  413"
            #  *  Output: 0
            #  *
            #  *  Input: s = "-91283472332"
            #  *  Output: -2147483648
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.myAtoi(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
