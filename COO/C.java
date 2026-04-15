public class C{
	public static void main(String[] args) {
			System.out.println(new A());
	
			B teste = new B();
			//System.out.println("  x = " + teste.x);
			teste.printa();
			// System.out.println(new B());
		}

}



public class A {
	int x = 2;

	public String toString() {
		return ("A.x = " + x);
	}

	private void printa() {
		System.out.println("asssdsd");
	}
}

class B extends A {
	double x = 3.14;

	void printa() {
		System.out.println("pppppp");
	}

	
	public String toString() {
		double x;

		// experimente o programa com estas três atribuições diferentes
		x = 10;
		// x = super.x;
		// x = this.x;
		return ("B.x = " + x);
	}
}