#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Para std::min
using namespace std;

// Clase base abstracta para operaciones
template <typename T>
class Operacion {
public:
    virtual T ejecutar(T a, T b) = 0;
    virtual ~Operacion() {}
};

// Operaciones concretas para números
template <typename T>
class Suma : public Operacion<T> {
public:
    T ejecutar(T a, T b) override { return a + b; }
};

template <typename T>
class Resta : public Operacion<T> {
public:
    T ejecutar(T a, T b) override { return a - b; }
};

template <typename T>
class Multiplicacion : public Operacion<T> {
public:
    T ejecutar(T a, T b) override { return a * b; }
};

template <typename T>
class Division : public Operacion<T> {
public:
    T ejecutar(T a, T b) override {
        if (b == 0) throw runtime_error("Division por cero");
        return a / b;
    }
};

// Especialización para strings
template <>
class Suma<string> : public Operacion<string> {
public:
    string ejecutar(string a, string b) override { return a + b; }
};

// Especialización para vectores
template <typename T>
class Suma<vector<T>> : public Operacion<vector<T>> {
public:
    vector<T> ejecutar(vector<T> a, vector<T> b) override {
        vector<T> resultado;
        for (size_t i = 0; i < min(a.size(), b.size()); ++i) {
            resultado.push_back(a[i] + b[i]);
        }
        return resultado;
    }
};

template <typename T>
class Resta<vector<T>> : public Operacion<vector<T>> {
public:
    vector<T> ejecutar(vector<T> a, vector<T> b) override {
        vector<T> resultado;
        for (size_t i = 0; i < min(a.size(), b.size()); ++i) {
            resultado.push_back(a[i] - b[i]);
        }
        return resultado;
    }
};

template <typename T>
class Multiplicacion<vector<T>> : public Operacion<vector<T>> {
public:
    vector<T> ejecutar(vector<T> a, vector<T> b) override {
        vector<T> resultado;
        for (size_t i = 0; i < min(a.size(), b.size()); ++i) {
            resultado.push_back(a[i] * b[i]);
        }
        return resultado;
    }
};

template <typename T>
class Division<vector<T>> : public Operacion<vector<T>> {  // Corregido el nombre de la clase
public:
    vector<T> ejecutar(vector<T> a, vector<T> b) override {
        vector<T> resultado;
        for (size_t i = 0; i < min(a.size(), b.size()); ++i) {
            if (b[i] == 0) throw runtime_error("Division por cero en elemento del vector");
            resultado.push_back(a[i] / b[i]);
        }
        return resultado;
    }
};

// Especialización para matrices (vectores de vectores)
template <typename T>
class Suma<vector<vector<T>>> : public Operacion<vector<vector<T>>> {
public:
    vector<vector<T>> ejecutar(vector<vector<T>> a, vector<vector<T>> b) override {
        if (a.size() != b.size() || a[0].size() != b[0].size()) {
            throw runtime_error("Las matrices deben tener las mismas dimensiones");
        }
        
        vector<vector<T>> resultado(a.size(), vector<T>(a[0].size()));
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < a[0].size(); ++j) {
                resultado[i][j] = a[i][j] + b[i][j];
            }
        }
        return resultado;
    }
};

template <typename T>
class Resta<vector<vector<T>>> : public Operacion<vector<vector<T>>> {
public:
    vector<vector<T>> ejecutar(vector<vector<T>> a, vector<vector<T>> b) override {
        if (a.size() != b.size() || a[0].size() != b[0].size()) {
            throw runtime_error("Las matrices deben tener las mismas dimensiones");
        }
        
        vector<vector<T>> resultado(a.size(), vector<T>(a[0].size()));
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < a[0].size(); ++j) {
                resultado[i][j] = a[i][j] - b[i][j];
            }
        }
        return resultado;
    }
};

template <typename T>
class Multiplicacion<vector<vector<T>>> : public Operacion<vector<vector<T>>> {
public:
    vector<vector<T>> ejecutar(vector<vector<T>> a, vector<vector<T>> b) override {
        if (a.size() != b.size() || a[0].size() != b[0].size()) {
            throw runtime_error("Las matrices deben tener las mismas dimensiones");
        }
        
        vector<vector<T>> resultado(a.size(), vector<T>(a[0].size()));
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < a[0].size(); ++j) {
                resultado[i][j] = a[i][j] * b[i][j];
            }
        }
        return resultado;
    }
};

template <typename T>
class Division<vector<vector<T>>> : public Operacion<vector<vector<T>>> {
public:
    vector<vector<T>> ejecutar(vector<vector<T>> a, vector<vector<T>> b) override {
        if (a.size() != b.size() || a[0].size() != b[0].size()) {
            throw runtime_error("Las matrices deben tener las mismas dimensiones");
        }
        
        vector<vector<T>> resultado(a.size(), vector<T>(a[0].size()));
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < a[0].size(); ++j) {
                if (b[i][j] == 0) throw runtime_error("Division por cero en elemento de matriz");
                resultado[i][j] = a[i][j] / b[i][j];
            }
        }
        return resultado;
    }
};

