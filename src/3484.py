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


class Spreadsheet:
    def __init__(self, rows: int):
        self.cell_values = {}

    def setCell(self, cell: str, value: int) -> None:
        self.cell_values[cell] = value

    def resetCell(self, cell: str) -> None:
        if cell in self.cell_values:
            del self.cell_values[cell]

    def getValue(self, formula: str) -> int:
        retVal = 0

        i = formula.find('+')
        cell1 = formula[1:i]
        cell2 = formula[i + 1:]
        val1 = self.cell_values.get(cell1, 0) if cell1[0].isalpha() else int(cell1)
        val2 = self.cell_values.get(cell2, 0) if cell2[0].isalpha() else int(cell2)
        retVal = val1 + val2

        return retVal

# Your Spreadsheet object will be instantiated and called as such:
# obj = Spreadsheet(rows)
# obj.setCell(cell,value)
# obj.resetCell(cell)
# param_3 = obj.getValue(formula)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip(
            [["Spreadsheet", "getValue", "setCell", "getValue", "setCell", "getValue", "resetCell", "getValue"]],
            [[[3], ["=5+7"], ["A1", 10], ["=A1+6"], ["B2", 15], ["=A1+B2"], ["A1"], ["=A1+B2"]]]
        ):
            # /* Example
            #  *  Input:
            #  *  ["Spreadsheet", "getValue", "setCell", "getValue", "setCell", "getValue", "resetCell", "getValue"]
            #  *  [[3], ["=5+7"], ["A1", 10], ["=A1+6"], ["B2", 15], ["=A1+B2"], ["A1"], ["=A1+B2"]]
            #  *  Output:
            #  *  [null, 12, null, 16, null, 25, null, 15]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "Spreadsheet":
                    obj = Spreadsheet(value)
                    displayStr.append(None)
                elif key == "getValue":
                    retVal = obj.getValue(value[0])
                    displayStr.append(retVal)
                elif key == "setCell":
                    obj.setCell(value[0], value[1])
                    displayStr.append(None)
                elif key == "resetCell":
                    retVal = obj.resetCell(value[0])
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

        print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

        sys.exit(0)
