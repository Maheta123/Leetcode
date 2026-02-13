class Solution:
    def longestBalanced(self, s: str) -> int:
        # --- helper: longest balanced substring with exactly two chars ---
        def longest_two_char_segment(start, end):
            parity_map = {0: start - 1}
            balance = 0
            best = 0
            last_char = -1
            sign = -1

            for i in range(start, end):
                v = ord(s[i]) - ord('a')

                # alternate sign when character switches
                if v != last_char:
                    last_char = v
                    sign *= -1

                balance += sign

                if balance in parity_map:
                    best = max(best, i - parity_map[balance])
                else:
                    parity_map[balance] = i

            return best

        # --- prefix-difference tracking for 3-character balance ---
        diff_map = {(0, 0, 0): -1}
        counts = [0, 0, 0]

        # track last occurrences for single / two-character runs
        last_char_info = [-1, -1]
        two_char_pair = [-1, -1]
        two_char_start = 0

        best = 0
        base = ord('a')

        for i, ch in enumerate(s):
            v = ord(ch) - base
            counts[v] += 1

            # normalize counts by subtracting minimum
            m = min(counts)
            if m > 0:
                counts = [c - m for c in counts]

            key = tuple(counts)

            # 3-character balanced substring
            if key in diff_map:
                best = max(best, i - diff_map[key])
            else:
                diff_map[key] = i

            # single-character or two-character handling
            if v != last_char_info[0]:
                best = max(best, i - last_char_info[1])

                if v not in two_char_pair:
                    two_char_pair = [last_char_info[0], v]

                    if i - two_char_start > best:
                        best = max(best,
                                   longest_two_char_segment(two_char_start, i))

                    two_char_start = last_char_info[1]

                last_char_info = [v, i]

        # final checks
        best = max(best, longest_two_char_segment(two_char_start, len(s)))
        best = max(best, len(s) - last_char_info[1])

        return best