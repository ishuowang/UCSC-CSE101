#include<string>
#include<sstream>
#include"BigInteger.h"

// BASE = 10^POWER, 0 <= POWER <= 9
const long BASE = 1000000000;   // 1 billion
const int POWER = 9;

// Helper function:
// Normalize BigInteger N.
// Guarantte each element in digits less than BASE.
// Clean front 0 element. eg: 000 000 230 000 000 -> 230 000 000
void normalize(BigInteger& N){
    while(N.digits.length() > 0 && N.digits.front() == 0){
        N.digits.moveFront();
        N.digits.eraseAfter();
    }
    if(N.digits.length() == 0){
        N.signum = 0;
        return;
    }
    
    N.digits.moveBack();
    while(N.digits.position() > 0){
        long carry = 0;
        long elem = N.digits.movePrev();
        if(elem < 0){
            if(N.digits.position() == 0){
                N.digits.setAfter(-elem);
                N.signum *= -1;
                break;
            }
            for(carry = -1; elem + -carry * BASE < 0; carry--) ;
            N.digits.setAfter(elem + -carry * BASE);
        }else if(elem >= BASE){
            carry = 1;
            for(carry = 1; elem + -carry * BASE >= BASE; carry++) ;
            N.digits.setAfter(elem + -carry * BASE);
        }
        if(N.digits.position() > 0){
            long prev_elem = N.digits.movePrev();
            N.digits.setAfter(prev_elem + carry);
            N.digits.moveNext();
        }else if(carry <= -1){
            // TODO
            N.digits.setAfter(- N.digits.front());
            N.signum = -1;
            if(N.digits.front() < 0){
                N.digits.setAfter(BASE + N.digits.front());
                N.digits.moveNext();
                while(N.digits.position() < N.digits.length()){
                    long n = N.digits.moveNext();
                    N.digits.setBefore(BASE - n);
                }
                break;
            }
            
        }else if (carry >= 1){
            N.digits.insertAfter(carry);
        }
    }
    N.digits.moveFront();
}

BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}

