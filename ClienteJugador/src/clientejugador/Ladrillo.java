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

        ImageIcon ii = new ImageIcon("src/imagen/morado.png");
        image = ii.getImage();
    }

    Boolean isDestroyed() {

        return destroyed;
    }

    void setDestroyed1(Boolean val) {

        destroyed = val;
    }
}
