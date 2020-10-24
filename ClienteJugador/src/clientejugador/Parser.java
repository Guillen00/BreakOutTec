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

    public Parser() {}

    public List<Integer> getPosX() {
        return posX;
    }

    public List<Integer> getPosY() {
        return posY;
    }

    public Integer getVidas() {
        return vidas;
    }

    public Integer getPosicionRaqX() {
        return posicionRaqX;
    }

    public Integer getBalones() {
        return balones;
    }

    public Integer getNumeroColumnas() {
        return numeroColumnas;
    }

    public Integer getNivel() {
        return nivel;
    }

    public Integer getRaquetaTamano() {
        return raquetaTamano;
    }

    public Integer getVelocidad() {
        return velocidad;
    }

    public Integer getPuntaje() {
        return puntaje;
    }

    public List<List<String>> getMatriz() {
        return Matriz;
    }


    public void parser(String texto){
        String[] aux =texto.split("\n")[0].split(";");
        vidas = Integer.parseInt(aux[0]);
        posicionRaqX = Integer.parseInt(aux[1]);
        balones = Integer.parseInt(aux[2]);
        numeroColumnas = Integer.parseInt(aux[3]);
        nivel = Integer.parseInt(aux[4]);
        raquetaTamano = Integer.parseInt(aux[5]);
        velocidad = Integer.parseInt(aux[6]);
        puntaje = Integer.parseInt(aux[7]);
        for (String dato:texto.split("\n")[1].split(";")){
            if(posY.size()==posX.size()){
                posX.add(Integer.parseInt(dato));
            }else{
                posY.add(Integer.parseInt(dato));
            }
        }
        insertarEnFila(Fila7,texto.split("\n")[2]);
        insertarEnFila(Fila6,texto.split("\n")[3]);
        insertarEnFila(Fila5,texto.split("\n")[4]);
        insertarEnFila(Fila4,texto.split("\n")[5]);
        insertarEnFila(Fila3,texto.split("\n")[6]);
        insertarEnFila(Fila2,texto.split("\n")[7]);
        insertarEnFila(Fila1,texto.split("\n")[8]);
        insertarEnFila(Fila0,texto.split("\n")[9]);
        agregarMatriz();
    }
    
    public void insertarEnFila(List fila,String aux){
        Integer pos = 0;
        while(pos != numeroColumnas){
            fila.add(aux.split(";")[pos]);
            pos ++;
        }
    }
    
    public void agregarMatriz(){
        Matriz.add(Fila7);
        Matriz.add(Fila6);
        Matriz.add(Fila5);
        Matriz.add(Fila4);
        Matriz.add(Fila3);
        Matriz.add(Fila2);
        Matriz.add(Fila1);
        Matriz.add(Fila0);
    }

    public void perderVida(){
        vidas--;
    }

    public void perderBola(){
        balones--;
    }

    public void updatePosRacket(Integer posx){
        posicionRaqX=posx;
    }

    public void setMatriz(Integer columna,Integer fila){
        Matriz.get(fila).set(columna, "1");
    }

    /**
    public static void main(String[] args) {
        Client client = new Client("127.0.0.1", 27015);
        String result = client.getMessage();
        //System.out.println(result);
        //client.sendMessage("4;4;4\n4;5;3;4\n0;0;0;0;0\n0;0;0;0;0\n0;0;0;0;0\n" +
        //        "0;0;0;0;0\n0;0;0;0;0\n0;0;0;0;0\n0;0;0;0;0\n0;0;0;0;0");

        Parser pa = new Parser();
        pa.parser(result);
        /**pa.parser(
                "3;0;1;5;1000;1000;0;-1;\n" +
                        "1;1\n"+
                "1;2;3;4;5\n" +
                "0;0;0;0;0\n" +
                "0;0;0;0;0\n" +
                "0;0;0;0;0\n" +
                "0;0;0;0;0\n" +
                "0;0;0;0;0\n" +
                "0;0;0;0;0\n" +
                "0;0;0;0;0");**/
       /* System.out.print(pa.toString());
    }*/
    public String toString(){
        return vidas.toString()         +";"+
                posicionRaqX.toString() +";"+
                balones.toString()      +"\n"+
                listaString(posX,posY)  +
                matrizString();
    }

    private String listaString(List list1,List list2){
        String aux = "";
        Integer pos = 0;
        while(pos != list1.size()){
            aux += list1.get(pos).toString();
            aux += ';';
            aux += list2.get(pos).toString();
            aux += ";";
            pos ++;
        }
        aux=aux.substring(0,aux.length()-1);
        aux+="\n";
        return aux;
    }

    private String matrizString(){
        String aux="";
        for(List<String> fila: Matriz){
            for(String elemento: fila){
                aux+=elemento;
                aux+=";";
            }
            aux=aux.substring(0,aux.length()-1);
            aux+="\n";
        }
        return aux;
    }
}