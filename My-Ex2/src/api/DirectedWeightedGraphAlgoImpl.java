package api;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.*;

public class DirectedWeightedGraphAlgoImpl implements DirectedWeightedGraphAlgorithms{

    private DirectedWeightedGraph graph;
    int time = 0;
    int gray = 153;
    int black = 0;
    int white = 255;

    public DirectedWeightedGraphAlgoImpl(){
        this.graph = new DirectedWeightedGraphImpl();
    }

    @Override
    public void init(DirectedWeightedGraph g) {
        this.graph = g;
    }

    @Override
    public DirectedWeightedGraph getGraph() {
        return this.graph;
    }

    @Override
    public DirectedWeightedGraph copy() {
        DirectedWeightedGraph g = new DirectedWeightedGraphImpl();
        Iterator<NodeData> iter = this.graph.nodeIter();
        while(iter.hasNext()){
            MyNode n = (MyNode)iter.next();
            g.addNode(n.copy());
        }
        return g;
    }

    private DirectedWeightedGraphImpl reverse(){
        DirectedWeightedGraphImpl reversed_graph = (DirectedWeightedGraphImpl) this.copy();
        Iterator<EdgeData> iter = reversed_graph.edgeIter();
        while (iter.hasNext()){
            MyEdge e = (MyEdge) iter.next();
            e.reverse();
        }
        return reversed_graph;
    }

    private void DFS(){
        Iterator<NodeData> iter = this.graph.nodeIter();
        while(iter.hasNext()){
            MyNode n = (MyNode) iter.next();
            n.setTag(white);
        }
        time = 0;
        iter = this.graph.nodeIter();
        while(iter.hasNext()){
            MyNode u = (MyNode) iter.next();
            if(u.getTag() == white){
                DFS_visit(u);
            }
        }
    }

    private void DFS_visit(MyNode u){
        u.setTag(gray);
        time++;
        u.setDiscovery_time(time);
        Iterator<EdgeData> iter = this.graph.edgeIter(u.getKey());
        while(iter.hasNext()){
            MyEdge e = (MyEdge) iter.next();
            if(e.getSrc() == u.getKey()){
                MyNode v = (MyNode) this.graph.getNode(e.getDest());
                if(v.getTag() == white){
                    DFS_visit(v);
                }
            }
        }
        u.setTag(black);
        u.setFinish_time(++time);
    }

    private int DFS2(DirectedWeightedGraph g){
        Iterator<NodeData> iter = g.nodeIter();
        while(iter.hasNext()){
            MyNode n = (MyNode) iter.next();
            n.setTag(white);
        }
        int counter = 0;
        iter = g.nodeIter();
        MyNode[] arr = new MyNode[g.nodeSize()];
        while(iter.hasNext()){
            MyNode n = (MyNode) iter.next();
            arr[counter++] = n;
        }
        counter = 0;
        mergeSort(arr,arr.length);
        for (int i=0; i< arr.length; i++){
            if(arr[i].getTag() == white){
                counter++;
                DFS2_visit(g,arr[i]);
            }
        }
        return counter;
    }

    private void DFS2_visit(DirectedWeightedGraph g,MyNode u){
        u.setTag(gray);
        Iterator<EdgeData> iter = g.edgeIter(u.getKey());
        while(iter.hasNext()){
            MyEdge e = (MyEdge) iter.next();
            if(e.getSrc() == u.getKey()){
                MyNode v = (MyNode) g.getNode(e.getDest());
                if(v.getTag() == white){
                    DFS2_visit(g,v);
                }
            }
        }
        u.setTag(black);
    }

    private void mergeSort(MyNode[] a, int n) {
        if (n < 2) {
            return;
        }
        int mid = n / 2;
        MyNode[] l = new MyNode[mid];
        MyNode[] r = new MyNode[n - mid];

        for (int i = 0; i < mid; i++) {
            l[i] = a[i];
        }
        for (int i = mid; i < n; i++) {
            r[i - mid] = a[i];
        }
        mergeSort(l, mid);
        mergeSort(r, n - mid);

        merge(a, l, r, mid, n - mid);
    }

    private void merge(MyNode[] a, MyNode[] l, MyNode[] r, int left, int right) {

        int i = 0, j = 0, k = 0;
        while (i < left && j < right) {
            if (l[i].getFinish_time() >= r[j].getFinish_time()) {
                a[k++] = l[i++];
            }
            else {
                a[k++] = r[j++];
            }
        }
        while (i < left) {
            a[k++] = l[i++];
        }
        while (j < right) {
            a[k++] = r[j++];
        }
    }

