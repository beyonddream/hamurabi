FROM ubuntu as build-base
RUN apt-get update && apt-get install build-essential -y
WORKDIR /build
COPY . .

# compile the binaries
RUN gcc -Wall -Wextra -Og -g -fsanitize=address,undefined -I./include -o hamurabi src/*.c

CMD ["/build/hamurabi"]
