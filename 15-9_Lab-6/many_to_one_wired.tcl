#Create a simulator object
set ns [new Simulator]

#Define different colors for data flows (for NAM)
$ns color 1 Black
$ns color 2 Red
$ns color 3 Blue
$ns color 4 Green

#Open the NAM trace file
set nf [open out1.nam w]
$ns namtrace-all $nf

#Define a 'finish' procedure
proc finish {} {
        global ns nf
        $ns flush-trace
        #Close the NAM trace file
        close $nf
        #Execute NAM on the trace file
        exec nam out1.nam &
        exit 0
}

#Create four nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

#Create links between the nodes
$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 1.7Mb 20ms DropTail
$ns duplex-link $n2 $n4 1.5Mb 15ms DropTail

#Set Queue Size of link (n2-n3) to 10
$ns queue-limit $n2 $n3 10

#Give node position (for NAM)
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n3 $n2 orient left-down
$ns duplex-link-op $n4 $n2 orient left-up

#Monitor the queue for link (n2-n3). (for NAM)
$ns duplex-link-op $n2 $n3 queuePos 0.5

#Setup a TCP connection
set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink
$ns connect $tcp $sink
$tcp set fid_ 1

#Setup a FTP over TCP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

#Setup a UDP connection
set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1
set null [new Agent/Null]
$ns attach-agent $n2 $null
$ns connect $udp1 $null
$udp1 set fid_ 3

set cbr3 [new Application/Traffic/CBR]
$cbr3 attach-agent $udp1
$cbr3 set type_ CBR
$cbr3 set packet_size_ 2000
$cbr3 set rate_ 2mb
$cbr3 set random_ true

set udp2 [new Agent/UDP]
$ns attach-agent $n3 $udp2
set null [new Agent/Null]
$ns attach-agent $n2 $null
$ns connect $udp2 $null
$udp2 set fid_ 2

set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp2
$cbr1 set type_ CBR
$cbr1 set packet_size_ 1000
$cbr1 set rate_ 1.5mb
$cbr1 set random_ true

set udp3 [new Agent/UDP]
$ns attach-agent $n4 $udp3
set null [new Agent/Null]
$ns attach-agent $n2 $null
$ns connect $udp3 $null
$udp3 set fid_ 4
#Setup a CBR over UDP connection
set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $udp3
$cbr2 set type_ CBR
$cbr2 set packet_size_ 500
$cbr2 set rate_ 1mb
$cbr2 set random_ true

#Schedule events for the CBR and FTP agents
$ns at 0.1 "$cbr1 start"
$ns at 0.2 "$cbr2 start"
$ns at 1.5 "$cbr3 start"
$ns at 3.0 "$ftp start"
$ns at 4.1 "$cbr2 stop"
$ns at 4.3 "$ftp stop"
$ns at 4.5 "$cbr3 stop"
$ns at 4.9 "$cbr1 stop"


#Detach tcp and sink agents (not really necessary)
$ns at 4.5 "$ns detach-agent $n0 $tcp ; $ns detach-agent $n3 $sink"

#Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"

#Print CBR packet size and interval
puts "CBR packet size = [$cbr3 set packet_size_]"
puts "CBR interval = [$cbr3 set interval_]"

#Run the simulation
$ns run