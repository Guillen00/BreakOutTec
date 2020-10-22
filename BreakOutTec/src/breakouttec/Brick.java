/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package breakouttec;

/**
 *
 * @author leona
 */
import javax.swing.ImageIcon;

public class Brick extends Sprite {

    private boolean destroyed;
    private int posX,posY;
    private String habilidad;
 
    public Brick(int posX, int posY) {

        initBrick(posX, posY);
    }
    
    public void setHabilidad(int posX , int posY,String habilidad){
        if(posX == this.posX && this.posY == posY){
            this.habilidad = habilidad;
        }
    }
    private void initBrick(int x, int y) {

        this.posX = x;
        this.posY = y;
        //this.habilidad = null;
        destroyed = false;

        loadImage();
        getImageDimensions();
    }

    private void loadImage() {

        ImageIcon ii = new ImageIcon("src/imagenes/brick.png");
        image = ii.getImage();
    }

    boolean isDestroyed() {

        return destroyed;
    }

    void setDestroyed(boolean val) {

        destroyed = val;
    }
}