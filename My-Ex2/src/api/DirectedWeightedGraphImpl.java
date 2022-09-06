package api;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

public class DirectedWeightedGraphImpl implements DirectedWeightedGraph{

    private HashMap<Integer,MyNode> graph;
    private int MC;

    public DirectedWeightedGraphImpl(){
        this.graph = new HashMap<>();
        this.MC =0;
    }

    public String toString(){
        return "Node size: " + this.nodeSize()+ " edges size: "+this.edgeSize()+ this.graph;
    }

    @Override
    public NodeData getNode(int key) {
        if(graph.get(key) != null){
            return graph.get(key);
        }
        return null;
    }

    @Override
    public EdgeData getEdge(int src, int dest) {
        MyNode n = (MyNode)this.getNode(src);
        MyPair p = new MyPair(src,dest);
        if(n.getEdges().get(p) != null){
            return n.getEdges().get(p);
        }
        return null;
    }


    @Override
    public void addNode(NodeData n) {
        int key = n.getKey();
        MyNode node = (MyNode)n;
        graph.put(key,node);
        MC++;
    }

    @Override
    public void connect(int src, int dest, double w) {
        MyEdge e = new MyEdge(src, dest, w);
        MyNode n1 = (MyNode)this.getNode(src);
        MyNode n2 = (MyNode)this.getNode(dest);
        n1.addEdge(e);
        n2.addEdge(e);
        MC++;

    }

    @Override
    public Iterator<NodeData> nodeIter() {
        ArrayList<NodeData> graph_list = new ArrayList<>(this.graph.values());
        return graph_list.iterator();
    }

    @Override
    public Iterator<EdgeData> edgeIter() {
        ArrayList<EdgeData> edges_list = new ArrayList<>();
        for(MyNode n : this.graph.values()){
            edges_list.addAll(n.getEdges().values());
        }
        return edges_list.iterator();
    }

    @Override
    public Iterator<EdgeData> edgeIter(int node_id) {
        ArrayList<EdgeData> edges_list = new ArrayList<>(this.graph.get(node_id).getEdges().values());
        return edges_list.iterator();
    }

    @Override
    public NodeData removeNode(int key) {
        MyNode n = this.graph.get(key);
        if(n != null) {
            Iterator<EdgeData> it = this.edgeIter();
            while (it.hasNext()){
                EdgeData e = it.next();
                if(e.getSrc() == key){
                    this.removeEdge(e.getSrc(),e.getDest());
                }
                if(e.getDest() == key){
                    this.removeEdge(e.getSrc(),e.getDest());
                }
            }
            this.graph.remove(key);
            MC++;
            return n;
        }
        return null;
    }

    @Override
    public EdgeData removeEdge(int src, int dest) {
        MyNode n1 = this.graph.get(src);
        MyEdge e1 = n1.getEdges().get(new MyPair(src,dest));
        MyNode n2 = this.graph.get(dest);
        MyEdge e2 = n2.getEdges().get(new MyPair(src,dest));
        if (e1 != null && e2 != null) {
            n1.getEdges().remove(new MyPair(src, dest));
            n2.getEdges().remove(new MyPair(src, dest));
            MC++;
            return e1;
        }
        return null;
    }

    @Override
    public int nodeSize() {
        return this.graph.size();

    }

    @Override
    public int edgeSize() {
        Iterator<EdgeData> iter = this.edgeIter();
        int counter = 0;
        while(iter.hasNext()){
            iter.next();
            counter++;
        }
        return counter/2;
    }

    @Override
    public int getMC() {
        return this.MC;
    }
}
