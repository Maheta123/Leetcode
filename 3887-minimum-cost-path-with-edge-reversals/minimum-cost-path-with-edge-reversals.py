class Solution:
    def minCost(self, n: int, edges: List[List[int]]) -> int:
        graph = [[] for _ in range(n)]
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, 2 * w))

        dist = [float("inf")] * n
        visited = [False] * n
        dist[0] = 0
        heap = [(0, 0)]
        while heap:
            cur_dist, u = heapq.heappop(heap)
            if u == n - 1:
                return cur_dist

            if visited[u]:
                continue
            visited[u] = True

            for v, w in graph[u]:
                new_dist = cur_dist + w
                if new_dist < dist[v]:
                    dist[v] = new_dist
                    heapq.heappush(heap, (new_dist, v))

        return -1
        # m = the number of edges
        # n = the number of vertices
        # time: O(n + mlogm)
        # space: O(n + m)