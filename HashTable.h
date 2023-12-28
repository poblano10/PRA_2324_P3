#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "/home/alumno.upv.es/atolcer/W/labPRA/PRA_2324_P1/ListLinked.h"  

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>* table;

	int h(std::string key){

        int sum = 0,i=0;
        while(key[i] != '\0'){
            sum += key[i];
            i++;
        }
        return sum % max;
        }


    public:

	HashTable(int size): n(0),max(size){

		table = new ListLinked<TableEntry<V>>[size];
	}
	~HashTable(){
		delete[] table;
	}
	int capacity(){

		return max;
	}

	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){

		out<<"HashTable [entries: "<<th.n<<", capacity:"<<th.max<<"]"<<std::endl;
		out<<"=============="<<std::endl;
		out<<std::endl;
		for(int i =0 ;i<th.max;i++){

			out<<"== Cubeta "<<i<<" =="<<std::endl;
			out<<std::endl;
			out<<"List => ["<<th.table[i]<<"]"<<std::endl;
			out<<std::endl;
		}
		return out;
	}

V operator[](std::string key){
		
	    V Value = search(key);
            return Value; 
            
            }
	 void insert(std::string key, V value )override{
	
       	     /*int indice = h(key);
       
            	for (int i =0;i<table[indice].size();i++) {
                	if (table[indice][i].key == key) {
                    		 throw std::runtime_error("La clave ya existe");
         			  } 	
                	}*/
                	
 		int indice = table[h(key)].search(key);
 		

                if(indice >= 0)
                        throw std::runtime_error("Ya introducido");    
                        
                                   	
                TableEntry new_table(key,value);
                table[h(key)].prepend(new_table);
                
                n++;
                
            	}

	 V search(std::string key)override{

       /* int indice = h(key);
	 V valor = -1;
       
            for (int i =0;i<table[indice].size();i++) {
                if (table[indice][i].key == key) {
                    	valor = table[indice][i].value ;
                    	break;
                }
            }
                if (valor == -1){
                	throw std::runtime_error("Clave no encontrada");}
                
                return valor;	
            }*/
            int indice = h(key);
		int pos = table[indice].search(key);

                if(pos < 0)
                        throw std::runtime_error("No encontrado");

                V aux = table[indice].get(pos).value;
                return aux;
	}
            
        
	 V remove(std::string key)override{
	
	
        int indice = h(key);
        V value= -1;
	for (int i =0;i<table[indice].size();i++){ 
       		if(table[indice][i].key == key){
       		value =	(table[indice].remove(i)).value;
       		n--;
       		break;
       		}
       	} 
           if (value == -1)
                throw std::runtime_error("Clave no encontrada");
                
      		
   	 
   	 return value;
  }
    
       int entries()override{
             return n;
	}
        
};



#endif
