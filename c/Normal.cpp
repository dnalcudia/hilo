//
//  Normal.cpp
//  HiLo
//
//  Created by Angel Daniel Alcudia on 2/16/19.
//  Copyright © 2019 Angel Daniel Alcudia. All rights reserved.
//

#include "Normal.hpp"

Normal::Normal(int secret, int counter, int counterAssist, int attempd, int finalScore){
    this->secret = secret;
    this->counter = counter;
    this->counterAssist = counterAssist;
    this->attempd = attempd;
    this->finalScore = finalScore;
}
void Normal::start(){
    //Empezando a jugar.
    cout << "\nEl número aleatorio ha sido creado satisfactoriamente, ¿qué número es? ";
    cin >> this->attempd;
    
    while(this->attempd!=this->secret){
        if(this->attempd>100 || this->attempd<=0){   //Validando que el intento esté dentro del rango.
            cout << "\nSolo se aceptan números entre 1 - 100. Inténtalo de nuevo: "; cin >> this->attempd;
        }else{
        this->counter++;
        if(this->attempd>this->secret){ //Las ayudas tienen un valor predeterminado de 2.
            this->counterAssist = this->counterAssist + 2;
            cout << "\nTe pasaste. Inténtalo de nuevo: "; cin >>this->attempd;
        }else if(this->attempd<this->secret){
            this->counterAssist = this->counterAssist + 2;
            cout << "\nTe quedaste corto. Inténtalo de nuevo: "; cin >>this->attempd;
        }
    }
}
    win();
}

void Normal::win(){
    //Una vez que ganas se muestra el número secreto y tu puntuación final.
    cout << endl << "¡Felicidades, lo has logrado! El número secreto es " << this->secret << "." << endl <<
    "\nTu cantidad de intentos fue: " << this->counter << "\nTus ayudas totales suman: " <<
    this->counterAssist << "\nTu puntuación final es " << (this->finalScore = (this->counter + this->counterAssist)) << "." << endl << endl;
}