BigInteger::BigInteger(std::string s){
    if(s.length() == 0){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    if((s[0] != '-' && s[0] != '+') && (s[0] > '9' || s[0] < '0')){
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    for(int i = s.length() - 1; i > 0; i--){
        if(s[i] > '9' || s[i] < '0'){
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }
    if(s == "0"){
        return;
    }
    // eg: "-1234"
    if(s.substr(0,1) == "-" || s.substr(0,1) == "+"){
        if(s.substr(0,1) == "-"){
            this->signum = -1;
        }else{
            this->signum = 1;
        }
        s = s.substr(1);
    }else{
        this->signum = 1;
    }

    int length = s.length();
    for(int i = 1; length - i * POWER > - POWER; i++){
        // pos and cnt is passed to function substr()
        int pos = length - i * POWER;
        int cnt = POWER;
        // Cut s ito separate POWER length string, 
        // and convert the cutted string to a long number.
        std::string num_str;
        if(pos > 0){
            num_str = s.substr(pos, cnt);
        }else{
            num_str = s.substr(0, pos + POWER);
        }
        long num = std::stol(num_str);
        this->digits.insertAfter(num);
    }
    // if(this->digits.front() < 0){
    //     this->digits.moveFront();
    //     this->digits.setAfter(-this->digits.front());
    //     this->signum = -1;
    // }
}

BigInteger::BigInteger(const BigInteger& N){
    this->signum = N.signum;
    // Use copy constructor
    this->digits = List(N.digits);
}

int BigInteger::sign() const{
    return signum;
}

int BigInteger::compare(const BigInteger& N) const{
    BigInteger ret = this->sub(N);
    return ret.sign();
}

void BigInteger::makeZero(){
    this->signum = 0;
    this->digits.clear();
}

void BigInteger::negate(){
    this->signum *= -1;
}

// TODO: check
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger newM(*this);
    BigInteger newN(N);
    if(newM.sign() != newN.sign()){
        if(newN.sign() > 0){
            return newN.add(newM);
        }
        // return newM - (- newN)
        newN.signum *= -1;
        return newM.sub(newN);
    }
    // perform A = newM + newN
    BigInteger A;
    A.signum = signum;  // *this->signum is equal to N.signum
    List digitsM = newM.digits;
    List digitsN = newN.digits;
    List digitsA;
    digitsM.moveBack();
    digitsN.moveBack();
    while(digitsM.position() > 0 && digitsN.position() > 0){
        long m = digitsM.movePrev();
        long n = digitsN.movePrev();
        digitsA.insertAfter(m + n);
    }
    // Insert rest ListElement in digitsM or digitsN into digitsA
    while(digitsM.position() > 0){
        long m = digitsM.movePrev();
        digitsA.insertAfter(m);
    }
    while(digitsN.position() > 0){
        long n = digitsN.movePrev();
        digitsA.insertAfter(n);
    }
    A.digits = digitsA;
    normalize(A);
    return A;
}

BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger newM(*this);
    BigInteger newN(N);

    // eg: 100 - (-20) = 100 + 20
    if(newM.sign() != newN.sign()){
        // return newM + (- newN )
        newN.signum *= -1;
        return newM.add(newN);
    }
    // make the bigone minus the littleone
    if(newN.digits.length() > newM.digits.length() ){
        BigInteger temp = newN - newM;
        temp.signum *= -1;
        return temp;
    }
    // Make sure front() function is used under pre-condition
    if( newN.digits.length() == newM.digits.length() ){
        if(newN.digits.length() > 0){
            if(newN.digits.front() > newM.digits.front()){
                BigInteger temp = newN - newM;
                temp.signum *= -1;
                return temp;
            }
        }
    }
    // perform A = newM + newN
    BigInteger A;
    A.signum = newM.signum;
    List digitsM = newM.digits;
    List digitsN = newN.digits;
    List digitsA;
    digitsM.moveBack();
    digitsN.moveBack();
    while(digitsM.position() > 0 && digitsN.position() > 0){
        long m = digitsM.movePrev();
        long n = digitsN.movePrev();
        digitsA.insertAfter(m - n);
        // digitsA.insertAfter(m - n > 0 ? m - n : n - m);
        // if(newM.sign() < 0 && newN.sign() < 0){
        //     digitsA.insertAfter(m - n > 0 ? m - n : n - m);
        // }else{
        //     digitsA.insertAfter(m - n);
        // }
    }
    // Insert rest ListElement in digitsM or digitsN into digitsA
    while(digitsM.position() > 0){
        long m = digitsM.movePrev();
        digitsA.insertAfter(m);
    }
    while(digitsN.position() > 0){
        long n = digitsN.movePrev();
        digitsA.insertAfter(-n);
    }
    A.digits = digitsA;
    normalize(A);
    return A;
}



void shift(BigInteger& N, int s){
    int pos = N.digits.position();
    N.digits.moveBack();
    for(int i = 0; i < s; i++){
        N.digits.insertBefore(0);
    }

    // recovery position.
    while(N.digits.position() != pos){
        if(N.digits.position() < pos){
            N.digits.moveNext();
        }else{
            N.digits.moveFront();
        }
    }
}

// TODO: Too slow
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger newM(*this);
    BigInteger newN(N);
    BigInteger A;
    if(newM.sign() != newN.sign()){
        A.signum = -1;
    }else{
        A.signum = 1;
    }
    List digitsM = newM.digits;
    List digitsN = newN.digits;
    List digitsA;
    digitsM.moveBack();
    int SHIFT = 0;
    while(digitsM.position() > 0){
        BigInteger scalerMult;
        scalerMult.signum = A.signum;
        long m = digitsM.movePrev();
        digitsN.moveBack();
        while(digitsN.position() > 0){
            long n = digitsN.movePrev();
            scalerMult.digits.insertAfter(m * n);
            scalerMult.digits.moveFront();
            // Shift N with i position, and padding with 0;
        }
        shift(scalerMult, SHIFT);
        // A += scalerMult;    // TODO: rewrite the add operation, do not use add function.
        // int pos = scalerMult.digits.position();
        A.digits.moveBack();
        scalerMult.digits.moveBack();
        while(A.digits.position() > 0 && scalerMult.digits.position() > 0){
            long a = A.digits.movePrev();
            long b = scalerMult.digits.movePrev();
            A.digits.setAfter(a + b);
        }
        while(scalerMult.digits.position() > 0){
            long b = scalerMult.digits.movePrev();
            A.digits.moveFront();
            A.digits.insertAfter(b);
        }
        // Recovery position
        // while(scalerMult.digits.position() != pos){
        //     if(scalerMult.digits.position() > pos){
        //         scalerMult.digits.movePrev();
        //     }else{
        //         scalerMult.digits.moveNext();
        //     }
        // }
        SHIFT ++;
    }
    normalize(A);

    return A;
}

std::string BigInteger::to_string(){
    if(this->signum == 0){
        return "0";
    }
    std::string s = "";
    if(this->signum == -1){
        s += '-';
        // +-------------------------------+ DEBUG USE +-------------------------------+ //
        // s += ' ';
        // +-------------------------------+ DEBUG END +-------------------------------+ //
    }
    digits.moveFront();
    while(digits.position() < digits.length()){
        long elem = digits.moveNext();
        std::string elem_str = std::to_string(elem);

        // Padding with 0.
        while(digits.position() != 1 && elem_str.length() < POWER){
            elem_str = '0' + elem_str;
        }
        s += elem_str;
        
        // Add some space between two digit.
        // +-------------------------------+ DEBUG USE +-------------------------------+ //
        // if(digits.position() < digits.length()){
        //     s += " ";
        // } 
        // +-------------------------------+ DEBUG END +-------------------------------+ //
    }
    return s;
}

std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ){
    BigInteger ret = A.sub(B);
    return ret.sign() == 0 ? true : false;
}

bool operator<( const BigInteger& A, const BigInteger& B ){
    BigInteger ret = A.sub(B);
    return ret.sign() < 0 ? true : false;
}

bool operator<=( const BigInteger& A, const BigInteger& B ){
    BigInteger ret = A.sub(B);
    return ret.sign() <= 0 ? true : false;
}

bool operator>( const BigInteger& A, const BigInteger& B ){
    BigInteger ret = A.sub(B);
    return ret.sign() > 0 ? true : false;
}

bool operator>=( const BigInteger& A, const BigInteger& B ){
    BigInteger ret = A.sub(B);
    return ret.sign() >= 0 ? true : false;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A.mult(B);
}