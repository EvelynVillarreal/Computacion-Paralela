import java.util.concurrent.Semaphore;

public class Main {
    public static void main(String[] args) {
        Semaphore sem = new Semaphore(2);
        new Philosopher(sem, "socrates").start();
        new Philosopher(sem, "plato").start();
        new Philosopher(sem, "aristotle").start();
        new Philosopher(sem, "thales").start();
        new Philosopher(sem, "pythagoras").start();
    }
}
