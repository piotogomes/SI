import java.util.*;

// Versão revisada em que o princípio aberto/fechado é respeitado.
// Também podemos verificar neste exemplo o princípio da inversão
// de dependencias.

interface Criterio {

	public boolean seleciona(int x);
}

class Todos implements Criterio {

	public boolean seleciona(int x){ return true; }
}

class Pares implements Criterio {

	public boolean seleciona(int x){ return x % 2 == 0; }
}

class Impares implements Criterio {

	private Criterio pares = new Pares();

	public boolean seleciona(int x){ return !pares.seleciona(x); }
}

class MenoresQue implements Criterio {

	private int k;

	public MenoresQue(int k) { this.k = k; }

	public boolean seleciona(int x){ return x < k; }
}

class MaioresQue implements Criterio {

	private int k;

	public MaioresQue(int k) { this.k = k; }

	public boolean seleciona(int x){ return x > k; }
}

class Positivos implements Criterio {

	public boolean seleciona(int x){ return x >= 0; }
}

class Entre implements Criterio {

	private int min, max;

	public Entre(int min, int max) { this.min = min; this.max = max; }

	public boolean seleciona(int x){ return x > min && x < max; }
}

class And implements Criterio {

	private Criterio c1, c2;

	public And(Criterio c1, Criterio c2) { this.c1 = c1; this.c2 = c2; }

	public boolean seleciona(int x){ 

		return c1.seleciona(x) && c2.seleciona(x);
	}
}

class FilterSet {

	private Collection<Integer> col;

	// Se uma instancia de FilterSet mantivesse uma referência
	// para um tipo concreto de critério, teriamos uma violação
	// do princípio da inversão de dependencia.
	
	//private Entre criterio;	//	FilterSet ----> Entre

	// Ao manter uma referencia para um Criterio, invertemos
	// o sentido da dependencia entre FilterSet e as classes que
	// efetivamente implementam os critérios. Tanto FilterSet quanto
	// as classes que implementam critérios passam a depender apenas
	// da abtração definida pela interface Criterio.
	
	private Criterio criterio;	//  	FilterSet ----> Criterio <----- Entre
				   	// 		          ^  ^--------- Pares
					//			  |------------ MaioresQue

	public FilterSet(Criterio crit){

		col = new TreeSet<>();
		criterio = crit;
	}

	public void adiciona(int x){

		if(criterio.seleciona(x)) col.add(x);
	}

	public String toString(){

		return col.toString();
	}
}

public class TestFilterSetRev {

	public static void teste(Criterio crit){

		FilterSet set = new FilterSet(crit);

		for(int i = -8; i < 16; i++) set.adiciona(i);

		System.out.println(set);
		System.out.println("----------------------------------------------------------------");
	}

	public static void main(String [] args){

		teste(new Todos());
		teste(new Pares());
		teste(new Impares());
		teste(new MenoresQue(10));
		teste(new MaioresQue(5));
		teste(new Positivos());
		teste(new Entre(5, 10));
	}
}


