package api;

public class MyEdge implements EdgeData {

    private final double weight;
    private String info;
    private int tag;
    private final MyPair pair;

    public MyEdge(int src, int dest, double w){
        this.pair = new MyPair(src,dest);
        this.weight = w;
        this.tag = 255;
        this.info = "src: " + src + "dest: " + dest + "weight: " + w + "tag: " + tag;
    }
    public String toString(){
        return "src: " +this.getSrc()+ " dest: " +this.getDest()+ " weight: " +this.weight;
    }
    public MyPair getPair(){
        return this.pair;
    }
    public void reverse(){
        this.pair.reverse();
    }

    public MyEdge copy(){
        return new MyEdge(this.getSrc(),this.getDest(),this.weight);
    }
    @Override
    public int getSrc() {
        return this.pair.getX();
    }

    @Override
    public int getDest() {
        return this.pair.getY();
    }

    @Override
    public double getWeight() {
        return this.weight;
    }

    @Override
    public String getInfo() {
        return this.info;
    }

    @Override
    public void setInfo(String s) {
        this.info = s;
    }

    @Override
    public int getTag() {
        return this.tag;
    }

    @Override
    public void setTag(int t) {
        this.tag = t;
    }
}
