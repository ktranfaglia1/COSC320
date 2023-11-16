/* Kyle Tranfaglia
*  COSC320 - Project01
*  Last updated 10/20/23
*  Implimentation of Function object
*/
#include "Function.h"

/*
 * Nifty trick to convert a numeric looking string to a numeric data type.
 * Examples:
 * from_string<double>(dval, str, dec)
 * from_string<int>(ival, str, dec)
 */
template<class T>
bool from_string(T &t, const string &s, ios_base& (*f)(ios_base&)) {
	istringstream iss(s);
	return !(iss >> f >> t).fail();
}

/*
 * ostream friend function for the ExpData data type.
 */
ostream& operator<<(ostream &ostr, ExpData &item) {
	string TempStr;

	if (item.op == "#") {
		ostr << item.num;
	}
	else {
		ostr << item.op;
	}

	return ostr;
}

/*
 * Function constructor.
 */
Function::Function() {
	root = nullptr;
	InputString = "";
	pos = 0;
}

/*
 * Function destructor.
 */
Function::~Function() {
	DeleteTree(root);
	root = nullptr;
}

/*
 * Function copy constructor.
 */
Function::Function(const Function &f) {
	root = CopyTree(f.root);
}

/*
 * Overloaded assignment statement.
 */
Function& Function::operator=(const Function &rhs) {
	if (root)
		this->ClearFunction();

	root = CopyTree(rhs.root);
	return *this;
}

/*
 * Clears all dynamically allocated memory stored in the expression tree.
 * Simply calls the recursive DeleteTree function on the root.
 */
void Function::ClearFunction() {
	DeleteTree(root);
	root = nullptr;
}

/*
 * Creates a new tree node with the parameter information and child links.
 * If the allocation fails the program is halted.
 */
ExpTreeNode* Function::MakeTreeNode(ExpData item, ExpTreeNode *lptr, ExpTreeNode *rptr) {
	ExpTreeNode *newNode = new ExpTreeNode(item, lptr, rptr);

	if (newNode == nullptr) {
		cerr << "Memory Allocation Error!";
		exit(1);
	}

	return newNode;
}

/*
 * Recursive function to copy a tree or subtree.
 */
ExpTreeNode* Function::CopyTree(ExpTreeNode *t) {
	ExpTreeNode *newlptr, *newrptr, *newnode;

	if (!t)
		return nullptr;

	if (t->left)
		newlptr = CopyTree(t->left);
	else
		newlptr = nullptr;

	if (t->right)
		newrptr = CopyTree(t->right);
	else
		newrptr = nullptr;

	newnode = MakeTreeNode(t->data, newlptr, newrptr);
	return newnode;
}

/*
 * Recursive function to clear all memory of a binary tree.
 */
void Function::DeleteTree(ExpTreeNode *t) {
	if (t) {
		DeleteTree(t->left);
		DeleteTree(t->right);
		delete t;
	}
}

/*
 * Retrieves the next token from the input string.
 */
ExpData Function::GetToken() {
	// variables
	string TempStr = "";
	ExpData ReturnVal;
	InfInt numval;
	// Ignores whitespace
	while (InputString[pos] == ' ') {
		pos++;
	}

	int startpos = pos; // Holds starting position
	// Checks if expression is alpha numeric
	if (isalnum(InputString[pos])) {
		// If string is digit
		if (isdigit(InputString[pos])) {
			// As long as it is digit, move along the string
			while (isdigit(InputString[pos])) {
				pos++;
			}
			TempStr = InputString.substr(startpos, pos - startpos); // Substrings the number
			ReturnVal.op = "#"; // Sets operator to number
			// Converts the substring to an InfInt and sets as return value .. if fails number is set to 0
			if (from_string<InfInt>(numval, TempStr, dec)) {
				ReturnVal.num = numval;
			}
			else {
				ReturnVal.num = 0;
			}
		}
		// Otherwise ... must be alphabetical
		else {
			// As long as it is alphabetical, move along string
			while (isalpha(InputString[pos])) {
				pos++;
			}
			TempStr = InputString.substr(startpos, pos - startpos); // Substrings the letters
			ReturnVal.op = TempStr; // Sets operator to the captured substring
			ReturnVal.num = 0; // Defaults value to 0
		}
	}
	else {
		ReturnVal.op = InputString[pos++]; // Must be an operator (or special character that will be caught as error) so set as op
		ReturnVal.num = 0; // Defaults value to 0
	}

	return ReturnVal;
}

