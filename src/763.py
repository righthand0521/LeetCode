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
    def __init__(self) -> None:
        self.lowercase = 26  # s consists of lowercase English letters.

    def partitionLabels(self, s: str) -> List[int]:
        retVal = []

        last = [0] * self.lowercase
        for idx, ch in enumerate(s):
            last[ord(ch)-ord('a')] = idx

        start = 0
        end = 0
        for idx, ch in enumerate(s):
            end = max(end, last[ord(ch)-ord('a')])
            if idx == end:
                retVal.append(idx - start + 1)
                start = idx + 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["ababcbacadefegdehijhklij", "eccbbbbdec"]:
            # /* Example
            #  *  Input: s = "ababcbacadefegdehijhklij"
            #  *  Output: [9,7,8]
            #  *
            #  *  Input: s = "eccbbbbdec"
            #  *  Output: [10]
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.partitionLabels(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
