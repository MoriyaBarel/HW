package api;

import java.util.Objects;

public class MyPair {
    private int x;
    private int y;

    public MyPair(int x,int y){
        this.x = x;
        this.y = y;
    }

    public int getX(){
        return this.x;
    }

    public int getY(){
        return this.y;
    }

    public void reverse(){
        int temp = this.y;
        this.y = this.x;
        this.x = temp;
    }

    @Override
    public boolean equals(Object o){
        if (o instanceof MyPair){
            if(((MyPair) o).x == this.x && ((MyPair) o).y == this.y){
                return true;
            }
        }
        return false;
    }

    @Override
    public int hashCode(){
        return Objects.hashCode(this.x) + Objects.hashCode(this.y);

    }

}
