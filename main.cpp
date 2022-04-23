#include <stdio.h>
#include "src/ik/chain.h"
#include "src/ik/inverse.h"

using namespace ik;
int main() {
    Chain chains[4] = {
            Chain("c0", {45,0,90}, {24,38,77}, {90,0,0},{0,0,0}),
            Chain("c1",{45,0,90}, {24,38,77}, {90,0,0},{0,0,0}),
            Chain("c2",{45,0,90}, {24,38,77}, {90,0,0},{0,0,0}),
            Chain("c3",{45,0,90}, {24,38,77}, {90,0,0},{0,0,0})
    };
    for(int i=0; i < 4; i++) {
        chains[i].print();
    }

    vector<float> target = chains[0].position;
    target.at(2) = 50;
    chains[0].targetAngle = ik3d(&chains[0], target);

    while(!chains[0].atTarget()) {
        chains[0].moveTowardTarget(1);
        chains[0].print();
    }


    return 0;
}
