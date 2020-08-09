import javax.swing.JOptionPane;

public class CC extends AI{
    protected int dummyAttempd; //Contador de intentos dummy.
    protected int[] totalNumbers= new int[100]; //Arreglo de números disponibles.
    protected long initialInstant, finalInstant;	//Variables para calcular el tiempo transcurrido en cada jugada.
    protected double secs;
	
	public CC() {
	    this.secret =(int) (Math.random() * 100) + 1;
	    this.counter = 1;
	    this.counterAssist = 0;
	    this.attempd = 0;
	    this.finalScore = 0;
	    this.range = (int) (Math.random() * 20);
	    this.lowLimit = this.secret-this.range-20; //Definiendo los rangos para el tipo de ayuda explícita.
	    this.uppLimit = this.secret + this.range;
	    if(this.lowLimit<0){this.lowLimit = 0;} if(this.uppLimit>100){this.uppLimit = 100;} //Validando los rangos.
	    this.dummyAttempd = 0;
	    for (int i=0; i<100; i++) { this.totalNumbers[i] = (i+1); }    //Inicializando el arreglo de números.
	}

	public int decision(){ //Método que decide el tipo de ayuda que se dará al jugador en función del perfil de jugador.
	    int decision=0;
	    	    
	    if(totalNumbers[this.attempd-1]==0){ this.dummyAttempd++; }	//Intento dummy.
	    
	    if(this.secs<=1 && this.dummyAttempd==0){ //0-Hábil/Concentrado.
	        decision=0;
	        this.totalNumbers[attempd-1] = 0; //Discriminando números según la ayuda.
	    } else if(this.secs>1 && this.dummyAttempd==0){   //1-Hábil/Distraido.
	        decision=1;
	        if(attempd>this.secret){ //Intento > número secreto.
	            for (int i=(this.attempd-1); i<100; i++) {
	                this.totalNumbers[i] = 0;
	            }
	        }else if(this.attempd<this.secret){ //Intento < número secreto.
	            for (int i=0; i<=(this.attempd-1); i++) {
	                this.totalNumbers[i] = 0;
	            }
	        }
	    } else if(this.secs<=1 && this.dummyAttempd>0){   //2-Tonto/Concentrado.
	        decision=2;
	        if(((this.attempd -this.secret)<0)&&((this.attempd - this.secret)>=-10)){   //Un poco bajo.
	            for (int i=0; i<=attempd-1; i++) {
	                this.totalNumbers[i] = 0;
	            }
	        }else if(((this.attempd - this.secret)>0)&&((this.attempd - this.secret)<=20)){ //Un poco alto.
	            for (int i=attempd-1; i<100; i++) {
	                this.totalNumbers[i] = 0;
	            }
	        }else if(((this.attempd - this.secret)<-10)&&((this.attempd - this.secret)>=-99)){   //Demasiado bajo.
	            for (int i=0; i<=attempd-1; i++) {
	                this.totalNumbers[i] = 0;
	            }
	        }else if(((this.attempd - this.secret)>10)&&((this.attempd -this.secret)<=99)){  //Demasiado alto.
	            for (int i=attempd-1; i<100; i++) {
	                this.totalNumbers[i] = 0;
	            }
	        }
	    } else if(this.secs>1 && this.dummyAttempd>0){    //3-Tonto/Distraido.
	        decision=3;
	        for (int i=0; i<(this.lowLimit-1); i++) { this.totalNumbers[i] = 0; }
	        for (int j=this.uppLimit; j<100; j++) { this.totalNumbers[j] = 0; }
	    }
	    return decision;
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
	    	this.initialInstant = System.currentTimeMillis();
	    	try {
	    	if(this.attempd>100 || this.attempd<=0){   //Validando que el intento esté dentro del rango.
			this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"Solo se aceptan números entre 1 - 100. Inténtalo de nuevo:",
			"¡Error!", JOptionPane.ERROR_MESSAGE));		    
			}else{
	        switch (decision()) {  //El tipo de ayuda se define según el método "decision".
	            case 0: //Sin ayuda.
	                this.counter++;
		            this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"No. Inténtalo de nuevo:",
		            "¡Error!", JOptionPane.ERROR_MESSAGE));
	                break;
	                
	            case 1: //Ayuda simple = 1.
	                this.counter++;
	                if(this.attempd>this.secret){
	                    this.counterAssist++; //Ayuda simple = 1 punto.
	    	            this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"Te pasaste. Inténtalo de nuevo:",
	    	            "¡Error!", JOptionPane.ERROR_MESSAGE));
	                }else if(this.attempd<this.secret){
	                    this.counterAssist++; //Ayuda simple = 1 punto.
	    	            this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"Te quedaste corto. Inténtalo de nuevo:",
	    	            "¡Error!", JOptionPane.ERROR_MESSAGE));
	                }
	                break;
	                
	            case 2: //Ayuda intermedia = 2 puntos.
	                if(((this.attempd -this.secret)<0)&&((this.attempd - this.secret)>=-10)){
	                    this.counter++;
	                    this.counterAssist += 2; //Ayuda intermedia = 2 puntos.
	    	            this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"Un poco bajo. Inténtalo de nuevo:",
	    	            "¡Error!", JOptionPane.ERROR_MESSAGE));
	                }else if(((this.attempd - this.secret)>0)&&((this.attempd - this.secret)<=20)){
	                    this.counter++;
	                    this.counterAssist += 2; //Ayuda intermedia = 2 puntos.
	    	            this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"Un poco alto. Inténtalo de nuevo:",
	    	            "¡Error!", JOptionPane.ERROR_MESSAGE));
	                }else if(((this.attempd - this.secret)<-10)&&((this.attempd - this.secret)>=-99)){
	                    this.counter++;
	                    this.counterAssist += 2; //Ayuda intermedia = 2 puntos.
	    	            this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"Demasiado bajo. Inténtalo de nuevo:",
	    	            "¡Error!", JOptionPane.ERROR_MESSAGE));
	                }else if(((this.attempd - this.secret)>10)&&((this.attempd -this.secret)<=99)){
	                    this.counter++;
	                    this.counterAssist += 2; //Ayuda intermedia = 2 puntos.
	    	            this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"Te pasaste. Inténtalo de nuevo:",
	    	            "¡Error!", JOptionPane.ERROR_MESSAGE));
	                }
	                break;
	                
	            case 3: //Ayuda explícita = 3 puntos.
	                this.counter++;
	                this.counterAssist += 3;
    	            this.attempd = Integer.parseInt(JOptionPane.showInputDialog(null,"El número está en un rango de: " +
	                this.lowLimit + " y " + this.uppLimit + ".\nInténtalo de nuevo:","¡Error!", JOptionPane.ERROR_MESSAGE));
	                break;
	    }
			}
	    	}catch (NumberFormatException n) {
				JOptionPane.showMessageDialog(null, "Debes ingresar un número. Inténtalo de nuevo: ","¡Error!",JOptionPane.WARNING_MESSAGE);
				this.dummyAttempd--;
			}
	    	this.finalInstant = System.currentTimeMillis();
	    	this.secs = (double) ((this.finalInstant - this.initialInstant)/1000);
	   }while(this.attempd!=secret);
	    win();
	}
}