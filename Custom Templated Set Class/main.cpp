#include <iostream>
#include <cassert>
#include "dSet.h"

/**
  @brief Struct vector2 che implement un vettore in 2D
*/
struct vector2
{
	int x;
	int y;

	vector2() : x(0), y(0)
	{}

	vector2(int x, int y) : x(x), y(y) 
	{}
};

/**
  @brief Funtore di confronto tra due tipi interi

  @return true se sono uguali e viceversa
*/
struct int_equal 
{
  bool operator()(int a, int b) const 
  {
  return a==b;
  }

};

/**
  @brief Funtore di confronto tra due tipi custom vector2

  @return true se sono uguali e viceversa
*/
struct vector2_equal 
{
  bool operator()(vector2 a, vector2 b) const {
  return a.x == b.x && a.y == b.y;}
  
};

/**
  @brief Funtore di confronto tra due tipi dSet

  @return true se sono uguali e viceversa
*/
struct set_equal 
{
	template <typename T>
  bool operator()(T a, T b) const 
  {
  return a==b;
  }

};

/**
  @brief Funtore predicato

  @return true se il valore passato è positivo
*/
struct is_positive {
  bool operator()(int a) const {
    return (a > 0);
  }
};

/**
  @brief overload di stream per il tipo custom vector2 

*/

std::ostream& operator<<(std::ostream& os, const vector2& p)
{
	std::cout << "x: " <<p.x<< " y: "<<p.y<<std::endl;
	return os;
}

/**
  @brief Test dei metodi fondamentali su interi
*/
void test_interi() 
{
	std::cout << "---Test del set su interi---" << std::endl;
	std::cout << "---Set con costruttore default---" << std::endl;
	dSet<int, int_equal> d;
	assert(d.get_size() == 0);
	assert(d.get_elements() == 0);
	std::cout << "Dimensione di d" << std::endl;
	std::cout << d.get_size() << std::endl;
	std::cout << "Elementi in d" << std::endl;
	std::cout << d.get_elements() << std::endl;
	std::cout << std::endl;

	std::cout << "---Set con costruttore secondario (solo size)---" << std::endl;
	dSet<int, int_equal> d1(10);
	assert(d1.get_size() == 10);
	assert(d1.get_elements() == 0);
	std::cout << "Dimensione di d" << std::endl;
	std::cout << d1.get_size() << std::endl;
	std::cout << "Elementi in d" << std::endl;
	std::cout << d1.get_elements() << std::endl;
	std::cout << std::endl;

	std::cout << "---Test add e remove---" << std::endl;
	
	bool added = d.add(2);//aggiunge elementi nuovi a d
	added = d.add(10);
	added = d.add(78);
	added = d.add(-12);
	assert(added == true);
	bool not_added = d.add(10);//aggiunge elemento già presente in d e fallisce
	assert(not_added == false);
	bool removed = d.remove(78);//elimina elemento presente in d, fa resize da 4 a 3
	assert(removed == true);
	bool not_removed = d.remove(500);//prova ad eliminare elemento non presente in d e fallisce, non fa resize
	assert(not_removed == false);

	std::cout << "Elementi presenti in d" << std::endl;
	std::cout << d.get_elements() << std::endl;
	assert(d.get_elements() == 3);

	std::cout << "Dimensione massima di d:" << std::endl;
  	std::cout << d.get_size() << std::endl;
  	assert(d.get_size() == 3);
  
  	std::cout << "Stampa di d dopo le modifiche:" << std::endl;
  	std::cout << d << std::endl;
	

	bool added1 = d1.add(24);//aggiunge elementi nuovi a d1
	added1 = d1.add(10);
	added1 = d1.add(739);
	added1 = d1.add(-12);
	assert(added1 == true);
	
	std::cout << "---Test concatenazione---" << std::endl;
	dSet<int, int_equal> d2;
	d2 = d+d1;//concatenazione di due set, copia tutti i valori di d e d1 ma non li duplica(es. 10 e -12)
	std::cout << "Elementi presenti in d2" << std::endl;
	std::cout << d2.get_elements() << std::endl;
	assert(d2.get_elements() == 5);

	std::cout << "Dimensione massima di d2:" << std::endl;
  	std::cout << d2.get_size() << std::endl;
  	assert(d2.get_size() == 5);
  
  	std::cout << "Stampa di d2 dopo le modifiche di concatenazione:" << std::endl;
  	std::cout << d2 << std::endl;

  	std::cout << "---Test intersezione---" << std::endl;
	d2 = d-d1;//intersezione di due set, copia tutti i valori comuni di d e d1
	std::cout << "Elementi presenti in d2" << std::endl;
	std::cout << d2.get_elements() << std::endl;
	assert(d2.get_elements() == 2);

	std::cout << "Dimensione massima di d2:" << std::endl;
  	std::cout << d2.get_size() << std::endl;
  	assert(d2.get_size() == 2);
  
  	std::cout << "Stampa di d2 dopo le modifiche di intersezione:" << std::endl;
  	std::cout << d2 << std::endl;
	std::cout << std::endl;

}

