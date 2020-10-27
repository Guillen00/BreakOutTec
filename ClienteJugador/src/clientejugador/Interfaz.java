/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientejugador;

/**
 *
 * @author leona
 */

import javax.swing.JPanel;
import javax.swing.Timer;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.RenderingHints;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.net.SocketException;
import java.net.SocketTimeoutException;


public class Interfaz extends JPanel {
    
    private Timer timer;
    private String message = "Game Over";
    private Bola ball;
    private Bola ball2;
    private Raqueta paddle;
    private Ladrillo[] bricks;
    static Integer vidas = 10000;
    private String vida = "";
    public static Integer niveles = 1;
    private String nivel = "";
    static Integer Puntaje = 0;
    private String puntaje = "";
    static Integer Record = 0;
    private String record = "";
    public static Boolean PowerBall = false;
    static Integer SubirNivel = 0;
    private Client client = new Client("127.0.0.1", 27015);
    private JPanel interfaz=this;
    private Thread thread = new Thread(new Server());

    public static Parser Parser_mensaje = Parser.getInstance();

    public Interfaz() {
        initBoard();
    }

    private void initBoard() {
        
        addKeyListener(new TAdapter());
        setFocusable(true);
        setPreferredSize(new Dimension(1300, 700));
        setBackground(Color.BLACK);
        thread.start();

        gameInit();
    }

