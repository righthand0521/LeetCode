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
    def __init__(self) -> None:
        # s and t consist of uppercase and lowercase English letters.
        self.ASCII_SIZE = 128

    def minWindow(self, s: str, t: str) -> str:
        retVal = ""

        sSize = len(s)
        tSize = len(t)

        hashSet = [0] * self.ASCII_SIZE
        for c in t:
            hashSet[ord(c)] += 1

        # /* Process
        #  *  |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |  12  | ABC           |
        #  *  |------------------------------------------------------------------------------------------|---------------|
        #  *  |   A  |   D  |   O  |   B  |   E  |   C  |   O  |   D  |   E  |   B  |   A  |   N  |   C  |               |
        #  *  | head |      |      |      |      | tail |      |      |      |      |      |      |      | => ADOBEC     |
        #  *  |      | head |      |      |      | tail |      |      |      |      |      |      |      | -X-> DOBEC    |
        #  *  |      | head |      |      |      |      |      |      |      |      | tail |      |      | => DOBECODEBA |
        #  *  |      |      | head |      |      |      |      |      |      |      | tail |      |      | => OBECODEBA  |
        #  *  |      |      |      | head |      |      |      |      |      |      | tail |      |      | => BECODEBA   |
        #  *  |      |      |      |      | head |      |      |      |      |      | tail |      |      | => ECODEBA    |
        #  *  |      |      |      |      |      | head |      |      |      |      | tail |      |      | => CODEBA     |
        #  *  |      |      |      |      |      |      | head |      |      |      | tail |      |      | -X-> ODEBA    |
        #  *  |      |      |      |      |      |      | head |      |      |      |      |      | tail | => ODEBANC    |
        #  *  |      |      |      |      |      |      |      | head |      |      |      |      | tail | => DEBANC     |
        #  *  |      |      |      |      |      |      |      |      | head |      |      |      | tail | => EBANC      |
        #  *  |      |      |      |      |      |      |      |      |      | head |      |      | tail | => BANC       |
        #  */
        count = 0
        head = 0
        retHead = 0
        retTail = 0
        minLen = float('inf')
        for i in range(sSize):
            # update hash set by character in s
            hashSet[ord(s[i])] -= 1

            # if character both in t and s
            if hashSet[ord(s[i])] >= 0:
                count += 1

            while (count == tSize):
                # update head and tail according to Minimum record
                if (i - head + 1) < minLen:
                    minLen = i - head + 1
                    retHead = head
                    retTail = i

                # update hash set by character in s
                hashSet[ord(s[head])] += 1

                # if character in s
                if hashSet[ord(s[head])] > 0:
                    count -= 1

                #  move head
                head += 1
        if minLen != float('inf'):
            retVal = s[retHead:retTail+1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, t in zip(["ADOBECODEBANC", "a", "a"], ["ABC", "a", "aa"]):
            # /* Example
            #  *  Input: s = "ADOBECODEBANC", t = "ABC"
            #  *  Output: "BANC"
            #  *
            #  *  Input: s = "a", t = "a"
            #  *  Output: "a"
            #  *
            #  *  Input: s = "a", t = "aa"
            #  *  Output: ""
            #  */
            logging.info("Input: s = \"%s\", t = \"%s\"", s, t)

            retVal = pSolution.minWindow(s, t)
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
