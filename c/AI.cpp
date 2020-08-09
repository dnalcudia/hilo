//
//  AI.cpp
//  HiLo
//
//  Created by Angel Daniel Alcudia on 2/16/19.
//  Copyright © 2019 Angel Daniel Alcudia. All rights reserved.
//

#include "AI.hpp"

//Empiezan las funciones internas.
void copy(int copyArray[],int copiedArray[]){ //Copia un arreglo sobre otro.
    for (int i=0; i<100; i++) {
        copyArray[i] = copiedArray[i];
    }
}

int calculatingDivider(int temporaryNumbers[],int divider){ //Contando los números disponibles.
    for (int i=0; i<100; i++) {
        if(temporaryNumbers[i]!=0){
            divider++;
        }
    }
    return divider;
}

float calculatingProbability(float probabilties,int divider){ //Calculando probabilidad.
    probabilties = (1.0/divider)*100;
    return probabilties;
}

//Terminan las funciones internas.

AI::AI(int secret, int counter, int counterAssist, int attempd, int finalScore,int range){ ::
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
    for (int i=0; i<100; i++) { this->totalNumbers[i] = (i+1); }
}

int AI::decision(){ //Método que decide el tipo de ayuda que se dará al jugador en función de las probabilidades de victoria.
    int decision=0; //Variable que decide el tipo de ayuda.
    float mayorProb=0.0; //Variable que almacena la mayor probabilidad.
    for (int i=0; i<4; i++) { this->divider[i] = 0; } //Reiniciando valor del denominador;
    
    //Probabilidad ayuda 0.
    copy(this->temporaryNumbers,this->totalNumbers); //Igualando los arreglos de números disponibles.
    for (int i=0; i<100; i++) { //Discriminando números según la ayuda.
        if(this->temporaryNumbers[i] == (this->attempd)){
            this->temporaryNumbers[i] = 0;
        }
    }
    divider[0] = calculatingDivider(this->temporaryNumbers,divider[0]); //Contando los números disponibles.
    this->probabilties[0]= calculatingProbability(probabilties[0],divider[0]);   //Calculando probabilidad.
    
    //Probabilidad ayuda 1.
    copy(this->temporaryNumbers,this->totalNumbers); //Igualando los arreglos de números disponibles.
    if(attempd>this->secret){   //Discriminando números según la ayuda.
        for (int i=(attempd-1); i<=100; i++) {
            this->temporaryNumbers[i] = 0;
        }
    }else if(attempd<this->secret){
        for (int i=0; i<=(attempd-1); i++) {
            this->temporaryNumbers[i] = 0;
        }
    }
    divider[1] = calculatingDivider(this->temporaryNumbers,divider[1]); //Contando los números disponibles.
    this->probabilties[1]= calculatingProbability(probabilties[1],divider[1]);   //Calculando probabilidad.

    //Probabilidad ayuda 2.
    copy(this->temporaryNumbers,this->totalNumbers); //Igualando los arreglos de números disponibles.
    if(((this->attempd -this->secret)<0)&&((this->attempd - this->secret)>=-10)){   //Discriminando números según la ayuda.
        for (int i=0; i<=attempd-1; i++) {
            this->temporaryNumbers[i] = 0;
        }
    }else if(((this->attempd - this->secret)>0)&&((this->attempd - this->secret)<=20)){
        for (int i=attempd-1; i<=100; i++) {
            this->temporaryNumbers[i] = 0;
        }
    }else if(((this->attempd - this->secret)<-10)&&((this->attempd - this->secret)>=-99)){
        for (int i=0; i<=attempd-1; i++) {
            this->temporaryNumbers[i] = 0;
        }
    }else if(((this->attempd - this->secret)>10)&&((this->attempd -this->secret)<=99)){
        for (int i=attempd-1; i<=100; i++) {
            this->temporaryNumbers[i] = 0;
        }
    }
    divider[2] = calculatingDivider(this->temporaryNumbers,divider[2]); //Contando los números disponibles.
    this->probabilties[2]= calculatingProbability(probabilties[2],divider[2]);  //Calculando probabilidad.

    //Probabilidad ayuda 3.
    copy(this->temporaryNumbers,this->totalNumbers); //Igualando los arreglos de números disponibles.
    for (int i=0; i<(this->lowLimit-1); i++) { this->temporaryNumbers[i] = 0; }   //Discriminando números según la ayuda.
    for (int j=this->uppLimit; j<=100; j++) { this->temporaryNumbers[j] = 0; }
    divider[3] = calculatingDivider(this->temporaryNumbers,divider[3]); //Contando los números disponibles.
    this->probabilties[3]= calculatingProbability(probabilties[3],divider[3]);   //Calculando probabilidad.
    
    //Ubicando la ayuda con mayor probabilidad de ganar.
    for (int i=0; i<4; i++) { if(this->probabilties[i]>=mayorProb){ mayorProb = probabilties[i]; } }
    
    //Asignando los valores de la ayuda con mayor probabilidad de ganar al arreglo original.
    if(probabilties[0] == mayorProb){   //Sin ayuda.
        decision = 0;
    this->totalNumbers[attempd-1] = 0;
    } else if(probabilties[1]==mayorProb){
        decision = 1;
    if(attempd>this->secret){ //Intento > número secreto.
            for (int i=(attempd-1); i<=100; i++) {
                this->totalNumbers[i] = 0;
            }
    }else if(attempd<this->secret){ //Intento < número secreto.
            for (int i=0; i<=(attempd-1); i++) {
                this->totalNumbers[i] = 0;
            }
        }
    } else if(probabilties[2]==mayorProb){
        decision = 2;
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
    } else if(probabilties[3]==mayorProb){  //Rango.
        decision = 3;
        for (int i=0; i<(this->lowLimit-1); i++) { this->totalNumbers[i] = 0; }
        for (int j=this->uppLimit; j<=100; j++) { this->totalNumbers[j] = 0; }
    }
    
    return decision;
}

