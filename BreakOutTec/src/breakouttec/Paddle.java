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
import java.awt.event.KeyEvent;
import javax.swing.ImageIcon;

public class Paddle extends Sprite  {

    private int dx;
    private int largo;

    public int getLargo() {
        return largo;
    }

    public void setLargo(int largo) {
        this.largo = largo;
    }
    
    public Paddle() {
        initPaddle();
    }

    private void initPaddle() {

        loadImage();
        getImageDimensions();

        resetState();
    }

    private void loadImage() {

        ImageIcon ii = new ImageIcon("src/imagenes/paddle.png");
        image = ii.getImage();
    }

    void move() {

        x += dx;

        if (x <= 0) {

            x = 0;
        }

        if (x >= Commons.WIDTH - imageWidth) {

            x = Commons.WIDTH - imageWidth;
        }
    }

    void keyPressed(KeyEvent e) {

        int key = e.getKeyCode();

        if (key == KeyEvent.VK_LEFT) {

            dx = -1;
        }

        if (key == KeyEvent.VK_RIGHT) {

            dx = 1;
        }
    }

    void keyReleased(KeyEvent e) {

        int key = e.getKeyCode();

        if (key == KeyEvent.VK_LEFT) {

            dx = 0;
        }

        if (key == KeyEvent.VK_RIGHT) {

            dx = 0;
        }
    }

    private void resetState() {

        x = Commons.INIT_PADDLE_X;
        y = Commons.INIT_PADDLE_Y;
    }
}