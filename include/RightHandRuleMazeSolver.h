#ifndef RIGHTHANDRULEMAZESOLVER_H
#define RIGHTHANDRULEMAZESOLVER_H

#include "Micromouse.h"
#include "DistanceSensor.h"

class RightHandRuleMazeSolver : public Micromouse {
public:
    RightHandRuleMazeSolver(std::shared_ptr<Maze> maze);
    
    void initialize() override;
    void makeDecision() override;
};

#endif // RIGHTHANDRULEMAZESOLVER_H
