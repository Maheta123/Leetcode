class Solution(object):
    def countUnguarded(self, m, n, guards, walls):
        """
        :type m: int
        :type n: int
        :type guards: List[List[int]]
        :type walls: List[List[int]]
        :rtype: int
        """
        # Faster grid creation
        arr = [[1] * n for _ in range(m)]

        # Mark walls
        for row, col in walls:
            arr[row][col] = -1

        # Mark guards
        for row, col in guards:
            arr[row][col] = -2   # use -2 for guards so they also block vision

        # Process each guard (your structure stays the same)
        for row, col in guards:

            # UP
            temp_row = row - 1
            while temp_row >= 0 and arr[temp_row][col] != -1 and arr[temp_row][col] != -2:
                if arr[temp_row][col] == 1:  # only mark if still unguarded
                    arr[temp_row][col] = 0
                temp_row -= 1

            # DOWN
            temp_row = row + 1
            while temp_row < m and arr[temp_row][col] != -1 and arr[temp_row][col] != -2:
                if arr[temp_row][col] == 1:
                    arr[temp_row][col] = 0
                temp_row += 1

            # LEFT
            temp_col = col - 1
            while temp_col >= 0 and arr[row][temp_col] != -1 and arr[row][temp_col] != -2:
                if arr[row][temp_col] == 1:
                    arr[row][temp_col] = 0
                temp_col -= 1

            # RIGHT
            temp_col = col + 1
            while temp_col < n and arr[row][temp_col] != -1 and arr[row][temp_col] != -2:
                if arr[row][temp_col] == 1:
                    arr[row][temp_col] = 0
                temp_col += 1

        # Count unguarded cells
        counter = 0
        for i in range(m):
            for j in range(n):
                if arr[i][j] == 1:
                    counter += 1

        return counter