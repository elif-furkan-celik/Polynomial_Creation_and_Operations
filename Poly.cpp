#include <stdio.h>
#include "Poly.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the first PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//
PolyNode *CreatePoly(char *expr){
    PolyNode *head;
    head = NULL;
    int temp = 0;
    int temp1 = 0;
    for(int i=0; i<strlen(expr); i++){
        if(expr[i] != ' '){
            temp1 += 1;
        }
    }
    char ply[temp1];
    temp1 = 0;
    for(int i=0; i<strlen(expr); i++){
        if(expr[i] != ' '){
            ply[temp1] = expr[i];
            temp1 += 1;
        }
    }
    for(int i = 0; i<strlen(ply); i++){

        if(ply[i] == 'x'){
            double coef = atof((ply + temp));
            if(coef == 0){
                if(ply[i-1] == '-'){
                        coef = -1.0;
                    }else{
                        coef = 1.0;
                    }
            }
            int exp;
            i += 1;
            temp = i;

            if(ply[i] == '^'){
                i += 1;
                temp +=1;
                exp = atoi(ply + i);
                if(exp < 10){
                    i += 1;
                    temp +=1;
                }else if(exp < 100){
                    i += 2;
                    temp +=2;
                }else if(exp < 1000){
                    i += 3;
                    temp +=3;
                }else if(exp > 1000){
                    i += 4;
                    temp +=4;
                }
            }else{
                exp = 1;
            }
            head = AddNode(head, coef, exp);
        }else if(i >= strlen(ply)-1){
            double coef = atof(ply + temp);
            int exp;
            exp = 0;
            head = AddNode(head, coef, exp);
        }
    }
	return head;
} //end-CreatePoly

/// -------------------------------------------------
/// Walk over the poly nodes & delete them
///
void DeletePoly(PolyNode* poly) {
	// Fill this in
	if(poly != NULL){
        PolyNode* temp;

        while(true){
            if(poly->next != NULL){
                temp = poly;
                poly = poly->next;
                delete temp;
                temp = NULL;
            }else{
                break;
            }
        }
    }
} // end-DeletePoly

//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//
PolyNode* AddNode(PolyNode *head, double coef, int exp){// hem sýralý hemde aynýlarýnýn toplanmasý lazým
	// Fill this in
	PolyNode *index;
	index = head;
	if(head == NULL){
        PolyNode *temp = new PolyNode;
        temp->coef = coef;
        temp->exp = exp;
        temp->next = NULL;
        head = temp;
        return head;
	}else{
	    if(index->next == NULL){
            if(index->exp == exp){
                index->coef += coef;
                return head;
            }else if(index->exp > exp){
                PolyNode *temp = new PolyNode;
                temp->coef = coef;
                temp->exp = exp;
                temp->next = NULL;
                index->next = temp;
                return head;
            }else if(index->exp < exp){
                PolyNode *temp = new PolyNode;
                temp->coef = coef;
                temp->exp = exp;
                temp->next = index;
                index->next = NULL;
                head = temp;
                return head;
            }
	    }
        while(true){

            if(index->next->exp == exp){
                index->next->coef += coef;
                break;
            }else if(index->next->exp < exp){
                PolyNode *temp = new PolyNode;
                temp->coef = coef;
                temp->exp = exp;
                temp->next = index->next;
                index = temp;
                break;
            }else if(index->next->exp > exp){
                if(index->next->next == NULL){

                    PolyNode *temp = new PolyNode;
                    temp->coef = coef;
                    temp->exp = exp;
                    temp->next = NULL;
                    index->next->next = temp;
                    break;
                }
                index = index->next;
            }
        }
	}
	return head;
} // end-AddNode

