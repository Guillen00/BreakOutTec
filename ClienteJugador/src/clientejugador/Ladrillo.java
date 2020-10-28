/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientejugador;

/**
 *
 * @author Leonardo Guillen
 * Esta clase se encarga de crear el objeto Ladrillo heredando las caracteristicas de la animacion
 */

import javax.swing.ImageIcon;

public class Ladrillo extends Animacion{
    /*Se inicializan las variables por utilizar en la clase
    *
    */
    
    private Boolean destroyed;

    public static Parser Aux = Parser.getInstance();

    /*Se crea un contructor el cual envia una posicion en X y Y 
    *
    */

    public Ladrillo(Integer x, Integer y) {

        initLadrillo(x, y);
    }

    /*Se crea un contructor el cual da una posicion en X y Y , carga la imagen u le da sus dimensiones
    *
    */
    private void initLadrillo(Integer x, Integer y) {

        this.x = x;
        this.y = y;

        destroyed = false;

        loadImage();
        getImageDimensionsBrick();
    }

    /*Esta funcion se encarga de cargar la imagen dependiendo de la fila en la cual se encuentra el ladrillo
    *
    */
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

    /*Retorna un boleano 
    *
    */
    Boolean isDestroyed() {

        return destroyed;
    }

    /*Asigna in valor para el booleano destroyed
    *
    */
    void setDestroyed1(Boolean val) {

        destroyed = val;
    }
    
    /*Esta funcion se encarga de recibir un X y Y del ladrillo y se envia a la funion LadrillosRotos la fila y columna en la cual se encuentra
    *
    */
    public void enviar_Matriz(Integer x,Integer y){
        Integer columna = 1;
        Integer fila = 1;
        columna= ((x-110)/70)+1;
        fila = ((y-50)/30)+1;
        Aux.LadrillosRotos(columna, fila);
        
    }
}
