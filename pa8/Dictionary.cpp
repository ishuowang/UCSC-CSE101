#include<string>
#include<iostream>
#include"Dictionary.h"

#define BLACK -1
#define RED 1

// Dictionary::Node* NIL = new Dictionary::Node("NIL", -1);

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    color = RED;    // TODO: check
    // TODO: how to make this field point to nil.
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R->key == "NIL"){
        return;
    }
    inOrderString(s, R->left);
    s += R->key + " : " + std::to_string(R->val) + "\n";
    inOrderString(s, R->right);
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R->key == "NIL"){
        return;
    }
    s += R->key + "\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
}


void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R->key == "NIL"){
        return;
    }
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

void Dictionary::postOrderDelete(Node* R){
    if(R->key == "NIL"){
        return;
    }
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    delete R;
    num_pairs --;
}


Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if(R == nullptr || R->key == "NIL" || R == nil){
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
    if(R->key == "NIL" || R == nil){
        // std::cerr << "findMin(): Empty Dictionary" << std::endl;
        return nil;
    }
    Node* N = R;
    while (N->left != nil ){
        N = N->left;
    }
    return N;
}

Dictionary::Node* Dictionary::findMax(Node* R){
    if(R->key == "NIL" || R == nil){
        // std::cerr << "findMax(): Empty Dictionary" << std::endl;
        return nil;
    }
    Node* N = R;
    while (N->right != nil){
        N = N->right;
    }
    return N;
}

Dictionary::Node* Dictionary::findNext(Node* N){
    if(N == nullptr || N == nil || N->key == "NIL"){
        return nil;
    }
    if(N->right != nil){
        return findMin(N->right);
    }
    Node* M = N->parent;
    while(M != nil && N == M->right){
        N = M;
        M = M->parent;
    }
    return M == nil ? nil : M;
}

Dictionary::Node* Dictionary::findPrev(Node* N){
    if(N == nullptr || N == nil || N->key == "NIL"){
        return nil;
    }

    if(N->left != nil){
        return findMax(N->left);
    }

    Node* M = N->parent;

    while(M != nil && M->left == N){
        N = M;
        M = M->parent;
    }
    return M == nil ? nil : M;
}

