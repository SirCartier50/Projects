/***
 * Mignot Mesele
 * mmesele
 * 2023 Fall CSE101 PA{7}
 * Dictionary.cpp
 * Dictionary ADT
 * ***/

#include <stdexcept>
#include"Dictionary.h"

/*** constructor/deconstructor ***/
Dictionary::Node::Node(keyType k, valType v){
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

Dictionary::Dictionary(){
	nil = new Node("nil", -1);
	root = nil;
	current = nil;
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
	nil = new Node("nil", -1);
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
		s += R->key + "\n";
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
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
	}else if(newnode->key < x->key){
		x->left = newnode;
		num_pairs++;
	}else if(newnode->key > x->key){
		x->right = newnode;
		num_pairs++;
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
		if(z->left == nil){
			transplant(z, z->right);
			delete z;
		}else if(z->right == nil){
			transplant(z, z->left);
			delete z;
		}else{
			Node* y = findMin(z->right);
			if( y->parent != z){
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			delete z;
		}
		num_pairs--;
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
