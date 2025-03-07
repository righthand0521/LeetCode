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
    def sieve(self, upperLimit):
        retVal = [True] * (upperLimit + 1)  # True = prime, False = not prime

        # 0 and 1 are not prime
        retVal[0] = False
        retVal[1] = False

        for number in range(2, int(upperLimit**0.5) + 1):
            if retVal[number] == False:
                continue
            for multiple in range(number * number, upperLimit + 1, number):
                retVal[multiple] = False  # Mark all multiples of 'number' as non-prime

        return retVal

    def closestPrimes(self, left: int, right: int) -> List[int]:
        retVal = [-1] * 2

        # Step 1: Get all prime numbers up to 'right' using sieve
        sieveArray = self.sieve(right)
        primeNumbers = []
        for num in range(left, right + 1):
            if sieveArray[num] == True:
                primeNumbers.append(num)

        # Step 2: Find the closest prime pair
        primeNumbersSize = len(primeNumbers)
        if primeNumbersSize < 2:
            return retVal  # Less than two primes

        minDifference = float("inf")
        for index in range(1, primeNumbersSize):
            difference = primeNumbers[index] - primeNumbers[index - 1]
            if difference < minDifference:
                minDifference = difference
                retVal[0] = primeNumbers[index - 1]
                retVal[1] = primeNumbers[index]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for left, right in zip([10, 4], [19, 6]):
            # /* Example
            #  *  Input: left = 10, right = 19
            #  *  Output: [11,13]
            #  *
            #  *  Input: left = 4, right = 6
            #  *  Output: [-1,-1]
            #  */
            logging.info("Input: left = %s, right = %s", left, right)

            retVal = pSolution.closestPrimes(left, right)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