    private void dijkstra_algo(MyNode src_node) {
        List<MyNode> queue = new LinkedList<>();
        Iterator<NodeData> iter = this.graph.nodeIter();
        while(iter.hasNext()){
            MyNode n = (MyNode) iter.next();
            n.setPrev(null);
            n.setDistance(Integer.MAX_VALUE);
            queue.add(n);
        }
        src_node.setDistance(0);

        while (queue.size() != 0) {
            int min_dist = getLowestDistanceNode(queue);
            if(min_dist == -1){
                break;
            }
            MyNode u = (MyNode) this.graph.getNode(min_dist);
            queue.remove(u);
            Iterator<EdgeData> EdgeIter = this.graph.edgeIter(u.getKey());
            while (EdgeIter.hasNext()) {
                MyEdge e = (MyEdge) EdgeIter.next();
                if (e.getSrc() == u.getKey()) {
                    MyNode v = (MyNode) this.graph.getNode(e.getDest());
                    double dis_from_src = u.getDistance() + e.getWeight();
                    if(dis_from_src < v.getDistance()){
                      v.setDistance(dis_from_src);
                      v.setPrev(u);
                    }
                }
            }
        }
    }

    private int getLowestDistanceNode(List<MyNode> queue){
        int lowestDistanceNode_index = -1;
        double lowestDistance = Integer.MAX_VALUE;
        for (MyNode n: queue) {
            double nodeDistance = n.getDistance();
            if (nodeDistance < lowestDistance) {
                lowestDistance = nodeDistance;
                lowestDistanceNode_index = n.getKey();
            }
        }
        return lowestDistanceNode_index;
    }

    @Override
    public boolean isConnected() {
        DFS();
        DirectedWeightedGraph g = reverse();
        int ans = DFS2(g);
        return ans == 1;
    }

    @Override
    public double shortestPathDist(int src, int dest) {
        dijkstra_algo((MyNode) this.graph.getNode(src));
        double shortest_dis = ((MyNode) this.graph.getNode(dest)).getDistance();
        if(shortest_dis == Integer.MAX_VALUE){
            return -1;
        }
        return shortest_dis;
    }

    @Override
    public List<NodeData> shortestPath(int src, int dest) {
        dijkstra_algo((MyNode) this.graph.getNode(src));
        MyNode prev = (MyNode) this.graph.getNode(dest);
        if(prev.getDistance() == Integer.MAX_VALUE){
            return null;
        }
        List<NodeData> ans = new LinkedList<>();
        while(prev != null){
            ans.add(prev);
            prev = ((MyNode)this.graph.getNode(prev.getKey())).getPrev();
        }
        List<NodeData> reversed_ans = new LinkedList<>();
        int i = ans.size()-1;
        while (i >= 0){
            reversed_ans.add(ans.get(i));;
            i--;
        }
        return reversed_ans;
    }

    @Override
    public NodeData center() {
//        if (!this.isConnected()) {
//            return null;
//        }
        double minOfMax = Integer.MAX_VALUE;
        NodeData ans = null;
        Iterator<NodeData> nodeIter = this.graph.nodeIter();
        while(nodeIter.hasNext()){
            MyNode n = (MyNode) nodeIter.next();
            dijkstra_algo(n);
            double max_dis = -1;
            for (int i=0; i<this.graph.nodeSize();i++){
                if(i != n.getKey()){
                    double temp_dis = ((MyNode)this.graph.getNode(i)).getDistance();
                    if(max_dis < temp_dis){
                        max_dis = temp_dis;
                    }
                }
            }
            if(max_dis < minOfMax){
                minOfMax = max_dis;
                ans = n;
            }
        }
        return ans;
    }

    @Override
    public List<NodeData> tsp(List<NodeData> cities) {
        List<NodeData> ans = new LinkedList<>(shortestPath(cities.get(0).getKey(), cities.get(1).getKey()));
        for(int i=2;i<cities.size()-1;i++){
            int j=0;
            while (j < ans.size()){
                if(cities.get(i) != ans.get(j)) {
                    ans.addAll(shortestPath(cities.get(i).getKey(), cities.get(i+1).getKey()));
                }
                j++;
            }
        }
        return ans;
    }

    @Override
    public boolean save(String file) {
        return false;
    }

    @Override
    public boolean load(String file) {
        try {
            FileReader fr = new FileReader(file);
            JsonElement file_elem = JsonParser.parseReader(fr);
            JsonObject object = file_elem.getAsJsonObject();
            JsonArray nodes = object.getAsJsonArray("Nodes");
            JsonArray edges = object.getAsJsonArray("Edges");
            DirectedWeightedGraph G = new DirectedWeightedGraphImpl();
            for (JsonElement elem : nodes) {
                JsonObject obj = elem.getAsJsonObject();
                String st = obj.get("pos").getAsString();
                String[] split = st.split(",");
                GeoLocation location = new GeoLocationImpl(Double.parseDouble(split[0]), Double.parseDouble(split[1]), Double.parseDouble(split[2]));
                MyNode n = new MyNode(obj.get("id").getAsInt(), location, 0);
                G.addNode(n);
            }
            for (JsonElement elem : edges) {
                JsonObject obj = elem.getAsJsonObject();
                int src,dest;
                double w;
                src = obj.get("src").getAsInt();
                dest = obj.get("dest").getAsInt();
                w = obj.get("w").getAsDouble();
                G.connect(src, dest, w);
            }
            init(G);
        } catch (FileNotFoundException E) {
            E.printStackTrace();
            return false;
        }
        return true;
    }
}
