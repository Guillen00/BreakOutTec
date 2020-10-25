/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Espectador;

import java.awt.Graphics;
import java.awt.Image;
import javax.swing.ImageIcon;
import javax.swing.JPanel;

/**
 *
 * @author leona
 */
public class Aux_Expectador extends JPanel{
    Image image;
    
    public Aux_Expectador(){}
    
    @Override
    public void paint(Graphics g){
        
        ImageIcon ii = new ImageIcon("src/imagen/amarillo.png");
        image = ii.getImage();
        g.drawImage(image, 5,5, 500,
                        500, this);
    }
    
}
