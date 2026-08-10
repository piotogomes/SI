import java.util.*;

// Exemplo que ilustra a violação do princípio aberto/fechado.
// Uma versão revisada do mesmo exemplo, em que o principio 
// é respeitado é mostrada no arquivo TestFilterSetRev.java.

class FilterSet {

	public static final int TODOS = 0;
	public static final int PARES = 1;
	public static final int IMPARES = 2;
	public static final int MENORES_QUE = 3;
	public static final int MAIORES_QUE = 4;

	// O que precisamos fazer para implementar um novo tipo de critério? 

	//public static final int POSITIVOS = 5;
	//public static final int ENTRE = 6;

	private Collection<Integer> col;

	private int criterio;
	private int parametro, parametro2;

	public FilterSet(int crit, int param, int param2){

		col = new TreeSet<>();
		criterio = crit;

		parametro = param;
		parametro2 = param2;
	}

	public void adiciona(int x){

		if(criterio == TODOS){
	
			col.add(x);
		}
		else if(criterio == PARES){

			if(x % 2 == 0) col.add(x);
		}
		else if(criterio == IMPARES){

			if(x % 2 != 0) col.add(x);
		}
		else if(criterio == MENORES_QUE){

			if(x < parametro) col.add(x);
		}
		else if(criterio == MAIORES_QUE){

			if(x > parametro) col.add(x);
		}
		/*
		else if(criterio == POSITIVOS){

			if(x >= 0) col.add(x);
		}
		else if(criterio == ENTRE){

			if(x > parametro && x < parametro2) col.add(x);
		}
		*/
		else {
			System.out.println("Criterio não especificado!");
		}
	}

	public String toString(){

		return col.toString();
	}
}

public class TestFilterSet {

	public static void teste(int crit, int param, int param2){

		FilterSet set = new FilterSet(crit, param, param2);

		for(int i = -8; i < 16; i++) set.adiciona(i);

		System.out.println(set);
		System.out.println("----------------------------------------------------------------");
	}

	public static void main(String [] args){

		teste(FilterSet.TODOS, 0, 0);
		teste(FilterSet.PARES, 0, 0);
		teste(FilterSet.IMPARES, 0, 0);
		teste(FilterSet.MENORES_QUE, 10, 0);
		teste(FilterSet.MAIORES_QUE, 5, 0);
		//teste(FilterSet.POSITIVOS, 0, 0);
		//teste(FilterSet.ENTRE, 5, 10);
	}
}


