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
    def longestStrChain(self, words: List[str]) -> int:
        retVal = 0

        count = defaultdict(int)

        words.sort(key=len)
        for word in words:
            count[word] = 1

            wordSize = len(word)
            for i in range(wordSize):
                previous = word[:i] + word[i+1:]
                if previous in count:
                    count[word] = max(count[word], count[previous] + 1)

            retVal = max(retVal, count[word])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words in [["a", "b", "ba", "bca", "bda", "bdca"], ["xbc", "pcxbcf", "xb", "cxbc", "pcxbc"], ["abcd", "dbqca"]]:
            # /* Example
            #  *  Input: words = ["a","b","ba","bca","bda","bdca"]
            #  *  Output: 4
            #  *
            #  *  Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
            #  *  Output: 5
            #  *
            #  *  Input: words = ["abcd","dbqca"]
            #  *  Output: 1
            #  */
            logging.info("Input: words = %s", words)

            retVal = pSolution.longestStrChain(words)
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