    private void gameInit() {
        SubirNivel =0;
        bricks = new Ladrillo[Variables.N_OF_BRICKS];
        ball = new Bola();
        paddle = new Raqueta();

        Integer k = 0;

        for (Integer i = 0; i < 8; i++) {

            for (Integer j = 0; j < 12; j++) {

                bricks[k] = new Ladrillo(j * 70 + 110, i * 30 + 50);
                k++;
            }
        }
        
        timer = new Timer(Variables.PERIOD, new GameCycle());
        timer.start();

    }
    

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;
        

        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);

        g2d.setRenderingHint(RenderingHints.KEY_RENDERING,
                RenderingHints.VALUE_RENDER_QUALITY);

        if (vidas>0) {

            drawObjects(g2d);
            drawPaddle(g2d);
            drawBall(g2d);
        } else {
            timer.stop();
            gameFinished(g2d);
        }

        Toolkit.getDefaultToolkit().sync();
    }

    private void drawObjects(Graphics2D g2d) {
        
        g2d.drawRect(0, 0, 1050, 800);
        Font font = new Font("Verdana", Font.BOLD, 18);
        g2d.setColor(Color.WHITE);
        g2d.setFont(font);
        g2d.drawString("Vidas: ",1100,30);
        vida = ""+ vidas;
        g2d.drawString(vida,1200,30);
        g2d.drawString("Nivel: ",1100,70);
        nivel = ""+ niveles;
        g2d.drawString(nivel,1200,70);
        g2d.drawString("Puntaje: ",1100,110);
        puntaje = ""+ Puntaje;
        g2d.drawString(puntaje,1200,110);
        g2d.drawString("Record: ",1100,150);
        record = ""+ Record;
        g2d.drawString(record,1200,150);

        for (Integer i = 0; i < Variables.N_OF_BRICKS; i++) {

            if (!bricks[i].isDestroyed()) {

                g2d.drawImage(bricks[i].getImage(), bricks[i].getX(),
                        bricks[i].getY(), bricks[i].getImageWidth(),
                        bricks[i].getImageHeight(), this);
            }
        }
    }

    private class TAdapter extends KeyAdapter {

        @Override
        public void keyReleased(KeyEvent e) {

            paddle.keyReleased(e);
        }

        @Override
        public void keyPressed(KeyEvent e) {

            paddle.keyPressed(e);
        }
    }
    
    
    private void gameFinished(Graphics2D g2d) {

        Font font = new Font("Verdana", Font.BOLD, 40);
        FontMetrics fontMetrics = this.getFontMetrics(font);

        g2d.setColor(Color.WHITE);
        g2d.setFont(font);
        g2d.drawRect(0, 0,  1050, 800);
        g2d.drawString(message, 400,350);
    }
    
    private void drawPaddle(Graphics2D g2d) {
        g2d.drawImage(paddle.getImage(), paddle.getX(), paddle.getY(),
                Raqueta.LARGORAQUETA, Raqueta.ANCHORAQUETA, this);
    }
    public Integer interruptor1=0;
     private void drawBall(Graphics2D g2d) {
         g2d.drawImage(ball.getImage(), ball.getX(), ball.getY(),
                ball.getImageWidth(), ball.getImageHeight(), this);
         if(PowerBall){
             if(interruptor1 == 0){
             ball = new Bola();
             interruptor1=1;}

         }

     }
     
     private class GameCycle implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {

            doGameCycle();
            
        }
    }

    int t=0;
    private Boolean flag=true;
    private class Server implements Runnable {
        public void run() {
            try {
                client.socket.setSoTimeout(400);
            } catch (SocketException e) {
                e.printStackTrace();
            }
            while(flag) {
                t=0;
                String entrada = client.getMessage();

                if (entrada != null) {
                    Parser_mensaje.parserText(entrada);
                    Parser_mensaje.Update();

                    t=1;

                    String message=Parser_mensaje.sendData(interfaz);
                    client.sendMessage(message);
                }else{
                    do {
                        try {
                            Thread.sleep(500);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        client.closeConnection();
                        client = new Client("127.0.0.1", 27015);
                        try {
                            client.socket.setSoTimeout(400);
                        } catch (NullPointerException|SocketException e) {
                            e.printStackTrace();
                        }
                    }while (client.socket==null);
                }
            }
        }
    }

    private void doGameCycle() {
        ball.move();
        paddle.move();
        checkCollision();
        repaint();
    }

    private void stopGame() {

        vidas = 0;
        timer.stop();
    }

    int xnono=0;
    private void checkCollision() {

        if (ball.getRectBall().getMaxY() > Variables.BOTTOM_EDGE) {
            if (vidas>0){
                vidas--;
                ball = new Bola();
            }
            else{
                stopGame();
            }
            
        }

        for (Integer i = 0, j = 0; i < Variables.N_OF_BRICKS; i++) {

            if (bricks[i].isDestroyed()) {

                j++;
            }

            if (j == Variables.N_OF_BRICKS) {
                
                message = "Victory";
                //stopGame();
                SubirNivel=1;
                niveles++;
                gameInit();
            }
        }

        if ((ball.getRectBall()).intersects(paddle.getRectPaddle())) {

            Integer paddleLPos = (int) paddle.getRectPaddle().getMinX();
            Integer ballLPos = (int) ball.getRectBall().getMinX();

            Integer first = paddleLPos + (Raqueta.LARGORAQUETA/4);
            Integer second = paddleLPos + (Raqueta.LARGORAQUETA/3);
            Integer third = paddleLPos + (Raqueta.LARGORAQUETA/2);
            Integer fourth = paddleLPos + (Raqueta.LARGORAQUETA/1);

            if (ballLPos < first) {

                ball.setXDir(-Bola.velocidad);
                ball.setYDir(-Bola.velocidad);
            }

            if (ballLPos >= first && ballLPos < second) {

                ball.setXDir(-Bola.velocidad);
                ball.setYDir(-Bola.velocidad * ball.getYDir());
            }

            if (ballLPos >= second && ballLPos < third) {

                ball.setXDir(0);
                ball.setYDir(-Bola.velocidad);
            }

            if (ballLPos >= third && ballLPos < fourth) {

                ball.setXDir(Bola.velocidad);
                ball.setYDir(-Bola.velocidad * ball.getYDir());
            }

            if (ballLPos > fourth) {

                ball.setXDir(Bola.velocidad);
                ball.setYDir(-Bola.velocidad);
            }
            
        }

        for (Integer i = 0; i < Variables.N_OF_BRICKS; i++) {

            if ((ball.getRectBall()).intersects(bricks[i].getRectBrick())) {

                Integer ballLeft = (int) ball.getRectBall().getMinX();
                Integer ballHeight = (int) ball.getRectBall().getHeight();
                Integer ballWidth = (int) ball.getRectBall().getWidth();
                Integer ballTop = (int) ball.getRectBall().getMinY();

                Point pointRight = new Point(ballLeft + ballWidth + 1, ballTop);
                Point pointLeft = new Point(ballLeft - 1, ballTop);
                Point pointTop = new Point(ballLeft, ballTop - 1);
                Point pointBottom = new Point(ballLeft, ballTop + ballHeight + 1);

                if (!bricks[i].isDestroyed()) {

                    if (bricks[i].getRectBrick().contains(pointRight)) {

                        ball.setXDir(-Bola.velocidad);
                    } else if (bricks[i].getRectBrick().contains(pointLeft)) {

                        ball.setXDir(Bola.velocidad);
                    }

                    if (bricks[i].getRectBrick().contains(pointTop)) {

                        ball.setYDir(Bola.velocidad);
                    } else if (bricks[i].getRectBrick().contains(pointBottom)) {

                        ball.setYDir(-Bola.velocidad);
                    }

                    bricks[i].setDestroyed1(true);
                    bricks[i].enviar_Matriz(bricks[i].x, bricks[i].y);

                }
            }
        }
    }

}
