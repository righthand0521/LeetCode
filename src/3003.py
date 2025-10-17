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
    def maxPartitionsAfterOperations(self, s: str, k: int) -> int:
        retVal = 0

        sSize = len(s)
        left = [[0] * 3 for _ in range(sSize)]
        right = [[0] * 3 for _ in range(sSize)]

        num, mask, count = 0, 0, 0
        for i in range(sSize - 1):
            binary = 1 << (ord(s[i]) - ord("a"))
            if not (mask & binary):
                count += 1
                if count <= k:
                    mask |= binary
                else:
                    num += 1
                    mask = binary
                    count = 1
            left[i + 1][0] = num
            left[i + 1][1] = mask
            left[i + 1][2] = count

        num, mask, count = 0, 0, 0
        for i in range(sSize - 1, 0, -1):
            binary = 1 << (ord(s[i]) - ord("a"))
            if not (mask & binary):
                count += 1
                if count <= k:
                    mask |= binary
                else:
                    num += 1
                    mask = binary
                    count = 1
            right[i - 1][0] = num
            right[i - 1][1] = mask
            right[i - 1][2] = count

        maxLetters = 26  # s consists only of lowercase English letters.
        for i in range(sSize):
            seg = left[i][0] + right[i][0] + 2
            totMask = left[i][1] | right[i][1]
            totCount = bin(totMask).count("1")
            if (left[i][2] == k) and (right[i][2] == k) and (totCount < maxLetters):
                seg += 1
            elif min(totCount + 1, maxLetters) <= k:
                seg -= 1
            retVal = max(retVal, seg)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, k in [["accca", 2], ["aabaab", 3], ["xxyz", 1]]:
            # /* Example
            #  *  Input: s = "accca", k = 2
            #  *  Output: 3
            #  *
            #  *  Input: s = "aabaab", k = 3
            #  *  Output: 1
            #  *
            #  *  Input: s = "xxyz", k = 1
            #  *  Output: 4
            #  */
            logging.info("Input: s = \"%s\", k = %s", s, k)

            retVal = pSolution.maxPartitionsAfterOperations(s, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
