class ByteMatrix:
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.data = [0] * (rows * cols)
    
    def set(self, row, col, value):
        self.data[row * self.cols + col] = 1 if value else 0
    
    def get(self, row, col):
        return self.data[row * self.cols + col]


