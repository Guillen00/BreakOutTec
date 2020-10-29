package Espectador;

import java.net.*;
import java.io.*;

/**
 * Clase cliente que se encarga de la comunicacion con el servidor
 */
public class Client
{
    private final String TIPO="Tipo: Espectador";
    public Socket socket;
    private PrintStream out;
    private BufferedReader in;

    /**
     * Constructor del cliente
     * @param address Direccion del servidor
     * @param port Puerto del servidor
     */
    public Client(String address, int port)
    {

        //Inicia el Socket
        try
        {
            socket = new Socket(address, port);

            out = new PrintStream( socket.getOutputStream() );
            in = new BufferedReader( new InputStreamReader( socket.getInputStream() ) );

            //Envia el tipo de coneccion
            sendMessage(this.TIPO);

        } catch(IOException u)
        {
           // closeConnection();
        }
    }

    /**
     * Funcion para obtener el mensaje del servidor
     * @return El mensaje del servidor
     */

    public String getMessage(){
        String update=null;
        try{
            update=read();
        }catch(IOException u){
            closeConnection();
        }
        return update;
    }

    /**
     * Funcion para enviar un mensaje
     * @param Message Mensaje a enviar
     */
    public void sendMessage(String Message){
        out.print(Message+"\0");
    }

    /**
     * Funcion para obtener la imagen
     * @return Retorna la imagen en string
     */
    public String getIMG(){
        try {
            String[] message= getMessage().split(";");
            return message[1];
        }catch (NullPointerException e){
            return null;
        }
    }

    /**
     * Funcion auxiliar para leer el mensaje recibido
     * @return Retorna el mensaje recibido
     * @throws IOException Error al recibir
     */
    private String read() throws IOException {
        String line = in.readLine();
        String message="";
        in.mark(1);
        while(in.read()!=0)
        {
            message+=line+'\n';
            in.reset();
            line = in.readLine();
            in.mark(1);
        }
        message+=line;
        return message;
    }

    /**
     * Metodo para cerrar la conexion con el servidor
     */
    public void closeConnection(){
        try
        {
            in.close();
            out.close();
            socket.close();
        }
        catch(IOException i)
        {
        }
    }

}