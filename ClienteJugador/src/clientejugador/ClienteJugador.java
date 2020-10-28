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
 * @author Leonardo Guillen
 * 
 * Esta clase se encarga de inicializar el programa heredando la cualidad de JFrame
 * 
 */
public class ClienteJugador extends JFrame{

    /**
     * @param args the command line arguments
     */
    
    /*Se crea un constructor el cual llama a la funcion initUI
    *
    */
    public ClienteJugador() {

        initUI();
    } 
    
    /* Funcion main la cual da inicio y ejecucion del programa llamando a la clase Cliente jugador
    haciendola visible
    *
    */
    public static void main(String[] args) {
        ClienteJugador game = new ClienteJugador();
        game.setVisible(true);
    }
    
    /*Funcion agrega una clase Interfaz al jframe y le da las caracteristicas parea la pantalla
    *
    */
    private void initUI() {

        add(new Interfaz());
        setTitle("BreakoutTEC");
        setLocation(0,0);

        setDefaultCloseOperation(EXIT_ON_CLOSE);
        
        setResizable(false);
        pack();
    }
}
