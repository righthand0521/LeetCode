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
    def decodeString(self, s: str) -> str:
        retVal = ""

        stack = []
        for c in s:
            if c != ']':
                stack.append(c)
                continue

            currentString = ""
            while stack[-1] != '[':
                currentString = stack[-1] + currentString
                stack.pop()
            stack.pop()

            number = ""
            while stack and stack[-1].isdigit():
                number = stack[-1] + number
                stack.pop()

            repeatTimes = int(number)
            while repeatTimes > 0:
                for currentChar in currentString:
                    stack.append(currentChar)
                repeatTimes -= 1

        retVal = retVal.join(stack)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["3[a]2[bc]", "3[a2[c]]", "2[abc]3[cd]ef"]:
            # /* Example
            #  *  Input: s = "3[a]2[bc]"
            #  *  Output: "aaabcbc"
            #  *
            #  *  Input: s = "3[a2[c]]"
            #  *  Output: "accaccacc"
            #  *
            #  *  Input: s = "2[abc]3[cd]ef"
            #  *  Output: "abcabccdcdcdef"
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.decodeString(s)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
