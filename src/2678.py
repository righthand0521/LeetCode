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
    def countSeniors(self, details: List[str]) -> int:
        retVal = 0

        for detail in details:
            age = 10 * (ord(detail[11])-ord('0')) + (ord(detail[12])-ord('0'))
            if age > 60:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for details in [["7868190130M7522", "5303914400F9211", "9273338290F4010"], ["1313579440F2036", "2921522980M5644"]]:
            # /* Example
            #  *  Input: details = ["7868190130M7522","5303914400F9211","9273338290F4010"]
            #  *  Output: 2
            #  *
            #  *  Input: details = ["1313579440F2036","2921522980M5644"]
            #  *  Output: 0
            #  */
            logging.info("Input: details = %s", details)

            retVal = pSolution.countSeniors(details)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
