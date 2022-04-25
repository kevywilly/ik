//
// Created by Kevin Williams on 4/23/22.
//

#ifndef IK_UTILS_H
#define IK_UTILS_H

#include <vector>
#include <stdio.h>
#include "types.h"

using namespace std;
namespace ik {

    void printVector(vector<float> v) {
        int s = v.size() - 1;
        int i = 0;
        printf("[");
        for (const auto &value: v) {
            printf("%f", value);
            if (i++ < s)
                printf(", ");

        }
        printf("]");
    }

    void printVector(char *label, vector<float> v) {
        printf("{\"%s\":", label);
        printVector(v);
        printf("}\n");
    }

    vector<float> vectorAdd(vector<float> v, vector<float> offset) {
        vector<float> newVec;
        for(int i=0; i < v.size(); i++) {
            newVec.push_back(v.at(i) + offset.at(i));
        }
        return newVec;
    }

    transform_matrix_t add(transform_matrix_t a, transform_matrix_t b) {
        transform_matrix_t m;
        for(int i=0; i < a.size(); i++) {
            m.push_back(vectorAdd(a.at(i), b.at(i)));
        }
        return m;
    }

}
#endif //IK_UTILS_H
