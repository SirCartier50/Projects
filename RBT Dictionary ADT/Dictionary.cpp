/***
 * Author: Mignot Mesele
 * Title: Dictionary.cpp
 * Purpose: Dictionary ADT
 * ***/

#include <stdexcept>
#include"Dictionary.h"

#define RED (-2)

#define BLACK (-3)

/*** constructor/deconstructor ***/
Dictionary::Node::Node(keyType k, valType v){
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = RED;
}

Dictionary::Dictionary(){
	nil = new Node("nil", -1);
	nil->color = BLACK;
	root = nil;
	current = nil;
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
	nil = new Node("nil", -1);
	nil->color = BLACK;
	root = nil;
	current = nil;
	num_pairs = 0;
	preOrderCopy(D.root, D.nil);
}
Dictionary::~Dictionary(){
	if(num_pairs != 0){
		clear();
	}
	delete nil;
}
/*** helper functions ***/
void Dictionary::inOrderString(std::string& s, Node* R) const{
	if(R != nil){
		inOrderString(s, R->left);
		s += R->key + " : " + std::to_string(R->val) + "\n";
		inOrderString(s, R->right);
	}
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
	if(R != nil){
		if(R->color == BLACK){
			s += R->key + "\n";
		}else if(R->color == RED){
			s += R->key + " (RED)\n";
		}
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

void Dictionary::BST_insert(Node* M){
	Node* y = nil;
	Node* x = root;
	while( x != nil){
		y = x;
		if(M->key < x->key){
			x = x->left;
		}else{
			x = x->right;
		}
	}
	M->parent = y;
	if(y == nil){
		root = M;
	}else if(M->key < y->key){
		y->left = M;
	}else{
		y->right = M;
	}
	M->left = nil;
	M->right = nil;
	M->color = RED;
	RB_InsertFixUp(M);
}

void Dictionary::preOrderCopy(Node* R, Node* N){
	if(R != N){
		setValue(R->key, R->val);
		preOrderCopy(R->left, N);
		preOrderCopy(R->right, N);
	}
}
void Dictionary::postOrderDelete(Node* R){
	if(R != nil){
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		delete R;
	}
}

void Dictionary::transplant(Node* u, Node* v){
	if(u->parent == nil){
		root = v;
	}else if(u == u->parent->left){
		u->parent->left = v;
	}else{
		u->parent->right = v;
	}
	if(v != nil){
		v->parent = u->parent;
	}
}
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
	if(R == nil || k == R->key){
		return R;
	}else if(k < R->key){
		return search(R->left, k);
	}else{
		return search(R->right, k);
	}
}

Dictionary::Node* Dictionary::findMin(Node* R){
	if(R == nil){
		return nil;
	}
	while(R->left != nil){
		R = R->left;
	}
	return R;
}

Dictionary::Node* Dictionary::findMax(Node* R){
	if(R == nil){
		return nil;
	}
	while(R->right != nil){
		R = R->right;
	}
	return R;
}   

Dictionary::Node* Dictionary::findNext(Node* N){
	if(N->right != nil){
		return findMin(N->right);
	}
	Node* parent = N->parent;
	while(parent != nil && N == parent->right){
		N = parent;
		parent = parent->parent;
	}
	return parent;
}

Dictionary::Node* Dictionary::findPrev(Node* N){
	if(N->left != nil){
		return findMax(N->left);
	}
	Node* parent = N->parent;
	while(parent != nil && N == parent->left){
		N = parent;
		parent = parent->parent;
	}
	return parent;
}
void Dictionary::LeftRotate(Node* N){
	Node* y = N->right;
	N->right = y->left;
	if(y->left != nil){
		y->left->parent = N;
	}
	y->parent = N->parent;
	if(N->parent == nil){
		root = y;
	}else if(N == N->parent->left){
		N->parent->left = y;
	}else{
		N->parent->right = y;
	}
	y->left = N;
	N->parent = y;
}

void Dictionary::RightRotate(Node* N){
	Node* y =  N->left;
	N->left = y->right;
	if(y->right != nil){
		y->right->parent = N;
	}
	y->parent = N->parent;
	if(N->parent == nil){
		root = y;
	}else if(N == N->parent->right){
		N->parent->right = y;
	}else{
		N->parent->left = y;
	}
	y->right = N;
	N->parent = y;
}

void Dictionary::RB_InsertFixUp(Node* N){
	Node* y;
	while(N->parent->color == RED){
		if(N->parent == N->parent->parent->left){
			y = N->parent->parent->right;
			if(y->color == RED){
				N->parent->color = BLACK;
				y->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			}else{
				if(N == N->parent->right){
					N = N->parent;
					LeftRotate(N);
				}
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				RightRotate(N->parent->parent);
			}
		}else{
			y = N->parent->parent->left;
			if(y->color == RED){
				N->parent->color = BLACK;
				y->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			}else{
				if(N == N->parent->left){
					N = N->parent;
					RightRotate(N);
				}
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				LeftRotate(N->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

void Dictionary::RB_Transplant(Node* u, Node* v){
	if(u->parent == nil){
		root = v;
	}else if(u == u->parent->left){
		u->parent->left = v;
	}else{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N){
	Node* w;
	while(N != root && N->color == BLACK){
		if(N == N->parent->left){
			w = N->parent->right;
			if(w->color == RED){
				w->color = BLACK;
				N->parent->color = RED;
				LeftRotate(N->parent);
				w = N->parent->right;
			}
			if(w->left->color == BLACK && w->right->color == BLACK){
				w->color = RED;
				N = N->parent;
			}else{
				if(w->right->color == BLACK){
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(w);
					w = N->parent->right;
				}
				w->color = N->parent->color;
				N->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(N->parent);
				N = root;
			}
		}else{
			w = N->parent->left;
			if(w->color == RED){
				w->color = BLACK;
				N->parent->color = RED;
				RightRotate(N->parent);
				w = N->parent->left;
			}
			if(w->right->color == BLACK && w->left->color == BLACK){
				w->color = RED;
				N = N->parent;
			}else{
				if(w->left->color == BLACK){
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(w);
					w = N->parent->left;
				}
				w->color = N->parent->color;
				N->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(N->parent);
				N = root;
			}
		}
	}
	N->color = BLACK;
}

void Dictionary::RB_Delete(Node* N){
	Node* y = N;
	Node* x;
	int y_original_color = y->color;
	if(N->left == nil){
		x = N->right;
		RB_Transplant(N, N->right);
		delete N;
	}else if(N->right == nil){
		x = N->left;
		RB_Transplant(N, N->left);
		delete N;
	}else{
		y = findMin(N->right);
		y_original_color = y->color;
		x = y->right;
		if(y->parent == N){
			x->parent = y;
		}else{
			RB_Transplant(y, y->right);
			y->right = N->right;
			y->right->parent = y;
		}
		RB_Transplant(N, y);
		y->left = N->left;
		y->left->parent = y;
		y->color = N->color;
		delete N;
	}
	if(y_original_color == BLACK){
		RB_DeleteFixUp(x);
	}
}
/*** access functions ***/
int Dictionary::size() const{
	return num_pairs;
}

bool Dictionary::contains(keyType k) const{
	if(search(root, k) == nil){
		return false;
	}else{
		return true;
	}
}

valType& Dictionary::getValue(keyType k) const{
	if(contains(k) == false){
		throw std::invalid_argument("not in dictionary");
	}
	Node* newnode = search(root, k);
	return newnode->val;
}

bool Dictionary::hasCurrent() const{
	if(current != nil){
		return true;
	}else{
		return false;
	}
}

keyType Dictionary::currentKey() const{
	if(hasCurrent()){
		return current->key;
	}
	throw std::invalid_argument("current is undefined");
}
valType& Dictionary::currentVal() const{
	if(hasCurrent()){
		return current->val;
	}
	throw std::invalid_argument("current is undefined");
}

/***Manipluators***/

void Dictionary::clear(){
	postOrderDelete(root);
	root = nil;
	current = nil;
	num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v){
	Node* newnode = new Node(k, v);
	newnode->left = nil;
	newnode->right = nil;
	Node* x = nil;
	Node* y = root;
	while(y != nil){
		x = y;
		if(newnode->key < y->key){
			y = y->left;
		}else if(newnode->key > y->key){
			y = y->right;
		}else{
			break;
		}
	}
	newnode->parent = x;
	if(x == nil){
		root = newnode;
		num_pairs++;
		RB_InsertFixUp(newnode);
	}else if(newnode->key < x->key){
		x->left = newnode;
		num_pairs++;
		RB_InsertFixUp(newnode);
	}else if(newnode->key > x->key){
		x->right = newnode;
		num_pairs++;
		RB_InsertFixUp(newnode);
	}else{
		x->val = newnode->val;
		delete newnode;
	}
}

void Dictionary::remove(keyType k){
	if(contains(k)){
		Node* z = search(root, k);
		if(z == current){
			current = nil;
		}
		num_pairs--;
		RB_Delete(z);
	}else if(contains(k) == false){
		throw std::invalid_argument("key not in dictionary");
	}
}

void Dictionary::begin(){
	if(root != nil){
		current = findMin(root);
	}
}

void Dictionary::end(){
	if(root != nil){
		current = findMax(root);
	}
}

void Dictionary::next(){
	if(hasCurrent() && current != findMax(root)){
		current = findNext(current);
	}else if(hasCurrent() == false){
		throw std::invalid_argument("current is undefined");
	}else{
		current = nil;
	}
}

void Dictionary::prev(){
	if(hasCurrent() && current != findMin(root)){
		current = findPrev(current);
	}else if(hasCurrent() == false){
		throw std::invalid_argument("current is undefined");
	}else{
		current = nil;
	}
}

bool Dictionary::equals(const Dictionary& D) const{
	std::string s;
	std::string c;
	inOrderString(s, root);
	D.inOrderString(c, D.root);
	if(s == c){
		return true;
	}else{
		return false;
	}

}

std::string Dictionary::to_string() const{
	std::string s;
	inOrderString(s, root);
	return s;
}

std::string Dictionary::pre_string() const{
	std::string s;
	preOrderString(s, root);
	return s;
}

std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
	return stream << D.to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ){
	return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ){
	if(this != &D){
		Dictionary temp = D;
		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);
	}
	return *this;
}
