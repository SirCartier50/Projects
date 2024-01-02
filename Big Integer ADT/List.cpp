/***
 * Author: Mignot Mesele
 * Title: List.cpp
 * Purpose: List ADT
 * ***/

#include <stdexcept>
#include"List.h"

List::Node::Node(ListElement x){
	data = x;
	prev = nullptr;
	next = nullptr;
}

List::List(){
	frontDummy = new Node(-1);
	backDummy = new Node(-2);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

List::List(const List& L){
	frontDummy = new Node(-1);
        backDummy = new Node(-2);
        frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
        beforeCursor = frontDummy;
        afterCursor = backDummy;
        pos_cursor = 0;
        num_elements = 0;

	Node* temp = L.frontDummy->next;
	while(temp != L.backDummy){
		insertBefore(temp->data);
		temp=temp->next;
	}
}

List::~List(){
	if(num_elements != 0){
		clear();
	}
	delete frontDummy;
	delete backDummy;
}

int List::length() const{
	return num_elements;
}

ListElement List::front() const{
	if(length() == 0){
		throw std::length_error("cant get the front of an empty list\n");
	}
	return frontDummy->next->data;
}

ListElement List::back() const{
	if(length() == 0){
		throw std::length_error("cant get the back of an empty list\n");
        }
	return backDummy->prev->data;
}

int List::position() const{
	if(pos_cursor < 0 || pos_cursor > length()){
		throw std::range_error("cant get the position of out the range of list\n");
	}
	return pos_cursor;
}

ListElement List::peekNext() const{
	if(position() >= length()){
		throw std::range_error("cant peek to next\n");
	}
	return afterCursor->data;
}

ListElement List::peekPrev() const{
	if(position() <= 0){
		throw std::range_error("cant peek to prev\n");
        }
        return beforeCursor->data;
}

void List::clear(){
	moveFront();
	while(length() > 0){
		eraseAfter();
	}
}
void List::moveFront(){
	if(length() > 0){
		beforeCursor = frontDummy;
		afterCursor = frontDummy->next;
		pos_cursor = 0;
	}
}

void List::moveBack(){
	if(length() > 0){
                beforeCursor = backDummy->prev;
                afterCursor = backDummy;
                pos_cursor = length();
        }
}

ListElement List::moveNext(){
	if(position()>=length()){
		throw std::range_error("cant move to next thats out of the list to the right\n");	
	}
	beforeCursor = beforeCursor->next;
	afterCursor = afterCursor->next;
	pos_cursor++;
	return peekPrev();
}
ListElement List::movePrev(){
	if(position()<=0){
		throw std::range_error("cant move to next thats out of the list to the left\n");
        }
        beforeCursor = beforeCursor->prev;
        afterCursor = afterCursor->prev;
	pos_cursor--;
        return peekNext();
}

void List::insertAfter(ListElement x){
	Node* N = new Node(x);
	beforeCursor->next = N;
	N->prev = beforeCursor;
	afterCursor->prev = N;
	N->next = afterCursor;
	afterCursor = N;
	num_elements++;
}
		
void List::insertBefore(ListElement x){
	Node* N = new Node(x);
	beforeCursor->next = N;
        N->prev = beforeCursor;
        afterCursor->prev = N;
        N->next = afterCursor;
        num_elements++;
        pos_cursor++;
	beforeCursor = N;
}
void List::setAfter(ListElement x){
	if(position()>=length()){
		throw std::range_error("cant set after cursor\n");
        }
	afterCursor->data = x;
}
	
void List::setBefore(ListElement x){
	if(position() <= 0){
		throw std::range_error("cant set before cursor\n");
        }
	beforeCursor->data = x;
}
void List::eraseAfter(){
	if(position()>=length()){
		throw std::range_error("can't erase. out of list on the right\n");
	}
	Node* temp = afterCursor;
	afterCursor = afterCursor->next;
	afterCursor->prev = beforeCursor;
	beforeCursor->next = afterCursor;
	delete temp;
	num_elements--;
}
void List::eraseBefore(){
	if(position() <= 0){
		throw std::range_error("can't erase. out of list on the before\n");
        }
        Node* temp = beforeCursor;
        beforeCursor = beforeCursor->prev;
        beforeCursor->next = afterCursor;
        afterCursor->prev = beforeCursor;
        delete temp;
        num_elements--;
	pos_cursor--;
}

int List::findNext(ListElement x){
	while(afterCursor != backDummy){
		if(peekNext() == x){
			moveNext();
			return position();
		}
		moveNext();
	}
	moveBack();
	return -1;
}
int List::findPrev(ListElement x){
	while(beforeCursor != frontDummy){
                if(peekPrev() == x){
                        movePrev();
                        return position();
                }
                movePrev();
        }
        moveFront();
        return -1;
}

void List::cleanup(){
	int end_pos = pos_cursor;
	moveFront();
	while(afterCursor != backDummy){
		int original = afterCursor->data;
		moveNext();
		int current_pos = pos_cursor;
		while(afterCursor != backDummy){
			while(afterCursor != backDummy && peekNext() == original){
				
				if(pos_cursor < end_pos){
					end_pos--;
				}
				eraseAfter();
			}
			if(afterCursor != backDummy){
				moveNext();
			}
		}
		while(pos_cursor != current_pos){
			movePrev();
		}
	}
	while(pos_cursor != end_pos){
		movePrev();
	}
}
	
List List::concat(const List& L) const{
	List J;
	Node* temp = frontDummy->next;
	Node* D = L.frontDummy->next;
	while(temp != backDummy){
		J.insertBefore(temp->data);
		temp = temp->next;
	}
	while(D != L.backDummy){
		J.insertBefore(D->data);
		D = D->next;
	}
	J.moveFront();
	return J;
}
std::string List::to_string() const{
	Node* N = nullptr;
	std::string s = "";
	for(N=frontDummy->next; N!=backDummy; N=N->next){
      		s += std::to_string(N->data)+" ";
   	}
	return s;
}
bool List::equals(const List& R) const{
	bool eq = false;
   	Node* N = nullptr;
   	Node* M = nullptr;
   	eq = ( num_elements == R.num_elements );
   	N = frontDummy;
   	M = R.frontDummy;
   	while( eq && N!=nullptr){
      		eq = (N->data==M->data);
      		N = N->next;
      		M = M->next;
   	}
   	return eq;
}
std::ostream& operator<<(std::ostream& stream, const List& L){
	return stream << L.to_string();
}
bool operator==(const List& A, const List& B){
	return A.equals(B);
}
List& List::operator=(const List& L){
	
	if( this != &L ){
		List temp = L;
		std::swap(frontDummy, temp.frontDummy);
      		std::swap(backDummy, temp.backDummy);
      		std::swap(num_elements, temp.num_elements);
		std::swap(pos_cursor, temp.pos_cursor);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
	}
	return *this;
}

