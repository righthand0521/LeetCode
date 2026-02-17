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
    def readBinaryWatch(self, turnedOn: int) -> List[str]:
        retVal = []

        for hour in range(12):  # represent the hours (0-11)
            for minute in range(60):  # represent the minutes (0-59)
                if (bin(hour).count('1')) + (bin(minute).count('1')) == turnedOn:
                    retVal.append(f"{hour}:{minute:02d}")

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [1, 9]:
            # /* Example
            #  *  Input: turnedOn = 1
            #  *  Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
            #  *
            #  *  Input: turnedOn = 9
            #  *  Output: []
            #  */
            logging.info("Input:  n = %s",  n)

            retVal = pSolution.readBinaryWatch(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
