#include <iostream>
#include <vector>

class SparseBinaryMatrix {
private:
    int rows, cols;
    std::vector<std::vector<int>*> columns; // Punteros a vectores con índices de filas con valor 1

public:
    SparseBinaryMatrix(int r, int c) : rows(r), cols(c), columns(c, nullptr) {}
    
    ~SparseBinaryMatrix() {
        for (auto& col : columns) {
            delete col;
        }
    }

    void set(int row, int col, bool value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) return;
        
        if (columns[col] == nullptr) {
            columns[col] = new std::vector<int>();
        }
        
        auto& col_data = *columns[col];
        auto it = std::lower_bound(col_data.begin(), col_data.end(), row);
        
        if (value) {
            // Insertar el 1 si no existe
            if (it == col_data.end() || *it != row) {
                col_data.insert(it, row);
            }
        } else {
            // Eliminar el 1 si existe
            if (it != col_data.end() && *it == row) {
                col_data.erase(it);
            }
        }
        
        // Eliminar la columna si queda vacía
        if (col_data.empty()) {
            delete columns[col];
            columns[col] = nullptr;
        }
    }

    bool get(int row, int col) const {
        if (col < 0 || col >= cols || columns[col] == nullptr) return false;
        
        const auto& col_data = *columns[col];
        auto it = std::lower_bound(col_data.begin(), col_data.end(), row);
        
        return (it != col_data.end() && *it == row);
    }

    // Método para imprimir la matriz (para debugging)
    void print() const {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                std::cout << get(r, c) << " ";
            }
            std::cout << std::endl;
        }
    }
};


