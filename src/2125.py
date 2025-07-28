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
    def numberOfBeams(self, bank: List[str]) -> int:
        retVal = 0

        previous = 0
        for row in bank:
            count1 = Counter(row)['1']
            if count1 != 0:
                retVal += (previous * count1)
                previous = count1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for bank in [["011001", "000000", "010100", "001000"], ["000", "111", "000"]]:
            # /* Example
            #  *  Input: bank = ["011001","000000","010100","001000"]
            #  *  Output: 8
            #  *
            #  *  Input: bank = ["000","111","000"]
            #  *  Output: 0
            #  */
            logging.info("Input: bank = \"%s\"", bank)

            retVal = pSolution.numberOfBeams(bank)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
