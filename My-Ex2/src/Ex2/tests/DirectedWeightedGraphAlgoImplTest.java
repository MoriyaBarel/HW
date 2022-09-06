package Ex2.tests;

import api.DirectedWeightedGraphAlgoImpl;
import api.MyNode;

import static org.junit.jupiter.api.Assertions.*;

class DirectedWeightedGraphAlgoImplTest {
    DirectedWeightedGraphAlgoImpl Algo;
    String st = "data/1000Nodes.json";
    String st2 = "data/G1.json";

    @org.junit.jupiter.api.Test
    void init() {
    }

    @org.junit.jupiter.api.Test
    void getGraph() {
    }

    @org.junit.jupiter.api.Test
    void copy() {
    }

    @org.junit.jupiter.api.Test
    void isConnected() {
        Algo = new DirectedWeightedGraphAlgoImpl();
        Algo.load(st);
        assertTrue(Algo.isConnected());
    }

    @org.junit.jupiter.api.Test
    void shortestPathDist() {
        Algo = new DirectedWeightedGraphAlgoImpl();
        Algo.load(st);
        double ans = Algo.shortestPathDist(2,7);
        assertEquals(948.281039429467, ans);
    }

    @org.junit.jupiter.api.Test
    void shortestPath() {
    }

    @org.junit.jupiter.api.Test
    void center() {
        Algo = new DirectedWeightedGraphAlgoImpl();
        Algo.load(st);
        MyNode n = (MyNode) Algo.center();
        MyNode v = (MyNode) Algo.getGraph().getNode(362);
        assertEquals(v, n);
    }

    @org.junit.jupiter.api.Test
    void tsp() {
    }

    @org.junit.jupiter.api.Test
    void save() {
    }

    @org.junit.jupiter.api.Test
    void load() {
    }
}