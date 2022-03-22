#include<string>
#include<iostream>
#include"Dictionary.h"

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R == nullptr){
        return;
    }
    inOrderString(s, R->left);
    s += R->key + " : " + std::to_string(R->val) + "\n";
    inOrderString(s, R->right);
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R == nullptr){
        return;
    }
    s += R->key + "\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
}


void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R == N || R == nil || R == nullptr){
        return;
    }
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

void Dictionary::postOrderDelete(Node* R){
    if(R == nullptr || R == nil){
        return;
    }
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    delete R;
    num_pairs --;
}


Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if(R == nullptr){
        return nil;
    }
    if(R->key == k){
        return R;
    }
    if(R->key > k){
        return search(R->left, k);
    }else{
        return search(R->right, k);
    }
}

Dictionary::Node* Dictionary::findMin(Node* R){
    if(R == nullptr){
        // std::cerr << "findMin(): Empty Dictionary" << std::endl;
        return nil;
    }
    Node* N = R;
    while (N->left != nullptr){
        N = N->left;
    }
    return N;
}

Dictionary::Node* Dictionary::findMax(Node* R){
    if(R == nullptr){
        // std::cerr << "findMax(): Empty Dictionary" << std::endl;
        return nil;
    }
    Node* N = R;
    while (N->right != nullptr){
        N = N->right;
    }
    return N;
}

Dictionary::Node* Dictionary::findNext(Node* N){
    if(N == nullptr || N == nil){
        return nil;
    }
    if(N->right != nullptr){
        return findMin(N->right);
    }
    Node* M = N->parent;
    while(M != nullptr && N == M->right){
        N = M;
        M = M->parent;
    }
    return M == nullptr ? nil : M;
}

Dictionary::Node* Dictionary::findPrev(Node* N){
    if(N == nullptr || N == nil){
        return nil;
    }

    if(N->left != nullptr){
        return findMax(N->left);
    }

    Node* M = N->parent;

    while(M != nullptr && M->left == N){
        N = M;
        M = M->parent;
    }
    return M == nullptr ? nil : M;
}

Dictionary::Dictionary(){
    nil = new Node("NIL", -1);
    // nil = nullptr;
    root = nullptr;
    current = nil;  // undefiend
    num_pairs = 0;
}


Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("NIL", -1);
    // nil = nullptr;
    root = nullptr;
    num_pairs = 0;
    current = nil;

    preOrderCopy(D.root, nullptr);
}

Dictionary::~Dictionary(){
    clear();
    delete nil;
    nil = nullptr;
    current = nullptr;
    root = nullptr;
}

int Dictionary::size() const{
    return num_pairs;
}

// Helper function for contains()
bool containsKey(Dictionary::Node* A, keyType k){
    if(A == nullptr){
        return false;
    }
    return A->key == k || containsKey(A->left, k) || containsKey(A->right, k);
}

bool Dictionary::contains(keyType k) const{
    // Use current;
    if(num_pairs <= 0){
        return false;
    }
    return containsKey(root, k);
}

valType& Dictionary::getValue(keyType k) const{
    if( ! contains(k) ){
        throw std::logic_error("getValue() pre-condition: contains(k)");
    }
    Node* N = search(this->root, k);
    return N->val;
}

bool Dictionary::hasCurrent() const{
    return current == nil ? false : true;
}

keyType Dictionary::currentKey() const{
    if( ! hasCurrent() ){
        // std:: cerr << "currentKey() Pre-condition: hasCurrent()" << std::endl;
        throw std::logic_error("getValue() pre-condition: contains(k)");
    }
    return current->key;
}

valType& Dictionary::currentVal() const{
    if( ! hasCurrent() ){
        // std::cerr << "currentKey() Pre-condition: hasCurrent()" << std::endl;
        throw std::logic_error("getValue() pre-condition: contains(k)");
    }
    return current->val;
}

void Dictionary::clear(){
    // for(begin(); current != nil; next()){
    //     delete search(root, current->key);
    // }
    postOrderDelete(root);
    current = nil;
}

