/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientejugador;

import javax.swing.ImageIcon;

/**
 *
 * @author Leonardo Guillen
 * Esta clase se encarga de crear el objeto bola heredando las caracteristicas de la animacion
 */
public class Bola extends Animacion{
    
    /*Se inicializan las variables por utilizar en la clase
    *
    */
    public Parser parser ;
    public static Integer velocidad = 2;
    private Integer xdir;
    private Integer ydir;

    /*Se crea un contructor de la clase la cual llama initBall
    *
    */
    public Bola() {

        initBall();
    }

    /*Esta funcion inicializa la bola dandole valores en X y Y , carga la imagen y le da sus dimensiones
    *
    */
    private void initBall() {

        xdir = velocidad;
        ydir = -velocidad;

        loadImage();
        getImageDimensionsBall();
        resetState();
    }

    /*Esta funcion carga una imagen desde la carpeta imagen 
    *
    */
    private void loadImage() {

        ImageIcon ii = new ImageIcon("src/imagen/bola1.png");
        image = ii.getImage();
    }
    /*Esta funcion se encarga del movimiento de la bola comparando su posicion con el tamaño de la pantalla para que no salga de la pantalla de juego
    *
    */
    void move() {

        x += xdir;
        y += ydir;

        if (x < 0) {

            setXDir(velocidad);
        }

        if (x > Variables.WIDTH - imageWidth) {

            setXDir(-velocidad);
        }

        if (y < 0) {

            setYDir(velocidad);
        }
    }

    /*Esta funcion establece el primer lugar donde se dibuja la bola
    *
    */
    private void resetState() {

        x = Variables.INIT_BALL_X;
        y = Variables.INIT_BALL_Y;
    }
    /*Esta funcion otorga un valor para x
    *
    */
    void setXDir(int x) {

        xdir = x;
    }
    /*Esta funcion otorga un valor para y
    *
    */
    void setYDir(int y) {

        ydir = y;
    }
    /*Esta funcion retorna un valor para y
    *
    */
    int getYDir() {

        return ydir;
    }
    
}
