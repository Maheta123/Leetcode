import bisect

class SegmentTree:
    def __init__(self, coords):
        self.n = len(coords) - 1
        self.xcoords = [float(x) for x in coords]
        self.coverCount = [0] * (4 * self.n)
        self.coveredLen = [0.0] * (4 * self.n)

    def clear(self):
        self.coverCount = [0] * (4 * self.n)
        self.coveredLen = [0.0] * (4 * self.n)

    def updateRange(self, idx, left, right, ql, qr, val):
        if ql > right or qr < left: return
        if ql <= left and right <= qr:
            self.coverCount[idx] += val
        else:
            mid = (left + right) // 2
            self.updateRange(idx << 1, left, mid, ql, qr, val)
            self.updateRange((idx << 1) + 1, mid + 1, right, ql, qr, val)
        self.coveredLen[idx] = (self.xcoords[right + 1] - self.xcoords[left]) if self.coverCount[idx] > 0 else (
            self.coveredLen[idx << 1] + self.coveredLen[(idx << 1) + 1] if left != right else 0.0
        )

    def update(self, xl, xr, val):
        if xl >= xr: return
        l = bisect.bisect_left(self.xcoords, float(xl))
        r = bisect.bisect_left(self.xcoords, float(xr))
        if l < r: self.updateRange(1, 0, self.n - 1, l, r - 1, val)

    def getCoveredLength(self):
        return self.coveredLen[1]

class Solution:
    def separateSquares(self, squares):
        """
        :type squares: List[List[int]]
        :rtype: float
        """
        events = []
        xvals = set()
        for x, y, l in squares:
            x2, y2 = x + l, y + l
            events.extend([(y, x, x2, +1), (y2, x, x2, -1)])
            xvals.update([x, x2])
        xvals = sorted(xvals)
        events.sort(key=lambda e: (e[0], e[3]))

        st = SegmentTree(xvals)
        totalArea = 0.0
        if events:
            st.update(events[0][1], events[0][2], events[0][3])
            coverage, prevY = st.getCoveredLength(), float(events[0][0])
            for y, x1, x2, typ in events[1:]:
                curY = float(y)
                totalArea += coverage * (curY - prevY)
                st.update(x1, x2, typ)
                coverage, prevY = st.getCoveredLength(), curY

        if abs(totalArea) < 1e-15:
            return float(min((sq[1] for sq in squares), default=0))

        halfArea = totalArea / 2.0
        st.clear()
        partialArea, prevY = 0.0, float(events[0][0]) if events else 0.0

        if events:
            st.update(events[0][1], events[0][2], events[0][3])
            coverage, prevY = st.getCoveredLength(), float(events[0][0])
            for y, x1, x2, typ in events[1:]:
                curY = float(y)
                segmentArea = coverage * (curY - prevY)
                if partialArea + segmentArea >= halfArea - 1e-15:
                    if abs(coverage) < 1e-15:
                        return prevY if abs(partialArea - halfArea) < 1e-9 else curY
                    else:
                        return prevY + (halfArea - partialArea) / coverage
                partialArea += segmentArea
                st.update(x1, x2, typ)
                coverage, prevY = st.getCoveredLength(), curY

        return prevY if events else 0.0