void Dictionary::setValue(keyType k, valType v){
    // use current to iterate all the tree.
    Node* Z = search(root, k);  // segmentation fault
    if(Z != nil){
        Z->val = v;
        return;
    }else{
        Z = new Node(k ,v);
        num_pairs ++;
    }
    Node* M = nullptr;
    Node* N = this->root;
    while(N != nullptr){
        M = N;
        if(Z->key < N->key){
            N = N->left;
        }else{
            N = N->right;
        }
    }
    Z->parent = M;
    if(M == nullptr){
        this->root = Z;
    }else if(Z->key < M->key){
        M->left = Z;
    }else{
        M->right = Z;
    }
}

void transplant(Dictionary* D, Dictionary::Node* U, Dictionary::Node* V){
    if(U->parent == nullptr){
        D->root = V;
    }else if(U == U->parent->left){
        U->parent->left = V;
    }else{
        U->parent->right = V;
    }
    if(V != nullptr){
        V->parent = U->parent;
    }
}

void Dictionary::remove(keyType k){

    // if( ! contains(k) ){
    //     std::cerr << "remove() Pre-condition: hasCurrent()" << std::endl;
    //     throw std::invalid_argument("remove() pre-condition: contains(k)");
    // }
    Node* Z = search(root, k);
    if(Z == nil || Z == nullptr){
        // std::cerr << "remove() Pre-condition: hasCurrent()" << std::endl;
        throw std::logic_error("remove() pre-condition: contains(k)");
    }
    // If that pair is current, then current becomes undefined.
    
    if(Z->left == nullptr){
        transplant(this, Z, Z->right);
    }else if (Z->right == nullptr){
        transplant(this, Z, Z->left);
    }else{
        Node* Y = findMin(Z->right);
        if(Y->parent != Z){
            transplant(this, Y, Y->right);
            Y->right = Z->right;
            Y->right->parent = Y;
        }
        transplant(this, Z, Y);
        Y->left = Z->left;
        Y->left->parent = Y;
    }
    if(Z == current){
        current = nil;
    }
    if(Z->parent != nullptr && Z->parent->right == Z){
        Z->parent->right = nullptr;
    }else if(Z->parent != nullptr && Z->parent->left == Z){
        Z->parent->left = nullptr;
    }
    delete Z;
    num_pairs --;
}

void Dictionary::begin(){
    if(num_pairs <= 0){
        // std::cerr << "Empty Dictionary" << std::endl;
        return;
    }
    // Place current at the left-most Node.
    current = root;
    while (current != nullptr && current->left != nullptr){
        current = current->left;
    }
}

void Dictionary::end(){
    if(num_pairs <= 0){
        // std::cerr << "Empty Dictionary" << std::endl;
        return;
    }
    // Place current at the right-most Node.
    current = root;
    while (current != nullptr && current->right != nullptr){
        current = current->right;
    }
}

bool isAncestor(Dictionary::Node* A, Dictionary::Node* B){
    if(A == nullptr || B == nullptr){
        // std::cerr << "isAncestor(): parameter A or B is nullptr" << std::endl;
        return false;
    }
    Dictionary::Node* left = A->left;
    Dictionary::Node* right = A->right;
    if(left == B || right == B){
        return true;
    }
    return isAncestor(left, B) || isAncestor(right, B);
}

void Dictionary::next(){
    current = findNext(current);
}

void Dictionary::prev(){
    current = findPrev(current);
}

std::string Dictionary::to_string() const{
    std::string s = "";
    // Use current iterator;
    Dictionary D = *this;
    inOrderString(s, D.root);
    return s;
}


std::string Dictionary::pre_string() const{
    Dictionary D = *this;
    std::string s = "";
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const{
    return to_string() == D.to_string();
}

std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ){
    if( this != &D ){ // not self assignment
        // make a copy of D
        Dictionary temp = D;    // copy constructor.

        // then swap the copy's fields with fields of this
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }

    // return this with the new data installed
    return *this;
}