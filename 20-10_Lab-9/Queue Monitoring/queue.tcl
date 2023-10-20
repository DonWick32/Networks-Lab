 #new Simulator creation
set ns [new Simulator]
#trace file creation for capturing the UDP data
set tf [open out.tr w]
set file1 [open qm.out w]
$ns trace-all $tf

set file2 [open out.nam w]
$ns namtrace-all $file2

#setting the exponential distribution param
set lambda 30.0
set mu     33.0

#creation of nodes
set n1 [$ns node]
set n2 [$ns node]
#The queue limit is 1Lakh as the capacity is infinite. Simulation will take # more time when the limit is increased.
set link [$ns simplex-link $n1 $n2 100kb 0ms DropTail]
$ns queue-limit $n1 $n2 100000

# generate random interarrival times and packet sizes
set InterArrivalTime [new RandomVariable/Exponential]
$InterArrivalTime set avg_ [expr 1/$lambda]
set pktSize [new RandomVariable/Exponential]
$pktSize set avg_ [expr 100000.0/(8*$mu)]

#create new agent UDP
set src [new Agent/UDP]
$ns attach-agent $n1 $src

# queue monitoring and send the output to queue.out file
set qmon [$ns monitor-queue $n1 $n2 [open queue.out w] 0.1]
$link queue-sample-timeout

proc finish {} {
    global ns tf
    $ns flush-trace
    close $tf
    global ns file2
    close $file2
    exec nam out.nam &
    # gawk '{ print $1, $4, $5, $6, $7, $8, $9, $10, $11 }' queue1.out > qm1.pre
    # xgraph qm1.pre -geometry 500x500 -t “MM1 Queuing Example”
    exit 0
}

proc sendpacket {} {
    global ns src InterArrivalTime pktSize
    set time [$ns now]
    $ns at [expr $time + [$InterArrivalTime value]] "sendpacket"
    set bytes [expr round ([$pktSize value])]
    $src send $bytes
}

set sink [new Agent/Null]
$ns attach-agent $n2 $sink
$ns connect $src $sink
$ns at 0.0001 "sendpacket"
$ns at 1000.0 "finish"

$ns run