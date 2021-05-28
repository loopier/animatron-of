s.quit;
n = NetAddr("localhost", 12345);
(
n.sendMsg("/new", "ala");
n.sendMsg("/new", "olo", -0.1, 0.1);
n.sendMsg("/animation", "ala", "mama");
n.sendMsg("/animation", "olo", "mama");
// )
// (
n.sendMsg("/play", "ala");
// n.sendMsg("/play", "olo");
)

(
n.sendMsg("/new", "ala");
n.sendMsg("/animation", "ala", "mama");
// n.sendMsg("/play", "ala");
n.sendMsg("/select", "ala");
)
n.sendMsg("/reverse", "ala");
n.sendMsg("/pause", "ala");
n.sendMsg("/stop", "ala");
n.sendMsg("/fps", "ala", 12.0);
n.sendMsg("/goto", "ala", 75);
n.sendMsg("/loop", "ala");
n.sendMsg("/noloop", "ala");
n.sendMsg("/pingpong", "ala");