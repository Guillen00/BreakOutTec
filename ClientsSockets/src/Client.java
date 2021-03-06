// A Java program for a Client
import java.net.*;
import java.io.*;
import java.util.concurrent.TimeUnit;

public class Client
{
    private final String TIPO="Tipo: Jugador";
    private Socket socket;
    private PrintStream out;
    private BufferedReader in;

    public Client(String address, int port)
    {
        //Inicia el Socket
        try
        {
            socket = new Socket(address, port);
            System.out.println("Connected");

            out = new PrintStream( socket.getOutputStream() );
            in = new BufferedReader( new InputStreamReader( socket.getInputStream() ) );

            //Envia el tipo de coneccion
            sendMessage(this.TIPO);

        } catch(IOException u)
        {
            System.out.println(u);
            closeConnection();
        }
    }

    public String getMessage(){
        String updade=null;
        try{
            updade=read();
        }catch(IOException u){
            System.out.println(u);
            closeConnection();
        }
        return updade;
    }

    public void sendMessage(String Message){
        out.print(Message+"\0");
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
        try {
            TimeUnit.MILLISECONDS.sleep(100);
        }catch (InterruptedException u){
            System.out.println(u);
        }

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
            System.out.println(i);
        }
    }

    public static void main(String args[])
    {
        Client client = new Client("127.0.0.1", 27015);
        String result = client.getMessage();
        System.out.println(result);
        client.sendMessage("4;4;4\n4;5;3;4\n0;0;0;0;0\n0;0;0;0;0\n0;0;0;0;0\n" +
                "0;0;0;0;0\n0;0;0;0;0\n0;0;0;0;0\n0;0;0;0;0\n0;0;0;0;0");
    }
}
