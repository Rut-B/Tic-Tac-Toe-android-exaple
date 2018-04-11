package com.example.rutbiton.tictactoe;

import android.util.Log;
import android.widget.Toast;

public class GameBoard {
    private static final char EMPTY = ' ';
    public static final int  X_WIN =0;
    public static final char O_WIN =1;
    public static final char DRWAS=2;
    public static final char NOT_OVER=3;
    public char board [][];
    private int winPlaces [];
    public GameBoard()
    {
        this.board = new char[3][3];
        this.winPlaces =new int[3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = EMPTY;
            }
        }
    }

    public void setPlayerAt(int row, int col, char player)
    {
        board[row][col] = player;
    }
    public int  gameOver()
    {

        //vertical
        if((board[0][0]== board[0][1]) && (board[0][0]== board[0][2])&&(board[0][0]!=EMPTY) )
        {
            winPlaces[0]=1; winPlaces[1]=2; winPlaces[2]=3;
            return ((board[0][0] =='X') ? X_WIN :O_WIN );

        }

        if((board[1][0]== board[1][1]) && (board[1][0]== board[1][2])&&(board[1][0]!=EMPTY) )
        {
            winPlaces[0]=4; winPlaces[1]=5; winPlaces[2]=6;
            return (((board[1][0] =='X')) ? X_WIN :O_WIN );
        }

        if((board[2][0]== board[2][1]) && (board[2][0]== board[2][2])&&(board[2][0]!=EMPTY) )
        {
            winPlaces[0]=7; winPlaces[1]=8; winPlaces[2]=9;
            return (((board[2][0] =='X')) ? X_WIN :O_WIN );
        }

        //horizontal
        if((board[0][0]== board[1][0]) && (board[0][0]== board[2][0])&&(board[0][0]!=EMPTY) )
        {
            winPlaces[0]=1; winPlaces[1]=4; winPlaces[2]=7;
            return (((board[0][0] =='X')) ? X_WIN :O_WIN );
        }

        if((board[0][1]== board[1][1]) && (board[0][1]== board[2][1])&&(board[0][1]!=EMPTY) )
        {
            winPlaces[0]=2; winPlaces[1]=5; winPlaces[2]=8;
            return (((board[0][1] =='X')) ? X_WIN :O_WIN );
        }

        if((board[0][2]== board[1][2]) && (board[0][2]== board[2][2]) &&(board[0][2]!=EMPTY))
        {
            winPlaces[0]=3; winPlaces[1]=6; winPlaces[2]=9;
            return (((board[0][2] =='X')) ? X_WIN :O_WIN );
        }
        //diagonals
        if((board[0][0]== board[1][1]) && (board[0][0]== board[2][2])&&(board[0][0]!=EMPTY) )
        {
            winPlaces[0]=1; winPlaces[1]=5; winPlaces[2]=9;
            return (((board[0][0] =='X')) ? X_WIN :O_WIN );
        }

        if((board[0][2]== board[1][1]) && (board[0][2]== board[2][0])&&(board[0][2]!=EMPTY) )
        {
            winPlaces[0]=3; winPlaces[1]=5; winPlaces[2]=7;
            return (((board[0][2] =='X')) ? X_WIN :O_WIN );
        }

        if(checkExistEmpty())
            return NOT_OVER;
        return DRWAS;
    }

    private boolean checkExistEmpty() {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
               if(board[i][j] == EMPTY)
               {
                   return true;
               }
            }
        }
        return false;
    }
    public int[] getWinPlaces(){
        return this.winPlaces;
    }
}
