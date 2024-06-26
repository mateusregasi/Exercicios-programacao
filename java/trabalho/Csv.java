public class Csv {
    public String nome;
    public BufferedReader br;
    public FileReader fr;
    Csv(String nome){
        this.path = nome;
        this.fr = new FileReader(path);
        this.br = new BufferedReader(fr);
    }
    public String[] getLine(){
        String line = this.br.readLine();
        if(line == null) return null;
        return line.split(";");
    }
    public void close(){
        this.br.close();
        this.fr.close();
    }
}
