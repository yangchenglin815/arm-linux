TARGET=roms.CZfh40g
OBJS=cini.o tools.o  TAesClass.o dlist.o  tcpsocket.o CZ_fh40g.o  linkkey.o
LIBPATH=/usr/lib
%.o:%.cpp
	g++ -c -g  -I.   $< -o $@ 

$(TARGET):$(OBJS)
	g++ $(OBJS) -L$(LIBPATH) -lpthread   -lmyodbc3   -o $(TARGET) -L/usr/linkivr/switch

install:
	cp $(TARGET)  /usr/linkivr/switch

clean:
	rm *.o
	rm $(TARGET)
	
