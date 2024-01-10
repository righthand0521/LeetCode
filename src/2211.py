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
    def countCollisions(self, directions: str) -> int:
        retVal = 0

        # https://leetcode.cn/problems/count-collisions-on-a-road/solutions/1352569/da-an-hui-bei-zhuang-ting-de-che-liang-s-yyfl/
        stack = []
        for direction in directions:
            if direction == 'L':
                if not stack:
                    continue
                while stack and stack[-1] == 'R':
                    retVal += 1
                    stack.pop()
                retVal += 1
                stack.append('S')
            elif direction == 'R':
                stack.append(direction)
            elif direction == 'S':
                while stack and stack[-1] == 'R':
                    retVal += 1
                    stack.pop()
                stack.append(direction)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for directions in ["RLRSLL", "LLRR", "SSRSSRLLRSLLRSRSSRLRRRRLLRRLSSRR"]:
            # /* Example
            #  *  Input: directions = "RLRSLL"
            #  *  Output: 5
            #  *
            #  *  Input: directions = "LLRR"
            #  *  Output: 0
            #  *
            #  *  Input: directions = "SSRSSRLLRSLLRSRSSRLRRRRLLRRLSSRR"
            #  *  Output: 20
            #  */
            logging.info("Input: directions = \"%s\"", directions)

            retVal = pSolution.countCollisions(directions)
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
