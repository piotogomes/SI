
// Exemplo em que o principio da substituição de Liskov é violado.

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

class Quadrado extends Retangulo {

	public Quadrado(double l){

		super(l, l);
	}

	public void set(double l){

		set(l, l);
	}

	public double lado(){
	
		return largura();
	}
}

public class TesteQuad {

	public static void processa(Retangulo [] retangulos){

		for(Retangulo r : retangulos){

			if(r != null) System.out.println(r + ": " + r.area());
		}
	}

	public static void reshape(Retangulo [] retangulos, double aspect){

		// Eventuais instancias de Quadrado (que também são retângulos)
		// contidas no array deixarão de ter lados iguais ao serem
		// manipuladas por este método. Isso deveria acontecer?
		
		for(Retangulo r : retangulos){

			double h = Math.sqrt(r.area() / aspect);
			r.set(h * aspect, h);
		}
	}

	public static void main(String [] args){
	
		Retangulo [] retangulos = new Retangulo[4];

		retangulos[0] = new Retangulo(3, 4);
		retangulos[1] = new Retangulo(25, 3); 
		retangulos[2] = new Retangulo(6, 8);
		retangulos[3] = new Quadrado(5 * Math.sqrt(3));

		processa(retangulos);
		reshape(retangulos, 3);
		System.out.println("-------------------------------------------");
		processa(retangulos);
	}
}

