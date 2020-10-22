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
    private boolean destroyed;

    public Ladrillo(int x, int y) {

        initLadrillo(x, y);
    }

    private void initLadrillo(int x, int y) {

        this.x = x;
        this.y = y;

        destroyed = false;

        loadImage();
        getImageDimensions();
    }

    private void loadImage() {

        ImageIcon ii = new ImageIcon("src/imagen/morado.png");
        image = ii.getImage();
    }

    boolean isDestroyed() {

        return destroyed;
    }

    void setDestroyed(boolean val) {

        destroyed = val;
    }
}
