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


import java.util.ArrayList;
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

    
    private static Parser instanciaUnica;
 
    private Parser() {}

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

    public void parserText(String texto){
        URL = texto.split(";")[0];
        imageNumber=texto.split(";")[1];
        puntaje = texto.split(";")[2];
        record = texto.split(";")[3];
        raquetaMitad = texto.split(";")[4];
        raquetaDoble = texto.split(";")[5];
        velocidadMas = texto.split(";")[6];
        velocidadMenos = texto.split(";")[7];
        masVida = texto.split(";")[8];
        dosBolas = texto.split(";")[9].substring(0,1);
    }
    public Boolean isRaquetaMitad(){
        return 1 ==  Integer.parseInt(this.raquetaMitad);
    }
    public Boolean isRaquetaDoble(){
        return 1 ==  Integer.parseInt(this.raquetaDoble);
    }
    public Boolean isVelocidadMas(){
        return 1 ==  Integer.parseInt(this.velocidadMas);
    }
    public Boolean isVelocidadMenos(){
        return 1 ==  Integer.parseInt(this.velocidadMenos);
    }
    public Boolean isMasVida(){
        return 1 ==  Integer.parseInt(this.masVida);
    }
    public Boolean isDosBolas(){
        return 1 ==  Integer.parseInt(this.dosBolas);
    } 
    
    
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
        Interfaz.Puntaje = Integer.parseInt(puntaje);
        Interfaz.Record = Integer.parseInt(record);

    } 
    
    public void LadrillosRotos(Integer columna,Integer fila){
        Columna=columna-1;
        Fila=fila-1;
    }

    public String getURL() {
        return URL;
    }

    public String sendData(){
      String aux;
      aux = URL + ";" + imageNumber+ ";"+ Interfaz.SubirNivel.toString() + ";" + Columna.toString() + ";"+ Fila.toString();
      Columna= -1;
      Fila= -1;      
      return aux;
    }

    public String getImageNumber() {
        return imageNumber;
    }

    public void setImageNumber(String imageNumber) {
        this.imageNumber = imageNumber;
    }
}