import javax.swing.ImageIcon;
import javax.swing.JOptionPane;

public class Normal {
	protected int secret, counter, counterAssist, attempd, exit, finalScore;
	protected int[] results = new int[3];
	protected ImageIcon iconic = new ImageIcon(Principal.class.getResource("high-low-250-2.png"));
	
	public int getCounter() { return this.counter; }
	
	public int getCounterAssist() {	return this.counterAssist; }
	
	public int getFinalScore() { return this.finalScore; }
	
	public void win() {
		//Una vez que ganas se muestra el número secreto y tu puntuación final.
		this.finalScore = this.counter + this.counterAssist;
		
		JOptionPane.showMessageDialog(null,"El número secreto es " + this.secret + 
		".\nTu cantidad de intentos fue: " + this.counter + ".\nTus ayudas totales suman: " +
		this.counterAssist + ".\nTu puntuación final es: " + 
		this.finalScore + ".\n\n","¡Felicidades, lo has logrado!",JOptionPane.INFORMATION_MESSAGE,iconic);
		}
	
	public Normal() {
		this.secret = (int) (Math.random() * 100) + 1;
		this.counter = 1;
		this.counterAssist = 0;
		this.attempd = 0;
		this.finalScore = 0;
	}
			
	public void start() {
		boolean next; //Booleando que permite avanzar en la partida.
		//Empezando a jugar.
		do { try {
		this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"El número aleatorio ha sido creado satisfactoriamente, ¿qué número es?",
		"¡Empezando!", JOptionPane.PLAIN_MESSAGE));
		next = true;
		}catch (NumberFormatException n) {
			JOptionPane.showMessageDialog(null, "Debes ingresar un número. Inténtalo de nuevo: ","¡Error!",JOptionPane.WARNING_MESSAGE);
			next=false;
	    } }while(next!=true);
		
	    do{ 
			try {
		    if(this.attempd>100 || this.attempd<=0){   //Validando que el intento esté dentro del rango.
		    this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"Solo se aceptan números entre 1 - 100. Inténtalo de nuevo:",
			"¡Error!", JOptionPane.ERROR_MESSAGE));		    
		    }else{
	        this.counter++;
	        if(this.attempd>this.secret){ //Las ayudas tienen un valor predeterminado de 2.
	            this.counterAssist = this.counterAssist + 2;
	            this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"Te pasaste. Inténtalo de nuevo:",
	            "¡Error!", JOptionPane.ERROR_MESSAGE));
	        }else if(this.attempd<this.secret){
	            this.counterAssist = this.counterAssist + 2;
	            this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"Te quedaste corto. Inténtalo de nuevo:",
	    	     "¡Error!", JOptionPane.ERROR_MESSAGE));
	        }
		    }
			}catch (NumberFormatException n) {
				JOptionPane.showMessageDialog(null, "Debes ingresar un número. Inténtalo de nuevo: ","¡Error!",JOptionPane.WARNING_MESSAGE);
		    }
	    }while(this.attempd!=this.secret);
	    win();
	}
}
