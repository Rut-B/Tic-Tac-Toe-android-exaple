package com.example.rutbiton.tictactoe;
import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class GameActivity extends AppCompatActivity {

    private GameBoard gameboard;
    private int xScore,oScore,drowsCount;
    private static final char X_PLAYER = 'X';
    private static final char O_PLAYER = 'O';
    private Button btn1,btn2,btn3,btn4,btn5,btn6,btn7,btn8,btn9;
    private TextView txvXscore,txvOscore,txvDraws,txvGame;
    private char turn;
    private int status_game;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
        //initilaize...
        status_game=-1;//start game
        gameboard = new GameBoard();
        xScore=0;
        oScore=0;
        drowsCount=0;
        turn = X_PLAYER;

        btn1 = (Button) findViewById(R.id.btn1ID);
        btn2 = (Button) findViewById(R.id.btn2ID);
        btn3 = (Button) findViewById(R.id.btn3ID);
        btn4 = (Button) findViewById(R.id.btn4ID);
        btn5 = (Button) findViewById(R.id.btn5ID);
        btn6 = (Button) findViewById(R.id.btn6ID);
        btn7 = (Button) findViewById(R.id.btn7ID);
        btn8 = (Button) findViewById(R.id.btn8ID);
        btn9 = (Button) findViewById(R.id.btn9ID);

        txvXscore = findViewById(R.id.txvXscoreID);
        txvOscore = findViewById(R.id.txvOscoreID);
        txvDraws  = findViewById(R.id.txvDrawsID);
        txvGame   = findViewById(R.id.txvGameID);
        initilaizeTxt();

    }

    public void playAgain(View view) {
        gameboard = new GameBoard();
        status_game=-1;//start game
        turn = X_PLAYER;
        txvGame.setText(turn+" Turn");
        initilaizeTxt();
        enableButtons();
    }

    public void btnOnclick(View view) {


        switch(view.getId())
        {
            case R.id.btn1ID:
                {

                    btn1.setText(" "+turn);
                    btn1.setEnabled(false);
                    gameboard.setPlayerAt(0,0,turn);
                    gameStep();
                }
                break;
            case R.id.btn2ID:
                {
                btn2.setText(" "+turn);
                btn2.setEnabled(false);
                gameboard.setPlayerAt(0, 1, turn);
                gameStep();
                }
                break;
            case R.id.btn3ID:
            {
                btn3.setText(" "+turn);
                btn3.setEnabled(false);
                gameboard.setPlayerAt(0, 2, turn);
                gameStep();
            }

            break;
            case R.id.btn4ID:
            {
                btn4.setText(" "+turn);
                btn4.setEnabled(false);
                gameboard.setPlayerAt(1, 0, turn);
                gameStep();
            }

            break;
            case R.id.btn5ID:
            {
                btn5.setText(" "+turn);
                btn5.setEnabled(false);
                gameboard.setPlayerAt(1, 1, turn);
                gameStep();
            }

            break;
            case R.id.btn6ID:
            {
                btn6.setText(" "+turn);
                btn6.setEnabled(false);
                gameboard.setPlayerAt(1, 2, turn);
                gameStep();
            }

            break;
            case R.id.btn7ID:
            {
                btn7.setText(" "+turn);
                btn7.setEnabled(false);
                gameboard.setPlayerAt(2, 0, turn);
                gameStep();
            }

            break;
            case R.id.btn8ID:
            {
                btn8.setText(" "+turn);
                btn8.setEnabled(false);
                gameboard.setPlayerAt(2, 1, turn);
                gameStep();
            }

            break;
            case R.id.btn9ID:
            {
                btn9.setText(" "+turn);
                btn9.setEnabled(false);
                gameboard.setPlayerAt(2, 2, turn);
                gameStep();
            }

            break;
            default:
                throw new RuntimeException("Unknow button ID");
        }

    }

    private void drowWinPlaces() {
        int  places []= new int [3];
        places = gameboard.getWinPlaces();
        if(places[0]==1 || places[1]==1||places[2]==1)
        {
            btn1.setTextColor(Color.parseColor("#0B2161"));
        }
        if(places[0]==2 || places[1]==2||places[2]==2)
        {
            btn2.setTextColor(Color.parseColor("#0B2161"));
        }
        if(places[0]==3 || places[1]==3||places[2]==3)
        {
            btn3.setTextColor(Color.parseColor("#0B2161"));
        }
        if(places[0]==4 || places[1]==4||places[2]==4)
        {
            btn4.setTextColor(Color.parseColor("#0B2161"));
        }
        if(places[0]==5 || places[1]==5||places[2]==5)
        {
            btn5.setTextColor(Color.parseColor("#0B2161"));
        }
        if(places[0]==6 || places[1]==6||places[2]==6)
        {
            btn6.setTextColor(Color.parseColor("#0B2161"));
        }
        if(places[0]==7 || places[1]==7||places[2]==7)
        {
            btn7.setTextColor(Color.parseColor("#0B2161"));
        }
        if(places[0]==8 || places[1]==8||places[2]==8)
        {
            btn8.setTextColor(Color.parseColor("#0B2161"));
        }
        if(places[0]==9 || places[1]==9||places[2]==9)
        {
            btn9.setTextColor(Color.parseColor("#0B2161"));
        }

    }

    private void disableButtons() {
        btn1.setEnabled(false);
        btn2.setEnabled(false);
        btn3.setEnabled(false);
        btn4.setEnabled(false);
        btn5.setEnabled(false);
        btn6.setEnabled(false);
        btn7.setEnabled(false);
        btn8.setEnabled(false);
        btn9.setEnabled(false);
    }
    private void enableButtons() {
        btn1.setEnabled(true);
        btn2.setEnabled(true);
        btn3.setEnabled(true);
        btn4.setEnabled(true);
        btn5.setEnabled(true);
        btn6.setEnabled(true);
        btn7.setEnabled(true);
        btn8.setEnabled(true);
        btn9.setEnabled(true);
    }


    public void initilaizeTxt() {
        btn1.setText(" ");
        btn1.setTextColor(Color.parseColor("#000000"));
        btn2.setText(" ");
        btn2.setTextColor(Color.parseColor("#000000"));
        btn3.setText(" ");
        btn3.setTextColor(Color.parseColor("#000000"));
        btn4.setText(" ");
        btn4.setTextColor(Color.parseColor("#000000"));
        btn5.setText(" ");
        btn5.setTextColor(Color.parseColor("#000000"));
        btn6.setText(" ");
        btn6.setTextColor(Color.parseColor("#000000"));
        btn7.setText(" ");
        btn7.setTextColor(Color.parseColor("#000000"));
        btn8.setText(" ");
        btn8.setTextColor(Color.parseColor("#000000"));
        btn9.setText(" ");
        btn9.setTextColor(Color.parseColor("#000000"));

    }
    private void gameStep(){
        status_game = gameboard.gameOver();
        if(status_game==gameboard.NOT_OVER)
        {
            turn=(turn==X_PLAYER)?O_PLAYER:X_PLAYER;
            txvGame.setText(turn+" Turn");
            return;
        }
        if(status_game==gameboard.DRWAS)
        {
            drowsCount++;
            txvGame.setText("Draw - No Winner!");
            txvDraws.setText(""+drowsCount);
            disableButtons();
            return;
        }

        if(status_game==gameboard.X_WIN)

        {
            xScore++;
            txvGame.setText("X WIN!");
            txvXscore.setText(""+xScore);
            disableButtons();
            drowWinPlaces();
            Toast.makeText(this, "Game Over!", Toast.LENGTH_LONG).show();
            return;

        }
        if(status_game==gameboard.O_WIN)

        {
            oScore++;
            txvGame.setText("O WIN!");
            txvOscore.setText(""+oScore);
            disableButtons();
            drowWinPlaces();
            Toast.makeText(this, "Game Over!", Toast.LENGTH_LONG).show();

        }

    }
}
