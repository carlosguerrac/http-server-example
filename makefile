.c.o :
	gcc -c -I /usr/local/include $<

#LIBS := -L /opt/stack/cscNetLib/cscNetLib/CscNetLib -lCscNet  
LIBS :=  -L /usr/local/lib -lCscNet 
all: netCliDemo netSrvDemo srvBaseDemo filePropertiesDemo \
     parseWordsOnLines netCliDemo-v.1 netCliDemo-v2 netSrvDemo-v2

netCliDemo-v.1: netCliDemo-v.1.o
	gcc netCliDemo-v.1.o $(LIBS) -o netCliDemo-v.1 
	
netCliDemo-v2: netCliDemo-v2.o
	gcc netCliDemo-v2.o $(LIBS) -o netCliDemo-v2 
	
netSrvDemo-v2: netSrvDemo-v2.o
	gcc netSrvDemo-v2.o $(LIBS) -o netSrvDemo-v2 

netCliDemo: netCliDemo.o
	gcc netCliDemo.o $(LIBS) -o netCliDemo
	
netSrvDemo: netSrvDemo.o
	gcc netSrvDemo.o $(LIBS) -o netSrvDemo

srvBaseDemo: srvBaseDemo.o
	gcc srvBaseDemo.o $(LIBS) -o srvBaseDemo

filePropertiesDemo: filePropertiesDemo.o
	gcc filePropertiesDemo.o $(LIBS) -o filePropertiesDemo

parseWordsOnLines: parseWordsOnLines.o
	gcc parseWordsOnLines.o $(LIBS) -o parseWordsOnLines

clean:
	rm srvBaseDemo netSrvDemo parseWordsOnLines filePropertiesDemo \
		netCliDemo netCliDemo-v.1 netCliDemo-v2 *.o