// TODO: helper function.
// LeftRotate()
void Dictionary::LeftRotate(Node* N){
    Node* M = N->right;
    N->right = M->left;
    if(M->left != nil){
        M->left->parent = N;
    }
    M->parent = N->parent;
    if(N->parent == nil){
        root = M;
    }else if(N == N->parent->left){
        N->parent->left = M;
    }else{
        N->parent->right = M;
    }
    M->left = N;
    N->parent = M;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
    Node* M = N->left;

    N->left = M->right;
    if(M->right != nil){
        M->right->parent = N;
    }
    M->parent = N->parent;
    if(N->parent == nil){
        root = M;
    }else if(N == N->parent->right){
        N->parent->right = M;
    }else{
        N->parent->left = M;
    }
    M->right = N;
    N->parent = M;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
    while(N->parent->color == RED){
        if(N->parent == N->parent->parent->left){
            Node* M = N->parent->parent->right;
            if(M->color == RED){
                N->parent->color = BLACK;
                M->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }else {
                if(N == N->parent->right){
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }else{
            Node* M = N->parent->parent->left;
            if(M->color == RED){
                N->parent->color = BLACK;
                M->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }else {
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

// RB_Transplant()
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

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
    while(N != root && N->color == BLACK){
        if(N == N->parent->left){
            Node* M = N->parent->right;
            if(M->color == RED){
                M->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                M = N->parent->right;
            }
            if(M->left->color == BLACK && N->right->color == BLACK){
                M->color = RED;
                N = N->parent;
            }else{
                if(M->right->color == BLACK){
                    M->left->color = BLACK;
                    M->color = RED;
                    RightRotate(M);
                    M = N->parent->right;
                }
                M->color = N->parent->color;
                N->parent->color = BLACK;
                M->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        }else{
            Node* M = N->parent->left;
            if(M->color == RED){
                M->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                M = N->parent->left;
            }
            if(M->right->color == BLACK && N->left->color == BLACK){
                M->color = RED;
                N = N->parent;
            }else{
                if(M->left->color == BLACK){
                    M->right->color = BLACK;
                    M->color = RED;
                    LeftRotate(M);
                    M = N->parent->left;
                }
                M->color = N->parent->color;
                N->parent->color = BLACK;
                M->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
    Node* Y = N;
    Node* X = nil;
    int Y_ORIGIN_COLOR = Y->color;
    if(Y->left == nil){
        X = N->right;
        RB_Transplant(N, N->right);
    }else if(N->right == nil){
        X = N->left;
        RB_Transplant(N, N->left);
    }else{
        Y = findMin(N->right);
        Y_ORIGIN_COLOR = Y->color;
        X = Y->right;
        if(Y->parent == N){
            X->parent = Y;
        }else{
            RB_Transplant(Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
        }
        RB_Transplant(N, Y);
        Y->left = N->left;
        Y->left->parent = Y;
        Y->color = N->color;
    }
    if(Y_ORIGIN_COLOR == BLACK){
        RB_DeleteFixUp(X);
    }
}


Dictionary::Dictionary(){
    // nil = nullptr;
    nil = new Node("NIL", -1);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = BLACK;
    root = nil;
    current = nil;  // undefiend
    num_pairs = 0;
}


Dictionary::Dictionary(const Dictionary& D){
    // nil = nullptr;
    nil = new Node("NIL", -1);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
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
bool containsKey(Dictionary::Node* A, Dictionary::Node* nil, keyType k){
    if(A == nil){
        return false;
    }
    return A->key == k || containsKey(A->left, nil, k) || containsKey(A->right, nil, k);
}

bool Dictionary::contains(keyType k) const{
    // Use current;
    if(num_pairs <= 0){
        return false;
    }
    return containsKey(root, nil, k);
}

valType& Dictionary::getValue(keyType k) const{
    if( ! contains(k) ){
        throw std::logic_error("Dictionary: getValue(): key " + k + " does not exist");
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
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

valType& Dictionary::currentVal() const{
    if( ! hasCurrent() ){
        // std::cerr << "currentKey() Pre-condition: hasCurrent()" << std::endl;
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}

void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
}


// TODO: different with BST
void Dictionary::setValue(keyType k, valType v){
    // use current to iterate all the tree.
    Node* Z = search(root, k);      // TODO: segementation fault
    if(Z != nil){
        Z->val = v;
        return;
    }else{
        Z = new Node(k ,v);
        if(k != "NIL"){
            Z->left = nil;
            Z->right = nil;
            Z->parent = nil;
        }
        num_pairs ++;
    }
    Node* M = nil;
    Node* N = this->root;
    while(N != nil){
        M = N;
        if(Z->key < N->key){
            N = N->left;
        }else{
            N = N->right;
        }
    }
    Z->parent = M;
    if(M == nil){
        this->root = Z;
    }else if(Z->key < M->key){
        M->left = Z;
    }else{
        M->right = Z;
    }
    Z->left = nil;
    Z->right = nil;
    Z->color = RED;
    RB_InsertFixUp(Z);
}

void transplant(Dictionary* D, Dictionary::Node* U, Dictionary::Node* V){
    if(U->parent == D->nil){
        D->root = V;
    }else if(U == U->parent->left){
        U->parent->left = V;
    }else{
        U->parent->right = V;
    }
    if(V != D->nil){
        V->parent = U->parent;
    }
}


// TODO: different with BST
void Dictionary::remove(keyType k){
    Node* Z = search(root, k);
    if(Z == nil || Z == nullptr){
        // std::cerr << "remove() Pre-condition: hasCurrent()" << std::endl;
        throw std::logic_error("Dictionary: remove(): key " + k + " does not ");
    }
    
    // if(Z->left == nil){
    //     transplant(this, Z, Z->right);
    // }else if (Z->right == nil){
    //     transplant(this, Z, Z->left);
    // }else{
    //     Node* Y = findMin(Z->right);
    //     if(Y->parent != Z){
    //         transplant(this, Y, Y->right);
    //         Y->right = Z->right;
    //         Y->right->parent = Y;
    //     }
    //     transplant(this, Z, Y);
    //     Y->left = Z->left;
    //     Y->left->parent = Y;
    // }
    RB_Delete(Z);
    // // If the removed pair is current, then current becomes undefined.
    if(Z == current){
        current = nil;
    }
    if(Z->parent != nil && Z->parent->right == Z){
        Z->parent->right = nil;
    }else if(Z->parent != nil && Z->parent->left == Z){
        Z->parent->left = nil;
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
    while (current != nil && current->left != nil){
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
    while (current != nil && current->right != nil){
        current = current->right;
    }
}

// bool isAncestor(Dictionary::Node* A, Dictionary::Node* B){
//     if(A == nullptr || B == nullptr){
//         // std::cerr << "isAncestor(): parameter A or B is nullptr" << std::endl;
//         return false;
//     }
//     Dictionary::Node* left = A->left;
//     Dictionary::Node* right = A->right;
//     if(left == B || right == B){
//         return true;
//     }
//     return isAncestor(left, B) || isAncestor(right, B);
// }

void Dictionary::next(){
    if( ! hasCurrent() ){
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    current = findNext(current);
}

void Dictionary::prev(){
    if( ! hasCurrent() ){
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    current = findPrev(current);
}

std::string Dictionary::to_string() const{
    std::string s = "";
    // Use current iterator;
    Dictionary D = *this;       // TODO: D's nil is not equals to *this's nil
    inOrderString(s, D.root);   // FIXME: inOrderString
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