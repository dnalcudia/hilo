//
//  CC.hpp
//  HiLo
//
//  Created by Angel Daniel Alcudia on 2/17/19.
//  Copyright © 2019 Angel Daniel Alcudia. All rights reserved.
//

#ifndef CC_hpp
#define CC_hpp

#include <stdio.h>
#include <ctime>
#include <unistd.h>
#include <iomanip>
#include "Normal.hpp"

class CC : public Normal{
protected:
    int range;
    int dummyAttempd; //Contador de intentos dummy.
    int totalNumbers[100]; //Arreglo de números disponibles.
    int lowLimit,uppLimit; //Límites del rango.
    time_t initialInstant, finalInstant, secs; //Variables para calcular el tiempo transcurrido en cada jugada.
public:
    CC(int secret, int counter, int counterAssist, int attempd, int finalScore, int range);
    int decision(); //Función que genera un número aleatorio "cambiante" para decidir la ayuda que se brindará al usuario. --TEMPORAL--
    void start();
};
#endif /* CC_hpp */
