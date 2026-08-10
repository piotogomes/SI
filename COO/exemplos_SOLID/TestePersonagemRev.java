import java.util.*;

// Versão revisada em que o princípio da segregação de interfaces é aplicado.
// Observe como a aplicação deste principio também resolve a violação do
// princípio da substituição de Liskov.

interface Lutador {

	public void atacar(Personagem alvo);
}	

interface UsuarioMagia {

	public void usarMagia(Personagem alvo);
}

abstract class Personagem {

	private String nome;

	public Personagem(String nome){

		this.nome = nome;
	}

	public void andar(){

		// move o personagem...
	}

	public String toString(){

		return nome;
	}
}

class Ranger extends Personagem implements Lutador, UsuarioMagia {

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

class Paladino extends Personagem implements Lutador, UsuarioMagia {

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


class Mago extends Personagem implements UsuarioMagia{

	public Mago(String nome){

		super(nome);
	}

	public void usarMagia(Personagem alvo){

		System.out.println(this + " usando magia em " + alvo);
	}
}

class Guerreiro extends Personagem implements Lutador{

	public Guerreiro(String nome){

		super(nome);
	}

	public void atacar(Personagem alvo){

		System.out.println(this + " atacando " + alvo);
	}
}

public class TestePersonagemRev {

	public static void testeAtaque(List<Lutador> lutadores, List<Personagem> todos){

		for(Lutador l : lutadores){

			int i = (int) (Math.random() * todos.size());
			Personagem alvo = todos.get(i);
	
			l.atacar(alvo);
		}
	}

	public static void testeMagia(List<UsuarioMagia> magos, List<Personagem> todos){

		for(UsuarioMagia m : magos){

			int i = (int) (Math.random() * todos.size());
			Personagem alvo = todos.get(i);
	
			m.usarMagia(alvo);
		}
	}

	public static void main(String [] args){
	
		List<Personagem> personagens = new ArrayList<>();
		List<Lutador> personagensQueAtacam = new ArrayList<>();
		List<UsuarioMagia> personagensQueUsamMagia = new ArrayList<>();

		Ranger ranger = new Ranger("Ranger");
		personagens.add(ranger);
		personagensQueAtacam.add(ranger);
		personagensQueUsamMagia.add(ranger);
		
		Paladino paladino = new Paladino("Paladino");
		personagens.add(paladino);
		personagensQueAtacam.add(paladino);
		personagensQueUsamMagia.add(paladino);

		Mago mago = new Mago("Mago");
		personagens.add(mago);
		personagensQueUsamMagia.add(mago);
		
		Guerreiro guerreiro = new Guerreiro("Guerreiro");
		personagens.add(guerreiro);		
		personagensQueAtacam.add(guerreiro);

		System.out.println("Todos: " + personagens);
		System.out.println("Usuários magia: " + personagensQueUsamMagia);
		System.out.println("Lutadores: " + personagensQueAtacam);

		System.out.println("--------------------------------------------");
		System.out.println("--------------------------------------------");

		testeAtaque(personagensQueAtacam, personagens);

		System.out.println("--------------------------------------------");

		testeMagia(personagensQueUsamMagia, personagens);

		System.out.println("--------------------------------------------");

	}
}
