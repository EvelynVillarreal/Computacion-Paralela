import java.util.concurrent.Semaphore;

class Philosopher extends Thread{
    private Semaphore sem;
    private boolean full = false;
    
    private String name;

    public Philosopher(Semaphore sem, String name) {
        this.sem = sem;
        this.name = name;
    }

    public void run(){
        try {
            if (!full) {
                System.out.println(name +" quiere entrar");
                sem.acquire();
                System.out.println(name+" se sienta en la mesa");
                sleep(300);
                full=true;
                System.out.println(name+" ha comido y deja la mesa");
                sem.release();
                sleep(300);
            }
        } catch (Exception e) {
            System.out.println("Algo salio mal");
        }
    }
}