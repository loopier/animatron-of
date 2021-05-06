n = NetAddr("localhost", 12345);
n.sendMsg("/alo", 1, 2.3, "all")

n.sendMsg("/help");
n.sendMsg("/verbose");
n.sendMsg("/silent");

n.sendMsg("/new", "alo");
n.sendMsg("/new", "olo", 0.3, 0.8);
n.sendMsg("/new", "ilo", 1.0.rand, 1.0.rand);
n.sendMsg("/info", "alo", "olo");
n.sendMsg("/info");
n.sendMsg("/list");
n.sendMsg("/select", "alo");
n.sendMsg("/select", "ilo");
n.sendMsg("/selected");
n.sendMsg("/remove", "ilo");
n.sendMsg("/moveto", 1.0.rand,1.0.rand);
n.sendMsg("/move", 0.1.rand2,0.1.rand2);
n.sendMsg("/deselect", "ilo");
(
Tdef(\a, {
	inf.do{|i|

	n.sendMsg("/move", i.mod(100)/100,0.4);
		0.03.postln.wait;
	}
}).stop
)
