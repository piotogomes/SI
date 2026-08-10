
// Inicio das modificações para evitar a violação do princípio

class Retangulo {

	private double w, h;
	
	public Retangulo(double w, double h){
		
		set(w, h);
	}

	public double largura(){

		return w;
	}

	public double altura(){
		
		return h;
	}

	public double area(){

		return w * h;
	}

	public void set(double w, double h){

		this.w = w;
		this.h = h;
	}

	public String toString(){

		double w, h;
		w = ((int)(this.w * 100)) / 100.0;
		h = ((int)(this.h * 100)) / 100.0;
		
		return getClass().getName() + " [" + w + ", " + h + "]";
	}
}

// desfazemos a relação de herança entre Quadrado e Retangulo, afinal
// um quadrado "faz menos" que um retângulo...

class Quadrado {

	// ... e usamos composição para reaproveitar a implementação
	// pronta de Retangulo que pode ser usada para implementar Quadrado

	private Retangulo ret;

	public Quadrado(double l){

		ret = new Retangulo(l, l);
	}

	public void set(double l){

		ret.set(l, l);
	}

	public double lado(){
	
		return ret.largura();
	}

	public double area(){

		return ret.area();
	}

	public String toString(){

		double l  = ((int)(lado() * 100)) / 100.0;
		return getClass().getName() + " [" + l + "]";
	}
}

public class TesteQuadRev {

	public static void processa(Retangulo [] retangulos){

		// Não é mais possível passar instâncias de Quadrado para
		// este método... mas para esse método a possibilidade de 
		// manipular Quadrado e Retangulo da mesma forma era conveniente
		// e não representava um problema. Como melhorar isso???

		for(Retangulo r : retangulos){

			if(r != null) System.out.println(r + ": " + r.area());
		}
	}

	public static void reshape(Retangulo [] retangulos, double aspect){

		// Não é mais possível passar instâncias de Quadrado para
		// serem manipuladas neste método... Neste caso, evitamos 
		// a violação do Princípio da Substituiçao de Liskov, sendo
		// importante que o método não aceite mais parâmetros do
		// tip Quadrado, para não executar comportamentos indevidos
		// ao tipo (ou seja, definir dimensões de largura e altura 
		// distintas).
		
		for(Retangulo r : retangulos){

			double h = Math.sqrt(r.area() / aspect);
			r.set(h * aspect, h);
		}
	}

	public static void main(String [] args){
	
		Retangulo [] retangulos = new Retangulo[3];
		
		retangulos[0] = new Retangulo(3, 4);
		retangulos[1] = new Retangulo(25, 3); 
		retangulos[2] = new Retangulo(6, 8);
		//retangulos[3] = new Quadrado(5 * Math.sqrt(3));	// não é mais possível fazer essa
									// atribuição, já que Quadrado não
									// é mais subtipo de Retangulo.

		processa(retangulos);
		reshape(retangulos, 3);
		System.out.println("-------------------------------------------");
		processa(retangulos);
	}
}

