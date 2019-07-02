
const incr = 100;   // millisonds

// We are intentionally not using setTimeout, trying to emulate heavy load
function mySleep(timeout:number): number {
    const start = Date.now();
    console.log(`Start sleep ${start}`);
    while (true) {
        const now = Date.now();
        const diff = now - start;
        if (diff >= timeout) {
            console.log(`Done sleep ${diff}`);
            break;
        }
    }
    return timeout + incr;
}

function main(args) {
    let i = 0, flag = 1;
    let timeout = incr;
    console.log(args);
    // Set breakpoint at nxt line, expand 'args' in Variables window and keep hitting the
    // Step-Over button. All of a sudden, you will the Variables window go blank and then
    // back to its default state and 'args' is collapsed. If this happens on the first 
    // Step-Over (sometimes it does), then re-expand 'args'
    timeout = mySleep(timeout);         // <=== place breakpoint here
    timeout = mySleep(timeout);
    timeout = mySleep(timeout);
    timeout = mySleep(timeout);
    timeout = mySleep(timeout);
    timeout = mySleep(timeout);
    timeout = mySleep(timeout);
    timeout = mySleep(timeout);
    timeout = mySleep(timeout);

    // Place breakpoint below and make sure 'args' is still expanded and cotinue.
    // Randomly pause debugger giving about a second between pauses. Tree loses state.
    console.log('Starting heavy duty infinit loop'); // <=== place breakpoint here
    while (true) {
        // Attempt a calculation without using any function calls
        for(i=2; i < (1 << 30); ++i)
        {
            // i is a prime number, flag will be equal to 1
            flag = 1;
            for(let j=2; j <= (i / 2); ++j)
            {
                if ((i % j) === 0)
                {
                    flag = 0;
                    break;
                }
            }
            if(flag === 1) {
                // Yes, we have a prime number
                // std::cout << i << ' ';
            }
        }
        console.log('Anouther round');
    }
}

main(['text',  100]);