//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
PolyNode *Add(PolyNode *poly1, PolyNode *poly2){
    PolyNode *head;
    PolyNode *p1;
    PolyNode *p2;
    p1 = poly1;
    p2 = poly2;

    if(p1 == NULL){
        if(p2 == NULL){
            return NULL;
        }else{
            head = p2;
            return head;
        }
    }else if(p2 == NULL){
        head = p1;
        return head;
    }else{

        while(true){
            if(p1->next !=NULL){
                if(p2->next != NULL){
                    head = AddNode(head, p1->coef, p1->exp);
                    head = AddNode(head, p2->coef, p2->exp);
                    p1 = p1->next;
                    p2 = p2->next;
                }else{
                    head = AddNode(head, p1->coef, p1->exp);
                    p1 = p1->next;
                }
            }else if(p2->next !=NULL){
                head = AddNode(head, p2->coef, p2->exp);
                p2 = p2->next;
            }else{
                head = AddNode(head, p1->coef, p1->exp);
                head = AddNode(head, p2->coef, p2->exp);
                break;
            }
        }
    }
	// Fill this in
	return head;
} //end-Add

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode *Subtract(PolyNode *poly1, PolyNode *poly2){
	// Fill this in
PolyNode *head;
    PolyNode *p1;
    PolyNode *p2;
    p1 = poly1;
    p2 = poly2;

    if(p1 == NULL){
        if(p2 == NULL){
            return NULL;
        }else{
            head = p2;
            return head;
        }
    }else if(p2 == NULL){
        head = p1;
        return head;
    }else{

        while(true){
            if(p1->next !=NULL){
                if(p2->next != NULL){
                    head = AddNode(head, p1->coef, p1->exp);
                    head = AddNode(head, -1*p2->coef, p2->exp);
                    p1 = p1->next;
                    p2 = p2->next;
                }else{
                    head = AddNode(head, p1->coef, p1->exp);
                    p1 = p1->next;
                }
            }else if(p2->next !=NULL){
                head = AddNode(head, -1*p2->coef, p2->exp);
                p2 = p2->next;
            }else{
                head = AddNode(head, p1->coef, p1->exp);
                head = AddNode(head, -1*p2->coef, p2->exp);
                break;
            }
        }
    }
	// Fill this in
	return head;
} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode *Multiply(PolyNode *poly1, PolyNode *poly2){
	// Fill this in
	PolyNode *head;
	PolyNode *p1;
	PolyNode *p2;
	p1 = poly1;
	p2 = poly2;

	if(p1 == NULL){
        return NULL;
	}else if(p2 == NULL){
        return NULL;
	}else{
        while(true){
            while(true){
                head = AddNode(head, (p1->coef * p2->coef), (p1->exp + p2->exp));
                if(p2->next == NULL){
                    break;
                }
                p2 = p2->next;
            }
            if(p1->next == NULL){
                break;
            }
            p2 = poly2;
            p1 = p1->next;
        }
	}
	return head;
} //end-Multiply

//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode *poly, double x){
	// Fill this in
	PolyNode *p;
	p = poly;
	double result = 0.0;
	int temp;
	if(p == NULL){
        return result;
	}else{
        while(true){
            temp = 1;
            if(p->exp > 0){
                for(int i=0; i<p->exp; i++){
                    temp *= x;
                }
            }else if(p->exp < 0){
                for(int i=p->exp; i<0; i++){
                    temp *= x;
                }
            }
            result += p->coef * temp;
            if(p->next == NULL){
                break;
            }
            p = p->next;
        }
	}
	return result;
} //end-Evaluate

//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode *Derivative(PolyNode *poly){
	// Fill this in
    PolyNode *p;
    PolyNode *head;
    head = NULL;
	p = poly;

	if(p != NULL){
        while(true){

            if(p->exp == 0){
                break;
            }else{
                head = AddNode(head, p->coef*p->exp, p->exp -1);
            }
            if(p->next == NULL){
                break;
            }
            p = p->next;
        }
    }
	return head;
} //end-Derivative

//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode *poly, int x1, int x2){
	// Fill this in
    char koordinat[25][(abs(x1)+abs(x2)+1)];

for(int i=0; i < 25; i++){
        for(int j=0; j<(abs(x1)+abs(x2)+1); j++){
            koordinat[i][j] = ' ';
        }
    }

    for(int i=0; i < (abs(x1)+abs(x2)+1); i++){
        koordinat[13][i] = '-';
    }
    for(int i=0; i < 25; i++){
        koordinat[i][(abs(x1)+1)] = '|';
    }

    for(int i= 0; i<(abs(x1)+abs(x2)+1); i++){
        koordinat[(int)Evaluate(poly,(x1+i))][i] = '*';
    }

    for(int i=0; i < 25; i++){
        for(int j=0; j<(abs(x1)+abs(x2)+1); j++){
            std::cout<<koordinat[i][j];
        }
        printf("\n");
    }


} //end-Plot

