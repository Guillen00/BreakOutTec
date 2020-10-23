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
    
    private Integer posX = null;
    private Integer posY = null;
    private Integer velocidad = null;

    public Integer getPosX() {
        return posX;
    }

    public void setPosX(Integer posX) {
        this.posX = posX;
    }

    public Integer getPosY() {
        return posY;
    }

    public void setPosY(Integer posY) {
        this.posY = posY;
    }
    
    public void sumarY(Integer velocidad){
        this.posY = this.posY + velocidad;
    } 
    
    public void sumarX(Integer velocidad){
        this.posX = this.posX + velocidad;
    }

    public Integer getVelocidad() {
        return velocidad;
    }

    public void setVelocidad(Integer velocidad) {
        this.velocidad = velocidad;
    }
    
    public void doblarVelovidad(){
        setVelocidad(getVelocidad()*2);
    }
    
    public void reducirVelocidad(){
        setVelocidad(getVelocidad()/2);
    }
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
    
    private int xdir;
    private int ydir;

    public Bola() {

        initBall();
    }

    private void initBall() {

        xdir = 1;
        ydir = -1;

        loadImage();
        getImageDimensions();
        resetState();
    }

    private void loadImage() {

        ImageIcon ii = new ImageIcon("src/imagen/bola1.png");
        image = ii.getImage();
    }

    void move() {

        x += xdir;
        y += ydir;

        if (x == 0) {

            setXDir(1);
        }

        if (x == Variables.WIDTH - imageWidth) {

            System.out.println(imageWidth);
            setXDir(-1);
        }

        if (y == 0) {

            setYDir(1);
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
