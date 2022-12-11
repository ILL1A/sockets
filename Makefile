CC = g++
CFLAGS = -std=c++20
ODIR = obj
SDIR = src
OBJS = socket.o logger.o message.o validator.o

_OBSSERVER = server.o $(OBJS)
_OBSCLIENT = client.o $(OBJS)
OBSSERVER = $(patsubst %, $(ODIR)/%, $(_OBSSERVER))
OBSCLIENT = $(patsubst %, $(ODIR)/%, $(_OBSCLIENT))

server: $(OBSSERVER)
	$(CC) $(CFLAGS) -o target/$@ $(OBSSERVER)

client: $(OBSCLIENT)
	$(CC) $(CFLAGS) -o target/$@ $(OBSCLIENT)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(ODIR)/*.o target/server target/client
