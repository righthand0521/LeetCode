import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from math import sqrt
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
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7

    def powerOfModulo(self, base: int, exponent: int) -> int:
        retVal = 1

        # Calculate the exponentiation using binary exponentiation
        while exponent > 0:
            # If the exponent is odd, multiply the result by the base
            if exponent % 2 == 1:
                retVal = (retVal * base) % self.MODULO

            # Square the base and halve the exponent
            base = (base * base) % self.MODULO
            exponent //= 2

        return retVal

    def maximumScore(self, nums: List[int], k: int) -> int:
        retVal = 1

        numsSize = len(nums)

        primeScores = [0] * numsSize
        # Calculate the prime score for each number in nums
        for index in range(numsSize):
            num = nums[index]
            # Check for prime factors from 2 to sqrt(n)
            for factor in range(2, int(sqrt(num)) + 1):
                if num % factor != 0:
                    continue
                # Increment prime score for each prime factor
                primeScores[index] += 1
                # Remove all occurrences of the prime factor from num
                while num % factor == 0:
                    num //= factor

            # If num is still greater than or equal to 2, it's a prime factor
            if num >= 2:
                primeScores[index] += 1

        # Initialize next and previous dominant index arrays
        nextDominant = [numsSize] * numsSize
        prevDominant = [-1] * numsSize
        # Stack to store indices for monotonic decreasing prime score
        decreasingPrimeScoreStack = []
        # Calculate the next and previous dominant indices for each number
        for index in range(numsSize):
            # While the stack is not empty and the current prime score is greater than the stack's top
            while (decreasingPrimeScoreStack) and (primeScores[decreasingPrimeScoreStack[-1]] < primeScores[index]):
                topIndex = decreasingPrimeScoreStack.pop()
                # Set the next dominant element for the popped index
                nextDominant[topIndex] = index

            # If the stack is not empty, set the previous dominant element for the current index
            if decreasingPrimeScoreStack:
                prevDominant[index] = decreasingPrimeScoreStack[-1]

            # Push the current index onto the stack
            decreasingPrimeScoreStack.append(index)

        # Calculate the number of subarrays in which each element is dominant
        numOfSubarrays = [0] * numsSize
        for index in range(numsSize):
            numOfSubarrays[index] = (nextDominant[index] - index) * (index - prevDominant[index])

        # Priority queue to process elements in decreasing order of their value
        processingQueue = []
        # Push each number and its index onto the priority queue
        for index in range(numsSize):
            heappush(processingQueue, (-nums[index], index))

        # Process elements while there are operations left
        while k > 0:
            # Get the element with the maximum value from the queue
            num, index = heappop(processingQueue)
            num = -num  # Negate back to positive

            # Calculate the number of operations to apply on the current element
            operations = min(k, numOfSubarrays[index])

            # Update the score by raising the element to the power of operations
            retVal = (retVal * self.powerOfModulo(num, operations)) % self.MODULO

            # Reduce the remaining operations count
            k -= operations

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[8, 3, 9, 3, 8], [19, 12, 14, 6, 10, 18]], [2, 3]):
            # /* Example
            #  *  Input: nums = [8,3,9,3,8], k = 2
            #  *  Output: 81
            #  *
            #  *  Input: nums = [19,12,14,6,10,18], k = 3
            #  *  Output: 4788
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.maximumScore(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
