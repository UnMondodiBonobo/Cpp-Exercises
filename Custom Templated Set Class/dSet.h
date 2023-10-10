#ifndef SET_H
#define SET_H

#include <iostream>
#include <utility>
#include <stddef.h>

/**
@brief Unordered set class

This class implements a generic set of elements of type T. 
Where m_size represents the maximum size of the set, 
m_elements the number of elements present inside the set, 
and m_set is a pointer to the actual array of elements. 
The functor Eql compares two values and returns true or false 
if the values are respectively equal or different from each other.
*/


template <typename T, typename Eql>

class dSet
{

public:
	typedef unsigned int size_type;
	typedef T value_type;
private:
	size_type m_size;
	size_type m_elements;
	value_type* m_set;
	Eql m_equals;

	

public:

	/**
	@brief Default Constructor

	@post m_size = 0
	@post m_elements = 0
	@post m_set = nullptr

	*/
	dSet(): m_size(0), m_set(nullptr), m_elements(0)
	{}

	/**
	Secondary constructor, elements is initialized to 0.
	
	    @param m_size maximum size of the set
	
	    @post m_size = size
	    @post m_set = new value_type[size]
	    @post m_elements = 0
	*/
	explicit dSet(size_type size):  m_size(0), m_set(nullptr), m_elements(0)
	{

		m_set = new value_type[size];
		m_size = size;

		
	}


	/**
	Copy constructor

	@param other Set to copy
	*/
	dSet(const dSet& other) :  m_size(0), m_set(nullptr), m_elements(0)
	{
		this->m_set = new value_type[other.m_size];
		try
		{
			size_type i = 0;
			while(i<other.m_size) 
			{
				this->m_set[i] = other.m_set[i];
				i++;
			}	
		}
		catch(...) 
		{
			clear();
			throw;
		}
		

		this->m_size = other.m_size;
		this->m_elements = other.m_elements;

		 
	}

	/**
	@brief Constructor with a pair of iterators
	
	Constructor that creates a dSet and adds elements taken from the
	beginning iterator that traverses the entire passed array.
	(It may call resize() if dSet has size = elements, and the exception
	is directly handled by resize())
	
	@param bg Beginning iterator
	@param ed End iterator
	*/

	template <typename Q>
	dSet(Q bg, Q ed) : m_size(0), m_elements(0), m_set(nullptr)
	{
		while(bg!=ed)
		{
			add(static_cast<T>(*bg));
			++bg;
		}
	}

	/**
	Operatore di assegnamento

	@param other Set da copiare
	@return reference al set modificato
	*/
	dSet& operator=(const dSet& other) 
	{
		//controllo se sono lo stesso oggetto
		if(this != &other) 
		{
			dSet tmp(other);
			tmp.swap(*this);
		}

		return *this;

	}

	/**
	Distruttore

	@post m_set = nullptr
	@post m_size = 0
	@post m_elements = 0
	*/
	~dSet(void) 
	{
		clear();

	}	

	/**
	
	Operatore di accesso solo lettura,ritorna una copia
	e non reference poichè non è un metodo di scrittura, l'assert previene 
	Undefined Behavior e non permette all'utente di accedere 
	ad un indice al di fuori del dSet. L'indice deve essere valido

	@param index indice dell'elemento scelto
	@return copia dell'elemento scelto
	*/
	value_type operator[](size_type index)
	{
		assert(index < m_size);
		return m_set[index];
			
		
	}

	/**
	
	Operatore di accesso solo lettura const, ritorna una copia
	e non reference poichè non è un metodo di scrittura, l'assert previene 
	Undefined Behavior e non permette all'utente di accedere 
	ad un indice al di fuori del dSet. L'indice deve essere valido


	@param index indice dell'elemento scelto
	@return copia dell'elemento scelto
	*/
	const value_type operator[](size_type index) const
	{
		assert(index < m_size);
		return m_set[index];
			
	}

