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
    def countOfAtoms(self, formula: str) -> str:
        retVal = ""

        formulaSize = len(formula)

        stack = [defaultdict(int)]
        index = 0
        while index < formulaSize:
            if formula[index] == "(":
                # If left parenthesis, insert a new hashmap to the stack.
                # It will keep track of the atoms and their counts in the nested formula
                stack.append(defaultdict(int))
                index += 1
            elif formula[index] == ")":
                # If right parenthesis, pop the top element from the stack.
                # Multiply the count with the multiplicity of the nested formula
                currMap = stack.pop()

                index += 1
                multiplier = ""
                while (index < formulaSize) and (formula[index].isdigit()):
                    multiplier += formula[index]
                    index += 1
                if multiplier:
                    multiplier = int(multiplier)
                    for atom in currMap:
                        currMap[atom] *= multiplier

                for atom in currMap:
                    stack[-1][atom] += currMap[atom]
            else:
                # Otherwise, it must be a UPPERCASE LETTER. Extract the complete
                # atom with frequency, and update the most recent hashmap
                currAtom = formula[index]
                index += 1
                while (index < formulaSize) and (formula[index].islower()):
                    currAtom += formula[index]
                    index += 1

                currCount = ""
                while (index < formulaSize) and (formula[index].isdigit()):
                    currCount += formula[index]
                    index += 1

                if currCount == "":
                    stack[-1][currAtom] += 1
                else:
                    stack[-1][currAtom] += int(currCount)

        finalMap = dict(sorted(stack[0].items()))
        for atom in finalMap:
            retVal += atom
            if finalMap[atom] > 1:
                retVal += str(finalMap[atom])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for formula in ["H2O", "Mg(OH)2", "K4(ON(SO3)2)2"]:
            # /* Example
            #  *  Input: formula = "H2O"
            #  *  Output: "H2O"
            #  *
            #  *  Input: formula = "Mg(OH)2"
            #  *  Output: "H2MgO2"
            #  *
            #  *  Input: formula = "K4(ON(SO3)2)2"
            #  *  Output: "K4N2O14S4"
            #  */
            logging.info("Input: formula = \"%s\"", formula)

            retVal = pSolution.countOfAtoms(formula)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
