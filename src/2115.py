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
    def findAllRecipes(self, recipes: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        retVal = []

        availableSupplies = set(supplies)  # Store available supplies
        dependencyGraph = defaultdict(list)  # Map ingredient to recipes that need it
        inDegree = [0] * len(recipes)  # Count of non-supply ingredients needed for each recipe
        # Build dependency graph
        for recipeIdx, ingredientList in enumerate(ingredients):
            for ingredient in ingredientList:
                if ingredient in availableSupplies:
                    continue
                dependencyGraph[ingredient].append(recipes[recipeIdx])
                inDegree[recipeIdx] += 1

        # Start with recipes that only need supplies
        queue = deque()
        for idx, count in enumerate(inDegree):
            if count == 0:
                queue.append(idx)

        # Map recipe to its index
        recipeToIndex = {recipe: idx for idx, recipe in enumerate(recipes)}

        # Process recipes in topological order
        while queue:
            recipeIdx = queue.popleft()
            recipe = recipes[recipeIdx]
            retVal.append(recipe)

            # Skip if no recipes depend on this one
            for dependentRecipe in dependencyGraph[recipe]:
                inDegree[recipeToIndex[dependentRecipe]] -= 1
                if inDegree[recipeToIndex[dependentRecipe]] == 0:
                    queue.append(recipeToIndex[dependentRecipe])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for recipes, ingredients, supplies in zip(
            [
                ["bread"],
                ["bread", "sandwich"],
                ["bread", "sandwich", "burger"]
            ],
            [
                [["yeast", "flour"]],
                [["yeast", "flour"], ["bread", "meat"]],
                [["yeast", "flour"], ["bread", "meat"], ["sandwich", "meat", "bread"]]
            ],
            [
                ["yeast", "flour", "corn"],
                ["yeast", "flour", "meat"],
                ["yeast", "flour", "meat"]
            ]
        ):
            # /* Example
            #  *  Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
            #  *  Output: ["bread"]
            #  *
            #  *  Input: recipes = ["bread","sandwich"],
            #  *  ingredients = [["yeast","flour"],["bread","meat"]],
            #  *  supplies = ["yeast","flour","meat"]
            #  *  Output:["bread","sandwich"]
            #  *
            #  *  Input: recipes = ["bread","sandwich","burger"],
            #  *  ingredients = [["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]],
            #  *  supplies = ["yeast","flour","meat"]
            #  *  Output: ["bread","sandwich","burger"]
            #  */
            logging.info("Input: recipes = %s, ingredients = %s, supplies = %s", recipes, ingredients, supplies)

            retVal = pSolution.findAllRecipes(recipes, ingredients, supplies)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
