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
    def isPalindrome(self, word: str) -> bool:
        retVal = True

        wordSize = len(word)
        left = 0
        right = wordSize - 1
        while left < right:
            if word[left] != word[right]:
                retVal = False
                break
            left += 1
            right -= 1

        return retVal

    def firstPalindrome(self, words: List[str]) -> str:
        retVal = ""

        for word in words:
            if self.isPalindrome(word) == True:
                retVal = word
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words in [["abc", "car", "ada", "racecar", "cool"], ["notapalindrome", "racecar"], ["def", "ghi"]]:
            # /* Example
            #  *  Input: words = ["abc","car","ada","racecar","cool"]
            #  *  Output: "ada"
            #  *
            #  *  Input: words = ["notapalindrome","racecar"]
            #  *  Output: "racecar"
            #  *
            #  *  Input: words = ["def","ghi"]
            #  *  Output: ""
            #  */
            logging.info("Input: words = %s", words)

            retVal = pSolution.firstPalindrome(words)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
