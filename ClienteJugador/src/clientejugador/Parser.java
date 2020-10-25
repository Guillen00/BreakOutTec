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


import javafx.util.Pair;
import jdk.internal.org.objectweb.asm.tree.IntInsnNode;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Usuario
 */
public class Parser{
/*
    private Integer vidas;
    private Integer posicionRaqX;
    private Integer balones;
    private Integer numeroColumnas;
    private Integer nivel;
    private Integer raquetaTamano;
    private Integer velocidad;
    private Integer puntaje;
    private List<Integer> posX  = new ArrayList<>();
    private List<Integer> posY  = new ArrayList<>();
    private List<String> Fila7 = new ArrayList<>();
    private List<String> Fila6 = new ArrayList<>();
    private List<String> Fila5 = new ArrayList<>();
    private List<String> Fila4 = new ArrayList<>();
    private List<String> Fila3 = new ArrayList<>();
    private List<String> Fila2 = new ArrayList<>();
    private List<String> Fila1 = new ArrayList<>();
    private List<String> Fila0 = new ArrayList<>();
    private List<List<String>> Matriz = new ArrayList<>();
    
    */
    private String URL;
    private String puntaje;
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


    public void parserText(String texto){
        System.out.print(texto);
        URL = texto.split(";")[0];
        puntaje = texto.split(";")[1];
        raquetaMitad = texto.split(";")[2];
        raquetaDoble = texto.split(";")[3];
        velocidadMas = texto.split(";")[4];
        velocidadMenos = texto.split(";")[5];
        masVida = texto.split(";")[6];
        dosBolas = texto.split(";")[7].substring(0,1);
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
        if(isRaquetaMitad()){
            Raqueta.LARGORAQUETA = Raqueta.LARGORAQUETA/2;
        }
        if(isRaquetaDoble()){
            Raqueta.LARGORAQUETA = Raqueta.LARGORAQUETA*2;
        }
        if(isVelocidadMas()){
            Bola.velocidad = Bola.velocidad+1;
        }
        if(isVelocidadMenos()){
            Bola.velocidad = Bola.velocidad-1;
        }
        if(isMasVida()){
            Interfaz.vidas = Interfaz.vidas+1;
        }
        if(isDosBolas()){
            Interfaz.PowerBall = true;
        }
        Interfaz.Puntaje = Integer.parseInt(puntaje);
    } 
    
    public void LadrillosRotos(Integer columna,Integer fila){
        Columna=columna-1;
        Fila=fila-1;
    }
    
    public String sendData(){
      String aux;
      aux = URL + ";" + Interfaz.SubirNivel.toString() + ";" + Columna.toString() + ";"+ Fila.toString();
      Columna= -1;
      Fila= -1;      
      System.out.print(aux);
      return aux;
    }
    
}