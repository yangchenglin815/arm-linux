TARGET=xtsms
OBJS=CSerial.o  xtsms.o
LIBPATH=/usr/lib
%.o:%.cpp
	g++ -c -g  -I.   $< -o $@ 

$(TARGET):$(OBJS)
	g++ $(OBJS) -L$(LIBPATH) -lpthread   -lmyodbc3   -o $(TARGET) -L/usr/linkivr/switch

install:
	cp $(TARGET)  /usr/roms1000/

clean:
	rm *.o
	rm $(TARGET)
	
