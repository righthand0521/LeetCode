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
    def bagOfTokensScore(self, tokens: List[int], power: int) -> int:
        retVal = 0

        tokensSize = len(tokens)

        tokens.sort()
        left = 0
        right = tokensSize - 1
        while left <= right:
            if power >= tokens[left]:
                power -= tokens[left]
                left += 1
                retVal += 1
            elif (left < right) and (retVal > 0):
                power += tokens[right]
                right -= 1
                retVal -= 1
            else:
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for tokens, power in zip([[100], [200, 100], [100, 200, 300, 400]], [50, 150, 200]):
            # /* Example
            #  *  Input: tokens = [100], power = 50
            #  *  Output: 0
            #  *
            #  *  Input: tokens = [200,100], power = 150
            #  *  Output: 1
            #  *
            #  *  Input: tokens = [100,200,300,400], power = 200
            #  *  Output: 2
            #  */
            logging.info("Input: tokens = %s, power = %s", tokens, power)

            retVal = pSolution.bagOfTokensScore(tokens, power)
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
