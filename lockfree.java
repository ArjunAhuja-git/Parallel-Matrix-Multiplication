import javafx.util.Pair;
import java.util.concurrent.atomic.*;
import java.util.*;
import java.io.*;
import java.io.IOException;
import java.util.Scanner;

class Node{
  public Pair<Integer,Integer> value;
  public AtomicReference<Node> next;
  public Node(Pair<Integer,Integer> value) {
    this.value = value;
    next = new AtomicReference<Node>(null);
  }
}

class lockfreeQueue{
  public AtomicReference<Node> tail;
  public AtomicReference<Node> head;
  public Node sentinel;
  lockfreeQueue(){
    sentinel = new Node(new Pair<Integer,Integer>(-1,-1));
    tail = new AtomicReference<Node>(null);
    head = new AtomicReference<Node>(null);
    tail.set(sentinel);
    head.set(sentinel);
  }

  public void enq(Pair<Integer,Integer> value) {
   Node node = new Node(value);
   while (true) {
     Node last = tail.get();
     Node next = last.next.get();
     if (last == tail.get()) {
       if (next == null) {
         if (last.next.compareAndSet(next, node)) {
           tail.compareAndSet(last, node);
           return;
         }
       } else {
         tail.compareAndSet(last, next);
       }
     }
   }
  }

  public Pair<Integer,Integer> deq() throws EmptyStackException {
   while (true) {
     Node first = head.get();
     Node last = tail.get();
     Node next = first.next.get();
     if (first == head.get()) {
       if (first == last) {
         if (next == null) {
           throw new EmptyStackException();
         }
         tail.compareAndSet(last, next);
       } else {
         Pair<Integer,Integer> value = next.value;
         if (head.compareAndSet(first, next))
          return value;
         }
       }
     }
  }
}

public class lockfree{
  static int mult(int[] a,int[] b,int size){
    int sum = 0;
    for (int i = 0 ; i < size ; i++) {
      sum += a[i]*b[i];
    }
    return sum;
  }

  public static void main(String[] args){
      lockfreeQueue Q =  new lockfreeQueue();
      try{
          Scanner sc = new Scanner(new File("inputMatrix3.txt"));
          Integer sizeOfMatrix = sc.nextInt();
          Integer NUMBER_OF_THREADS = sc.nextInt();
          int[][] matrixA = new int[sizeOfMatrix][sizeOfMatrix];
          int[][] matrixB = new int[sizeOfMatrix][sizeOfMatrix];
          int[][] ansMatrix = new int[sizeOfMatrix][sizeOfMatrix];
          for (int i = 0;i<sizeOfMatrix;i++) {
            for (int j = 0;j<sizeOfMatrix;j++) {
              matrixA[i][j] = sc.nextInt();
              ansMatrix[i][j] = 0;
              Q.enq(new Pair <Integer,Integer> (i,j));
            }
          }
          for (int i = 0;i<sizeOfMatrix;i++) {
            for (int j = 0;j<sizeOfMatrix;j++) {
              matrixB[j][i] = sc.nextInt();
            }
          }
          Thread[] threads = new Thread[NUMBER_OF_THREADS];
          for (int i = 0; i < threads.length; i++) {
             threads[i] = new Thread(new Runnable() {
                 public void run() {
                     while(true){
                       try{
                         Pair<Integer,Integer> p = Q.deq();
                         ansMatrix[p.getKey()][p.getValue()] = mult(matrixA[p.getKey()],matrixB[p.getValue()],sizeOfMatrix);
                       } catch(EmptyStackException e){
                         break;
                       }
                     }
                 }
             });
             threads[i].start();
          }
          for (int i = 0; i < threads.length; i++) {
             threads[i].join();
          }
          PrintWriter writer = new PrintWriter("lockfreeOutput.txt", "UTF-8");
          for (int i = 0;i<sizeOfMatrix;i++) {
            for (int j = 0;j<sizeOfMatrix;j++) {
              writer.print(ansMatrix[i][j]+" ");
            }
            writer.print("\n");
          }
          writer.close();
      } catch(Exception e){
        return;
      }
  }
}
