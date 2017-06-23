ORBACUS_DIR = /home/gerwand/corba/OB-4.3.3
JTC_DIR     = $(ORBACUS_DIR)/jtc
LIB_PATH    = $(ORBACUS_DIR)/lib
INCLUDE_PATH = $(ORBACUS_DIR)/include

#SPRNG_DIR = /home/gerwand/sprng5

NUM_INSTANCES = 5

ORB_ENV = LD_LIBRARY_PATH=$(LIB_PATH)

IDL_APP = $(ORBACUS_DIR)/bin/idl
IDL = $(ORB_ENV) $(IDL_APP)

SERVER_NAME = server
CLIENT_NAME = client
RAND_NAME = random_provider

LFLAGS    = -lOB -lCosNaming -lJTC -ldl -lpthread
CXXFLAGS = --std=c++11 -Wall -g -w -fpermissive -fopenmp
CXXFLAGS += -L$(LIB_PATH) -I$(INCLUDE_PATH) -I.
#CXXFLAGS +=  -DSIMPLE_SPRNG
#CXXFLAGS += -I${SPRNG_DIR}/include -L${SPRNG_DIR}/lib

OBJ_CLIENT = client-naming_service.o GeneticTT.o DataParser.o Population.o
OBJ_CLIENT += Timetable.o CustomFunctions.o Period.o Resource.o

OBJ_SERV = server-naming_service.o GeneticTT_skel.o GeneticImplementation.o
OBJ_SERV += GeneticTT.o RandomInterface.o Population.o Timetable.o Period.o
OBJ_SERV += CustomFunctions.o

OBJ_RAND = random-naming_service.o RandomInterface_skel.o RandomInterface.o


all:  idl random server client  # make all and strip executables to reduce their size


idl:    GeneticTT.idl RandomInterface.idl  # create C++ interfaces from IDL file
	$(IDL) $^


server: ${OBJ_SERV}
	${CXX} ${CXXFLAGS} -o ${SERVER_NAME} ${OBJ_SERV} ${LFLAGS}

random: ${OBJ_RAND}
	${CXX} ${CXXFLAGS} -o ${RAND_NAME} ${OBJ_RAND} ${LFLAGS}

client: ${OBJ_CLIENT}
	${CXX} ${CXXFLAGS} -o ${CLIENT_NAME} ${OBJ_CLIENT} ${LFLAGS}


#${APP}: ${OBJ}
#	${CXX} $^ -o $@ ${LFLAGS}

server-naming_service.o: server-naming_service.cpp GeneticImplementation.o GeneticTT_skel.o random-naming_service.o
	${CXX} ${CXXFLAGS} -c $< -o $@

random-naming_service.o: random-naming_service.cpp RandomImplementation.h RandomInterface_skel.o
	${CXX} ${CXXFLAGS} -c $< -o $@

client-naming_service.o: client-naming_service.cpp GeneticTT.o DataParser.o Population.o
	${CXX} ${CXXFLAGS} -c $< -o $@

GeneticImplementation.o: GeneticImplementation.cpp GeneticImplementation.h GeneticTT_skel.o DataResources.h Population.o RandWrapper.h Timetable.o
	${CXX} ${CXXFLAGS} -c $< -o $@

Population.o: Population.cpp Population.h Timetable.o GeneticTT.o
	${CXX} ${CXXFLAGS} -c $< -o $@

#TimetableMPI.o: TimetableMPI.cpp TimetableMPI.h Timetable.o
#	${CXX} ${CXXFLAGS} -c $< -o $@

Timetable.o: Timetable.cpp Timetable.h Period.o
	${CXX} ${CXXFLAGS} -c $< -o $@

Period.o: Period.cpp Period.h DataTuples.h Resource.o CustomFunctions.o
	${CXX} ${CXXFLAGS} -c $< -o $@

DataParser.o: DataParser.cpp DataParser.h DataTuples.h DataResources.h Resource.o CustomFunctions.o
	${CXX} ${CXXFLAGS} -c $< -o $@

Resource.o: Resource.cpp Resource.h ContainerWrapper.h
	${CXX} ${CXXFLAGS} -c $< -o $@

CustomFunctions.o: CustomFunctions.cpp CustomFunctions.h
	${CXX} ${CXXFLAGS} -c $< -o $@

GeneticTT_skel.o: GeneticTT_skel.cpp GeneticTT_skel.h GeneticTT.o
	${CXX} ${CXXFLAGS} -c $< -o $@

GeneticTT.o: GeneticTT.cpp GeneticTT.h
	${CXX} ${CXXFLAGS} -c $< -o $@

RandomInterface_skel.o: RandomInterface_skel.cpp RandomInterface_skel.h RandomInterface.o
	${CXX} ${CXXFLAGS} -c $< -o $@

RandomInterface.o: RandomInterface.cpp RandomInterface.h
	${CXX} ${CXXFLAGS} -c $< -o $@

run:
	./run.sh ${NUM_INSTANCES}

clean:
	rm -f $(SERVER_NAME) ${RAND_NAME} ${CLIENT_NAME} *.o

