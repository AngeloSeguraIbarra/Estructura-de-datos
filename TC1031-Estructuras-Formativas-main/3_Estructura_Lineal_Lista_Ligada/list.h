#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

template <class T> class List;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T value;
	Link<T> *next;

	friend class List<T>;
};

template <class T>
Link<T>::Link(T val): value(val), next(0){}

template <class T>
Link<T>::Link(T val, Link *nxt): value(val), next(nxt){}

template <class T>
Link<T>::Link(const Link<T> &source): value(source.value), next(source.next){}


template<class T>
class List{
    private:
	    Link<T> *head;
	    int 	size;
    public:
	    List();
        void clear();
        std::string toString()const;
        void insertion(T);
        int search(T);
        void update(T,T);
        void deleteAt(T);
};

template<class T>
List<T>::List():head(0), size(0){}

template<class T>
void List<T>::insertion(T val){
    Link<T> *nuevo= new Link<T>(val);
    if(head==0){
        nuevo->next=head;
    head=nuevo;
    size++;
    }
    else{
        Link<T> *p;
        p=head;
        while(p->next!=0){
            p=p->next;
        }
        nuevo->next=0;
        p->next=nuevo;
        size++;
    }
}

template<class T>
int List<T>::search(T val){
    int pos=0;
    Link<T> *p=head;
    while(p!=0){
        if(p->value==val){
            return pos;
        }
        p=p->next;
        pos++;
    }
    return -1;
}

template<class T>
void List<T>::update(T index,T val){
    int pos=0;
    Link<T> *p;
    p=head;
    while(pos!=index){
        p=p->next;
        pos++;
    }
    p->value=val;
}

template<class T>
void List<T>::deleteAt(T index){
    if(index==0){
        Link<T> *temp=head;
        head=temp->next;
        delete temp;
        return;
    }

    Link<T> *p=head;
    int pos=0;
    while(p!=nullptr && pos<index-1){ // llegamos a un indice anterior del que queremos eliminar
        p=p->next;
        pos++;
    }
    Link<T> *todelate = p->next;    // adelantamos al nodo que queremos eliminar 
    p->next=todelate->next;        // hacemos que el puntero salte el nodo que se va a eliminar 
    delete todelate;
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

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

#endif