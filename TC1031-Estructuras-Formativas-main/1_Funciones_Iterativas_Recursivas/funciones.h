/*
 * funciones.h
 *
 *  Created on: 13/08/2024
 *      Author: Angelo Segura Ibarra
 */


#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>
using namespace std;

class Funciones{
    public:

        long int sumaDirecta(int n)
        {   
          return (n*(n+1)/2);
        }

        long int sumaIterativa(int n)
        {
          long int sum=0;
          for(int i=0;i<=n;i++)
          {
            sum=sum+i;
          }  
          return sum;
        }

        long int sumaRecursiva(int n)
        {
          long int sum=0;
          if(n<=0)
          {
            return 0;    //caso base 
          }
          else
          {
            return(n+sumaRecursiva(n-1));
          }  
        }

};


#endif