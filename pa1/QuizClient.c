#include<stdio.h>

#include"List.h"

// Return true if the integer sequence represented by 𝐿 is a palindrome 
// (i.e. is identical to its own reversal), and will return false if 𝐿 is not a palindrome.
bool isPalindrome(List L){
	List copyL = copyList(L);
    // Store the curosr location
    int origin = index(L);
    moveFront(L);
    moveBack(copyL);
    while(index(L) >= 0 && index(copyL) >= 0){
        int x = get(L);
        int copyX = get(copyL);
        if(x != copyX){
            return false;
        }
        moveNext(L);
        movePrev(copyL);
    }
    freeList(&copyL);
    // Recover the curosr location
    moveFront(L);
    while(index(L) != origin){
        moveNext(L);
    }
    return true;
}

// Replace the first (i.e. closest to front) occurrence of 𝑥 in 𝐿 with 𝑦. 
// If 𝑥 is not in 𝐿, your function will make no changes to the integer sequence in 𝐿.
void Replace(List L, int x, int y){
    // Store the curosr location
    int origin = index(L);
    moveFront(L);
    while(index(L) >= 0){
        int data = get(L);
        if(data == x){
            set(L, y);
            break;
        }
        moveNext(L);
    }
    // Recover the curosr location
    moveFront(L);
    while(index(L) != origin){
        moveNext(L);
    }
}

int main(int argc, char const *argv[])
{
    List L = newList();
    append(L,1);
    append(L,2);
    append(L,3);
    append(L,4);
    append(L,4);
    append(L,3);
    append(L,2);
    append(L,1);
    if(isPalindrome(L)){
        printf("This list is a Palindrome !\n");
    }else{
        printf("This list is not a Palindrome !\n");
    }
    Replace(L,3,5);
    printList(stderr,L);
    if(isPalindrome(L)){
        printf("This list is a Palindrome !\n");
    }else{
        printf("This list is not a Palindrome !\n");
    }
    return 0;
}
