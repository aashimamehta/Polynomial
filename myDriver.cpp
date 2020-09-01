//Author : Aashima Mehta, CSS343 -Wooyoung Kim 
//Modified By: Aashima Mehta 
//Date Created: 6/28/2020
//Date of Last Modification: 7/04/2020
//-------------------------------------
//Topic of this assignment : Circular Doubly Linked List
//This program is a class for polynomials represented using 
//Circular Doubly Linked List. 


#include <iostream>
using namespace std;
#include "polynomial.h"

int main()

{
    cout << endl << "****************************************************************************** " << endl;
    cout << "This Driver will test all the polynomial methods implemented in polynomial.h " << endl;
    cout << endl << "****************************************************************************** " << endl;
    Polynomial p1;

    cout << endl << "p1 = " << p1 << endl;
    //create a circular doubly linked list

    //then you can do any modifications that you want to 
    cout << "After adding values in p1 using changeCoefficient we have " << endl;
    p1.changeCoefficient(1, 4);
    p1.changeCoefficient(5, 0);
    p1.changeCoefficient(4, 1);
    p1.changeCoefficient(2.2, 2);
    p1.changeCoefficient(-3.8, 3);

    cout << "p1 = " << p1 << endl;
    cout << "Get the size of p1 using getSize() >> " << p1.getSize() << endl;
    cout << "The degree of p1 using degree() >> " << p1.degree() << endl;
    p1.changeCoefficient(6, 4);
    cout << "Change the coefficient of the term with power 4 with 6 " << endl;
    cout << "p1 = " << p1 << endl;
    cout << "The coefficient of term with power 4 using coefficient(power) >> " << p1.coefficient(4) << endl;

    Polynomial poly;
    poly.changeCoefficient(1, 2);
    poly.changeCoefficient(3, 3);
    poly.changeCoefficient(4, 4);
    poly.changeCoefficient(3, 5);
    poly.changeCoefficient(4, 6);
    cout << endl << "poly = " << poly << endl;


    //using assingnment operator
    Polynomial poly2 = poly;
    cout << "Created poly2 from poly using = assignment " << endl;
    cout << "poly2 = " << poly2 << endl;
    cout << "Using != operator is poly2 and poly not equal? poly2 != poly >> " << (poly2 != poly) << endl << endl;

    ////using copy constructor operator
    cout << "Using copy constructor on p1 as --- p1(p2)" << endl;
    Polynomial p2(p1);
    cout << "Copied p1 to p2" << endl;
    cout << "p2 = " << p2 << endl;
    p2.changeCoefficient(9.5, 2);

    //Testing operators
    cout << "Change one term in p2 >> " << p2 << endl;;
    cout << "p1 == p2? " << (p1 == p2) << endl;

    //Arthimetic operators
    cout << endl << "Here we will test + operator ";
    Polynomial p3 = p2 + poly;
    cout << endl << "p3 = p2 + poly = " << p3 << endl;

    cout << "Here we will test - operator " << endl;
    Polynomial p5 = p2 - poly;
    cout << "p2 = " << p2 << endl;
    cout << "poly = " << poly << endl;
    cout << "p5 = p2 - poly = " << (p5) << endl;

    cout << endl << "Here we will test += operator " << endl;
    Polynomial k;
    k.changeCoefficient(0, 3);
    k.changeCoefficient(3, 2);
    k.changeCoefficient(5, 3);

    Polynomial p6;
    p6.changeCoefficient(0, 6);
    p6.changeCoefficient(3, 2);
    p6.changeCoefficient(4, 5);
    cout << "p6 = " << p6 << endl;
    cout << "k = " << k << endl;
    p6 += k;
    cout << "p6 += k  >> " << p6 << endl;

    cout << endl << "Here we will test -= operator " << endl;
    Polynomial p7;
    p7.changeCoefficient(4, 2);
    p7.changeCoefficient(3, 3);
    p7.changeCoefficient(5, 5);
    cout << "p7 = " << p7 << endl;
    cout << "k = " << k << endl;
    p7 -= k;
    cout << "p7 -= k  >> " << p7 << endl;

    cout << endl << "p3 = " << p3 << endl;
    cout << "Here we will test remove() method " << endl;
    cout << "Now delete p3 >> ";
    (p3.delHelper(p3));
    if (p3.getSize() == 0)
        cout << " Deletion successful " << endl;
    cout << p3 << endl;

    cout << endl << "****************************************************************************** " << endl;
    cout << "                End of driver -- Tested all methods " << endl;
    cout << endl << "****************************************************************************** " << endl;
}