/**
  @brief Test dei metodi fondamentali su tipi dSet
*/
void test_set() 
{
	std::cout << "---Test del dSet su elementi di tipo dSet---" <<std::endl;
	dSet <int, int_equal> d(4);
	d.add(1);
	d.add(15);
	d.add(67);
	d.add(-42);

	dSet<int, int_equal> d1(3);
	d1.add(18);
	d1.add(15);
	d1.add(90);

	dSet<int, int_equal> d2(6);
	d2.add(12);
	d2.add(111);
	d2.add(-84);
	d2.add(-42);
	d2.add(156);
	d2.add(1);

	dSet <int, int_equal> d3(4);//uguale a d per testare intersezione
	d3.add(1);
	d3.add(15);
	d3.add(67);
	d3.add(-42);

	dSet<dSet<int, int_equal>, set_equal > d4;
	std::cout << "---Stampa d4 dopo il costruttore di default---" << std::endl;
	d4.print();
	bool added = d4.add(d);
	added = d4.add(d1);
	added = d4.add(d2);
	assert(added == true);
	bool not_added = d4.add(d3);//Non aggiunge d4 poichè uguale 
	assert(not_added == false);
	bool removed = d4.remove(d2);//rimuove d2 perchè presente 
	assert(removed == true);
	std::cout << std::endl;

	dSet<dSet<int, int_equal>, set_equal > d5;
	std::cout << "---Stampa di d5 dopo il costruttore di default---" << std::endl;
	d5.print();
	bool added1 = d5.add(d2);
	assert(added1 == true);
	bool added2 = d5.add(d3);
	assert(added2 == true);
	std::cout << std::endl;

	std::cout << "---Stampa di d4 dopo le add e remove---" << std::endl;
	d4.print();
	std::cout << std::endl;
	std::cout << "---Stampa di d5 dopo le add e remove---" << std::endl;
	d5.print();
	std::cout << std::endl;

	dSet<dSet<int, int_equal>, set_equal > d6;
	std::cout << "---Test di d6 dopo il costruttore di default---" << std::endl;
	std::cout << "Elementi presenti in d6" << std::endl;
	std::cout << d6.get_elements() << std::endl;
	assert(d6.get_elements() == 0);

	std::cout << "Dimensione massima di d6:" << std::endl;
  	std::cout << d6.get_size() << std::endl;
  	assert(d6.get_size() == 0);
  
  	std::cout << "Stampa di d6 prima delle modifiche:" << std::endl;
  	d6.print();
  	std::cout << std::endl;

	d6 = d4+d5; //concatena gli elementi di d4 e d5 in d6(non copia il duplicato d3 poichè uguale a d)
	std::cout << "---Test di d6 dopo la concatenazione:---" << std::endl;
	std::cout << "Elementi presenti in d6" << std::endl;
	std::cout << d6.get_elements() << std::endl;
	assert(d6.get_elements() == 3);

	std::cout << "Dimensione massima di d6:" << std::endl;
  	std::cout << d6.get_size() << std::endl;
  	assert(d6.get_size() == 3);
  
  	std::cout << "Stampa di d6 dopo le modifiche di concatenazione:" << std::endl;
  	d6.print();
  	std::cout << std::endl;

	dSet<dSet<int, int_equal>, set_equal> d7 = d4-d5;//intersezione in d7 degli elementi di d4 e d5(cioè d3 in d5 poichè uguale a d in d4)
	std::cout << "---Test di d7 dopo l'intersezione:---" << std::endl;
	std::cout << "Elementi presenti in d7" << std::endl;
	std::cout << d7.get_elements() << std::endl;
	assert(d7.get_elements() == 1);

	std::cout << "Dimensione massima di d7:" << std::endl;
  	std::cout << d7.get_size() << std::endl;
  	assert(d7.get_size() == 1);
  
  	std::cout << "Stampa di d7 dopo le modifiche di intersezione:" << std::endl;
  	d7.print();
  	std::cout << std::endl;

}