// Función para mostrar un vector
template <typename T>
void mostrarVector(const vector<T>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i != vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

// Función para mostrar una matriz
template <typename T>
void mostrarMatriz(const vector<vector<T>>& mat) {
    cout << "[\n";
    for (const auto& fila : mat) {
        cout << "  ";
        mostrarVector(fila);
        cout << "\n";
    }
    cout << "]";
}

// Función principal con menú
int main() {
    int tipoDato;
    cout << "Seleccione el tipo de dato:\n";
    cout << "1. Numeros\n2. Strings\n3. Vectores\n4. Matrices\n";
    cout << "Opcion: ";
    cin >> tipoDato;
    
    int operacion;
    cout << "Seleccione la operacion:\n";
    cout << "1. Suma\n2. Resta\n3. Multiplicacion\n4. Division\n";
    cout << "Opcion: ";
    cin >> operacion;
    
    try {
        switch (tipoDato) {
            case 1: { // Numeros
                int num1, num2;
                cout << "Ingrese el primer numero: ";
                cin >> num1;
                cout << "Ingrese el segundo numero: ";
                cin >> num2;
                
                Operacion<int>* op = nullptr;
                switch (operacion) {
                    case 1: op = new Suma<int>(); break;
                    case 2: op = new Resta<int>(); break;
                    case 3: op = new Multiplicacion<int>(); break;
                    case 4: op = new Division<int>(); break;
                    default: throw runtime_error("Operacion no valida");
                }
                
                cout << "Resultado: " << op->ejecutar(num1, num2) << endl;
                delete op;
                break;
            }
            case 2: { // Strings
                string str1, str2;
                cout << "Ingrese el primer string: ";
                cin.ignore();
                getline(cin, str1);
                cout << "Ingrese el segundo string: ";
                getline(cin, str2);
                
                Operacion<string>* op = nullptr;
                switch (operacion) {
                    case 1: op = new Suma<string>(); break;
                    default: throw runtime_error("Solo suma esta implementada para strings");
                }
                
                cout << "Resultado: " << op->ejecutar(str1, str2) << endl;
                delete op;
                break;
            }
            case 3: { // Vectores
                int n;
                cout << "Tamaño de los vectores: ";
                cin >> n;
                
                vector<int> vec1(n), vec2(n);
                cout << "Ingrese el primer vector (separado por espacios): ";
                for (int i = 0; i < n; ++i) cin >> vec1[i];
                cout << "Ingrese el segundo vector (separado por espacios): ";
                for (int i = 0; i < n; ++i) cin >> vec2[i];
                
                Operacion<vector<int>>* op = nullptr;
                switch (operacion) {
                    case 1: op = new Suma<vector<int>>(); break;
                    case 2: op = new Resta<vector<int>>(); break;
                    case 3: op = new Multiplicacion<vector<int>>(); break;
                    case 4: op = new Division<vector<int>>(); break;
                    default: throw runtime_error("Operacion no valida");
                }
                
                cout << "Resultado: ";
                mostrarVector(op->ejecutar(vec1, vec2));
                cout << endl;
                delete op;
                break;
            }
            case 4: { // Matrices
                int filas, columnas;
                cout << "Filas de las matrices: ";
                cin >> filas;
                cout << "Columnas de las matrices: ";
                cin >> columnas;
                
                vector<vector<int>> mat1(filas, vector<int>(columnas));
                vector<vector<int>> mat2(filas, vector<int>(columnas));
                
                cout << "Ingrese la primera matriz (fila por fila):\n";
                for (int i = 0; i < filas; ++i) {
                    for (int j = 0; j < columnas; ++j) {
                        cin >> mat1[i][j];
                    }
                }
                
                cout << "Ingrese la segunda matriz (fila por fila):\n";
                for (int i = 0; i < filas; ++i) {
                    for (int j = 0; j < columnas; ++j) {
                        cin >> mat2[i][j];
                    }
                }
                
                Operacion<vector<vector<int>>>* op = nullptr;
                switch (operacion) {
                    case 1: op = new Suma<vector<vector<int>>>(); break;
                    case 2: op = new Resta<vector<vector<int>>>(); break;
                    case 3: op = new Multiplicacion<vector<vector<int>>>(); break;
                    case 4: op = new Division<vector<vector<int>>>(); break;
                    default: throw runtime_error("Operacion no valida");
                }
                
                cout << "Resultado:\n";
                mostrarMatriz(op->ejecutar(mat1, mat2));
                cout << endl;
                delete op;
                break;
            }
            default:
                throw runtime_error("Tipo de dato no valido");
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}