from collections import defaultdict

class SparseMatrix:
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.data = defaultdict(bool)  # Solo almacena los 1s
    
    def set(self, row, col, value):
        if 0 <= row < self.rows and 0 <= col < self.cols:
            if value:
                self.data[(row, col)] = True
            else:
                self.data.pop((row, col), None)
    
    def get(self, row, col):
        return self.data.get((row, col), False)



