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
    //p    private Boolean destroyed = new Boolean(false);
    private Boolean destroyed;
    private Integer posX = null;
    private Integer posY = null;
    private Integer golpes = null;
    private Integer puntacion = null;
    private String habilidad;
    public static Parser Aux = Parser.getInstance();

    public Integer getGolpes() {
        return golpes;
    }

    public void setGolpes(Integer golpes) {
        this.golpes = golpes;
    }

    public Integer getPuntacion() {
        return puntacion;
    }

    public void setPuntacion(Integer puntacion) {
        this.puntacion = puntacion;
    }
    
    public Boolean getDestroyed() {
        return destroyed;
    }

    public void setDestroyed(Boolean destroyed) {
        this.destroyed = destroyed;
    }

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

    public String getHabilidad() {
        return habilidad;
    }

    public void setHabilidad(String habilidad) {
        this.habilidad = habilidad;
    }
    
    public void sumarPuntacion(Integer punt){
        this.puntacion = this.puntacion + punt;
    }
    
    public void aplicacionHabilidad(){
        if(getDestroyed()== true){
            //Introducir funcion que aplique algun cambio en las pelotas 
            //en la raqueta o en la veolicidad del juego 
        }
    }
    

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
        System.out.println("----------------------------------------------------");
        System.out.println("Columna");
        System.out.println(columna);
        System.out.println("Fila");
        System.out.println(fila);
        Aux.LadrillosRotos(columna, fila);
        //Matrix.setMatriz(columna, fila);
        
    }
}
