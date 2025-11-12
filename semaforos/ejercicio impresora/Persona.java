import java.util.concurrent.Semaphore;

public class Persona extends Thread{
    private Semaphore sem;
    private boolean full = false;
    private boolean archivo;
    private String name;

    public Persona(Semaphore sem, String name,boolean archivo){
        this.sem =sem;
        this.name = name;
        this.archivo=archivo;
    }
    public void run(){
        try {
            if (!full && archivo) {
                System.out.println(name+" quiere imprimir");
                sem.acquire();
                System.out.println(name+" imprime");
                sleep(300);
                full=true;
                System.out.println(name+" finaliza");
                sem.release();
                sleep(300);
            }else{
                if (!archivo) {
                    System.out.println(name+" no tiene archivo para imprimir");
                    return;
                }
            }
        } catch (Exception e) {
            System.out.println("Algo salio mal");
        }
    }
}
