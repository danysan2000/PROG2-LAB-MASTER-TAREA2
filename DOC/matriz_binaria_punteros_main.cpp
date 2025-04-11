int main() {
    SparseBinaryMatrix mat(5, 5);
    
    mat.set(1, 2, true);  // Fila 1, Columna 2 = 1
    mat.set(3, 4, true);  // Fila 3, Columna 4 = 1
    mat.set(1, 2, false); // Fila 1, Columna 2 = 0
    
    std::cout << "Valor en (3,4): " << mat.get(3, 4) << std::endl;
    
    std::cout << "Matriz completa:" << std::endl;
    mat.print();
    
    return 0;
}


