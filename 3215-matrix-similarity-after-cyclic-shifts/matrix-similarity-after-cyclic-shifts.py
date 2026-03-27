class Solution:
    def areSimilar(self, mat, k):
        m = len(mat)
        n = len(mat[0])
        
        shift = k % n
        
        if shift == 0:
            return True
        
        for i in range(m):
            row = mat[i]
            
            if i % 2 == 0:
                # even row → left shift
                shifted = row[shift:] + row[:shift]
            else:
                # odd row → right shift
                shifted = row[-shift:] + row[:-shift]
            
            if shifted != row:
                return False
        
        return True