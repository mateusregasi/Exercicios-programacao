import java.io.*;
public class Voos implements Arquivo{
    private String origem;
    private String destino;
    private String data;
    private int horario;
    private int assentos;
    private int preco;
    public Arquivo[] get_registros(){
        Arquivo reg[]; 
        Csv arquivo = new Csv("formato_voos.csv");


        arquivo.close();
    }
}