/*
 * Function to load a new expression string into the tree.
 */
void Function::LoadFunction(string str) {
	ConvertExpression(str);
}

/*
 * Function to load a new expression string into the tree.
 */
void Function::ConvertExpression(string str) {

	pos = 0;
	InputString = str + "==";

	ExpData Token = GetToken();;

	ClearFunction();
	root = Expression(Token);
}

/*
 * BNF-ish
 * Expression := {-} Term {+ / - Term}
 * Term := Factor {* / / Factor}
 * Factor := Power {^ Power}
 * Power := Terminal | (Expression) | Function(Expression)
 */

/*
 * Function to process an expression.
 */
ExpTreeNode* Function::Expression(ExpData &Token) {
	ExpData ThisToken;
	ExpTreeNode *temp = nullptr, *temp2 = nullptr;

	if (Token.op == "-") {
		ThisToken = Token;
		Token = GetToken();
		temp = Term(Token);
		ThisToken.op = '~';
		temp = MakeTreeNode(ThisToken, nullptr, temp);
	} else
		temp = Term(Token);

	while ((Token.op == "+") || (Token.op == "-")) {
		ThisToken = Token;
		Token = GetToken();
		temp2 = Term(Token);
		temp = MakeTreeNode(ThisToken, temp, temp2);
	}
	return temp;
}

/*
 * Function to process a term.
 */
ExpTreeNode* Function::Term(ExpData &Token) {
	ExpData ThisToken;
	ExpTreeNode *temp = nullptr, *temp2 = nullptr;

	temp = Factor(Token);

	while ((Token.op == "*") || (Token.op == "/") || (Token.op == "%")) {
		ThisToken = Token;
		Token = GetToken();
		temp2 = Factor(Token);
		temp = MakeTreeNode(ThisToken, temp, temp2);
	}
	return temp;
}

/*
 * Function to process a factor.
 */
ExpTreeNode* Function::Factor(ExpData &Token) {
	ExpData ThisToken;
	ExpTreeNode *temp = nullptr, *temp2 = nullptr;

	temp = Power(Token);

	while (Token.op == "^") {
		ThisToken = Token;
		Token = GetToken();
		temp2 = Power(Token);
		temp = MakeTreeNode(ThisToken, temp, temp2);
	}
	return temp;
}

/*
 * Function to process a power.
 */
ExpTreeNode* Function::Power(ExpData &Token) {
	ExpTreeNode *temp = nullptr;
	ExpData ThisToken;

	if (Token.op == "#") {
		temp = MakeTreeNode(Token);
		Token = GetToken();
	} 
	else if (Token.op == "(") {
		Token = GetToken();
		temp = Expression(Token);
		if (Token.op == ")")
			Token = GetToken();
		else
			throw std::invalid_argument("Right Parenthesis Expected.\n");
	}
	else if (Token.op == "fact" || Token.op == "fib" || Token.op == "sqrt") {
		ThisToken = Token;
		Token = GetToken();
		if (Token.op == "(") {
			Token = GetToken();
			temp = Expression(Token);
			temp = MakeTreeNode(ThisToken, nullptr, temp);
			if (Token.op == ")")
				Token = GetToken();
			else
				throw std::invalid_argument("Right Parenthesis Expected.\n");
		} else
			throw std::invalid_argument("Left Parenthesis Expected.\n");
	}
	else {
		throw std::invalid_argument("Operand or Left Parenthesis Expected.\n");
	}
	return temp;
}

