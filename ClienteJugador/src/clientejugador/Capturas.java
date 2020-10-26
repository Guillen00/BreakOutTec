package clientejugador;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Capturas {
    private JPanel componente;
    private int number;

    public Capturas(JPanel componente){
        this.componente=componente;
        this.number=0;
    }

    public void capturar(Parser parser){
            try {

                BufferedImage img = new BufferedImage(componente.getWidth(), componente.getHeight(), BufferedImage.TYPE_INT_RGB);
                componente.paint(img.getGraphics());
                parser.setImageNumber(String.valueOf(number));
                File outputfile = new File(parser.getURL() + parser.getImageNumber() +".jpeg");
                try {
                    ImageIO.write(img, "jpeg", outputfile);
                    number++;
                   /** if(number==300){
                        number=0;
                    }*/
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }catch (IllegalArgumentException ignored){}
    }
}
