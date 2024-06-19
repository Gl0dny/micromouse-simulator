#ifndef RIGHTHANDRULEMAZESOLVER_H
#define RIGHTHANDRULEMAZESOLVER_H

#include "Micromouse.h"
// #include "DistanceSensor.h"

class RightHandRuleMazeSolver : public Micromouse {
public:
    RightHandRuleMazeSolver();
    void readSensors() override;
    void makeDecision() override;

private:
    // std::unique_ptr<DistanceSensor> distanceSensor;
};

#endif // RIGHTHANDRULEMAZESOLVER_H