	/**
	@brief Operatore di confronto tra due set
	usando il funtore Eql

	@param other set di confronto
	@return true se i due elementi sono uguali e viceversa
	*/
	bool operator==(const dSet& other) 
	{
		if(this->m_elements != other.m_elements)
		{
			return false;
		}

		size_type i = 0;
		while(i<m_elements) 
		{
			if(!m_equals(m_set[i], other.m_set[i]))
			{
				return false;
			}
			++i;
		}
		return true;
	}

	/**
	@brief Operatore di confronto tra due set const
	usando il funtore Eql

	@param other set di confronto
	@return true se i due elementi sono uguali e viceversa
	*/
	const bool operator==(const dSet& other) const
	{
		if(this->m_elements != other.m_elements) 
		{
			return false;
		}

		size_type i = 0;
		while(i<m_elements) 
		{
			if(!m_equals(m_set[i], other.m_set[i]))
			{
				return false;
			}
			++i;
		}
		return true;
	}

	/**
	@brief Svuota il dSet

	@post m_set = nullptr
	@post m_size = 0
	@post m_elements = 0
	*/
	void clear() 
	{
		delete[] m_set;
		m_set = nullptr;
		m_size = 0;
		m_elements = 0;
	}

	/**
	Metodo di aggiunta di un singolo elemento.
	Chiama resize() se size == elements. Chiama sempre
	find_element per verificare che l'elemento
	da inserire non sia già presente nel set

	@param element elemento da aggiungere
	@return true se l'aggiunta è avvenuta con successo, altrimenti false
	*/
	bool add(const value_type& element) 
	{
		if(find_element(element)) 
		{
			

			return false;
		}

		if(m_elements == m_size) 
		{	
			this->resize(m_size+1);
			m_set[m_elements] = element;
			m_elements = m_size;
		}

		else
		{
			m_set[m_elements] = element;
			++m_elements;
		}
		
		
		return true;


	}
	/**
	Metodo per la rimozione di un elemento dal set.
	Chiama sempre find_element per verificare che 
	l'elemento sia presente. Se viene rimosso l'elemento,
	viene chiamata resize() e setta size = elements per
	non sprecare spazio

	@param element elemento da rimuovere
	@return true se la rimozione è avvenuta con successo,
	altrimenti false
	*/
	bool remove(const value_type& element) 
	{
		if(this->find_element(element)) 
		{

			dSet tmp(m_size);
			size_type i = 0;
			while(i<m_elements) 
			{
				if(!m_equals(m_set[i], element))
				{
					tmp.add(m_set[i]);
					++i;
				}
				else{++i;}

			}
			*this = tmp;
			this->resize(m_elements);
			return true;
		}
		return false;
		
	}

	/**
	Metodo utilizzato per aumentare o diminuire la size del set.
	Crea un set temporaneo d'appoggio su cui salvare
	i vecchi dati se l'assegnamento della nuova size fallisce.
	Successivamente copia gli elementi del set temporaneo
	in quello originale. Non genera un nuovo set, ma modifica
	quello originale.

	@param new_size nuova size da assegnare al set

	@throw std::bad_alloc possibile eccezione di allocazione
	*/
	void resize(const size_type& new_size) 
	{
		
		dSet tmp(*this);

		delete[] this->m_set;
		this->m_set = nullptr;

		this->m_set = new value_type[new_size];
		try
		{
			size_type i = 0;
			while(i<m_elements) 
			{
				this->m_set[i] = tmp.m_set[i];
				++i;
			}	
		}
		catch(...) 
		{
			clear();
			throw;
		}
		this->m_size = new_size;
	}

	/**
	Metodo utilizzato per cercare un elemento già presente nell'array.

	@param element elemento da cercare

	@return true se l'elemento è presente, altrimenti false
	*/
	bool find_element(const value_type& element) 
	{
		size_type i = 0;
		while(i<m_elements) 
		{
			if(m_equals(m_set[i], element)) 
			{
				
				return true;
			}		
			++i;
		}

		
		return false;

	}

	/**
	Metodo pubblico utilizzato principalmente dalle funzioni globali

	@return size size del set
	*/
	size_type get_size() const 
	{
		return m_size;

	}

