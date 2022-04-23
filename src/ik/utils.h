//
// Created by Kevin Williams on 4/23/22.
//

#ifndef IK_UTILS_H
#define IK_UTILS_H

#include <vector>
#include <stdio.h>

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

}
#endif //IK_UTILS_H
