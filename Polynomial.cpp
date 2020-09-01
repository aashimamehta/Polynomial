//Author : Aashima Mehta CSS343 
//Date Created: 6/28/2020
//Date of Last Modification: 7/04/2020
//-------------------------------------
//Topic of this assignment : Circular Doubly Linked List
//This program is a class for polynomials represented using 
//Circular Doubly Linked List. 

#include "polynomial.h"
#include "math.h"
#include <iostream>
using namespace std;

//Constructor: default constructor for polynomial class
//preconditions: head is unassigned and the list doesnt exist
//postconditions: initialization of the circular dummy header
//  with power and coeff as zero
Polynomial::Polynomial() 
{
	head = new Term;
	head->coeff = 0.0;
	head->power = 0;
	//circular linkedlist therefore points towards itself
	head->next = head;
	head->prev = head;
	size = 0;
}
//end of default constructor

//deep copy constructor: copies the original list
//preconditions: The original list exists in the program
//postconditions: The method deep copies the original list
Polynomial::Polynomial(const Polynomial& p) 
{
	head = new Term;
	head->power = 0;
	head->coeff = 0.0;
	head->next = head; 
	head->prev = head;
	size = 0; 
	*this = p; //this will copy the linked list
}
//end of deep copy constructor

//destructor: destructs the Polynomial
//preconditions: Polynomial exists
//postconditions: Polynomial is successfully de-allocated from the 
//  memory.
Polynomial::~Polynomial() 
{ 
	delHelper(*this); //removes all nodes except head
	head = NULL; //removes head
	delete head;
}
//end of destructor

//degree(): returns the degree of the polynomial
//preconditions: the circular linked list exists
//postconditions: The highest degree of the polynomial
//  is returned.
int Polynomial::degree() const 
{
	if (head == NULL)
	{
		//cout << "The doubly linked list is NULL" << endl;
		return 0;
	}
	//Technically the highest degree is in the front
	if (head->next->power > head->power)
		return head->next->power;
	else
		return head->power;
}
//end of degree

//coefficient(const int power): returns the coeff of the power
//precondition: assumes that the power exists
//postconditions: returns the coeff if exists, else error
double Polynomial::coefficient(const int power) const 
{
	Term* cur = head;
	double val = 0.0;
	for(int i = 0; i < size; i++) 
	{
		if (cur->power == power) 
		{
			val = cur->coeff;
			break;
		}
		cur = cur->next;
	}
	if (val == 0.0) {
		cout << "Power not found! Try again." << endl;
	}
	return val;
}
//end of coefficient

//changeCoefficient(newCoefficient, power): adds a new
//    polynomial to the linked list.
//preconditions: the newCoeff is non-zero value
//postconditions: inserts the new node or changes the 
//  exiting coeff accordingly.
bool Polynomial::changeCoefficient(const double newCoefficient, const int power)
{
	if (newCoefficient == 0) 
	{
		//check if the power in the list exists
		if (degree() >= power) {
			Term* cur = head->next;
			while (cur->next->power >= power)
			{
				cur = cur->next;
			}
			if (cur->power == power)
			{
				remove(cur);
			}
			cur = NULL;
			delete cur;
		}
		return true; //otherwise newCoeff can be neglected 0 * anything = 0
	}
	if (power == 0)
	//special case -- because dummy's power is zero too
	{
		Term* newnode = new Term;
		newnode->coeff = newCoefficient;
		newnode->power = power;
		if (size == 0)
		{
			head->next = newnode;
			head->prev = newnode;
			newnode->next = head;
			newnode->prev = head;
			size++;
		}
		else {
			Term* cur = head->next;
			while (cur->next != head)
			{
				cur = cur->next;
			}
			if (cur->power != 0) {
				newnode->next = head;
				newnode->prev = cur;
				cur->next = newnode;
				head->prev = newnode;
				size++;
			}
			else {
				cur->coeff = newCoefficient;
			}
		}
		return true;
	}
	else if (size == 0) 
	{
		insert(head, newCoefficient, power);
		return true;
	}
	else if (size == 1)
	{
		insert(head->next, newCoefficient, power);
		return true;
	}
	else
	{
		Term* cur = head->next;
		int i = 0; //iterate until the reached the correct position
		while (i < size || cur->next->power >= power)
		{
			i++;
			cur = cur->next;
		}
		if (cur->power == power)
		{
			cur->coeff = newCoefficient;
			return true;
		}
		if (cur->next->power == power)
		{
			cur->coeff = newCoefficient;
			return true;
		}
		return insert(cur->next, newCoefficient, power);
	}
}
// end of changeCoefficient

