//
//  main.cpp
//  HiLo
//
//  Created by Angel Daniel Alcudia on 2/7/19.
//  Copyright © 2019 Angel Daniel Alcudia. All rights reserved.
//  Una disculpa por el espanglish.

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include "Normal.hpp"
#include "AI.hpp"
#include "CC.hpp"

using namespace std;

void funcExit();
void showMenu();
void normal();
void AI();
void cognitiveComputing();

// =========================================================================================== //

int main(int argc, const char * argv[]) {
    //Saludando al usuario y explicando instrucciones.
    cout << " === BIENVENIDOS A HI-LO ===" << endl <<endl << "Instrucciones del juego: " <<
    endl << "El programa generará un número secreto entre 1 y 100. Tu misión es adivinar dicho número. " <<
    endl << "Las ayudas tienen un valor adicional sobre la calificación final, esto se definirá según el modo de juego. " << endl << endl;
    showMenu();
    return 0;
}

// =========================================================================================== //

void funcExit(){     //Regresando al menú inicial.
    int exit; cout << "Presiona 0 para regresar al menú inical. "; cin >> exit; cout << endl;
    if(exit==0){ showMenu(); }
}

// =========================================================================================== //

void showMenu(){    //Creando el menú inicial.
    int exit=0;
    do {
        cout << "Selecciona la versión que deseas probar: " <<
        endl << endl << "1. Normal." << endl << "2. Artificial Inteligence." << endl << "3. Cognitive Computing." << endl << "0. Exit." << endl << endl;
        
        int select;
        cin >> select;
        switch (select) {
            case 1:
                normal();
                break;
            case 2:
                AI();
                break;
            case 3:
                cognitiveComputing();
                break;
            case 0:
                cout << "\n¡Gracias por probar Hi-Lo!" << endl << endl;
                break;
            default:
                cout << "\n¡Tienes que elegir una opción! " << endl << endl;
                showMenu();
                break;
        }
    } while (exit!=0);
}

// =========================================================================================== //

void normal(){
    cout << "\n === VERSIÓN NORMAL ===" << endl << endl;
    cout << "En esta versión se añade la siguiente regla: \n1. Las ayudas tienen un valor de 2 sobre tu calificación final. " << endl;
    
    srand(time(NULL));
    int secret=rand() % 100 + 1;    //Generando número aleatorio entre 1 y 100. SECRET.
    int attempd = 0, finalScore = 0, counterNormal = 1, counterAssist = 0;
    
    Normal game(secret,counterNormal,counterAssist,attempd,finalScore);
    game.start();
    funcExit();    //Regresando al menú inicial.
}

// =========================================================================================== //

void AI(){
    cout << "\n === VERSIÓN CON INTELIGENCIA ARTIFICIAL ===" << endl << endl;
    cout << "En esta versión se añaden las siguientes reglas: \n1. Las ayudas simples tienen valor de 1 sobre tu calificación final. \n2. Las ayudas intermedias tienen valor de 2 sobre tu calificación final. \n3. Las ayudas explícitas/rango tienen valor de 3 sobre tu calificación final. " << endl;
    
    srand(time(NULL));
    int secret = rand() % 100 + 1;    //Generando número aleatorio entre 1 y 100. SECRET.
    int range = rand() % 20 + 0;     //Generando el rango de ayuda para el usuario (0 y 20). RANGE.
    int attempd=0, counterAI = 1, counterAssist = 0, finalScore=0;
    
    class AI game(secret,counterAI,counterAssist,attempd,finalScore,range);
    game.start();
    funcExit();    //Regresando al menú inicial.
}

// =========================================================================================== //

void cognitiveComputing(){
    cout << "\n === VERSIÓN CON COMPUTACIÓN COGNITIVA===" << endl << endl;
    cout << "En esta versión se añaden las siguientes reglas: \n1. Las ayudas simples tienen valor de 1 sobre tu calificación final. \n2. Las ayudas intermedias tienen valor de 2 sobre tu calificación final. \n3. Las ayudas explícitas/rango tienen valor de 3 sobre tu calificación final. " << endl;
    
    srand(time(NULL));
    int secret = rand() % 100 + 1;    //Generando número aleatorio entre 1 y 100. SECRET.
    int range = rand() % 20 + 0;     //Generando el rango de ayuda para el usuario (0 y 20). RANGE.
    int attempd=0, counterAI = 1, counterAssist = 0, finalScore=0;
    
    class CC game(secret,counterAI,counterAssist,attempd,finalScore,range);
    game.start();
    funcExit();    //Regresando al menú inicial.
}
