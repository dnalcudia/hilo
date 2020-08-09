//
//  Principal.java
//  HiLo
//
//  Created by Angel Daniel Alcudia on 2/7/19.
//  Copyright © 2019 Angel Daniel Alcudia. All rights reserved.
//  Una disculpa por el espanglish.

import java.sql.*;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;
import java.util.Random;

public class Principal {
	
static ImageIcon iconic = new ImageIcon(Principal.class.getResource("high-low-250-2.png"));	//Imagen para los menús.	
static Conexion a = new Conexion(); //Objeto para conectarse al servidor web.

// =========================================================================================== //

    public static void main(String[] args) {
            
            //Conectando al servidor.
            a.conecting();
             
            //Saludando al usuario y explicando instrucciones. 
            JOptionPane.showMessageDialog(null, "Bienvenido a Hi-Lo Game.\n\nInstrucciones del juego: \n1.   El programa generará un número secreto entre 1 y 100. "
            + "Tu misión es adivinar dicho número.\n2.   Se te proporcionarán una serie de ayudas, "
            + "estas tienen un valor adicional sobre la calificación final.\n3.   Tú decides la cantidad de partidas que deseas jugar."
            + "\n4.   Una vez iniciada la partida, no se puede salir del juego."
            + "\n\nObjetivo:\nAcumular la menor cantidad de puntos posible.", "HI-LO GAME",JOptionPane.INFORMATION_MESSAGE,iconic);
		
            play();
	}

// =========================================================================================== //
	
public static void play() {	//Creando el menú incial.
		
    boolean next; //Booleando que permite avanzar en la partida.
    int games=0; //Total de partidas a jugar.
    Random rand = new Random();
    
    do { try {
    games= Integer.parseInt(JOptionPane.showInputDialog(null,"¿Cuántas partidas deseas jugar?",
    "Ingresa el # de partidas a jugar.", JOptionPane.WARNING_MESSAGE));
    next = true;
    }catch (NumberFormatException n) {
    JOptionPane.showMessageDialog(null, "Debes ingresar un número. Inténtalo de nuevo: ","¡Error!",JOptionPane.WARNING_MESSAGE);
    next=false;
    } }while(next!=true);
    
    //Empezando a jugar.

	for(int i=0;i<games;i++) {
        int hiloType = rand.nextInt(3);
		JOptionPane.showMessageDialog(null, "Cargando...","Partida # " + (i+1),
		JOptionPane.INFORMATION_MESSAGE,iconic);
        switch (hiloType) {
            case 0:
                {
                    Normal gameNormal = new Normal();
                    gameNormal.start();
                    INSERT(hiloType,gameNormal.counter,gameNormal.counterAssist,gameNormal.finalScore);
                    break;
                }
            case 1:
                {
                    CC gameCC = new CC();
                    gameCC.start();
                    INSERT(hiloType,gameCC.counter,gameCC.counterAssist,gameCC.finalScore);
                    break;
                }
            case 2:
                {
                    AI gameAI = new AI();
                    gameAI.start();
                    INSERT(hiloType,gameAI.counter,gameAI.counterAssist,gameAI.finalScore);
                    break;
                }
            default:
            break;
        }
		}
                
        int replay = JOptionPane.showConfirmDialog(null,"¿Deseas seguir jugando?", "¡Gracias por probar Hi-Lo Game!",
        JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE, iconic);
        if(replay == JOptionPane.YES_OPTION){ play(); }
	}

// =========================================================================================== //

public static void INSERT(int tipoPartida, int intentos, int ayudas, int resultadoFinal){
     System.out.println("Valores: "+"\ntipoPartida: "+tipoPartida + 
     "\nIntentos: "+ intentos + "\nAyudas: " + ayudas + "\nResultado final: "+ resultadoFinal);
     
    try {
      String query = "INSERT INTO results (tipoPartida, intentos, ayudas, resultadoFinal) VALUES(?,?,?,?)"; //Query 
      
      PreparedStatement preparedStmt = a.conn.prepareStatement(query);
      preparedStmt.setInt(1, tipoPartida);
      preparedStmt.setInt(2, intentos);
      preparedStmt.setInt(3, ayudas);
      preparedStmt.setInt(4, resultadoFinal);

      //Ejecutar el preparedstatement.
      preparedStmt.execute();
                  
            System.out.println("Datos insertados con éxito en la BD.");
        } catch (SQLException e) {
            System.out.println("Error, los datos no han sido insertados.");
        }
}
}