//insert(pos, newCoefficient, power): inserts a new node
//    or replaces a node in the doubly linked list
//preconditions: assumptions the node passed is where(before) the 
//	new node is supposed to go. Meaning the power and the position
//	in the doubly linked list provided is correct.
//postconditions: if the node with the same power exists then the
//  coeff gets replaced. If it doesnt then the new node gets added in the
//  circular linked list.
bool Polynomial::insert(Term* pos, const double newCoefficient, const int power)
{
	if (pos == NULL || head == NULL) //if NULL linked list
	{
		cout << "The pointer is NULL" << endl;
		return false;
	}
	else if (pos->power == power)
	{
		pos->coeff = newCoefficient;
		return true;
	}
	else if (pos->next->power == power)
	{
		pos->coeff = newCoefficient;
		return true;
	}
	else if (pos == head) //  if size is zero
	{
		Term* newnode = new Term;
		newnode->coeff = newCoefficient;
		newnode->power = power;
		size++;
		newnode->next = pos;
		newnode->prev = pos;
		pos->prev = newnode;
		pos->next = newnode;
		return true;
	}
	else if (pos == head->next) 
	{
		// check the correct position
		if (pos->power <= power)
		{
			//then simply add the newnode between head and pos
			Term* newnode = new Term;
			newnode->coeff = newCoefficient;
			newnode->power = power;
			size++;
			newnode->next = pos;
			newnode->prev = head;
			head->next = newnode;
			pos->prev = newnode;
		}
		else
		{
			//add the newnode after the pos // because the power is greater
			Term* newnode = new Term;
			newnode->coeff = newCoefficient;
			newnode->power = power;
			size++;
			newnode->next = pos;
			newnode->prev = pos;
			pos->next = newnode;
			pos->prev = newnode;
		}
		return true;
	}
	else
	{
		//assumptions that the node we are given is correct
		//the node should be placed before pos
		Term* newnode = new Term;
		newnode->coeff = newCoefficient;
		newnode->power = power;
		size++;
		//travese to find the term before pos in the list
		Term* before = head;
		while (before->next != pos)
			before = before->next;
		newnode->next = pos;
		newnode->prev = before;
		before->next = newnode;
		pos->prev = newnode;
		return true;
	}
	
	return true;
}
//end of insert

//remove(pos): removes the node that it is passed
//preconditions: The node is passed in the remove method that 
//   needs to be deleted
//postconditions: The node is deleted 
bool Polynomial::remove(Term* pos) 
{
	if (head == NULL || pos == NULL)
		return false;
	else if (pos == head)
	{
		if (size == 1)
		{
			head->next = head;
			head->prev = head;
			pos = NULL;
			delete pos;
		}
		else if (size == 2)
		{
			Term* cur = head->next;
			Term* save = head;
			head = head->next;
			head->next = head;
			head->prev = head;
			save = NULL;
			delete save;
		}
		else
		{
			//any other size
			Term* before = head->next;
			while (before->next != pos)
				before = before->next;
			//before is the prev node now
			Term* nextnode = pos->next;
			nextnode->prev = before;
			before->next = nextnode;
			pos = NULL;
			delete pos;
		}
		size--;
		return true;
	}
	else if (pos == head->next)
	{
		//before == head; after node -- doesnt matter
		Term* after = pos->next; //can be head or something else
		after->prev = head;
		head->next = after;
		pos = NULL;
		delete pos;// free(pos);
		size--;
		return true;
	}
	else 
	{
		Term* before = pos->prev;
		Term* after = pos->next;
		before->next = after;
		after->prev = before;
		size--;
		before = NULL;
		delete before;
		after = NULL;
		delete after;
		return true;
	}
}
//end of remove(pos)


// Arithmetic operators

//+ operator : is to add two polynomials together
//preconditions: the one that needs to be added is passed
//postconditions: the addition is made to the original one
Polynomial Polynomial::operator+(const Polynomial& p) const
{
	//need to make copies of the actual polynomials
	Polynomial sum(*this); 
	Polynomial p2(p);
	Term* cur; 
	Term* cur2 = p2.head->next; 
	bool found= false;

	while (cur2 != p2.head) { 
		found = false;
		cur = sum.head->next; 
		while (cur != sum.head) {
			if (cur2->power == cur->power) {
				sum.changeCoefficient(cur->coeff + cur2->coeff, cur->power); 
				found = true;
			}
			cur = cur->next;
		}
		//if the item hasnt been changed yet then found will be false
		//so you add the item using changeCoeff
		if (!found) {
			sum.changeCoefficient(cur2->coeff, cur2->power); 
		}
		cur2 = cur2->next;
	}
	return sum;
}
//end of + operator

//- operator : is to subtract two polynomials
//preconditions: the one that needs to be subtracted is passed
//postconditions: the subtraction is made to the original one
Polynomial Polynomial::operator-(const Polynomial& p) const 
{
	//convert all the poly terms so that we can use + operator for these
	Polynomial k(p);
	Term* cur = k.head->next;
	while (cur != k.head)
	{
		k.changeCoefficient((cur->coeff) * (-1), cur->power);
		cur = cur->next;
	}
	cur = NULL;
	delete cur;
	return ((*this + k));
}
//end of - operator

