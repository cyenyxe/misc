/**
 *
 * @author Cristina Yenyxe Gonzalez Garcia <cyenyxe@ebi.ac.uk>
 */
public class JniMain {

    public JniMain() {
    }

    private native void nativePrint();
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        new JniMain().nativePrint();
    }
    
}
