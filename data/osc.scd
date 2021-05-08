n = NetAddr("localhost", 12345);
n.sendMsg("/alo", 1, 2.3, "all")

n.sendMsg("/help");
n.sendMsg("/verbose");
n.sendMsg("/silent");

(
o = Array.fill(4, {|i| "alo"++i});
o.do{|obj| n.sendMsg("/new", obj, 0.5.rand2+0.5, 0.5.rand2+0.5)};
)

n.sendMsg("/ortho");

(
o.do{|obj,i|
	n.sendMsg("/select", obj );
	n.sendMsg("/moveto", 0.5.rand2+0.5, 0.5.rand2+0.5);
	n.sendMsg("/rotate", 1.0.rand2);
	n.sendMsg("/scale", rrand(0.2,2.0));
	n.sendMsg("/deselect", obj );
};
)

o.do{|obj| n.sendMsg("/select", obj)}; n.sendMsg("/remove");

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
n.sendMsg("/move", "alo1", 0.1.rand2,0.1.rand2);
n.sendMsg("/moveto", "alo1", 0.5.rand/2+0.5,0.5.rand/2+0.5);
n.sendMsg("/rotate", "alo1", 1.0.rand);
n.sendMsg("/deselect", "ilo");
(
Tdef(\a, {
	inf.do{|i|

	n.sendMsg("/move", i.mod(100)/100,0.4);
		0.03.postln.wait;
	}
}).stop
)
