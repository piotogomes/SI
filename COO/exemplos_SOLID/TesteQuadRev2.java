
// Algumas melhorias para permitir que instâncias de 
// Quadrado e Retangulo possam ser manipuladas da mesma
// forma em relação aos comportamentos que são comuns a 
// ambos os tipos (calculo da área).
//
// Note ainda que esta revisão final, acaba por aplicar 
// também o princípio da segregação das interfaces, pois
// na versão inicial tinhamos uma interface "inchada" atrelada
// ao  tipo Retangulo (getters/setters para largura/altura, mais
// calculo da área) que erra "empurrada" para a classe Quadrado.
//
// Agora temos uma segregação dessa interface: a interface 
// FormaGeometrica contempla o comportamento comum a quadrados
// e retangulos (e potencialmente a qualquer tipo que representa 
// uma forma geométrica com área); a classe Retangulo possui seus 
// métodos especificos (getter/setter para largura/algura); e a classe
// Quadrado possui getters/setters apenas para o lado. Ou seja,
// unificamos o que pode ser unificado, e tratamos separadamente
// aquilo que é particular de cada tipo, sem "empurrar" comportamentos
// indevidos para a classe Quadrado.

interface FormaGeometrica {

	public double area();
}

class Retangulo implements FormaGeometrica{

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

class Quadrado implements FormaGeometrica{

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

public class TesteQuadRev2 {

	public static void processa(FormaGeometrica [] formas){

		// Podemos receber tanto retangulos, como quadrados
		// neste método. Na verdade, qualquer instância de
		// classes que implementem a interface FormaGeometrica.

		for(FormaGeometrica f : formas){

			if(f != null) System.out.println(f + ": " + f.area());
		}
	}

	public static void reshape(Retangulo [] retangulos, double aspect){

		// Não é mais possível passar instâncias de Quadrado para
		// serem manipuladas neste método... o que é desejável.
		
		for(Retangulo r : retangulos){

			double h = Math.sqrt(r.area() / aspect);
			r.set(h * aspect, h);
		}
	}

	public static void main(String [] args){
	
		FormaGeometrica formas [] = new FormaGeometrica[4];
		Retangulo [] retangulos = new Retangulo[3];
		
		formas[0] = retangulos[0] = new Retangulo(3, 4);
		formas[1] = retangulos[1] = new Retangulo(25, 3); 
		formas[2] = retangulos[2] = new Retangulo(6, 8);
		formas[3] = new Quadrado(5 * Math.sqrt(3));

		processa(formas);
		reshape(retangulos, 3);
		System.out.println("-------------------------------------------");
		processa(formas);
	}
}

