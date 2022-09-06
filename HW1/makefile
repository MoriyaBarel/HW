FLAGS = -Wall -g
LOOPS = advancedClassificationLoop.o
REC = advancedClassificationRecursion.o
BASIC = basicClassification.o

loops: libclassloops.a


all: libclassloops.a recursives recursived loopd mains maindloop maindrec

mains: main.o libclassrec.a
	gcc $(FLAGS) -o mains main.o libclassrec.a

maindloop: main.o $(LOOPS) $(BASIC) libclassloops.so
	gcc $(FLAGS) -o maindloop main.o ./libclassloops.so

maindrec: main.o $(REC) $(BASIC) libclassrec.so
	gcc $(FLAGS)  -o maindrec main.o $(REC) $(BASIC) ./libclassrec.so

libclassloops.a: $(BASIC) $(LOOPS) 
	ar -rcs libclassloops.a $(LOOPS) $(BASIC) 

loopd: $(BASIC) $(LOOPS)
	gcc $(FLAGS) -shared -o libclassloops.so $(BASIC) $(LOOPS)

recursives: $(BASIC) $(REC)
	ar -rcs libclassrec.a $(BASIC) $(REC)

recursived: advancedClassificationRecursion.o
	gcc -shared -o libclassrec.so advancedClassificationRecursion.o

basicClassification.o: basicClassification.c NumClass.h
	gcc $(FLAGS) -c basicClassification.c

advancedClassificationLoops.o: advancedClassificationLoop.c NumClass.h
	gcc $(FLAGS) -c advancedClassificationLoop.c

advancedClassificationRecursion.o: advancedClassificationRecursion.c NumClass.h
	gcc $(FLAGS) -c advancedClassificationRecursion.c

main.o: main.c NumClass.h
	gcc $(FLAGS) -c main.c

clean:
	rm -f *.o *.a *.so mains maindloop maindrec