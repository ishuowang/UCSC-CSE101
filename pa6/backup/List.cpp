#include<iostream>
#include<string>
#include"List.h"

using namespace std;

#define DUMMY 0

// Node constructor
List::Node::Node(long x){
   data = x;
   prev = nullptr;
   next = nullptr;
}

List::List(){
    // The empty state describe in pa4.pdf
    frontDummy = new Node(DUMMY);
    backDummy = new Node(DUMMY);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L){ 
    // The empty state is described in pa4.pdf
    frontDummy = new Node(DUMMY);
    backDummy = new Node(DUMMY);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    // See: example
    Node* N = L.frontDummy->next;
    while(N != L.backDummy){
        ListElement data = N->data;
        this->insertBefore(data);
        N = N->next;
    }
    this->moveFront();
    while(this->pos_cursor != L.pos_cursor){
        this->moveNext();
    }
}

List::~List(){
    this->clear();
    delete this->frontDummy;
    delete this->backDummy;
}

// `this` pointer always point to `this` object,
// keyword const means that pointer `this` are not able to be modified.
int List::length() const{
    return this->num_elements;
}

ListElement List::front() const{
    if(this->length() <= 0){
        // cerr << "front() pre-condition: length() > 0";
        throw std::length_error("front() pre-condition: length() > 0");
    }
    return frontDummy->next->data;
}

ListElement List::back() const{
    if(this->length() <= 0){
        // cerr << "back() pre-condition: length() > 0";
        throw std::length_error("back() pre-condition: length() > 0");
    }
    return backDummy->prev->data;
}

ListElement List::peekNext() const{
    if(this->position() >= this->length()){
        // cerr << "peekNext() pre-condition: position() < length()" << endl;
        throw std::range_error("peekNext() pre-condition: position() < length()");
    }
    return afterCursor->data;
}

ListElement List::peekPrev() const{
    if(this->position() <= 0){
        // cerr << "peekNext() pre-condition: position() > 0" << endl;
        throw std::range_error("peekNext() pre-condition: position() > 0");
    }
    return beforeCursor->data;
}

int List::position() const{
    return this->pos_cursor;
}

void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor = beforeCursor->next;
    this->pos_cursor = 0;
}

void List::moveBack(){
    afterCursor = backDummy;
    beforeCursor = afterCursor->prev;
    this->pos_cursor = this->length();
}

long List::moveNext(){
    if(this->position() >= this->length()){
        // cerr << "moveNext() pre-condition: position()<length()" <<endl;
        throw std::range_error("moveNext() pre-condition: position()<length()");
    }
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    this->pos_cursor ++;
    return beforeCursor->data;
}

long List::movePrev(){
    if(this->position() <= 0){
        // cerr << "moveNext() pre-condition: position()>0" <<endl;
        throw std::range_error("moveNext() pre-condition: position()>0");
    }
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    this->pos_cursor --;
    return afterCursor->data;
}

void List::insertAfter(long x){
    Node* N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    this->num_elements ++;
}

void List::insertBefore(long x){
    Node* N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    this->num_elements ++;
    this->pos_cursor ++;
}

void List::setAfter(ListElement x){
    if(this->position() >= this->length()){
        // cerr << "setAfter() pre-condition: pre: position()<length()" <<endl;
        throw std::range_error("setAfter() pre-condition: pre: position()<length()");
        return;
    }
    afterCursor->data = x;
}

void List::setBefore(ListElement x){
    if(this->position() <= 0){
        // cerr << "setAfter() pre-condition: pre: position()>0" <<endl;
        throw std::range_error("setAfter() pre-condition: pre: position()>0");
        return;
    }
    beforeCursor->data = x;
}

void List::eraseAfter(){
    if(this->position() >= this->length()){
        // cerr << "eraseAfter() pre-condition: pre: position()<length()" <<endl;
        throw std::range_error("eraseAfter() pre-condition: pre: position()<length()");
        return;
    }
    Node* erase = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    this->num_elements --;
    delete erase;
}

void List::eraseBefore(){
    if(this->position() <= 0){
        // cerr << "eraseAfter() pre-condition: pre: position()>0" <<endl;
        throw std::range_error("eraseAfter() pre-condition: pre: position()>0");
        return;
    }
    Node* erase = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    this->pos_cursor --;
    this->num_elements --;
    delete erase;
}

