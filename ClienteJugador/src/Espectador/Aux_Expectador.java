/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Espectador;

import java.awt.Graphics;
import java.awt.Image;
import java.io.File;
import javax.swing.ImageIcon;
import javax.swing.JPanel;

/**
 *
 * @author leona
 */
public class Aux_Expectador extends JPanel implements Runnable{
    private Image image;
    private Client client = new Client("127.0.0.1", 27015);
    String filename = client.getURL() + ".jpeg";

    public Aux_Expectador () {
    }

    @Override
    public void paint(Graphics g) {
        ImageIcon ii = new ImageIcon(filename);
        File file = new File(filename);
        image = ii.getImage();
        g.drawImage(image, 0, 0, 1300,
                700, this);
        file.delete();
    }

    public void run() {
        while (true) {
            filename = client.getURL() + ".jpeg";
            repaint();
        }
    }
}