/*
 * Non-Recursive Evaluate Function
 */
InfInt Function::Evaluate() {
	InfInt num = 0;
	if (root) {
		num = Eval(root);
	}
	return num;
}

/*
 * General recursive evaluation function
 */
InfInt Function::Eval(ExpTreeNode *nodeptr) {
	// Vraiables
	InfInt result = 0, rightValue = 0, leftValue = 0;
	// While nodes remain to traverse in expression tree
	if (nodeptr) {
		// If number, get the number
		if (nodeptr->data.op == "#") {
			result = nodeptr->data.num;
		}
		// if '~', denoting a '-' at beginning of function, multiply evaluation by -1
		else if (nodeptr->data.op == "~") {
			InfInt sign = -1;
			result = sign * (Eval(nodeptr->right));
		}
		// If operator, error check argument, calculate left and right subtree, then preform calculation
		else if (nodeptr->data.op == "+" || nodeptr->data.op == "-" || nodeptr->data.op == "*" || nodeptr->data.op == "/" || nodeptr->data.op == "%" || nodeptr->data.op == "^") {
			leftValue = Eval(nodeptr->left); // Eval left sub tree
			rightValue = Eval(nodeptr->right); // Eval right sub tree
			// Checks if the denominator of division is 0 and throws error if true
			if (rightValue == 0 && (nodeptr->data.op == "%" || nodeptr->data.op == "/")) {
				throw std::invalid_argument("Division by zero is not allowed");
			}
			// Checks if operator is '^'
			if (nodeptr->data.op == "^") {
				// Checks that power is positive
				if (rightValue < 0) {
					throw std::invalid_argument("Can not assess negative powers");
				}
				try {
					result = leftValue;
					// Calculates the power of leftvalue^rigthvalue
					for (int i = 0; i < rightValue.toInt() - 1; i++) {
						result *= leftValue;
					}
				}
				catch (InfIntException &e) {
               		throw std::runtime_error(e.what());
				}
			}
			// Checks if modulo, then performs modulo
			else if (nodeptr->data.op == "%") {
				result = leftValue % rightValue;
			}
			// Checks if division, then performs division
			else if (nodeptr->data.op == "/") {
				result = leftValue / rightValue;
			}
			// Checks if multiplication, then performs multiplication
			else if (nodeptr->data.op == "*") {
				result = leftValue * rightValue;
			}
			// Checks if addition, then performs addition
			else if (nodeptr->data.op == "+") {
				result = leftValue + rightValue;
			}
			// Checks if subtraction, then performs subtraction
			else if (nodeptr->data.op == "-") {
				result = leftValue - rightValue;
			}
			else {
				throw std::logic_error("Evaluation error");
			}
		}
		// If one of the valid functions
		else if (nodeptr->data.op == "fact" || nodeptr->data.op == "fib" || nodeptr->data.op == "sqrt") {
			rightValue = Eval(nodeptr->right); // Evaluate right value
			// If right value is negative, it is an function input error
			if (rightValue < 0) {
				throw std::invalid_argument("Function values can not be negative");;
			}
			// If fact, evaluate factorial
			else if (nodeptr->data.op == "fact") {
				try {
					result = Factorial(rightValue.toInt()); // Calls factorial function with integer
				}
				catch (InfIntException &e) {
               		throw std::runtime_error(e.what());
				}
			}
			// If fib, evaluate fibonacci
			else if (nodeptr->data.op == "fib") {
				try {
					result = Fibonacci(rightValue.toInt()); // Calls fibonacci function with integer
				}
				catch (InfIntException &e) {
               		throw std::runtime_error(e.what());
				}
			}
			// If sqrt, evaluate square root
			else if (nodeptr->data.op == "sqrt") {
				try {
					result = rightValue.intSqrt(); // Calls square root function built into InfInt class
				}
				catch (InfIntException &e) {
               		throw std::runtime_error(e.what());
				}
			}
			else {
				throw std::logic_error("Evaluation error");
			}
		}
		else {
			throw std::invalid_argument("The expression contains an element that can not be evaluated");
		}
	}
	return result;
}
// Iterative factorial function
InfInt Function::Factorial(int value) {
	InfInt result = 1; // Returns this value if 0!
	// If negative, factorial is 0
	if (value < 0) {
		result = 0;
	}
	else {
		// iteratively calculates factorial
		for (int i = 1; i <=value; i++) {
			result *= i;
		}
	}
	return result;
}
// Iterative Fibonacci function
InfInt Function::Fibonacci(int value) {
	InfInt result = 0;
	// Base case, if 0, then 0
	if (value <= 0) {
		result = 0;
	}
	// Base case, if 1, then 1
	else if (value == 1) {
		result = 1;
	}
	// Otherwise, compute ith Fibonacci number iteratively
	else {
		InfInt fibprev1 = 0, fibprev2 = 1; // Sets previous terms
		// Loop to calculate next term iteratively and keep track of the two previous terms
		for (int i = 2; i <= value; i++) {
			result = fibprev1 + fibprev2;
			fibprev1 = fibprev2;
			fibprev2 = result;
		}
	}
	return result;
}

