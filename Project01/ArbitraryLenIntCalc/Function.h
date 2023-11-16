/* Kyle Tranfaglia
*  COSC320 - Project01
*  Last updated 10/20/23
*  Declaration of Function object with a data structure and tree node object declaration for tree
*/
#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <stdexcept>

#include "InfInt.h"

using namespace std;

// Tree Node data structure to hold the operator and number for each node
class ExpData {
public:
	string op;
	InfInt num;

	ExpData() {
		op = "";
		num = 0;
	}

	friend ostream& operator<<(ostream &, ExpData &); // Overloaded std out
};
// Standard Tree Node using the created structure as data type 
class ExpTreeNode {
public:
	ExpData data;
	ExpTreeNode *left;
	ExpTreeNode *right;

	ExpTreeNode(ExpData val, ExpTreeNode *lptr = nullptr, ExpTreeNode *rptr = nullptr) {
		data = val;
		left = lptr;
		right = rptr;
	}
};
// Function object that acts as an expression tree to manipulate and assess expressions
class Function {
private:
	ExpTreeNode *root;
	string InputString;
	int pos;

	ExpTreeNode* MakeTreeNode(ExpData, ExpTreeNode *lptr = nullptr, ExpTreeNode *rptr = nullptr);
	void DeleteTree(ExpTreeNode*);
	ExpTreeNode* CopyTree(ExpTreeNode*);

	ExpData GetToken();
	ExpTreeNode* Expression(ExpData &);
	ExpTreeNode* Term(ExpData &);
	ExpTreeNode* Factor(ExpData &);
	ExpTreeNode* Power(ExpData &);

	InfInt Eval(ExpTreeNode *);

	bool IsLeaf(ExpTreeNode*);
	bool IsNumber(ExpTreeNode*);
	void IndentBlock(int num = 4);

public:
	Function();
	Function(const Function &);
	~Function();
	Function& operator=(const Function &);

	void ConvertExpression(string);
	void LoadFunction(string);

	InfInt Evaluate();
	InfInt Factorial(int);
	InfInt Fibonacci(int);

	friend istream& operator>>(istream &, Function &);
	friend ostream& operator<<(ostream &, Function &);

	string toString(ExpTreeNode *);
	string toString();

	void PrintFunctionTree(ExpTreeNode*, int Indent = 6, int Level = 0);
	void PrintFunctionTree(int Indent = 6, int Level = 0);
	void PrintFunction();
	void PrintFunction(ExpTreeNode*);
	void PrintFunctionPostfix();
	void PrintFunctionPostfix(ExpTreeNode*);
	void ClearFunction();
};

#endif