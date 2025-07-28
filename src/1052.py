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
    def maxSatisfied(self, customers: List[int], grumpy: List[int], minutes: int) -> int:
        retVal = 0

        # Calculate initial number of unrealized customers in first 'minutes' window
        unrealizedCustomers = 0
        for i in range(minutes):
            unrealizedCustomers += customers[i] * grumpy[i]
        maxUnrealizedCustomers = unrealizedCustomers

        # Slide the 'minutes' window across the rest of the customers array
        customersSize = len(customers)
        for i in range(minutes, customersSize):
            # Add current minute's unsatisfied customers if the owner is grumpy
            # and remove the customers that are out of the current window
            unrealizedCustomers += customers[i] * grumpy[i]
            unrealizedCustomers -= customers[i - minutes] * grumpy[i - minutes]

            # Update the maximum unrealized customers
            maxUnrealizedCustomers = max(maxUnrealizedCustomers, unrealizedCustomers)

        # Start with maximum possible satisfied customers due to secret technique
        totalCustomers = maxUnrealizedCustomers

        # Add the satisfied customers during non-grumpy minutes
        for i in range(customersSize):
            totalCustomers += customers[i] * (1 - grumpy[i])

        # Return the maximum number of satisfied customers
        retVal = totalCustomers

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for customers, grumpy, minutes in zip([[1, 0, 1, 2, 1, 1, 7, 5], [1]], [[0, 1, 0, 1, 0, 1, 0, 1], [0]], [3, 1]):
            # /* Example
            #  *  Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
            #  *  Output: 16
            #  *
            #  *  Input: customers = [1], grumpy = [0], minutes = 1
            #  *  Output: 1
            #  */
            logging.info("Input: customers = %s, grumpy = %s, minutes = %s", customers, grumpy, minutes)

            retVal = pSolution.maxSatisfied(customers, grumpy, minutes)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
