# p2pFileContentShare
Relay based Peer-to-Peer System using Client-Server socket programming

## How to compile?
$ cd src

$ ./cmd.sh

## How to run?
* First start relay server which act as server for transmittion between nodes and clients
$ ./relay <relay_port>

* Start nodes which act at file sender
$ ./node <relay_ip> <relay_port>

* Start client which act as file reciver
$ ./client <relay_ip> <relay_port>
client will be prompted to enter the file name that they are looking for.

check out topic.pdf for functionality details
