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
    def minOperations(self, logs: List[str]) -> int:
        retVal = 0

        for log in logs:
            if log == "../":
                if retVal > 0:
                    retVal -= 1
            elif log == "./":
                continue
            else:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for logs in [["d1/", "d2/", "../", "d21/", "./"],
                     ["d1/", "d2/", "./", "d3/", "../", "d31/"],
                     ["d1/", "../", "../", "../"]]:
            # /* Example
            #  *  Input: logs = ["d1/","d2/","../","d21/","./"]
            #  *  Output: 2
            #  *
            #  *  Input: logs = ["d1/","d2/","./","d3/","../","d31/"]
            #  *  Output: 3
            #  *
            #  *  Input: logs = ["d1/","../","../","../"]
            #  *  Output: 0
            #  */
            logging.info("Input: logs = %s", logs)

            retVal = pSolution.minOperations(logs)
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
