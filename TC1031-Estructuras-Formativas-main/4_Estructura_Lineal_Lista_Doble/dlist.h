/**Angelo Segura Ibarra
 * A01711723
 */

#ifndef DLIST_H_
#define DLIST_H_

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

template <class T> class DList;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}
template<class T>

class DList{
    private:
        DLink<T> *head;
        DLink<T> *tail;
        int size;
    public:
        DList();
        void insertion(T);
        std::string toStringForward()const;
        std::string toStringBackward() const;
        int search(T);
        void update(T,T);
        void deleteAt(T);

        bool empty() const;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template<class T>
void DList<T>::insertion(T val){
    DLink<T> *nuevo= new DLink<T>(val);
    if(empty()){
        head=nuevo;
        tail=nuevo;
    }
    else{
        tail->next=nuevo;
        nuevo->previous=tail;
        tail=nuevo;
    }
}

template <class T>
std::string DList<T>::toStringForward()const{
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward()const{
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != nullptr ) {
		aux << p->value;
		if (p->previous != nullptr) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

template <class T>
int DList<T>::search(T val) {
    DLink<T> *p = head;
    int index = 0;
    while (p != nullptr) {
        if (p->value == val) {
            return index;
        }
        p = p->next;
        index++;
    }
    return -1;  // Valor no encontrado
}

template <class T>
void DList<T>::update(T index, T newVal) {
    DLink<T> *p = head;
	int pos=0;
	while (p != nullptr) {
        if (pos==index) {
            p->value=newVal;
        }
        p = p->next;
        pos++;
    }
}

template <class T>
void DList<T>::deleteAt(T index) {
    DLink<T> *temp=head;
	if(index==0){
        if(head==tail){
            delete head;
            head=tail=nullptr;
        }else{
            head=head->next;
            head->previous=nullptr;
            delete temp;
        }
        size--;
        return;
	}
	else if(index==size-1){
        temp=tail;
		tail=tail->previous;
        tail->next=nullptr;
        delete temp;
        size--;
        return;
	}

	int pos=0;
	while(pos<index){ // llegamos a un indice anterior del que queremos eliminar
		temp=temp->next;
        pos++;
	}
    temp->previous->next = temp->next;

  if (temp->next != nullptr) { // Solo actualizamos si no es el último
        temp->next->previous = temp->previous;
    }
    delete temp;
    size--;
}


template <class T>
bool DList<T>::empty() const {
	return (head == 0 && tail == 0);
}

#endif
