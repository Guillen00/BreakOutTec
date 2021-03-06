/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientejugador;

/**
 *
*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import javax.imageio.IIOImage;
import javax.imageio.ImageIO;
import javax.imageio.ImageWriteParam;
import javax.imageio.ImageWriter;
import javax.imageio.stream.ImageOutputStream;
import javax.swing.*;
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

/**
 *
 * @author Juan
 */
public class Parser{

    private String URL;
    private String imageNumber;
    private String puntaje;
    private String record;
    private String raquetaDoble;
    private String raquetaMitad;
    private String velocidadMas;
    private String velocidadMenos;
    private String masVida;
    private String dosBolas;
    private Integer Columna=-1;
    private Integer Fila =-1;
    private Integer oldPuntaje=0;
    
    private static Parser instanciaUnica;
 
    private Parser() {}
    /*
    Se utiliza el patron de diseño singeltonde manera tal de que cuando se valla a 
    utilizar una intancia del tipo parser sea las misma puesto que esta clase es la encargada de 
    obtener, modificar y enviar valores al servidor
    */
    private synchronized static void createInstance() {
        if (instanciaUnica == null) { 
            instanciaUnica = new Parser();
        }
    }
 
    public static Parser getInstance() {
        createInstance();

        return instanciaUnica;
    }


    public void setURL(String URL) {
        this.URL = URL;
    }
    /*
    
    */
    public void parserText(String texto){
        URL = texto.split(";")[1];
        imageNumber=texto.split(";")[0];
        puntaje = texto.split(";")[2];
        record = texto.split(";")[3];
        raquetaMitad = texto.split(";")[4];
        raquetaDoble = texto.split(";")[5];
        velocidadMas = texto.split(";")[6];
        velocidadMenos = texto.split(";")[7];
        masVida = texto.split(";")[8];
        dosBolas = texto.split(";")[9].substring(0,1);
    }
    /*
    Revisa si el servidor el valor actual de this.raquetaMitad en caso de que este
    sea uno devuelve verdadero en caso contrario un falso este boleano es evaluado 
    para que la raqueta se divida a la mitad 
    */
    public Boolean isRaquetaMitad(){
        return 1 ==  Integer.parseInt(this.raquetaMitad);
    }
    /*
    Revisa si el servidor el valor actual de this.raquetaDoble en caso de que este
    sea uno devuelve verdadero en caso contrario un falso este boleano es evaluado 
    para que la raqueta se devuelva a la mitad
    */
    public Boolean isRaquetaDoble(){
        return 1 ==  Integer.parseInt(this.raquetaDoble);
    }
    /*
    Revisa si el servidor el valor actual de this.velocidadMas en caso de que este
    sea uno devuelve verdadero en caso contrario un falso este boleano es evaluado 
    para que la pelota aumente su velocidad    
    */
    public Boolean isVelocidadMas(){
        return 1 ==  Integer.parseInt(this.velocidadMas);
    }
    /*
    Revisa si el servidor el valor actual de this.velocidadMenos en caso de que este
    sea uno devuelve verdadero en caso contrario un falso este boleano es evaluado 
    para que la pelota disminuya de su velocidad    
    */
    public Boolean isVelocidadMenos(){
        return 1 ==  Integer.parseInt(this.velocidadMenos);
    }
    /*
    Revisa si el servidor el valor actual de this.masVida en caso de que este
    sea uno devuelve verdadero en caso contrario un falso este boleano es evaluado 
    para que aumente su cantidad de vidas actuales  
    */
    public Boolean isMasVida(){
        return 1 ==  Integer.parseInt(this.masVida);
    }
    /*
    Por cuestiones de errores esta funcion no se utiliza
    */
    public Boolean isDosBolas(){
        return 1 ==  Integer.parseInt(this.dosBolas);
    } 
    
    
    /*
    Actualiza las variables dentro del juego en caso de que se de las varaibles y 
    se encuentre dentro de los limites etablecidos 
    */
    
    public void Update(){
        if(isRaquetaMitad() && (Raqueta.minLargo <= Raqueta.LARGORAQUETA)){
            Raqueta.LARGORAQUETA = Raqueta.LARGORAQUETA/2;
        }
        if(isRaquetaDoble()&& (Raqueta.maxLargo >= Raqueta.LARGORAQUETA)){
            Raqueta.LARGORAQUETA = Raqueta.LARGORAQUETA*2;
        }
        if(isVelocidadMas() && (Bola.velocidad <= 8 )){
            Bola.velocidad = Bola.velocidad+1;
        }
        if(isVelocidadMenos()&& (Bola.velocidad >= 2)){
            Bola.velocidad = Bola.velocidad-1;
        }
        if(isMasVida()){
            Interfaz.vidas = Interfaz.vidas+1;
        }
        if(isDosBolas()){
            Interfaz.PowerBall = true;
        }
        if(Integer.parseInt(puntaje)==0){
            oldPuntaje=Interfaz.Puntaje;
        }
        Interfaz.Puntaje = Integer.parseInt(puntaje)+oldPuntaje;
        Interfaz.Record = Integer.parseInt(record);

    } 
    /*
    
    */
    public void LadrillosRotos(Integer columna,Integer fila){
        Columna=columna-1;
        Fila=fila-1;
    }
    /*
    
    */
    public String getURL() {
        return URL;
    }
    /*
    
    */
    public String sendData(JPanel componente){
      String aux;

      BufferedImage img=null;
      try {

          img = new BufferedImage(componente.getWidth(), componente.getHeight(), BufferedImage.TYPE_INT_RGB);
          componente.paint(img.getGraphics());

          ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
          try {

              ImageIO.write(img, "jpeg", byteArrayOutputStream);

              URL= Arrays.toString(byteArrayOutputStream.toByteArray());

              imageNumber=String.valueOf(byteArrayOutputStream.size());
          } catch (IOException e) {
              e.printStackTrace();
          }
      }catch (IllegalArgumentException e){
          URL= "NULL";
          imageNumber="0";
      }
      aux = imageNumber+ ";"+ URL + ";" +Interfaz.SubirNivel.toString() +";"+ Interfaz.Puntaje+ ";" + Columna.toString() + ";"+ Fila.toString();
      Columna= -1;
      Fila= -1;      
      return aux;
    }
    /*
    
    */
    public String getImageNumber() {
        return imageNumber;
    }
    /*
    
    */
    public void setImageNumber(String imageNumber) {
        this.imageNumber = imageNumber;
    }
}