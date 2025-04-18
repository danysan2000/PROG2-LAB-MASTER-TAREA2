class BitMatrix:
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        # Cada entero almacena 32 bits (depende de la plataforma)
        self.data = [0] * ((rows * cols + 31) // 32)
    
    def set(self, row, col, value):
        index = row * self.cols + col
        word = index // 32
        bit = index % 32
        if value:
            self.data[word] |= (1 << bit)
        else:
            self.data[word] &= ~(1 << bit)
    
    def get(self, row, col):
        index = row * self.cols + col
        word = index // 32
        bit = index % 32
        return (self.data[word] >> bit) & 1

