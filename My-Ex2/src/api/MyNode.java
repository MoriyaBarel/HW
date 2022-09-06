package api;
import java.util.HashMap;
import java.util.Map;

public class MyNode implements NodeData{

    private final int key;
    private GeoLocationImpl location;
    private double weight;
    private String info;
    private int tag;
    private HashMap<MyPair,MyEdge> edges;
    private int discovery_time;
    private int finish_time;
    private double distance;
    private MyNode prev;

    public MyNode(int id, GeoLocation loc, double w) {
        this.key = id;
        this.tag = 255;
        this.location = (GeoLocationImpl) loc;
        this.weight = w;
        this.edges = new HashMap<>();
        this.discovery_time = 0;
        this.finish_time = 0;
        this.distance = 0;
        this.prev = null;
    }

    public MyNode(int id) {
        this.key = id;
        this.tag = 255;
        this.info = "";
        this.weight = 0;
        this.location = null;
        this.edges = new HashMap<>();
        this.discovery_time = 0;
        this.finish_time = 0;
        this.distance = 0;
        this.prev = null;
    }

    public int getDiscovery_time(){
        return this.discovery_time;
    }

    public int getFinish_time(){
        return this.finish_time;
    }

    public void setDiscovery_time(int s){
        this.discovery_time = s;
    }

    public void setFinish_time(int f){
        this.finish_time = f;
    }

    public double getDistance(){
        return this.distance;
    }

    public MyNode getPrev(){
        return this.prev;
    }

    public void setDistance(double d){
        this.distance = d;
    }

    public void setPrev(MyNode n){
        this.prev = n;
    }

    public void addEdge(MyEdge e){
        MyPair p = new MyPair(e.getSrc(),e.getDest());
        edges.put(p,e);
    }

    public String toString() {
        return "key: " + this.key + " weight: " + this.weight + " tag: " + this.tag + " discovery time: " + this.discovery_time
                + " finish time: " + this.finish_time;
    }

    public MyNode copy(){
        MyNode n = new MyNode(this.key);
        n.tag = this.tag;
        n.weight = this.weight;
        n.info = this.info;
        n.location = this.location.copy();
        n.discovery_time = this.discovery_time;
        n.finish_time = this.finish_time;
        n.prev = this.prev;
        n.distance = this.distance;
        for (Map.Entry<MyPair,MyEdge> map_entry : this.edges.entrySet()){
            MyEdge e = map_entry.getValue().copy();
            n.edges.put(e.getPair(),e);
        }
        return n;
     }

    public HashMap<MyPair,MyEdge> getEdges() {
        return this.edges;
    }

    @Override
    public int getKey() {
        return this.key;
    }

    @Override
    public GeoLocation getLocation() {
        return this.location;
    }

    @Override
    public void setLocation(GeoLocation p) {
        this.location = (GeoLocationImpl) p;
    }

    @Override
    public double getWeight() {
        return this.weight;
    }

    @Override
    public void setWeight(double w) {
        this.weight = w;
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
