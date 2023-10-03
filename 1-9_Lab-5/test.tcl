#------------------------------------------------------- 
# This ns script has been created by the nam editor.
# If you edit it manually, the nam editor might not
# be able to open it properly in the future.
#
# EDITING BY HAND IS AT YOUR OWN RISK!
#------------------------------------------------------- 
# Create a new simulator object.
set ns [new Simulator]
# Create a nam trace datafile.
set namfile [open /home/nitt/Desktop/106121087/Sem-5/Networks Lab/1-9_Lab-5/test.nam]
$ns namtrace-all $namfile

# Create wired nodes.
set node(3) [$ns node]
## node(3) at 522.453125,558.375000
$node(3) set X_ 522.453125
$node(3) set Y_ 558.375000
$node(3) set Z_ 0.0
$node(3) color "black"

set node(2) [$ns node]
## node(2) at 567.828125,599.281250
$node(2) set X_ 567.828125
$node(2) set Y_ 599.281250
$node(2) set Z_ 0.0
$node(2) color "black"

set node(1) [$ns node]
## node(1) at 498.734344,603.750000
$node(1) set X_ 498.734344
$node(1) set Y_ 603.750000
$node(1) set Z_ 0.0
$node(1) color "black"


# Create links between nodes.
$ns simplex-link $node(3) $node(2) 1.000000Mb 20.000000ms DropTail
$ns simplex-link-op $node(3) $node(2) queuePos 0.5
$ns simplex-link-op $node(3) $node(2) color black
$ns simplex-link-op $node(3) $node(2) orient 42.0deg
# Set Queue Properties for link 3->2
[[$ns link $node(3) $node(2)] queue] set limit_ 20

$ns simplex-link $node(3) $node(1) 1.000000Mb 20.000000ms DropTail
$ns simplex-link-op $node(3) $node(1) queuePos 0.5
$ns simplex-link-op $node(3) $node(1) color black
$ns simplex-link-op $node(3) $node(1) orient 117.6deg
# Set Queue Properties for link 3->1
[[$ns link $node(3) $node(1)] queue] set limit_ 20

$ns simplex-link $node(2) $node(3) 1.000000Mb 20.000000ms DropTail
$ns simplex-link-op $node(2) $node(3) queuePos 0.5
$ns simplex-link-op $node(2) $node(3) color black
$ns simplex-link-op $node(2) $node(3) orient 222.0deg
# Set Queue Properties for link 2->3
[[$ns link $node(2) $node(3)] queue] set limit_ 20

$ns simplex-link $node(2) $node(1) 1.000000Mb 20.000000ms DropTail
$ns simplex-link-op $node(2) $node(1) queuePos 0.5
$ns simplex-link-op $node(2) $node(1) color black
$ns simplex-link-op $node(2) $node(1) orient 176.3deg
# Set Queue Properties for link 2->1
[[$ns link $node(2) $node(1)] queue] set limit_ 20

$ns simplex-link $node(1) $node(3) 1.000000Mb 20.000000ms DropTail
$ns simplex-link-op $node(1) $node(3) queuePos 0.5
$ns simplex-link-op $node(1) $node(3) color black
$ns simplex-link-op $node(1) $node(3) orient 297.6deg
# Set Queue Properties for link 1->3
[[$ns link $node(1) $node(3)] queue] set limit_ 20

$ns simplex-link $node(1) $node(2) 1.000000Mb 20.000000ms DropTail
$ns simplex-link-op $node(1) $node(2) queuePos 0.5
$ns simplex-link-op $node(1) $node(2) color black
$ns simplex-link-op $node(1) $node(2) orient 356.3deg
# Set Queue Properties for link 1->2
[[$ns link $node(1) $node(2)] queue] set limit_ 20

# Add Link Loss Models

# Create agents.

# Connect agents.
# Run the simulation
proc finish {} {
	global ns namfile
	$ns flush-trace
	close $namfile
	exec nam -r 2000.000000us /home/nitt/Desktop/106121087/Sem-5/Networks Lab/1-9_Lab-5/test.nam &	
	exit 0
	}
$ns at 60.000000 "finish"
$ns run
