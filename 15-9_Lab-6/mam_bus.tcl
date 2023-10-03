#Creating five nodes
set node1 [$ns node]
setnode2 [$ns node]
set node3 [$ns node]
setnode4 [$ns node]
set node5 [$ns node]
#Creating Lan connection between the nodes
set lan0 [$ns newLan “$node1 $node2$node3 $node4 $node5” 0.7Mb 20ms LL Queue/FQ MAC/Csma/Cd Channel]
#Creating a TCP agent and attaching it to node 1
set tcp0 [new Agent/TCP]
$tcp0 set class_ 1
$ns attach-agent $node1 $tcp0
#Creating a TCP Sink agent for TCP and attaching it to node 3
set sink0 [new Agent/TCPSink]
$ns attach-agent $node3 $sink0
#Connecting the traffic sources with the traffic sink
$ns connect $tcp0 $sink0
# Creating a CBR traffic source and attach it to tcp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$ cbr0 set interval_ 0.05
$cbr0 attach-agent $tcp0
#Schedule events for the CBR agents
$ns at 0.5 “$cbr0 start time”
$ ns at 5.5 “$cbr0 stop time”
#Here we call the finish procedure after 10 seconds of simulation time
$ns at 10.0 “End”
#Finally run the simulation
$ns run