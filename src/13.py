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
    def romanToInt(self, s: str) -> int:
        retVal = 0

        romanMapping = {
            'I': 1,
            'V': 5,
            'X': 10,
            'L': 50,
            'C': 100,
            'D': 500,
            'M': 1000,
        }

        # III = I + I + I = 1 + 1 + 1 = 3
        # LVIII = L + V + I + I + I = 50 + 5 + 1 + 1 + 1 = 58
        # MCMXCIV = M + C + M + X + C + I + V = 1000 - 100 + 1000 - 10 + 100 - 1 + 5 = 1994
        sSize = len(s)
        for i in range(sSize-1):
            currentValue = romanMapping[s[i]]
            nextValue = romanMapping[s[i+1]]
            if currentValue < nextValue:
                retVal -= currentValue
            else:
                retVal += currentValue
        currentValue = romanMapping[s[sSize-1]]
        retVal += currentValue

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["III", "LVIII", "MCMXCIV"]:
            # /* Example
            #  *  Input: s = "III"
            #  *  Output: 3
            #  *
            #  *  Input: s = "LVIII"
            #  *  Output: 58
            #  *
            #  *  Input: s = "MCMXCIV"
            #  *  Output: 1994
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.romanToInt(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