/*
 * Determines if the node is a leaf.
 */
bool Function::IsLeaf(ExpTreeNode *t) {
	return (!t->left && !t->right);
}

/*
 * Stream in operator to a function.  Since this is streaming into a
 * string before conversion the user should not include any whitespace
 * during input.
 */
istream& operator>>(istream &istr, Function &fx) {
	string InputString;
	istr >> InputString;
	fx.ConvertExpression(InputString);
	return istr;
}

/*
 * Recursive function to convert an expression subtree to a string.
 */
string Function::toString(ExpTreeNode *t) {
	stringstream ss;
	ss.str("");

	if (t) {
		ss << "(";
		ss << toString(t->left);
		ss << t->data;
		ss << toString(t->right);
		ss << ")";
	}
	return ss.str();
}

/*
 * Function to convert an expression to a string.
 */
string Function::toString() {
	if (root)
		return toString(root);

	return "";
}

/*
 * Overloaded stream out operator.
 */
ostream& operator<<(ostream &ostr, Function &fx) {
	ostr << fx.toString();
	return ostr;
}

/*
 * Indentation helper function for tree printing.
 */
void Function::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

/*
 * Recursive function for printing an expression tree in tree form.
 */
void Function::PrintFunctionTree(ExpTreeNode *t, int Indent, int Level) {
	if (t) {
		PrintFunctionTree(t->right, Indent, Level + 1);
		IndentBlock(Indent * Level);
		cout << t->data << "\n";
		PrintFunctionTree(t->left, Indent, Level + 1);
	}
}

/*
 * Function for printing an expression tree in tree form.
 */
void Function::PrintFunctionTree(int Indent, int Level) {
	if (root)
		PrintFunctionTree(root, Indent, Level);
}

/*
 * Recursive function for printing an expression to standard out.
 */
void Function::PrintFunction(ExpTreeNode *t) {
	if (t) {
		cout << "(";
		PrintFunction(t->left);
		cout << t->data;
		PrintFunction(t->right);
		cout << ")";
	}
}

/*
 * Function for printing an expression to standard out.
 */
void Function::PrintFunction(void) {
	if (root)
		PrintFunction(root);
}

/*
 * Recursive function for printing an expression in postfix form to standard out.
 */
void Function::PrintFunctionPostfix(ExpTreeNode *t) {
	if (t) {
		PrintFunctionPostfix(t->left);
		PrintFunctionPostfix(t->right);
		cout << t->data << " ";
	}
}

/*
 * Function for printing an expression in postfix form to standard out.
 */
void Function::PrintFunctionPostfix(void) {
	if (root)
		PrintFunctionPostfix(root);
}