//
//  Matrix.h
//  Clean
//
//  Created by Alessio Aboudan on 13/10/14.
//  Copyright (c) 2014 IASF. All rights reserved.
//

#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <cstdio>
#include <cstring>

template <typename T>
T** matrixCreate(size_t row, size_t col) {
    
    T **d = new T*[row];
    
    for (size_t i = 0; i < row; i++) {
        d[i] = new T[col];
        memset(d[i], 0, col*sizeof(T));
    }
    
    return d;
    
}

template <typename T>
void matrixDestroy(size_t row, size_t col, T **d) {
    
    for (size_t i = 0; i < row; i++)
        delete []d[i];
    
    delete []d;
    
}

template <typename T>
T*** matrixCreate(size_t row, size_t col, size_t len) {
    
    T ***d = new T**[row];
    
    for (size_t i = 0; i < row; i++) {
        
        d[i] = new T*[col];
        
        for (size_t j = 0; j < col; j++) {
            d[i][j] = new T[len];
            memset(d[i][j], 0, len*sizeof(T));
        }
        
    }
    
    return d;
    
}

template <typename T>
void matrixDestroy(size_t row, size_t col, T ***d) {
    
    for (size_t i = 0; i < row; i++) {
        
        for (size_t j = 0; j < col; j++)
            delete []d[i][j];
        
        delete []d[i];
        
    }
    
    delete []d;
    
}

template <typename T>
void matrixPrint(size_t row, size_t col, T *d) {

    for (size_t i = 0; i < row; i++) {
        
        for (size_t j = 0; j < col; j++)
            printf("%10.2f ", *d++);
        
        printf("\n");
        
    }
    
}

template <typename T>
void matrixPrint(size_t row, size_t col, T **d) {
    
    for (size_t i = 0; i < row; i++) {
        
        for (size_t j = 0; j < col; j++)
            printf("%10.2f ", d[i][j]);
        
        printf("\n");
        
    }
    
}

template <typename T>
void matrixPrint(size_t row, size_t col, size_t len, T ***d) {
    
    for (size_t i = 0; i < row; i++) {
        
        for (size_t j = 0; j < col; j++) {
            
            printf("[ ");
            
            for (size_t k = 0; k < len; k++)
                printf("%3d ", d[i][j][k]);
            
            printf("] ");
        
        }
        
        printf("\n");
    
    }
    
}

#endif // __MATRIX_HPP__
