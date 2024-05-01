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
    def reversePrefix(self, word: str, ch: str) -> str:
        retVal = word

        idx = word.find(ch) + 1
        retVal = word[:idx][::-1] + word[idx:]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word, ch in zip(["abcdefd", "xyxzxe", "abcd"], ["d", "z", "z"]):
            # /* Example
            #  *  Input: word = "abcdefd", ch = "d"
            #  *  Output: "dcbaefd"
            #  *
            #  *  Input: word = "xyxzxe", ch = "z"
            #  *  Output: "zxyxxe"
            #  *
            #  *  Input: word = "abcd", ch = "z"
            #  *  Output: "abcd"
            #  */
            logging.info("Input: word = \"%s\", ch = \"%s\"", word, ch)

            retVal = pSolution.reversePrefix(word, ch)
            logging.info("Output: \"%s\"", retVal)

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
