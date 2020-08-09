//
//  Normal.hpp
//  HiLo
//
//  Created by Angel Daniel Alcudia on 2/16/19.
//  Copyright © 2019 Angel Daniel Alcudia. All rights reserved.
//

#ifndef Normal_hpp
#define Normal_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

class Normal{
protected:
    int secret, counter, counterAssist, attempd, exit, finalScore;
public:
    Normal(int secret=0, int counter=0, int counterAssist=0, int attempd=0, int finalScore=0);
    void start();
    void win();
};
#endif /* Normal_hpp */