/**
  @brief Test dei metodi fondamentali su interi const
*/
void test_const_interi() 
{
	dSet<int,int_equal> d;
	d.add(10);
	d.add(20);
	d.add(30);
	d.add(40);

	dSet<int,int_equal> d1;
	d1.add(10);
	d1.add(50);
	d1.add(60);
	d1.add(40);


	//add(), remove() e resize() non possono essere eseguite su un dSet const poichè ritorna lo stesso set modificato
	std::cout << "---Test del CONST set su interi---" << std::endl;
	std::cout << "---Test CONST concatenazione---" << std::endl;
	const dSet<int, int_equal> d2 = d+d1;//concatenazione di due set su un set const.
	
	std::cout << "Elementi presenti in d2" << std::endl;
	std::cout << d2.get_elements() << std::endl;
	assert(d2.get_elements() == 6);

	std::cout << "Dimensione massima di d2:" << std::endl;
  	std::cout << d2.get_size() << std::endl;
  	assert(d2.get_size() == 6);
  
  	std::cout << "Stampa di d2 dopo le modifiche di concatenazione:" << std::endl;
  	std::cout << d2 << std::endl;

  	std::cout << "---Test CONST intersezione---" << std::endl;
	const dSet<int, int_equal> d3 = d-d1;//intersezione di due set  su set const
	std::cout << "Elementi presenti in d3" << std::endl;
	std::cout << d3.get_elements() << std::endl;
	assert(d3.get_elements() == 2);

	std::cout << "Dimensione massima di d3:" << std::endl;
  	std::cout << d3.get_size() << std::endl;
  	assert(d3.get_size() == 2);
  
  	std::cout << "Stampa di d3 dopo le modifiche di intersezione:" << std::endl;
  	std::cout << d3 << std::endl;
	std::cout << std::endl;



}
/**
  @brief Test dei metodi fondamentali su tipo custom vector2
*/
void test_vector2_custom() 
{
	vector2 v1(10,27);
	vector2 v2(15,-9);
	vector2 v3(-60,-12);
	vector2 v4(-17,27);
	vector2 v6(10,27);//uguale a v1 per testare intersezione

	std::cout << "---Test set su tipi custom vector2---" << std::endl;
	dSet<vector2, vector2_equal> v5(4);
	std::cout << "---Stampa di v5 dopo costruttore secondario con size---" << std::endl;
	v5.print();
	assert(v5.get_size() == 4);
	assert(v5.get_elements() == 0);
	std::cout << std::endl;

	bool added = v5.add(v1);
	assert(added == true);
	added = v5.add(v2);
	added = v5.add(v3);
	assert(added == true);
	bool not_added = v5.add(v1);//fallisce perchè v1 è già presente e non sono accettati valori duplicati(utilizza il funtore vector2_equal)
	assert(not_added == false);
	bool removed = v5.remove(v3);
	assert(removed == true);
	bool not_removed = v5.remove(v4);//fallisce perchè v4 non è presente in v5
	assert(not_removed == false);
	assert(v5.get_size() == 2);//la remove chiama resize() con parametro elements per non occupare memoria inutilizzata dall'array
	assert(v5.get_elements() == 2);
	std::cout << "---Stampa di v5 dopo add e remove---" << std::endl;
	v5.print();
	std::cout << std::endl;

	dSet<vector2, vector2_equal> v7(2);
	v7.add(v4);
	v7.add(v6);
	dSet<vector2, vector2_equal> vf(2);

	std::cout << "---Test concatenazione di dSet con tipo vector2 custom---" << std::endl;
	vf = v7+v5;
	std::cout << "Elementi presenti in vf" << std::endl;
	std::cout << vf.get_elements() << std::endl;
	assert(vf.get_elements() == 3);

	std::cout << "Dimensione massima di vf:" << std::endl;
  	std::cout << vf.get_size() << std::endl;
  	assert(vf.get_size() == 3);
  
  	std::cout << "Stampa di vf dopo le modifiche di concatenazione:" << std::endl;
  	std::cout << vf << std::endl;
	std::cout << std::endl;

	std::cout << "---Test intersezione di dSet con tipo vector2 custom---" << std::endl;
	vf = v7-v5;
	std::cout << "Elementi presenti in vf" << std::endl;
	std::cout << vf.get_elements() << std::endl;
	assert(vf.get_elements() == 1);

	std::cout << "Dimensione massima di vf:" << std::endl;
  	std::cout << vf.get_size() << std::endl;
  	assert(vf.get_size() == 1);
  
  	std::cout << "Stampa di vf dopo le modifiche di concatenazione:" << std::endl;
	std::cout << vf << std::endl;

}
/**
  @brief Test del costruttore con iteratori
*/
void test_costruttore_iteratori() 
{
	std::cout<<"---Test del set con iteratori---"<<std::endl;
	int a[10] = {10,12,736,1,29,18,100,420,69,1000};
	dSet<int, int_equal> d(a,a+10); // costruttore con iteratori begin e en	
	std::cout << "---Stampa di d dopo il costruttore:---" << std::endl;
	std::cout << d << std::endl; 
	std::cout << "Dimensione massima di d:" << std::endl;	std::cout << d.get_size() << std::endl;
	assert(d.get_size() == 10);
	std::cout << "Elementi in d:" << std::endl;
	std::cout << d.get_elements() << std::endl;
	assert(d.get_elements() == 10);

	bool found = d.find_element(736);
	assert(found == true);

	bool not_found = d.find_element(99);
	assert(not_found == false);

	bool deleted = d.remove(1000);
	assert(deleted == true);

	bool deleted2 = d.remove(736);
	assert(deleted2 == true);

	bool not_deleted = d.remove(50);
	assert(not_deleted == false);

	std::cout << "Dimensione massima di d:" << std::endl;
	std::cout << d.get_size() << std::endl;
	assert(d.get_size() == 8);
  
	std::cout << "Elementi in d:" << std::endl;
	std::cout << d.get_elements() << std::endl;
	assert(d.get_elements() == 8);

	std::cout << "---Stampa di d dopo le modifiche:---" << std::endl;
	std::cout << d << std::endl;
}
/**
  @brief Test del metodo filter_out
*/
void test_filter_out_interi() {
    int arr[7] = {8,1,0,-1,-10,25,-7};
	dSet<int,int_equal> d(arr, arr+7);

    std::cout<<"---Test filter_out---"<<std::endl;

    std::cout<<"Stampa di d<<"<<std::endl;
    std::cout<< d << std::endl;
    is_positive p;

    std::cout<<"Stampa di d dopo le modifiche di filter_out"<<std::endl;
    d = filter_out(d,p);
    std::cout << d <<std::endl;
}

/**
Tutti i metodi fondamentali, tranne filter_out 
e il costruttore con iteratori
(che hanno i loro test dedicati), vengono testati
in ognuna delle funzioni di test. Ogni funzione
testa dSet inizializzati con elementi di tipo primitivo(int) 
di tipo dSet(a matriosca) e di tipo custom(vector2)
*/
int main(int argc, char* argv[]) 
{

	test_interi();

	test_const_interi();

	test_set();

	test_costruttore_iteratori();

	test_vector2_custom();

	test_filter_out_interi();
	

	return 0;
}