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


class Bank:
    def __init__(self, balance: List[int]):
        self.balance = balance
        self.balanceSize = len(balance)

    def transfer(self, account1: int, account2: int, money: int) -> bool:
        retVal = False

        if (self.balanceSize < account1) or (self.balanceSize < account2):
            return retVal
        elif self.balance[account1-1] < money:
            return retVal

        self.balance[account1-1] -= money
        self.balance[account2-1] += money
        retVal = True

        return retVal

    def deposit(self, account: int, money: int) -> bool:
        retVal = False

        if (self.balanceSize < account):
            return retVal

        self.balance[account-1] += money
        retVal = True

        return retVal

    def withdraw(self, account: int, money: int) -> bool:
        retVal = False

        if (self.balanceSize < account):
            return retVal
        elif self.balance[account-1] < money:
            return retVal

        self.balance[account-1] -= money
        retVal = True

        return retVal

# Your Bank object will be instantiated and called as such:
# obj = Bank(balance)
# param_1 = obj.transfer(account1,account2,money)
# param_2 = obj.deposit(account,money)
# param_3 = obj.withdraw(account,money)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, values in [[
            ["Bank", "withdraw", "transfer", "deposit", "transfer", "withdraw"],
            [[[10, 100, 20, 50, 30]], [3, 10], [5, 1, 20], [5, 20], [3, 4, 15], [10, 50]]
        ]]:
            # /* Example
            #  *  Input
            #  *  ["Bank", "withdraw", "transfer", "deposit", "transfer", "withdraw"]
            #  *  [[[10, 100, 20, 50, 30]], [3, 10], [5, 1, 20], [5, 20], [3, 4, 15], [10, 50]]
            #  *  Output
            #  *  [null, true, true, true, false, false]
            #  */
            logging.info("%s", methods)
            logging.info("%s", values)

            displayStr = []
            for key, value in zip(methods, values):
                if key == "Bank":
                    obj = Bank(value[0])
                    displayStr.append(None)
                elif key == "withdraw":
                    retVal = obj.withdraw(value[0], value[1])
                    displayStr.append(retVal)
                elif key == "transfer":
                    retVal = obj.transfer(value[0], value[1], value[2])
                    displayStr.append(retVal)
                elif key == "deposit":
                    retVal = obj.deposit(value[0], value[1])
                    displayStr.append(retVal)
            logging.info("Output")
            logging.info("%s", displayStr)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