	/**
	Metodo pubblico utilizzato principalmente dalle funzioni globali

	@return elements numero di elementi nel set
	*/
	size_type get_elements() const 
	{
		return m_elements;
	}

	/**
	Metodo di swap tra i dati di un set

	@other set da cui prendere i dati

	@post m_set = other.m_set
	@post m_size = other.m_size
	@post m_elements = other.m_elements
	*/
	void swap(dSet& other)
	{
		std::swap(this->m_set, other.m_set);
		std::swap(this->m_size, other.m_size);
		std::swap(this->m_elements, other.m_elements);

	}

	/**
	Metodo alternativo all operatore << per la stampa di un set
	*/
	void print() const
	{
		std::cout << "SIZE: " << m_size << std::endl;
		std::cout << "ELEMENTS: " << m_elements << std::endl;
		size_type i = 0;
		while(i<m_elements) 
		{
			std::cout << m_set[i] << " ";
			i++;
		}

		std::cout << std::endl;

	}
	/**
	Metodo pubblico che  ritorna il risultato del funtore.
	Utilizzato unicamente dalle funzioni globali poichè sono funzioni globali
	non friend.

	@param a primo valore generico da confrontare
	@param b secondo valore generico da confrontare

	@return true se secondo il funtore custom sono uguali, altrimenti false
	*/
	bool is_equal(const value_type& a, const value_type& b) const
	{
		return m_equals(a, b);
	}


	class const_iterator {

	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                        value_type;
		typedef ptrdiff_t                difference_type;
		typedef const T* pointer;
		typedef const T& reference;


		const_iterator() :_ptr(nullptr) {
		}

		const_iterator(const const_iterator& other) : _ptr(other._ptr){
		}

		const_iterator& operator=(const const_iterator& other) {
			_ptr = other._ptr;
			return *this;
		}

		~const_iterator() {
		}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return *_ptr;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return _ptr;
		}

		// Operatore di accesso random
		reference operator[](int index) {
			return _ptr[index];
		}

		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			_ptr++;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
			_ptr++;
			return *this;

		}

		// Operatore di iterazione post-decremento
		const_iterator operator--(int) {
			const_iterator tmp(*this);
			_ptr--;
			return tmp;
		}

		// Operatore di iterazione pre-decremento
		const_iterator& operator--() {
			_ptr--;
			return *this;
		}

		// Spostamentio in avanti della posizione
		const_iterator operator+(int offset) {
			return (_ptr + offset);
		}

		// Spostamentio all'indietro della posizione
		const_iterator operator-(int offset) {
			return(_ptr - offset);
		}

		// Spostamentio in avanti della posizione
		const_iterator& operator+=(int offset) {
			_ptr += offset;
			return *this;
		}

		// Spostamentio all'indietro della posizione
		const_iterator& operator-=(int offset) {
			_ptr -= offset;
			return *this;
		}

		// Numero di elementi tra due iteratori
		difference_type operator-(const const_iterator& other) {
			return std::distance(_ptr, other._ptr);
		}

		// Uguaglianza
		bool operator==(const const_iterator& other) const {
			return (_ptr == other._ptr);
		}

		// Diversita'
		bool operator!=(const const_iterator& other) const {
			return (_ptr != other._ptr);
		}

		// Confronto
		bool operator>(const const_iterator& other) const {
			return (_ptr > other._ptr);
		}


		bool operator>=(const const_iterator& other) const {
			return (_ptr >= other._ptr);
		}

		// Confronto
		bool operator<(const const_iterator& other) const {
			return (_ptr < other._ptr);
		}


		// Confronto
		bool operator<=(const const_iterator& other) const {
			return (_ptr <= other._ptr);
		}

	private:

		friend class dSet;

		const_iterator(pointer ptr) {
			_ptr = ptr;
		}

		pointer _ptr;

	}; 

	/**
	Metodo che ritorna l'iteratore all'inizio della
	sequenza di dati

	@return copia dell'iteratore
	*/
	const_iterator begin() const {
		return const_iterator(m_set);
	}

	/**
	Metodo che ritorna l'iteratore alla fine della
	sequenza di dati

	@return copia dell'iteratore
	*/
	const_iterator end() const {
		return const_iterator(m_set + m_size);
	}
};

