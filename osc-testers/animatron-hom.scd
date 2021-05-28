n = NetAddr("localhost", 12345);

(
n.sendMsg("/new", "hom", "hom-up-stairs-hd");
n.sendMsg("/new", "hum", "hom-up-stairs-hd");
n.sendMsg("/select", "hom");
n.sendMsg("/select", "hum");
// n.sendMsg("/goto", 150);
n.sendMsg("/fps", "hom", 124);
n.sendMsg("/fps", "hum", 24);
n.sendMsg("/play");
n.sendMsg("/pingpong", "hum");
)
n.sendMsg("/sequence", "hum", "hom-up-stairs-hd");
n.sendMsg("/selected");
n.sendMsg("/goto", 150);
n.sendMsg("/play");
n.sendMsg("/play", "hum");
n.sendMsg("/rotate", pi/2);
n.sendMsg("/rotate", "hum", pi/2);
n.sendMsg("/fps", "hum", 12);
n.sendMsg("/fps", 126);
n.sendMsg("/pingpong", "hum");
(
n.sendMsg("/animation", "hom", "ma");
)
n.sendMsg("/midimap", "midi-map-default.json");
