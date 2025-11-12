import java.util.concurrent.Semaphore;

public class main2 {
    public static void main(String[] args) {
        Semaphore sem = new Semaphore(1);
        new Persona(sem, "socrates",true).start();
        new Persona(sem, "plato",false).start();
        new Persona(sem, "aristotle",true).start();
        new Persona(sem, "thales",true).start();
        new Persona(sem, "pythagoras",true).start();
    }
}
