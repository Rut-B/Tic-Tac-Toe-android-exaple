package com.example.rutbiton.tictactoe;
import android.content.Intent;
import android.view.View;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    public void startPlay(View view){
        Intent in = new Intent(this,GameActivity.class);
        startActivity(in);
    }

    public void instMove(View view){
        Intent in = new Intent(this,InstructionsActivity.class);
        startActivity(in);
    }

}
