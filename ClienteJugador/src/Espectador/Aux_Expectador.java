/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Espectador;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.net.SocketException;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JPanel;

/**
 *
 * @author leona
 */
public class Aux_Expectador extends JPanel implements Runnable{
    private Image image=null;
    private Client client = new Client("127.0.0.1", 27015);

    public Aux_Expectador () {
    }

    @Override
    public void paint(Graphics g) {
        if(image!=null) {
            g.drawImage(image, 0, 0, 1400,
                    800, this);
        }
    }



    public void run() {
        while (true) {
            try{
                String preimage=client.getURL();
                if(preimage!=null) {
                    String[] preByteArray = preimage.substring(1, preimage.length() - 1).split(", ");
                    byte[] imageArray = new byte[preByteArray.length];
                    try {

                        for (Integer i = 0; i < preByteArray.length; i++) {

                            imageArray[i] = (byte) Integer.parseInt(preByteArray[i]);
                        }

                        try {
                            image = ImageIO.read(new ByteArrayInputStream(imageArray));
                            repaint();
                        } catch (IOException ignored) {
                        }

                    }catch (NumberFormatException e){
                        e.printStackTrace();
                    }
                }
            }catch (IndexOutOfBoundsException ignored) {}
        }
    }
}