#base image used
FROM gcc:latest

#flex, bison download
RUN apt-get update && apt-get install -y \
    flex \
    bison \
    && rm -rf /var/lib/apt/list/*

#setting working directory
WORKDIR /usr/src/ppl

#copying code
COPY . .

#auto make
RUN make

CMD ["/bin/bash"]