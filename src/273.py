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
    def numberToWords(self, num: int) -> str:
        retVal = ""

        if num == 0:
            retVal = "Zero"
            return retVal

        ones = ["", "One", "Two", "Three", "Four",
                "Five", "Six", "Seven", "Eight", "Nine",
                "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"]
        tens = ["", "", "Twenty", "Thirty", "Forty",
                "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"]
        thousands = ["", "Thousand", "Million", "Billion"]

        groupIndex = 0
        while num > 0:
            if num % 1000 != 0:
                groupResult = ""
                part = num % 1000

                if part >= 100:
                    groupResult += ones[part // 100] + " Hundred "
                    part %= 100

                if part >= 20:
                    groupResult += tens[part // 10] + " "
                    part %= 10

                if part > 0:
                    groupResult += ones[part] + " "

                groupResult += thousands[groupIndex] + " "
                retVal = groupResult + retVal

            num //= 1000
            groupIndex += 1

        retVal = retVal.strip()

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [123, 12345, 1234567]:
            # /* Example
            #  *  Input: num = 123
            #  *  Output: "One Hundred Twenty Three"
            #  *
            #  *  Input: num = 12345
            #  *  Output: "Twelve Thousand Three Hundred Forty Five"
            #  *
            #  *  Input: num = 1234567
            #  *  Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
            #  */
            logging.info("Input: num = %d", nums)

            retVal = pSolution.numberToWords(nums)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
