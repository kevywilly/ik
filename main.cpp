#include <stdio.h>
#include "src/ik/chain.h"
#include "src/ik/inverse.h"

using namespace ik;
int main() {
    // Initialize 4 chains for quadruped

    Chain chains[4] = {
            Chain("c0",{45,0,90}, {24,38,82}, {90,0,0},{0,0,0}),
            Chain("c1", {45,0,90}, {24,38,82}, {90,0,0},{0,0,0}),
            Chain("c2", {45,0,90}, {24,38,82}, {90,0,0},{0,0,0}),
            Chain("c3", {45,0,90}, {24,38,82}, {90,0,0},{0,0,0})
    };

    chains[0].print();
    // Modify target position for chain 0 and 1.
    chains[0].targetAngles = ik3d_transform(&chains[0], {0, 10, 0});
    while(!chains[0].atTarget()) {
        chains[0].moveTowardTarget(1);
    }
    chains[0].print();


    return 0;
}