// Boolean comparison operators

//== operator : is to compare two polynomials together if they are equal
//preconditions: the one that needs to be compared is passed
//postconditions: the comparison is made with the original one
bool Polynomial::operator==(const Polynomial& p) const 
{
	if (p.size != size)
		return false;
	else
	{
		Term* cur = head->next; //for *this
		Term* cur2 = p.head->next; //for checking the other list
		while(cur->next != head)
		{
			if (cur->power != cur2->power || cur->coeff != cur2->coeff)
			{
				return false;
			}
			cur = cur->next;
			cur2 = cur2->next;
		}
		cur = NULL;
		delete cur;
		cur2 = NULL;
		delete cur2;
		return true;
	}
}
//end of == operator

//!= operator : is to compare two polynomials if they are equal
//preconditions: the one that needs to be added is passed
//postconditions: the addition is made to the original one
bool Polynomial::operator!=(const Polynomial& p) const
{
	return !(*this == p);
}
//end of != operator

// Assignment operators

//= operator : is to make original poly equal to the one passed
//preconditions: the one that needs to be assinged is passed
//     assumptions: the linked list passed is already in order
//postconditions: the assingment is made to the original one
Polynomial& Polynomial::operator=(const Polynomial& p) 
{
	if (p.size > 0) {
		Term* node = p.head->next;
		Term* cur = head;
		Term* tmp = head->next;
		while (node != p.head) {
			Term* newnode = new Term;
			newnode->coeff = node->coeff;
			newnode->power = node->power;
			if (cur == head) {
				cur->next = newnode;
				cur->prev = newnode;
				newnode->next = cur;
				newnode->prev = cur;
			}
			else if (cur == head->next) {
				Term* after = head->next;
				newnode->next = head;
				newnode->prev = after;
				after->next = newnode;
				head->prev = newnode;
			}
			else {
				Term* before = head->prev;
				before->next = newnode;
				head->prev = newnode;
				newnode->next = head;
				newnode->prev = before;
			}
			size++;
			cur = cur->next;
			node = node->next;
		}
		tmp = NULL;
		delete tmp;
		node = NULL;
		delete node;
		size = p.size;
	}
	return *this;
}
//end of = operator

//delHelper(): is to delete all the nodes in the Polynomial list
//preconditions: the list contains some nodes, i.e, size != 0
//postconditions: the list is free'd from the memory
void Polynomial::delHelper(const Polynomial& p) {
	Term* cur = p.head->next;
	while (cur->next != p.head)
	{
		//save the next node // and delete the current node
		Term* save = cur->next;
		remove(cur);
		cur = save; // traverse
	}
	//delete cur to not have memory leaks
	if (cur->next == p.head) {
		head->prev = head;
		head->next = head;
		size = 0;
		cur = NULL;
		delete cur;
	}
	cur = NULL;
	delete cur;
}
//end of delHelper()


//+= operator : is to add the passed polynomial with original
//preconditions: the one thatneeds to be added is passed
//postconditions: the addition is made to the original one
Polynomial& Polynomial::operator+=(const Polynomial& p) 
{
	//Polynomial sum;
	//sum = (*this + p);
	//return sum;
	return (*this = (*this + p));
}
//end of += operator

//-= operator : is to subtract polynomial from original
//preconditions: the one that needs to be dubtracted is passed
//postconditions: the subtraction is made to the original one
Polynomial& Polynomial::operator-=(const Polynomial& p)
{
	return (*this = (*this - p));
}
//end of -= operator

//getSize() - to get the size of the poly 
//preconditions: polynomial exists
//postconiditions: the correct size is returned of the poly
int Polynomial::getSize()
{
	return size;
}


//Stream I/O operators

//<< operator : is to print polynomials
//preconditions: the one that needs to be printed is passed
//postconditions: the output is in form
//            Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0

ostream& operator<<(ostream& ostr, const Polynomial& c)
{
	Polynomial::Term* node = c.head->next;
	for(int i = 0; i < c.size; i++)
	{ 
		if (node->coeff != 0)
		{
			//exception for coeff
			if (node->coeff < 0)
				ostr << node->coeff * (-1);
			else if (node->coeff  == -1)
				ostr <<"";
			else if (node->coeff != 1 && node->coeff != -1)
				ostr << node->coeff;
			if(node->power != 0)
				ostr << "x^";

			//exception for power == 0
			if(node->power != 0)
				ostr << node->power;
			node = node->next;

			//printing next node with negative values differently
			if (node->coeff >= 1)
			{
				if (i != c.size - 1)
					ostr << " + ";
			}
			else if(node->coeff < 0)
			{
				if (i != c.size - 1)
					ostr << " - ";
			}
		}
		
    } 
	return ostr;
}


