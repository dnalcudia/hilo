import javax.swing.JOptionPane;

public class AI extends Normal{
	protected int range;
	protected int[] totalNumbers = new int[100];	//Arreglo que almacena el total de números.
	protected int lowLimit,uppLimit; //Límites del rango.
	
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
	    probabilties = (1.0f/divider)*100.0f;
	    return probabilties;
	}
	//Terminan las funciones internas.
	
	public AI() {
		this.secret = (int) (Math.random() * 100) + 1;
		this.counter = 1;
		this.counterAssist = 0;
		this.attempd = 0;
		this.finalScore = 0;
		this.range = (int) (Math.random() * 20);
		this.lowLimit = this.secret-this.range-20; //Definiendo los rangos para el tipo de ayuda explícita.
	    this.uppLimit = this.secret + this.range;
	    if(this.lowLimit<0){this.lowLimit = 0;} if(this.uppLimit>100){this.uppLimit = 100;} //Validando los rangos.
	    for (int i=0; i<100; i++) { this.totalNumbers[i] = (i+1); }
	}

	public int decision() {	//Método que decide el tipo de ayuda que se dará al jugador en función de las probabilidades de victoria.
	    int decision=0; //Variable que decide el tipo de ayuda.
	    float mayorProb=0.0f; //Variable que almacena la mayor probabilidad.
	    float[] probabilities = new float[4];	//Probabilidades de ganar por ayuda.
		int[] divider = new int[4];//Total de números disponibles por ayuda.
		int[] temporaryNumbers = new int[100];   //Arreglo que almacena los números disponibles.
	    for (int i=0; i<4; i++) { divider[i] = 0; } //Reiniciando valor del denominador;
	    
	    //Probabilidad ayuda 0.
	    copy(temporaryNumbers,this.totalNumbers); //Igualando los arreglos de números disponibles.
	    for (int i=0; i<100; i++) { //Discriminando números según la ayuda.
	    	if(temporaryNumbers[i] == (this.attempd)){ temporaryNumbers[i] = 0; }
	    }
	    divider[0] = calculatingDivider(temporaryNumbers,divider[0]); //Contando los números disponibles.
	    probabilities[0]= calculatingProbability(probabilities[0],divider[0]);   //Calculando probabilidad.
	    
	    //Probabilidad ayuda 1.
	    copy(temporaryNumbers,this.totalNumbers); //Igualando los arreglos de números disponibles.
	    if(attempd>this.secret){   //Discriminando números según la ayuda.
	    	for (int i=(this.attempd-1); i<100; i++) { temporaryNumbers[i] = 0; }
	    }else if(attempd<this.secret){
	    	for (int i=0; i<=(attempd-1); i++) { temporaryNumbers[i] = 0; }
	    }
	    divider[1] = calculatingDivider(temporaryNumbers,divider[1]); //Contando los números disponibles.
	    probabilities[1]= calculatingProbability(probabilities[1],divider[1]);   //Calculando probabilidad.
	 
	    //Probabilidad ayuda 2.
	    copy(temporaryNumbers,this.totalNumbers); //Igualando los arreglos de números disponibles.
	    if(((this.attempd -this.secret)<0)&&((this.attempd - this.secret)>=-10)){   //Discriminando números según la ayuda.
	    	for (int i=0; i<=attempd-1; i++) { temporaryNumbers[i] = 0; }
	    }else if(((this.attempd - this.secret)>0)&&((this.attempd - this.secret)<=10)){
	    	for (int i=attempd-1; i<100; i++) { temporaryNumbers[i] = 0; }
	    }else if(((this.attempd - this.secret)<-10)&&((this.attempd - this.secret)>-20)){
	    	for (int i=0; i<=attempd-1; i++) { temporaryNumbers[i] = 0; }
	    }else if(((this.attempd - this.secret)>10)&&((this.attempd -this.secret)<20)){
	    	for (int i=attempd-1; i<100; i++) { temporaryNumbers[i] = 0; }
	    }
	    divider[2] = calculatingDivider(temporaryNumbers,divider[2]); //Contando los números disponibles.
	    probabilities[2]= calculatingProbability(probabilities[2],divider[2]);  //Calculando probabilidad.

	    //Probabilidad ayuda 3.
	    copy(temporaryNumbers,this.totalNumbers); //Igualando los arreglos de números disponibles.
	    for (int i=0; i<(this.lowLimit-1); i++) { temporaryNumbers[i] = 0; }   //Discriminando números según la ayuda.
	    for (int j=this.uppLimit; j<100; j++) { temporaryNumbers[j] = 0; }
	    divider[3] = calculatingDivider(temporaryNumbers,divider[3]); //Contando los números disponibles.
	    probabilities[3]= calculatingProbability(probabilities[3],divider[3]);   //Calculando probabilidad. */
	    
	    //Ubicando la ayuda con mayor probabilidad de ganar.
	    for (int i=0; i<4; i++) { if(probabilities[i]>=mayorProb){ mayorProb = probabilities[i]; } }
	    
	    //Asignando los valores de la ayuda con mayor probabilidad de ganar al arreglo original.
	    if(probabilities[0] == mayorProb){   //Sin ayuda.
	       decision = 0;
	    this.totalNumbers[attempd-1] = 0;
	    } else if(probabilities[1]==mayorProb){	//Ayuda simple.
	       decision = 1;
	    if(attempd>this.secret){ //Intento > número secreto.
	    	for (int i=(attempd-1); i<100; i++) { this.totalNumbers[i] = 0; }
	    }else if(attempd<this.secret){ //Intento < número secreto.
	    	for (int i=0; i<=(attempd-1); i++) { this.totalNumbers[i] = 0; }
	        }
	    } else if(probabilities[2]==mayorProb){	//Ayuda intermedia.
	        decision = 2;
	        if(((this.attempd -this.secret)<0)&&((this.attempd - this.secret)>=-10)){   //Un poco bajo.
	        	for (int i=0; i<=attempd-1; i++) { this.totalNumbers[i] = 0; }
	        }else if(((this.attempd - this.secret)>0)&&((this.attempd - this.secret)<=20)){ //Un poco alto.
	        	for (int i=attempd-1; i<100; i++) { this.totalNumbers[i] = 0; }
	        }else if(((this.attempd - this.secret)<-10)&&((this.attempd - this.secret)>=-99)){   //Demasiado bajo.
	        	for (int i=0; i<=attempd-1; i++) { this.totalNumbers[i] = 0; }
	        }else if(((this.attempd - this.secret)>10)&&((this.attempd -this.secret)<=99)){  //Demasiado alto.
	        	for (int i=attempd-1; i<100; i++) { this.totalNumbers[i] = 0; }
	        }
	    } else if(probabilities[3]==mayorProb){  //Ayuda explícita.
	        decision = 3;
	        for (int i=0; i<(this.lowLimit-1); i++) { this.totalNumbers[i] = 0; }
	        for (int j=this.uppLimit; j<100; j++) { this.totalNumbers[j] = 0; }
	    }
	    
	    //System.out.println(probabilities[0] + "\n" + probabilities[1] + "\n" + probabilities[2] + "\n" + probabilities[3]);	//CONFIRMANDO PROBS.
	    
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
			}
	   }while(this.attempd!=secret);
	    win();
	}
}
