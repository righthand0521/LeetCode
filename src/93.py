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
    def dfs(self, s: str, step: int, index: int, path: List[str], result: List[str]) -> None:
        sSize = len(s)

        if step == 4:
            if index == sSize:
                result.append('.'.join(path))
            return

        remaining = sSize - index
        if (remaining < (4 - step)) or (remaining > (4 - step) * 3):
            return

        for length in range(1, 4):
            if index + length > sSize:
                break

            segment = s[index:index + length]
            segmentSize = len(segment)
            if ((segment.startswith('0') == True) and (segmentSize > 1)) or int(segment) > 255:
                continue

            path.append(segment)
            self.dfs(s, step + 1, index + length, path, result)
            path.pop()

    def restoreIpAddresses(self, s: str) -> List[str]:
        retVal = []

        sSize = len(s)
        if 4 <= sSize <= 12:
            self.dfs(s, 0, 0, [], retVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["25525511135", "0000", "101023"]:
            # /* Example
            #  *  Input: s = "25525511135"
            #  *  Output: ["255.255.11.135","255.255.111.35"]
            #  *
            #  *  Input: s = "0000"
            #  *  Output: ["0.0.0.0"]
            #  *
            #  *  Input: s = "101023"
            #  *  Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.restoreIpAddresses(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
