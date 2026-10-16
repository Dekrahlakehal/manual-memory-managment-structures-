#include <stdio.h> // for input output functions like the printf and stuff 
#include <stdlib.h> // for memeory managment fucntions like memory and free 
#include <string.h> // for string manipulation functions like memcpy strlen strcmp etc
#include <stdbool.h> // for boolean data type and values true and false


typedef struct {
    unsigned char *data ; // pointer to the raw heap memeory block 
    size_t capacity ; // total bytes rented for this buffer 
    size_t size ; // how many bytes are currently used  for this buffer   btw size_t is jusst a data type like int  or float but it is used to represent sizes of objects in bytes  and it is guaranteed to be able to represent the size of the largest possible object on the target platform 
} Bytebuffer ; // a simple buffer sturct to hold raw bytes  btw we coudlve used just a raw pointer but this is easier to manager  like this we dont need to resize our buffer every time we append data 


Bytebuffer *bb_create(size_t initial_capacity) {
    Bytebuffer *buf_pointer = (Bytebuffer *)malloc(sizeof(Bytebuffer)); // allocate memory for the buffer struct 
    if (!buf_pointer) { // check if the allocation was successful 
        return NULL; // return NULL if allocation failed  EX it can fail if system ran out of memory  or for os safety limits z3ma maykhlikch u alocate more than a specifc size per program 
    }
    buf_pointer->data = (unsigned char *)malloc(initial_capacity); // allocate memory for the data buffer
    if (!buf_pointer->data) { // check if the allocation was successful 
        free(buf_pointer); // free the buffer struct if data allocation failed 
        return NULL; // return NULL if allocation failed 
    }
    buf_pointer->capacity = initial_capacity; // set the initial capacity 
    buf_pointer->size = 0; // initialize size to 0 
    return buf_pointer; // return the newly created buffer 
}


bool bb_push(Bytebuffer *buf, const unsigned char *data, size_t data_size) {
    if (buf->size + data_size > buf->capacity) { // check if we need to resize the buffer 
        size_t new_capacity = buf->capacity * 2; // double the capacity 
        while (new_capacity < buf->size + data_size) { // ensure new capacity is enough 
            new_capacity *= 2; // keep doubling until it's enough 
        }
        unsigned char *new_data = (unsigned char *)realloc(buf->data, new_capacity); // reallocate memory for the data buffer
        if (!new_data) { // check if the reallocation was successful 
            return false; // return false if reallocation failed 
        }
        buf->data = new_data; // update the data pointer to the new memory block 
        buf->capacity = new_capacity; // update the capacity 
    }
    memcpy(buf->data + buf->size, data, data_size); // copy the new data into the buffer 
    buf->size += data_size; // update the size of the buffer 
    return true; // return true indicating success 
}


void bb_free(Bytebuffer *buf) {
    if (buf) { // check if the buffer pointer is not NULL 
        free(buf->data); // free the data buffer 
        free(buf); // free the buffer struct 
    }
}