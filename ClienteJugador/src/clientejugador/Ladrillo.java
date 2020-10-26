/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientejugador;

/**
 *
 * @author Usuario
 */

import javax.swing.ImageIcon;

public class Ladrillo extends Animacion{
    private Boolean destroyed;

    public static Parser Aux = Parser.getInstance();

    

    public Ladrillo(Integer x, Integer y) {

        initLadrillo(x, y);
    }

    private void initLadrillo(Integer x, Integer y) {

        this.x = x;
        this.y = y;

        destroyed = false;

        loadImage();
        getImageDimensionsBrick();
    }

    private void loadImage() {
        
        if(((this.y-50)/30) == 7){
            ImageIcon ii = new ImageIcon("src/imagen/verde.png");
            image = ii.getImage();
        }
        else if(((this.y-50)/30) == 6){
            ImageIcon ii = new ImageIcon("src/imagen/verde.png");
            image = ii.getImage();
        }
        else if(((this.y-50)/30) == 5){
            ImageIcon ii = new ImageIcon("src/imagen/amarillo.png");
            image = ii.getImage();
        }
        else if(((this.y-50)/30) == 4){
            ImageIcon ii = new ImageIcon("src/imagen/amarillo.png");
            image = ii.getImage();
        }
        else if(((this.y-50)/30) == 3){
            ImageIcon ii = new ImageIcon("src/imagen/naranja.png");
            image = ii.getImage();
        }
        else if(((this.y-50)/30) == 2){
            ImageIcon ii = new ImageIcon("src/imagen/naranja.png");
            image = ii.getImage();
        }
        else if(((this.y-50)/30) == 1){
            ImageIcon ii = new ImageIcon("src/imagen/rojo.png");
            image = ii.getImage();
        }
        else{
        ImageIcon ii = new ImageIcon("src/imagen/rojo.png");
        image = ii.getImage();}
    }

    Boolean isDestroyed() {

        return destroyed;
    }

    void setDestroyed1(Boolean val) {

        destroyed = val;
    }
    
    public void enviar_Matriz(Integer x,Integer y){
        Integer columna = 1;
        Integer fila = 1;
        columna= ((x-110)/70)+1;
        fila = ((y-50)/30)+1;
        Aux.LadrillosRotos(columna, fila);
        
    }
}
