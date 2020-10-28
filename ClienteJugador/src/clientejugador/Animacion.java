/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientejugador;

import java.awt.Image;
import java.awt.Rectangle;

/**
 *
 * @author Leonardo Guillen
 * Esta clase se enarga se otrogar valores a X y Y en los objetos en los cuales se llama
 * Crea rectangulos no visibles para manejar la colision de las figuras y maneja el tamaño de las imagenes
 */
public class Animacion {
    /*Se inicializan las variables por utilizar en la clase
    *
    */
    Integer x;
    Integer y;
    Integer imageWidth;
    Integer imageHeight;
    Image image;

    /* Esta funcion da un valor para x
    *
    */
    protected void setX(Integer x) {

        this.x = x;
    }
    
    /*Esta funcion retorna un valor x
    *
    */

    int getX() {

        return x;
    }

    /*Esta funcion otorga un  valor para y
    *
    */
    protected void setY(Integer y) {

        this.y = y;
    }

    /*Esta funcion retorna un valor para y
    *
    */
    int getY() {

        return y;
    }

    /*Esta funcion da un ancho para imagen
    *
    */
    int getImageWidth() {

        return imageWidth;
    }

    /*Esta funcion da un largo para la imagen
    *
    */
    int getImageHeight() {

        return imageHeight;
    }

    /*Esta funcion retorna una imagen otorgada a un elemento
    *
    */
    Image getImage() {

        return image;
    }

    /*Crea rectangulos no visibles para la raqueta
    *
    */
    Rectangle getRectPaddle() {

        return new Rectangle(x, y,
                 Raqueta.LARGORAQUETA , Raqueta.ANCHORAQUETA);
    }
    /*Crea rectangulos no visibles para la bola
    *
    */
    Rectangle getRectBall() {

        return new Rectangle(x, y,
                image.getWidth(null), image.getHeight(null));
    }
    /*Crea rectangulos no visibles para los ladrillos
    *
    */
    Rectangle getRectBrick() {

        return new Rectangle(x, y,
                image.getWidth(null), image.getHeight(null));
    }

    /*Otorga las dimensiones para la imagen de la raqueta
    *
    */
    void getImageDimensionsPaddle() {

        imageWidth =  Raqueta.ANCHORAQUETA;
        imageHeight = Raqueta.LARGORAQUETA;
    }
    /*Otorga las dimensiones para la imagen de la bola
    *
    */
    void getImageDimensionsBall() {

        imageWidth = image.getWidth(null);
        imageHeight = image.getHeight(null);
    }
    /*Otorga las dimensiones para la imagen de los ladrillos
    *
    */
    void getImageDimensionsBrick() {

        imageWidth = 60;
        imageHeight = 18;
    }
}