/**
Funzione GLOBALE che fa overload dell'operatore di stream.
Non è friend quindi vengono chiamati i metodi pubblici

@param os stream di output
@param d set da inviare allo stream

@return stream di output  
*/

template <typename T, typename Eql>
std::ostream& operator<<(std::ostream& os, const dSet<T,Eql>& d) 
{
	os << "Max size: " << d.get_size() << std::endl;
	os << "Numero di elementi: " << d.get_elements() << std::endl;
	typename dSet<T, Eql>::size_type i = 0;
	os<< "Elementi: ";
	while(i<d.get_elements()) 
	{
		os << " " << d[i];
		i++;
	}

	os << std::endl;
	return os;
}

/**
Funzione GLOBALE che fa overload dell'operatore + 
e ritorna una copia del nuovo set che contiene gli elementi
del primo set e del secondo set. Non contiene duplicati.
Non è friend quindi vengono chiamati i metodi pubblici

@param left primo set di cui si vogliono copiare gli elementi
@param right secondo set di cui si vogliono copiare gli elementi

@return set copia contenente tutti gli elementi di left e right(non duplicati)
*/
template <typename T, typename Eql>
dSet<T, Eql> operator+(const dSet<T, Eql>& left, const dSet<T, Eql>& right) 
{
	typename dSet<T, Eql>::size_type new_size = left.get_size()+right.get_size();
	typename dSet<T, Eql>::size_type i = 0;
	dSet<T, Eql> new_set(new_size);
	while(i<left.get_elements()) 
	{
		new_set.add(left[i]);
		++i;
	}
	i = 0;
	while(i<right.get_elements()) 
	{
		new_set.add(right[i]);
		++i;
	}
	new_set.resize(new_set.get_elements());
	return new_set;
}

/**
Funzione GLOBALE che fa overload dell'operatore - 
e ritorna una copia del nuovo set che contiene gli elementi
in comune del primo set e del secondo set. Non contiene duplicati.
Non è friend quindi vengono chiamati i metodi pubblici

@param left primo set di cui si vogliono confrontare gli elementi
@param right secondo set di cui si vogliono confrontare gli elementi

@return set copia contenente l'intersezione di 
tutti gli elementi di left e right(non duplicati)
*/
template <typename T, typename Eql>
dSet<T, Eql> operator-(const dSet<T, Eql>& left, const dSet<T, Eql>& right) 
{
	typename dSet<T, Eql>::size_type new_size = 0;
	left.get_size() < right.get_size() ? new_size = left.get_size() : new_size = right.get_size();
	typename dSet<T, Eql>::size_type i = 0;
	typename dSet<T, Eql>::size_type j = 0;
	dSet<T, Eql> new_set(new_size);
	while (i < left.get_elements()) 
	{
		while (j < right.get_elements()) 
		{
			if (new_set.is_equal(left[i], right[j]))
			{
				new_set.add(left[i]);
				j = right.get_elements();
			}			
			++j;
		}
		j = 0;
		++i;
	}
	new_set.resize(new_set.get_elements());
	return new_set;

}

/**
Funzione GLOBALE filter_out che ritorna un nuovo set
contenente gli elementi del set originale che soddisfano un 
predicato generico di tipo P. 


@param d set di cui si vogliono controllare gli elementi
@param pr predicato 

@return set copia che contiene gli elementi che soddisfano il predicato pr
*/
template <typename T, typename Eql, typename P>
dSet<T,Eql> filter_out(const dSet<T,Eql>& d, P pr) 
{
	typename dSet<T,Eql>::const_iterator bg, ed;
	bg = d.begin(); 
	ed = d.end();
	dSet<T, Eql> new_set(d.get_size());
	while(bg != ed) 
	{
		if(pr(*bg)) 
		{
			new_set.add(*bg);
		}
		++bg;
	}
	new_set.resize(new_set.get_elements());
	return new_set;
}


#endif
