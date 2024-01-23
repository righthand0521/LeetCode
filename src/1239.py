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
        self.returnLength = 0

    def backtracking(self, masks: List[int], start: int, end: int, mask: int) -> None:
        for i in range(start, end):
            if (mask & masks[i]) == 0:
                self.backtracking(masks, i+1, end,  (mask | masks[i]))

        count = 0
        while mask:
            count += (mask & 1)
            mask >>= 1
        self.returnLength = max(self.returnLength, count)

    def maxLength(self, arr: List[str]) -> int:
        retVal = 0

        arrSize = len(arr)
        masks = [0] * arrSize
        for idx, value in enumerate(arr):
            for c in value:
                mask = 1 << (ord(c) - ord('a'))
                if (mask & masks[idx]) != 0:
                    masks[idx] = 0
                    break
                masks[idx] |= mask
        self.returnLength = 0
        self.backtracking(masks, 0, arrSize, 0)

        retVal = self.returnLength

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [["un", "iq", "ue"], ["cha", "r", "act", "ers"],
                    ["abcdefghijklmnopqrstuvwxyz"], ["a", "abc", "d", "de", "def"]]:
            # /* Example
            #  *  Input: arr = ["un","iq","ue"]
            #  *  Output: 4
            #  *
            #  *  Input: arr = ["cha","r","act","ers"]
            #  *  Output: 6
            #  *
            #  *  Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
            #  *  Output: 26
            #  *
            #  *  Input: arr = ["a", "abc", "d", "de", "def"]
            #  *  Output: 6
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.maxLength(arr)
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
