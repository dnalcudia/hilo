//
//  CC.cpp
//  HiLo
//
//  Created by Angel Daniel Alcudia on 2/17/19.
//  Copyright © 2019 Angel Daniel Alcudia. All rights reserved.
//

#include "CC.hpp"

CC::CC(int secret, int counter, int counterAssist, int attempd, int finalScore,int range){ ::
    Normal(secret, counter, counterAssist, attempd, finalScore);
    this->secret = secret;
    this->counter = counter;
    this->counterAssist = counterAssist;
    this->attempd = attempd;
    this->finalScore = finalScore;
    this->range = range;
    this->lowLimit = this->secret-this->range-20; //Definiendo los rangos para el tipo de ayuda explícita.
    this->uppLimit = this->secret + this->range;
    if(this->lowLimit<0){this->lowLimit = 0;} if(this->uppLimit>100){this->uppLimit = 100;} //Validando los rangos.
    this->dummyAttempd = 0;
    for (int i=0; i<100; i++) { this->totalNumbers[i] = (i+1); }    //Inicializando el arreglo de números.
}

int CC::decision(){ //Método que decide el tipo de ayuda que se dará al jugador en función del perfil de jugador.
    int decision=0;
    
    if(this->secs<=3 && this->dummyAttempd==0){ //0-Hábil/Concentrado.
        decision=0;
        this->totalNumbers[attempd-1] = 0; //Discriminando números según la ayuda.
    } else if(this->secs>3 && this->dummyAttempd==0){   //1-Hábil/Distraido.
        decision=1;
        if(attempd>this->secret){ //Intento > número secreto.
            for (int i=(attempd-1); i<=100; i++) {
                this->totalNumbers[i] = 0;
            }
        }else if(attempd<this->secret){ //Intento < número secreto.
            for (int i=0; i<=(attempd-1); i++) {
                this->totalNumbers[i] = 0;
            }
        }
    } else if(this->secs<=3 && this->dummyAttempd>0){   //2-Tonto/Concentrado.
        decision=2;
        if(((this->attempd -this->secret)<0)&&((this->attempd - this->secret)>=-10)){   //Un poco bajo.
            for (int i=0; i<=attempd-1; i++) {
                this->totalNumbers[i] = 0;
            }
        }else if(((this->attempd - this->secret)>0)&&((this->attempd - this->secret)<=20)){ //Un poco alto.
            for (int i=attempd-1; i<=100; i++) {
                this->totalNumbers[i] = 0;
            }
        }else if(((this->attempd - this->secret)<-10)&&((this->attempd - this->secret)>=-99)){   //Demasiado bajo.
            for (int i=0; i<=attempd-1; i++) {
                this->totalNumbers[i] = 0;
            }
        }else if(((this->attempd - this->secret)>10)&&((this->attempd -this->secret)<=99)){  //Demasiado alto.
            for (int i=attempd-1; i<=100; i++) {
                this->totalNumbers[i] = 0;
            }
        }
    } else if(this->secs>3 && this->dummyAttempd>0){    //3-Tonto/Distraido.
        decision=3;
        for (int i=0; i<(this->lowLimit-1); i++) { this->totalNumbers[i] = 0; }
        for (int j=this->uppLimit; j<=100; j++) { this->totalNumbers[j] = 0; }
    }
    
    return decision;
}

void CC::start(){

    //Empezando a jugar;
    cout << "\nEl número aleatorio ha sido creado satisfactoriamente, ¿qué número es? ";
    cin >> this->attempd;
    
    while(this->attempd!=this->secret){
        if(this->attempd>100 || this->attempd<=0){   //Validando que el intento esté dentro del rango.
            cout << "\nSolo se aceptan números entre 1 - 100. Inténtalo de nuevo: "; cin >> this->attempd;
        }else{
        if(totalNumbers[this->attempd-1]==0){ this->dummyAttempd++; }   //Intento dummy.
        this->initialInstant = time(0);    //Inicializando el instante inicial.
        switch (decision()) {   //La decision se toma según el perfil del jugador en cada jugada.
            case 0: //Sin ayuda.
                this->counter++;
                cout << endl << "No. Inténtalo de nuevo: " << endl;
                cin >>this->attempd;
                break;
                
            case 1: //Ayuda simple = 1.
                this->counter++;
                if(this->attempd>this->secret){
                    this->counterAssist++; //Ayuda simple = 1 punto.
                    cout << endl << "Te pasaste. Inténtalo de nuevo: " << endl;
                    cin >>this->attempd;
                }else if(this->attempd<this->secret){
                    this->counterAssist++; //Ayuda simple = 1 punto.
                    cout << endl << "Te quedaste corto. Inténtalo de nuevo: " << endl;
                    cin >>this->attempd;
                }
                break;
                
            case 2: //Ayuda intermedia = 2 puntos.
                if(((this->attempd -this->secret)<0)&&((this->attempd - this->secret)>=-10)){
                    this->counter++;
                    this->counterAssist += 2; //Ayuda intermedia = 2 puntos.
                    cout << endl << "Un poco bajo. Inténtalo de nuevo: " << endl;
                    cin >>attempd;
                }else if(((this->attempd - this->secret)>0)&&((this->attempd - this->secret)<=20)){
                    this->counter++;
                    this->counterAssist += 2; //Ayuda intermedia = 2 puntos.
                    cout << endl << "Un poco alto. Inténtalo de nuevo: " << endl;
                    cin >>this->attempd;
                }else if(((this->attempd - this->secret)<-10)&&((this->attempd - this->secret)>=-99)){
                    this->counter++;
                    this->counterAssist += 2; //Ayuda intermedia = 2 puntos.
                    cout << endl << "Demasiado bajo. Inténtalo de nuevo: " << endl;
                    cin >>this->attempd;
                }else if(((this->attempd - this->secret)>10)&&((this->attempd -this->secret)<=99)){
                    this->counter++;
                    this->counterAssist += 2; //Ayuda intermedia = 2 puntos.
                    cout << endl << "Demasiado alto. Inténtalo de nuevo: " << endl;
                    cin >>this->attempd;
                }
                break;
                
            case 3: //Ayuda explícita = 3 puntos.
                this->counter++;
                this->counterAssist += 3;
                cout << endl << "El número está en un rango de: " << lowLimit << " y " << uppLimit << ". \nInténtalo de nuevo: " << endl;
                cin >> this->attempd;
                break;
        }
        this->finalInstant = time(0);  //Inicializando el instante final.
        this->secs = this->finalInstant - this->initialInstant;   //Calculando los segundos transcurridos al momento de la decisión.
        //cout << "\nTardaste: " << this->secs << " secs." << endl;
        //cout << "Dummy: " << this->dummyAttempd << endl;
    }
}
    win();
}
