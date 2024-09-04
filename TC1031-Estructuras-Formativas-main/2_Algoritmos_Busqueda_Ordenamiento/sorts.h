#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
#include <list>

template <class T>
class Sorts {
private:
    void swap(std::vector<T>& v, int i, int j);
    void mergesplit(std::vector<T>&, std::vector<T>&, int, int);
    void copyarray(std::vector<T>&A, std::vector<T>&B, int, int);
    void mergearray(std::vector<T>&, std::vector<T>&, int, int, int);
public:
    void ordenaBurbuja(std::vector<T>&);
    void ordenaSeleccion(std::vector<T>&);
    int busqBinaria(const std::vector<T>&, T);
    int rec_aux(const std::vector<T>& v, int low, int high, T valor);
    int busqSecuencial(const std::vector<T>&, T);
    std::vector<T> ordenaMerge(std::vector<T>&);
};

template <class T>
void Sorts<T>::swap(std::vector<T>& v, int i, int j) {
    T aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T>& v) {
    int aux;
    for (int i = 0; i < v.size() - 1; i++) {
        aux = i;
        for (int j = i + 1; j < v.size(); j++) {
            if (v[j] < v[aux]) {
                aux = j;
            }
        }
        if (aux != i) {
            swap(v, i, aux);
        }
    }
}

template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T>& v) {
    for (int i = v.size() - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (v[j] > v[j + 1]) {
                swap(v, j, j + 1);
            }
        }
    }
}

template <class T>
void Sorts<T>::copyarray(std::vector<T>& A, std::vector<T>& B, int low, int high) {
    for (int i = low; i <= high; i++) {
        A[i] = B[i];
    }
}

template <class T>
void Sorts<T>::mergearray(std::vector<T>& A, std::vector<T>& B, int low, int mid, int high) {
    int i_ordenado = low;
	int i = low;
	int j = mid + 1;

	  while (i <= mid && j <= high) {
        if (A[i] <= A[j]) {
            B[i_ordenado] = A[i];
            i++;
        } else {
            B[i_ordenado] = A[j];
            j++;
        }
        i_ordenado++;
    }
		while (i <= mid) {
        B[i_ordenado] = A[i];
        i++;
        i_ordenado++;
    }
		while (j <= high) {
        B[i_ordenado] = A[j];
        j++;
        i_ordenado++;
    }
		copyarray(A, B, low, high);
}

template <class T>
void Sorts<T>::mergesplit(std::vector<T>& A, std::vector<T>& B, int low, int high) {
    if(low < high)
	{
		int mitad = (high + low) / 2;
		mergesplit(A,B,low,mitad);
		mergesplit(A,B,mitad + 1, high);
		mergearray(A,B,low, mitad,high);
	}
}

template <class T>
std::vector<T> Sorts<T>::ordenaMerge(std::vector<T>& source) {
	std::vector<T> tmp(source.size());

	mergesplit(source, tmp, 0, source.size() - 1);
	
	return source;
}


template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T>& v, T valor) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] ==valor) {
            return i;
        }
    }
    return -1; // No encontrado
}

template <class T>
int Sorts<T>::busqBinaria(const std::vector<T>& v, T valor) {
    return rec_aux(v, 0, v.size() - 1, valor);
}

template <class T>
int Sorts<T>::rec_aux(const std::vector<T>& v, int low, int high, T valor) {
    if (low > high) {
        return -1; // Caso base: no encontrado
    }

    int mid = low + (high - low) / 2; // Calcular el punto medio
    if (v[mid] == valor) {
        return mid;
    } else if (valor > v[mid]) {
        return rec_aux(v, mid + 1, high, valor);
    } else {
        return rec_aux(v, low, mid - 1, valor);
    }
}

#endif
