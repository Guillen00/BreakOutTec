/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientejugador;

import javax.swing.ImageIcon;

/**
 *
 * @author Usuario 
 */
public class Bola extends Animacion{
    public Parser parser = new Parser();
    private Integer posX = null;
    private Integer posY = null;
    public static Integer velocidad = 1;
    
    
    
    
   
    /*
    public void movimiento(Integer largo,Integer alto){

    }
    
    public void movAribaAbajo(){
        sumarX(getVelocidad());
    }
    
    public void movAbajoArriba(){
        sumarX(-getVelocidad());
    }
    
    public void movDiaDerArriba(){
        sumarX(getVelocidad());
        sumarY(getVelocidad());
    }
    
    public void movDiaDerAbajo(){
        sumarX(getVelocidad());
        sumarY(-getVelocidad());
    }
    
    public void movDiaIzqArriba(){
        sumarX(-getVelocidad());
        sumarY(getVelocidad());
    }
    
    public void movDiaIzqAbejo(){
        sumarX(getVelocidad());
        sumarY(-getVelocidad()); 
    }
*/
    
    private Integer xdir;
    private Integer ydir;

    public Bola() {

        initBall();
    }

    private void initBall() {

        xdir = velocidad;
        ydir = -velocidad;

        loadImage();
        getImageDimensionsBall();
        resetState();
    }

    private void loadImage() {

        ImageIcon ii = new ImageIcon("src/imagen/bola1.png");
        image = ii.getImage();
    }

    void move() {

        x += xdir;
        y += ydir;

        if (x < 0) {

            setXDir(velocidad);
        }

        if (x > Variables.WIDTH - imageWidth) {

            System.out.println(imageWidth);
            setXDir(-velocidad);
        }

        if (y < 0) {

            setYDir(velocidad);
        }
    }

    private void resetState() {

        x = Variables.INIT_BALL_X;
        y = Variables.INIT_BALL_Y;
    }

    void setXDir(int x) {

        xdir = x;
    }

    void setYDir(int y) {

        ydir = y;
    }

    int getYDir() {

        return ydir;
    }
    
}
