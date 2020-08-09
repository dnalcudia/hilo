//
//  AI.hpp
//  HiLo
//
//  Created by Angel Daniel Alcudia on 2/16/19.
//  Copyright © 2019 Angel Daniel Alcudia. All rights reserved.
//

#ifndef AI_hpp
#define AI_hpp

#include <stdio.h>
#include <ctime>
#include <unistd.h>
#include <iomanip>
#include "Normal.hpp"

class AI : public Normal{
protected:
    int range;
    int totalNumbers[100], temporaryNumbers[100];   //Arreglos que almacenan el total de números y los números disponibles (AI).
    int divider[4];//Total de números disponibles por ayuda.
    int lowLimit,uppLimit; //Límites del rango.
    float probabilties[4]; //Probabilidades de ganar por ayuda.
public:
    AI(int secret, int counter, int counterAssist, int attempd, int finalScore, int range);
    int decision();  //Función que según la mayor posiblidad de ganar, devuelve un tipo de ayuda.
    void start();
};
#endif /* AI_hpp */
