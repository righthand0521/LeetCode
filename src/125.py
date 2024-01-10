import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy


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
    def isPalindrome(self, s: str) -> bool:
        retVal = True

        # A phrase is a palindrome if, after converting all uppercase letters into lowercase letters
        # and removing all non-alphanumeric characters, it reads the same forward and backward.
        # Alphanumeric characters include letters and numbers.
        palindrome = "".join(ch.lower() for ch in s if ch.isalnum())

        head = 0
        tail = len(palindrome) - 1
        while head < tail:
            if palindrome[head] != palindrome[tail]:
                retVal = False
                break
            head += 1
            tail -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["A man, a plan, a canal: Panama", "race a car", " "]:
            # /* Example
            #  *  Input: s = "A man, a plan, a canal: Panama"
            #  *  Output: true
            #  *
            #  *  Input: s = "race a car"
            #  *  Output: false
            #  *
            #  *  Input: s = " "
            #  *  Output: true
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.isPalindrome(s)
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
