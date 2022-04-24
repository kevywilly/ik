//
// Created by Kevin Williams on 4/23/22.
//

#ifndef IK_INVERSE_H
#define IK_INVERSE_H

#include <vector>
#include <math.h>
#include "chain.h"

#ifndef DEGREES
#define DEGREES 57.296
#endif
#ifndef PI
#define PI 3.14159
#endif

namespace ik {

    vector<float> ik3d(Chain *chain, vector<float> pos) {

        float coxa_length = chain->radius.at(0);
        float femur_length = chain->radius.at(1);
        float tibia_length = chain->radius.at(2);

        float x = pos.at(0);
        float y = pos.at(1);
        float z = pos.at(2);

        float lenFemurToTibia;                       // Length between Femur and Tibia
        float radiansFemurTibiaGround;  // Angle of the line Femur and Tibia with respect to the ground in radians
        float radiansFemurTibia;        // Angle of the line Femur and Tibia with respect to the femur in radians
        float distCoxaToGround;                // Distance between the Coxa and Ground Contact

        // Distance between the Coxa and Ground Contact
        distCoxaToGround = sqrt(pow(x, 2) + pow(y, 2));

        // lenFemurToTibia - Length between Femur axis and Tibia
        lenFemurToTibia = sqrt(pow((distCoxaToGround - coxa_length), 2) + pow(z, 2));

        // radiansFemurTibiaGround - Angle between Femur and Tibia line and the ground in radians
        radiansFemurTibiaGround = atan2(distCoxaToGround - coxa_length, z);

        // radiansFemurTibia - Angle of the line Femur and Tibia with respect to the Femur in radians
        radiansFemurTibia = acos(((pow(femur_length, 2) - pow(tibia_length, 2)) + pow(lenFemurToTibia, 2)) /
                                 (2 * femur_length * lenFemurToTibia));


        // Calc angles relative to ZERO

        // ikCoxaAngle in degrees
        float coxa = -(atan2(y, x) * 180 / PI - chain->theta.at(0));

        // ikFemurAngle in degrees
        float femur = -(radiansFemurTibiaGround + radiansFemurTibia) * 180 / PI + 90 - chain->theta.at(1);

        // ikTibiaAngle in degrees
        float tibia = (chain->theta.at(2) - (((acos((pow(femur_length, 2) + pow(tibia_length, 2) - pow(lenFemurToTibia, 2)) /
                                      (2 * femur_length * tibia_length))) * 180) / PI));

        vector<float> result = {coxa, femur, tibia};

        return result;
    };
}
#endif //IK_INVERSE_H
