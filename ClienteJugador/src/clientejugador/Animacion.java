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
 * @author leona
 */
public class Animacion {
    Integer x;
    Integer y;
    Integer imageWidth;
    Integer imageHeight;
    Image image;

    protected void setX(Integer x) {

        this.x = x;
    }

    int getX() {

        return x;
    }

    protected void setY(Integer y) {

        this.y = y;
    }

    int getY() {

        return y;
    }

    int getImageWidth() {

        return imageWidth;
    }

    int getImageHeight() {

        return imageHeight;
    }

    Image getImage() {

        return image;
    }

    Rectangle getRectPaddle() {

        return new Rectangle(x, y,
                 Raqueta.LARGORAQUETA , Raqueta.ANCHORAQUETA);
    }
    Rectangle getRectBall() {

        return new Rectangle(x, y,
                image.getWidth(null), image.getHeight(null));
    }
    Rectangle getRectBrick() {

        return new Rectangle(x, y,
                image.getWidth(null), image.getHeight(null));
    }

    void getImageDimensionsPaddle() {

        imageWidth =  Raqueta.ANCHORAQUETA;
        imageHeight = Raqueta.LARGORAQUETA;
    }
    
    void getImageDimensionsBall() {

        imageWidth = image.getWidth(null);
        imageHeight = image.getHeight(null);
    }
    void getImageDimensionsBrick() {

        imageWidth = 60;
        imageHeight = 18;
    }
}
