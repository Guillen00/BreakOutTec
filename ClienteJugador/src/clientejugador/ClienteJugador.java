/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientejugador;

import javax.swing.JFrame;
import static javax.swing.JFrame.EXIT_ON_CLOSE;

/**
 *
 * @author Usuario
 */
public class ClienteJugador extends JFrame{

    /**
     * @param args the command line arguments
     */
    
    public ClienteJugador() {

        initUI();
    } 
    
    public static void main(String[] args) {
        ClienteJugador game = new ClienteJugador();
        game.setVisible(true);
    }
    private void initUI() {

        add(new Interfaz());
        setTitle("BreakoutTEC");
        setLocation(0,0);

        setDefaultCloseOperation(EXIT_ON_CLOSE);
        
        setResizable(false);
        pack();
    }
}
