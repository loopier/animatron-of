n = NetAddr("localhost", 12345);
n.sendMsg("/alo", 1, 2.3, "all")

n.sendMsg("help");

n.sendMsg("/new", "alo");
n.sendMsg("/new", "olo", 0.3, 0.8);
n.sendMsg("/new", "ilo", 1.0.rand, 1.0.rand);
n.sendMsg("/node/info", "alo");
n.sendMsg("/list");
n.sendMsg("/select", "alo");
n.sendMsg("/select", "ilo");
n.sendMsg("/selected");
n.sendMsg("/remove", "ilo");
n.sendMsg("/move", 1.0.rand,1.0.rand);
n.sendMsg("/deselect", "ilo");
(
Tdef(\a, {
	inf.do{|i|

	n.sendMsg("/move", i.mod(100)/100,0.4);
		0.03.postln.wait;
	}
}).stop
)
