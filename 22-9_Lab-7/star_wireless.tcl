set val(chan) Channel/WirelessChannel

set val(prop) Propagation/TwoRayGround

set val(ant) Antenna/OmniAntenna

set val(ll) LL

set val(ifq) Queue/DropTail/PriQueue

set val(ifqlen) 50

set val(netif) Phy/WirelessPhy

set val(mac) Mac/802_11

set val(rp) DSDV

set val(nn) 50

set val(x) 2000

set val(y) 1000

set val(stop) 10

set val(traffic) cbr

set val(traffic) tcp

set ns [new Simulator]

set tracefd [open out.tr w]

$ns trace-all $tracefd

set namtrace [open out.nam w]

$ns namtrace-all-wireless $namtrace $val(x) $val(y)

set topo [new Topography]

$topo load_flatgrid $val(x) $val(y)

set god_ [create-god $val(nn)]

$ns node-config –adhocRouting $val(rp) \
-llType $val(ll) \
-macType $val(mac) \
-ifqType $val(ifq) \
-ifqLen $val(ifqlen) \
-antType $val(ant) \
-propType $val(prop) \
-phyType $val(netif) \
-channelType $val(chan) \
-topoInstance $topo \
-agentTrace ON \
-routerTrace ON \
-macTrace OFF \
-movementTrace ON

# Creating node objects

for {set i 0} {$i < [expr $val(nn)]} { incr i } {
set node_($i) [$ns node]

}

# To define node initial position in nam
for {set i 0} {$i < [expr $val(nn)]} { incr i } {
 $ns initial_node_pos $node_($i) 30

}

# use of random mobility positions
proc destination {} {

global ns val node_

set time 1.0

set now [$ns now]

for {set i 0} {$i<$val(nn)} {incr i} {

set xx [expr rand()*1600]

set yy [expr rand()*800]

$ns at $now “$node_($i) setdest $xx $yy 1000.0”

}

$ns at [expr $now+$time] “destination”

}

# To change node colors at the time of 1.0 , 2.0 , 3.0
for {set i 0} {$i < $val(nn) } {incr i } {

$node_($i) color yellow

$ns at 1.0 “$node_($i) color red”

}

for {set i 0} {$i < $val(nn) } {incr i } {

$node_($i) color yellow

$ns at 2.0 “$node_($i) color lightgreen”

}

for {set i 0} {$i < $val(nn) } {incr i } {

$node_($i) color yellow

$ns at 3.0 “$node_($i) color orange”

}

# To end nam and the simulation
$ns at $val(stop) “$ns nam-end-wireless $val(stop)”

$ ns at $val(stop) “stop”

$ns at 10.5 “puts \”end simulation\” ; $ns halt”

#  Execute the nam file
proc stop {} {

global ns tracefd namtrace

$ns flush-trace

close $tracefd

close $namtrace

exec nam out.nam &

}

$ns run