int List::findNext(long x){
    Node* N = this->afterCursor;
    int r = 1;  // relative right;
    while(N != this->backDummy){
        if(N->data == x){
            this->beforeCursor = N;
            this->afterCursor = N->next;
            this->pos_cursor += r;
            return this->pos_cursor;
        }
        N = N->next;
        r ++;
    }
    this->afterCursor = backDummy;
    this->beforeCursor = afterCursor->prev;
    this->pos_cursor = length();
    return -1;
}

int List::findPrev(long x){
    Node* N = this->beforeCursor;
    int l = 1;  // relative left;
    while(N != this->frontDummy){
        if(N->data == x){
            beforeCursor = N->prev;
            afterCursor = N;
            pos_cursor -= l;
            return this->pos_cursor;
        }
        N = N->prev;
        l ++;
    }
    this->beforeCursor = frontDummy;
    this->afterCursor = beforeCursor->next;
    this->pos_cursor = 0;
    return -1;
}


// beforeCursor point to a an unknown data
void List::cleanup(){
    Node* N = this->frontDummy->next;
    int outter_pos = 0;
    while(N != this->backDummy){
        int i = N->data;
        Node* M = N->next;
        int inner_pos = outter_pos + 1;
        while(M != this->backDummy){
            int j = M->data;
            Node* before = M->prev;
            Node* after = M->next;
            Node* erase = M;
            M = after;
            if(j == i){
                before->next = after;
                after->prev = before;
                delete erase;
                this->num_elements --;
                if(inner_pos <= pos_cursor){
                    pos_cursor --;
                }
            }
            inner_pos ++;
        }
        outter_pos ++;
        N = N->next;
    }
    int pos = this->pos_cursor;
    this->moveFront();
    while(this->position() != pos){
        this->moveNext();
    }
}

void List::clear(){
    this->moveFront();
    while(this->length() > 0){
        this->eraseAfter();
    }
}

List List::concat(const List& L) const{
    List newL;
    newL.moveBack();
    Node* N;
    // Insert all elememt to newL in this list.
    N = this->frontDummy->next;
    while(N != this->backDummy){
        newL.insertBefore(N->data);
        N = N->next;
    }
    // Insert all elememt to newL in L list.
    N = L.frontDummy->next;
    while(N != L.backDummy){
        newL.insertBefore(N->data);
        N = N->next;
    }
    newL.beforeCursor = newL.frontDummy;
    newL.afterCursor = newL.beforeCursor->next;
    newL.pos_cursor = 0;
    return newL;
}

// std::string List::to_string() const{
//     string s;
//     // s += "(" ;
//     List::Node* N = this->frontDummy->next;
//     while(N != this->backDummy){
//         s += std::to_string(N->data);
//         // if(N->next != this->backDummy){
//         //     s +=", " ;
//         // }
//         N = N->next;
//     }
//     // s += ")" ;
//     return s;
// }

std::string List::to_string() const{
    // BASE = 10^POWER, 0 <= POWER <= 9
    // const long BASE = 1000000000;   // 1 billion
    const int POWER = 9;
    string s;
    List L(*this);
    L.moveFront();
    while(L.position() < L.length()){
        ListElement elem = L.moveNext();
        std::string elem_str = std::to_string(elem);

        // Padding with 0.
        while(L.position() != 1 && elem_str.length() < POWER){
            elem_str = "0" + elem_str;
        }
        s += elem_str;

        // Add some space between tow elem
        if(L.position() < L.length()){
            s += " ";
        }
    }
    return s;
}

bool List::equals(const List& R) const{
    if(this->length() != R.length()){
        return false;
    }
    Node* N = this->frontDummy->next;
    Node* M = R.frontDummy->next;
    while(N != this->backDummy && M != R.backDummy){
        int n = N->data;
        int m = M->data;
        if(n != m){
            return false;
        }
        N = N->next;
        M = M->next;
    }
    return true;
}

std::ostream& operator<<(std::ostream& stream, const List & L ){
    return stream << L.to_string();
}

bool operator==(const List& A, const List& B ){
    return A.equals(B);
}

List& List::operator=( const List& L ){
    if( this != &L ){ // not self assignment
        // make a copy of L
        List temp = L;

        // then swap the copy's fields with fields of this
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
        // temp.clear();
    }

    // return this with the new data installed
    return *this;

    // the copy, if there is one, is deleted upon return  
}