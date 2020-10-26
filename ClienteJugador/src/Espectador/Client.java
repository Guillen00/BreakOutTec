package Espectador;

import javax.print.attribute.standard.NumberUp;
import java.net.*;
import java.io.*;
import java.util.concurrent.TimeUnit;

public class Client
{
    private final String TIPO="Tipo: Espectador";
    private Socket socket;
    private PrintStream out;
    private BufferedReader in;


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
            closeConnection();
        }
    }

    public String getMessage(){
        String update=null;
        try{
            update=read();
        }catch(IOException u){
            closeConnection();
        }
        return update;
    }

    public void sendMessage(String Message){
        out.print(Message+"\0");
    }

    public String getURL(){
        try {
            String[] message= getMessage().split(";");
            return message[1];
        }catch (NullPointerException e){
            return null;
        }
    }

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
/*
        try {
            TimeUnit.MILLISECONDS.sleep(100);
        }catch (InterruptedException u){
        }
*/

        return message;
    }

    private void closeConnection(){
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