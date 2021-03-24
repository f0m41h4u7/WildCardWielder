FROM gcc:10.2.0
RUN apt-get update && apt-get install -y make cmake libboost-dev
WORKDIR /home
COPY . .
RUN mkdir build && cd build && cmake ..
WORKDIR /home/build
ENTRYPOINT ["make"]
