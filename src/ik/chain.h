//
// Created by Kevin Williams on 4/23/22.
//

#ifndef IK_CHAIN_H
#define IK_CHAIN_H

#include <vector>
#include "utils.h"
#include "math.h"
#include "matrix.h"

using namespace std;

namespace ik {
    constexpr double RADIANS = 0.0174533;

    class Chain {
    public:
        const char *id;
        const vector<float> theta;
        const vector<float> radius;
        const vector<float> alpha;
        const vector<float> dOffset;

        vector<float> angles;
        vector<float> targetAngles;
        vector<float> position;
        vector<float> positionZero;
        vector<Matrix> matrices;
        Matrix *matrix;
        int numLinks;

        Chain() {}
        Chain(const char *id, const vector<float> &theta, const vector<float> &radius, const vector<float> &alpha,
              const vector<float> &dOffset) : id(id), theta(theta), radius(radius), alpha(alpha), dOffset(dOffset) {

            // Set num links
            numLinks = theta.size();

            // Initialize link fk matrices
            for (int i = 0; i < numLinks; i++) {
                matrices.push_back({4, 4, new float[16]});
                angles.push_back(0);
                targetAngles.push_back(0);
            }
            // Create chain fk matrix
            matrix = new Matrix(4, 4);
            calcPosition();
            positionZero = position;
        }

        vector<float> positionOffset(vector<float> offset) {
            return vectorAdd(positionZero, offset);
        }

        void calcPosition() {
            buildMatrices();
            matrix = matrices.at(0).copy();
            for (int i = 1; i < angles.size(); i++) {
                if (i > 0)
                    matrix = (*matrix * &matrices.at(i));
            }
            position.clear();
            position.push_back(matrix->x[3]);
            position.push_back(matrix->x[7]);
            position.push_back(matrix->x[11]);
        }

        void buildMatrices() {
            for (int i = 0; i < angles.size(); i++) {
                buildLinkMatrix(i);
            }
        }

        void buildLinkMatrix(int index) {
            float *data = new float[16];

            float t = angles.at(index) + theta.at(index);
            float a = alpha.at(index);
            float r = radius.at(index);
            float d = dOffset.at(index);

            float cosTheta = cos(t * RADIANS);
            float sinTheta = sin(t * RADIANS);
            float cosAlpha = cos(a * RADIANS);
            float sinAlpha = sin(a * RADIANS);
            data[0] = cosTheta;
            data[1] = -sinTheta * cosAlpha;
            data[2] = sinTheta * sinAlpha;
            data[3] = r * cosTheta;
            data[4] = sinTheta;
            data[5] = cosTheta * cosAlpha;
            data[6] = -cosTheta * sinAlpha;
            data[7] = r * sinTheta;
            data[8] = 0;
            data[9] = sinAlpha;
            data[10] = cosAlpha;
            data[11] = d;
            data[12] = 0;
            data[13] = 0;
            data[14] = 0;
            data[15] = 1;
            matrices.at(index).x = data;
        }

        void print() {
            printf("{");
            printf("\n\t\"chain-id\":\"%s\",", id);
            printf("\n\t\"theta\":");
            printVector(theta);
            printf(",");
            printf("\n\t\"angles\":");
            printVector(angles);
            printf(",");
            printf("\n\t\"target-angles\":");
            printVector(targetAngles);
            printf(",");
            printf("\n\t\"radius\":");
            printVector(radius);
            printf(",");
            printf("\n\t\"alpha\":");
            printVector(alpha);
            printf(",");
            printf("\n\t\"position\":");
            printVector(position);
            printf("\n}\n");
        }

        void moveTowardTarget(float step) {
            if(atTarget())
                return;
            for(int i=0; i < angles.size(); i++) {
                float diff = targetAngles[i] - angles[i];
                if(diff == 0) {
                    continue;
                }
                if(abs(diff) < abs(step)) {
                    angles[i] = targetAngles[i];
                } else {
                    angles[i] = diff > 0 ? angles[i] + step : angles[i] - step;
                }
            }
            calcPosition();
        }
        bool atTarget() {
            return angles == targetAngles;
        }
    };

}
#endif //IK_CHAIN_H
