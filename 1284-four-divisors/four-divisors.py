from typing import List
import math

class Solution:
    def sumFourDivisors(self, nums: List[int]) -> int:
        def is_prime(x: int) -> bool:
            if x < 2:
                return False
            for i in range(2, int(math.sqrt(x)) + 1):
                if x % i == 0:
                    return False
            return True

        total = 0

        for n in nums:
            # Case 1: n = p^3
            p = round(n ** (1 / 3))
            if p ** 3 == n and is_prime(p):
                total += 1 + p + p * p + n
                continue

            # Case 2: n = p * q (p != q, both primes)
            for i in range(2, int(math.sqrt(n)) + 1):
                if n % i == 0:
                    j = n // i
                    if i != j and is_prime(i) and is_prime(j):
                        total += 1 + i + j + n
                    break

        return total
