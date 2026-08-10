import java.util.*;

// Exemplo que viola o principio da segregação de interfaces na modelagem
// da classe Personagem (e de certa forma o principio da substituição de
// Liskov). Este exemplo é revisado no arquivo TestePersonagemRev.java.

abstract class Personagem {

	private String nome;

	public Personagem(String nome){

		this.nome = nome;
	}

	public abstract void atacar(Personagem alvo);
	public abstract void usarMagia(Personagem alvo);
	
	public void andar(){

		// move o personagem...
	}

	public String toString(){

		return nome;
	}
}

class Ranger extends Personagem {

	public Ranger(String nome){

		super(nome);
	}

	public void atacar(Personagem alvo){

		System.out.println(this + " atacando " + alvo);
	}

	public void usarMagia(Personagem alvo){

		System.out.println(this + " usando magia em " + alvo);
	}
}

class Paladino extends Personagem {

	public Paladino(String nome){

		super(nome);
	}

	public void atacar(Personagem alvo){

		System.out.println(this + " atacando " + alvo);
	}

	public void usarMagia(Personagem alvo){

		System.out.println(this + " usando magia em " + alvo);
	}
}

class Mago extends Personagem {

	public Mago(String nome){

		super(nome);
	}

	public void atacar(Personagem alvo){

		// não faz nada...
	}

	public void usarMagia(Personagem alvo){

		System.out.println(this + " usando magia em " + alvo);
	}
}

class Guerreiro extends Personagem {

	public Guerreiro(String nome){

		super(nome);
	}

	public void atacar(Personagem alvo){

		System.out.println(this + " atacando " + alvo);
	}

	public void usarMagia(Personagem alvo){

		// não faz nada...
	}
}

public class TestePersonagem {

	public static void teste(List<Personagem> personagens){

		for(Personagem p : personagens){

			int i = (int) (Math.random() * personagens.size());
			Personagem alvo = personagens.get(i);

			p.andar();
			p.atacar(alvo);
			p.usarMagia(alvo);

			System.out.println("--------------------------------------------");
		}
	}

	public static void main(String [] args){

		List<Personagem> personagens = new ArrayList<>();

		personagens.add(new Ranger("Ranger"));
		personagens.add(new Paladino("Paladino"));
		personagens.add(new Mago("Mago"));
		personagens.add(new Guerreiro("Guerreiro"));

		teste(personagens);
	}
}
