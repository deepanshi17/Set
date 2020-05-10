/*
 * Copy the contents of header.txt (filled out) and paste here
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }

    destroySet(self);
    createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    int mid;
    int low;
    int high;

    low = 0;
    high = self->len - 1;

    while (high >= low) {
        mid = (high + low) / 2;
        if (self->elements[mid] < x) {
            low = mid + 1;
        }
        else if (self->elements[mid] > x) {
            high = mid - 1;
        }
        else {
            return true;
        }
    }

    return false; // not found
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elements[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    int j = -1;
    for (int i = 0; i < self->len; i++) {
        if (self->elements[i] == x) {
            j = i;
        }
    }
    if (j != -1) {
    } else {
        self->elements = (int *) realloc(self->elements, ((self->len) + 1) * sizeof(int));
        self->elements[self->len] = x;
        self->len++;
        int j = 0;
        int temp = 0;
        for (int i = 1; i < self->len; i++) {
            j = i;
            while (j > 0 && self->elements[j] < self->elements[j - 1]) {
                temp = self->elements[j];
                self->elements[j] = self->elements[j - 1];
                self->elements[j - 1] = temp;
                j--;
            }
        }
    }
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    int j = -1;
    for (int i = 0; i < self->len; i++) {
        if (self->elements[i] == x) {
            j = i;
        }
    }
    if (j == -1) {
    } else {
        for (; j < (self->len) - 1; j++) {
            self->elements[j] = self->elements[j + 1];
        }
        self->len--;
    }
}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if(self->len != other->len){
        return false;
    }
    if(isEmptySet(self)){
        return true;
    }
    for(int i=0; i<(self->len); i++){
        if(self->elements[i] != other->elements[i]){
            return false;
        }
    }
    return true;
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    if(isEmptySet(self)){
        return true;
    }
    if(isEmptySet(other)){
        return false;
    }
    if(self->len > other->len){
        return false;
    }
    int *selfFirst = &(self->elements[0]);
    int *otherFirst = &(other->elements[0]);
    for(int i=0; i<self->len; i++){
        if (*selfFirst < *otherFirst) {
            return false;
        } else if (*otherFirst < *selfFirst) {
            otherFirst++;
        } else {
            selfFirst++;
            otherFirst++;
        }
    }
    return true;
}

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    int i = 0;
    if (isEmptySet(self)) {
    } else if (isEmptySet(other)) {
        self->len = 0;
    } else {
        int *selfFirst = &(self->elements[0]);
        int *selfLast = &(self->elements[self->len]);
        int *otherFirst = &(other->elements[0]);
        int *otherLast = &(other->elements[other->len]);
        struct Set* result = (struct Set*) malloc(sizeof(struct Set) * self->len);
        result->elements = (int*)malloc(self->len*sizeof(int));
        result->len = 0;
        while (selfFirst != selfLast && otherFirst != otherLast) {
            if (*selfFirst < *otherFirst) {
                selfFirst++;
            } else if (*otherFirst < *selfFirst) {
                otherFirst++;
            } else {
                result->elements[i] = *selfFirst;
                i++;
                result->len++;
                selfFirst++;
                otherFirst++;
            }
        }
        for(int i=0; i<result->len; i++){
            self->elements[i] = result->elements[i];
        }
        self->len = result->len;
        free(result->elements);
        free(result);
    }
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    if(isEmptySet(self)){
    }
    else if(isEmptySet(other)){
    }
    else {
        int* selfFirst = &(self->elements[0]);
        int* selfLast = &(self->elements[self->len]);
        int* otherFirst = &(other->elements[0]);
        int* otherLast = &(other->elements[other->len]);
        struct Set* result = (struct Set*) malloc(sizeof(struct Set) * self->len);
        result->elements = (int*)calloc(self->len, sizeof(int));
        result->len = 0;
        int i=0;
        while (selfFirst!=selfLast && otherFirst!=otherLast){
            if (*selfFirst<*otherFirst){
                result->elements[i] = *selfFirst;
                result->len++;
                i++;
                selfFirst++;
            }
            else if(*otherFirst<*selfFirst){
                otherFirst++;
            }
            else {
                selfFirst++;
                otherFirst++;
            }
        }
        while(selfFirst != selfLast){
            result->elements[i] = *selfFirst;
            result->len++;
            i++;
            selfFirst++;
        }
        for(int i=0; i<result->len; i++){
            self->elements[i] = result->elements[i];
        }
        self->len = result->len;
        free(result->elements);
        free(result);
    }
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    if (isEmptySet(self)) {
        self->elements = (int*) realloc(self->elements, sizeof(int)*other->len);
        for(int i=0; i<other->len; i++){
            self->elements[i] = other->elements[i];
        }
        self->len = other->len;
    } else if (isEmptySet(other)) {
    } else {
        int *selfFirst = &(self->elements[0]);
        int *selfLast = &(self->elements[self->len]);
        int *otherFirst = &(other->elements[0]);
        int *otherLast = &(other->elements[other->len]);
        struct Set* result = (struct Set*) malloc(sizeof(struct Set) * self->len);
        result->elements = (int*)calloc((self->len+other->len), sizeof(int));
        result->len = 0;
        int i=0;
        while (selfFirst != selfLast && otherFirst != otherLast) {
            if (*selfFirst < *otherFirst) {
                result->elements[i] = *selfFirst;
                result->len++;
                i++;
                selfFirst++;
            } else if (*otherFirst < *selfFirst) {
                result->elements[i] = *otherFirst;
                result->len++;
                i++;
                otherFirst++;
            } else {
                result->elements[i] = *selfFirst;
                result->len++;
                i++;
                selfFirst++;
                otherFirst++;
            }
        }
        if(selfFirst != selfLast){
            while(selfFirst != selfLast){
                result->elements[i] = *selfFirst;
                result->len++;
                i++;
                selfFirst++;
            }
        }
        if(otherFirst != otherLast){
            while(otherFirst != otherLast){
                result->elements[i] = *otherFirst;
                result->len++;
                i++;
                otherFirst++;
            }
        }
        self->elements = (int*)realloc(self->elements, sizeof(int)*result->len);
        for(int i=0; i<result->len; i++){
            self->elements[i] = result->elements[i];
        }
        self->len = result->len;
        free(result->elements);
        free(result);
    }
}
