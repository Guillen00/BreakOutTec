/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientejugador;

import java.awt.event.KeyEvent;
import javax.swing.ImageIcon;

/**
 *
 * @author Leonardo Guillen
 * Esta clase se encarga de crear el objeto Raqueta heredando las caracteristicas de la animacion
 */
public class Raqueta extends Animacion{
    /*Se inicializan las variables por utilizar en la clase
    *
    */
    private Integer dx = 0;
    public static Integer maxLargo = 350;
    public static Integer minLargo = 100;
    public static  Integer LARGORAQUETA = 120;
    public static Integer ANCHORAQUETA = 20;
    public static Integer velocidad =5;
    public static Integer posX =0 ;

    /*Se crea un contructor el cual llama a la funcion initPaddle
    *
    */
    public Raqueta() {

        initPaddle();
    }

    /*Esta funcion carga una imagen para la raqueta, de las dimensiones y una posicion inicial
    *
    */
    private void initPaddle() {
        loadImage();
        getImageDimensionsPaddle();
        resetState();
    }

    /*Esta funcion carga una imagen de la carpeta imagen
    *
    */
    private void loadImage() {
        ImageIcon ii = new ImageIcon("src/imagen/raqueta.png");
        image = ii.getImage();
    }
    
    /*Esta funcion de encarga del movimiento de la raqueta verificando que no se salga de la pantalla de juego
    *
    */
    void move() {
        x += dx;      
        if (x < 0) {
            x = 0;
        }
        if (x > Variables.WIDTH - LARGORAQUETA) {
            x = Variables.WIDTH - LARGORAQUETA;
        }
        posX=x;
    }

    /*Esta funcion recibe un evento y este verifica si el evento es una tecla de direccion y si si lo es cambia el valor de x de la raqueta
    *
    */
    void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();
        if (key == KeyEvent.VK_LEFT) {
            dx = -velocidad;
        }
        if (key == KeyEvent.VK_RIGHT) {
            dx = velocidad;
        }
    }

    /*Esta funcion verifica si la tecla se dejo de presionar no varia su posicion en x
    *
    */
    void keyReleased(KeyEvent e) {
        int key = e.getKeyCode();
        if (key == KeyEvent.VK_LEFT) {
            dx = 0;
        }
        if (key == KeyEvent.VK_RIGHT) {
            dx = 0;
        }
    }

    /*Esta funcion da una posicion incial a la raqueta
    *
    */
    private void resetState() {
        x = Variables.INIT_PADDLE_X;
        y = Variables.INIT_PADDLE_Y;
    }
}
