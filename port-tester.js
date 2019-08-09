const os = require('os');
const ifaces = os.networkInterfaces();
const net = require('net');

let aliases = [];
Object.keys(ifaces).forEach(function (ifname) {
    ifaces[ifname].forEach(function (iface) {
	if ('IPv4' !== iface.family) {
	    // we only want internal ipv4 addresses
	    console.log('skipping ' + iface.address);
	    return;
	}

	// console.log(ifname, iface.address);
	aliases.push(iface.address);
    });
});


// setTimeout(() => {}, 500);

['0.0.0.0', ''].forEach((h) => {
    if (!aliases.find((a) => { return a === h ; })) {
	console.log('Adding default: ' + h);
	aliases.push(h);
    }
});

console.log('Aliases for this host: ', aliases);

function is_port_in_use(host, port) {
    return new Promise((resolve,reject) => {
	const server = net.createServer((c) => {
	    console.log('created');
	});
	server.once('error', (e) => {
	    console.log(`port status ${host}:${port} error code ${e}`);
	    server.close();
	    resolve(true);
	});
	
	server.listen(port, host, () => {		// Port not in use
	    console.log(`port '${host}:${port}' was free...`);
	    server.close();
	    resolve(false);
	});
    });
}

function test_server(port) {
    let inUse = false;
    //aliases = aliases.reverse();
    for (let ix = 0; ix < aliases.length ; ix++ ) {
	const host = aliases[ix];
	// console.log(`Trying host ${host}...`);
	setTimeout(async () => {
	    inUse = await is_port_in_use(host, port) || inUse;
	}, 100);
    }
}

test_server(55000)