void AI::start(){

    /*cout << endl << "Número secreto: " << this->secret << endl; //Imprimiendo el número secreto.
    cout << endl << "Números disponibles al momento: " << endl; //Imprimiendo los números disponibles.
    for (int i=0; i<100; i++) {
        cout << setw(5) << totalNumbers[i];
    }
    */
    
    //Empezando a jugar;
    cout << endl << endl << "El número aleatorio ha sido creado satisfactoriamente, ¿qué número es? ";
    cin >> this->attempd;
    
    while(this->attempd!=this->secret){
        if(this->attempd>100 || this->attempd<=0){   //Validando que el intento esté dentro del rango.
            cout << "\nSolo se aceptan números entre 1 - 100. Inténtalo de nuevo: "; cin >> this->attempd;
        }else{
        switch (decision()) {  //El tipo de ayuda se define según el método "decision".
            case 0: //Sin ayuda.
                this->counter++;
                cout << endl << "No. Inténtalo de nuevo: ";
                
                /*
                cout << endl << endl << "Números disponibles al momento: " << endl;
                for (int i=0; i<100; i++) {
                    cout << setw(5) << totalNumbers[i];
                }
                
                cout << endl << endl << "Probabilidades de ganar: " << endl
                << "Ayuda 0: 1/" << this->divider[0] << " = " << this->probabilties[0] << endl
                << "Ayuda 1: 1/" << this->divider[1] << " = " << this->probabilties[1] << endl
                << "Ayuda 2: 1/" << this->divider[2] << " = " << this->probabilties[2] << endl
                << "Ayuda 3: 1/" << this->divider[3] << " = " << this->probabilties[3] << endl;
                */
                
                cout << endl;
                cin >>this->attempd;
                break;
            case 1: //Ayuda simple = 1.
                this->counter++;
                if(this->attempd>this->secret){
                    this->counterAssist++; //Ayuda simple = 1 punto.
                    cout << endl << "Te pasaste. Inténtalo de nuevo: ";
                    
                    /*
                    cout << endl << endl << "Números disponibles al momento: " << endl;
                    for (int i=0; i<100; i++) {
                        cout << setw(5) << totalNumbers[i];
                    }
                    
                    cout << endl << endl << "Probabilidades de ganar: " << endl
                    << "Ayuda 0: 1/" << this->divider[0] << " = " << this->probabilties[0] << endl
                    << "Ayuda 1: 1/" << this->divider[1] << " = " << this->probabilties[1] << endl
                    << "Ayuda 2: 1/" << this->divider[2] << " = " << this->probabilties[2] << endl
                    << "Ayuda 3: 1/" << this->divider[3] << " = " << this->probabilties[3] << endl;
                    */
                    
                    cout << endl;
                    cin >>this->attempd;
                }else if(this->attempd<this->secret){
                    this->counterAssist++; //Ayuda simple = 1 punto.
                    cout << endl << "Te quedaste corto. Inténtalo de nuevo: ";
                    
                    /*
                    cout << endl << endl << "Números disponibles al momento: " << endl;
                    for (int i=0; i<100; i++) {
                        cout << setw(5) << totalNumbers[i];
                    }
                    
                    cout << endl << endl << "Probabilidades de ganar: " << endl
                    << "Ayuda 0: 1/" << this->divider[0] << " = " << this->probabilties[0] << endl
                    << "Ayuda 1: 1/" << this->divider[1] << " = " << this->probabilties[1] << endl
                    << "Ayuda 2: 1/" << this->divider[2] << " = " << this->probabilties[2] << endl
                    << "Ayuda 3: 1/" << this->divider[3] << " = " << this->probabilties[3] << endl;
                    */
                    
                    cout << endl;
                    cin >>this->attempd;
                }
                break;
            case 2: //Ayuda intermedia = 2 puntos.
                if(((this->attempd -this->secret)<0)&&((this->attempd - this->secret)>=-10)){
                    this->counter++;
                    this->counterAssist += 2; //Ayuda intermedia = 2 puntos.
                    cout << endl << "Un poco bajo. Inténtalo de nuevo: ";
                    
                    /*
                    cout << endl << endl << "Números disponibles al momento: " << endl;
                    for (int i=0; i<100; i++) {
                        cout << setw(5) << totalNumbers[i];
                    }
                    
                    cout << endl << endl << "Probabilidades de ganar: " << endl
                    << "Ayuda 0: 1/" << this->divider[0] << " = " << this->probabilties[0] << endl
                    << "Ayuda 1: 1/" << this->divider[1] << " = " << this->probabilties[1] << endl
                    << "Ayuda 2: 1/" << this->divider[2] << " = " << this->probabilties[2] << endl
                    << "Ayuda 3: 1/" << this->divider[3] << " = " << this->probabilties[3] << endl;
                    */
                    
                    cout << endl;
                    cin >>attempd;
                }else if(((this->attempd - this->secret)>0)&&((this->attempd - this->secret)<=20)){
                    this->counter++;
                    this->counterAssist += 2; //Ayuda intermedia = 2 puntos.
                    cout << endl << "Un poco alto. Inténtalo de nuevo: ";
                    
                    /*
                    cout << endl << endl << "Números disponibles al momento: " << endl;
                    for (int i=0; i<100; i++) {
                        cout << setw(5) << totalNumbers[i];
                    }
                    
                    cout << endl << endl << "Probabilidades de ganar: " << endl
                    << "Ayuda 0: 1/" << this->divider[0] << " = " << this->probabilties[0] << endl
                    << "Ayuda 1: 1/" << this->divider[1] << " = " << this->probabilties[1] << endl
                    << "Ayuda 2: 1/" << this->divider[2] << " = " << this->probabilties[2] << endl
                    << "Ayuda 3: 1/" << this->divider[3] << " = " << this->probabilties[3] << endl;
                    */
                    
                    cout << endl;
                    cin >>this->attempd;
                }else if(((this->attempd - this->secret)<-10)&&((this->attempd - this->secret)>=-99)){
                    this->counter++;
                    this->counterAssist += 2; //Ayuda intermedia = 2 puntos.
                    cout << endl << "Demasiado bajo. Inténtalo de nuevo: ";
                    
                    /*
                    cout << endl << endl << "Números disponibles al momento: " << endl;
                    for (int i=0; i<100; i++) {
                        cout << setw(5) << totalNumbers[i];
                    }
                    
                    cout << endl << endl << "Probabilidades de ganar: " << endl
                    << "Ayuda 0: 1/" << this->divider[0] << " = " << this->probabilties[0] << endl
                    << "Ayuda 1: 1/" << this->divider[1] << " = " << this->probabilties[1] << endl
                    << "Ayuda 2: 1/" << this->divider[2] << " = " << this->probabilties[2] << endl
                    << "Ayuda 3: 1/" << this->divider[3] << " = " << this->probabilties[3] << endl;
                    */
                    
                    cout << endl;
                    cin >>this->attempd;
                }else if(((this->attempd - this->secret)>10)&&((this->attempd -this->secret)<=99)){
                    this->counter++;
                    this->counterAssist += 2; //Ayuda intermedia = 2 puntos.
                    cout << endl << "Demasiado alto. Inténtalo de nuevo: ";
                    
                    /*
                    cout << endl << endl << "Números disponibles al momento: " << endl;
                    for (int i=0; i<100; i++) {
                        cout << setw(5) << totalNumbers[i];
                    }
                    
                    cout << endl << endl << "Probabilidades de ganar: " << endl
                    << "Ayuda 0: 1/" << this->divider[0] << " = " << this->probabilties[0] << endl
                    << "Ayuda 1: 1/" << this->divider[1] << " = " << this->probabilties[1] << endl
                    << "Ayuda 2: 1/" << this->divider[2] << " = " << this->probabilties[2] << endl
                    << "Ayuda 3: 1/" << this->divider[3] << " = " << this->probabilties[3] << endl;
                    */
                    
                    cout << endl;
                    cin >>this->attempd;
                }
                break;
            case 3: //Ayuda explícita = 3 puntos.
                this->counter++;
                this->counterAssist += 3;
                cout << endl << "El número está en un rango de: " << lowLimit << " y " << uppLimit << ". \nInténtalo de nuevo: ";
                
                /*
                cout << endl << endl << "Números disponibles al momento: " << endl;
                for (int i=0; i<100; i++) {
                    cout << setw(5) << totalNumbers[i];
                }
                
                cout << endl << endl << "Probabilidades de ganar: " << endl
                << "Ayuda 0: 1/" << this->divider[0] << " = " << this->probabilties[0] << endl
                << "Ayuda 1: 1/" << this->divider[1] << " = " << this->probabilties[1] << endl
                << "Ayuda 2: 1/" << this->divider[2] << " = " << this->probabilties[2] << endl
                << "Ayuda 3: 1/" << this->divider[3] << " = " << this->probabilties[3] << endl;
                */
                
                cout << endl;
                cin >> this->attempd;
                break;
        }
    }
    }
    win();
}
        
