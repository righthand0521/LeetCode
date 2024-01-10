import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy
from math import sqrt


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
    def bulbSwitch(self, n: int) -> int:
        # /*      1   2   3   4   5   6   7   8   9   10
        #  *    +---+
        #  *  1 | V | V   V   V   V   V   V   V   V   V   =>  1
        #  *    +---+---+
        #  *  2 | V   X | V   X   V   X   V   X   V   X   =>  1
        #  *    +-------+---+
        #  *  3 | V   X   X | X   V   V   V   X   X   X   =>  1
        #  *    +-----------+---+
        #  *  4 | V   X   X   V | V   V   V   V   X   X   =>  2
        #  *    +---------------+---+
        #  *  5 | V   X   X   V   X | V   V   V   X   V   =>  2
        #  *    +-------------------+---+
        #  *  6 | V   X   X   V   X   X | V   V   X   V   =>  2
        #  *    +-----------------------+---+
        #  *  7 | V   X   X   V   X   X   X | V   X   V   =>  2
        #  *    +---------------------------+---+
        #  *  8 | V   X   X   V   X   X   X   X | X   V   =>  2
        #  *    +-------------------------------+---+
        #  *  9 | V   X   X   V   X   X   X   X   V | V   =>  3
        #  *    +-----------------------------------+---+
        #  * 10 | V   X   X   V   X   X   X   X   V   X | =>  3
        #  *    +---------------------------------------+
        #  */
        retVal = int(sqrt(n+0.5))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [3, 0, 1]:
            # /* Example
            #  *  Input: n = 3
            #  *  Output: 1
            #  *
            #  *  Input: n = 0
            #  *  Output: 0
            #  *
            #  *  Input: n = 1
            #  *  Output: 1
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.bulbSwitch(n)
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
