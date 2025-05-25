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
    def longestPalindrome(self, words: List[str]) -> int:
        retVal = 0

        frequency = Counter(words)

        middle = False
        for word, count in frequency.items():
            reverseWord = word[1] + word[0]
            if word == reverseWord:
                if count % 2 == 1:
                    middle = True
                retVal += (2 * (count // 2 * 2))
            elif word > reverseWord:
                retVal += (4 * min(frequency[word], frequency[reverseWord]))
        if middle == True:
            retVal += 2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words in [["lc", "cl", "gg"], ["ab", "ty", "yt", "lc", "cl", "ab"], ["cc", "ll", "xx"]]:
            # /* Example
            #  *  Input: words = ["lc","cl","gg"]
            #  *  Output: 6
            #  *
            #  *  Input: words = ["ab","ty","yt","lc","cl","ab"]
            #  *  Output: 8
            #  *
            #  *  Input: words = ["cc","ll","xx"]
            #  *  Output: 2
            #  */
            logging.info("Input: words = %s", words)

            retVal = pSolution.longestPalindrome(words)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
