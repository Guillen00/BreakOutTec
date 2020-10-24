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
 * @author Usuario
 */
public class Raqueta extends Animacion{
    private Integer dx = 0;
    private Integer largo = 10;//Introducir valor adecuado con la interfaz
    public static  Integer LARGORAQUETA = 60;
    public static Integer ANCHORAQUETA = 20;
    public static Integer velocidad =1;
    public static Integer posX =0 ;
    
    public Integer getLargo() {
        return largo;
    }
    public void setLargo(Integer largo) {
        this.largo = largo;
    }
    public Integer getdX() {
        return dx;
    }
    public void setdX(Integer dX) {
        this.dx = dX;
    }
    public void reducirMitad(){
        setLargo(getLargo()/2);
    }
    public void doblarMitad(){
        setLargo(getLargo()*2);
    }
    public Raqueta() {

        initPaddle();
    }

    private void initPaddle() {

        loadImage();
        getImageDimensionsPaddle();

        resetState();
    }

    private void loadImage() {

        ImageIcon ii = new ImageIcon("src/imagen/raqueta.png");
        image = ii.getImage();
    }
    //public Integer posX; 
    
    void move() {
        x += dx;
        //x += dx;
        
        if (x < 0) {

            x = 0;
        }

        if (x > Variables.WIDTH - LARGORAQUETA) {

            x = Variables.WIDTH - LARGORAQUETA;
        }
        posX=x;
    }

    void keyPressed(KeyEvent e) {

        int key = e.getKeyCode();

        if (key == KeyEvent.VK_LEFT) {

            dx = -velocidad;
        }

        if (key == KeyEvent.VK_RIGHT) {

            dx = velocidad;
        }
    }

    void keyReleased(KeyEvent e) {

        int key = e.getKeyCode();

        if (key == KeyEvent.VK_LEFT) {

            dx = 0;
        }

        if (key == KeyEvent.VK_RIGHT) {

            dx = 0;
        }
    }

    private void resetState() {

        x = Variables.INIT_PADDLE_X;
        y = Variables.INIT_PADDLE_Y;
    }
}
