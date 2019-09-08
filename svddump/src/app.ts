import {SVDParser} from './svd';
import {PeripheralBaseNode} from './nodes/basenode';
import {PeripheralNode} from './nodes/peripheralnode';
import {PeripheralRegisterNode} from './nodes/peripheralregisternode';
import {PeripheralClusterNode} from './nodes/peripheralclusternode';
import {AddressRangesInUse} from './addrranges';

import program from 'commander';
import stream from 'stream';

import { createWriteStream, WriteStream } from 'fs';

class MyMain {
    private peripherials: PeripheralNode[] = [];
    constructor(public svdFileName: string, public outStream: WriteStream | NodeJS.WriteStream) {
    }

    private outputNode(node: PeripheralBaseNode, offset: number, prefix = '') {
        const type = node.constructor.name;
        if (node instanceof PeripheralRegisterNode) {
            const reg = node as PeripheralRegisterNode;
            function pad(str: string): string {
                return ('00000000' + str).substr(-8);
            }
            const addr = pad((offset + reg.offset).toString(16));
            const len = (reg.size / 8).toString(10);
            this.outStream.write(`  reg: ${prefix}.${reg.name} 0x${addr},${len}\n`);
            return;
        } else if (node instanceof PeripheralClusterNode) {
            const cluster = node as PeripheralClusterNode;
            const offt = cluster.getAddress(offset);
            for (const child of cluster.getChildren()) {
                this.outputNode(child, offt, prefix + '.' + cluster.name);
            }
        } else {
            throw new Error(`Unknown type ${type}`);
        }
    }
    
    public doiIt(merge: boolean, mergeThreshold: number) {
        SVDParser.parseSVD(this.svdFileName).then((peripherals) => {
            for (const peripheral of peripherals) {
                const addr = peripheral.getAddress(0).toString(16);
                this.outStream.write(`Peripheral: ${peripheral.name} 0x${addr}\n`);
                const children = peripheral.getChildren() as PeripheralBaseNode[];
                if (children) {
                    for (const node of children) {
                        this.outputNode(node, peripheral.getAddress(0));
                    }
                }
                const ranges = peripheral.markAddressesOpt(merge, mergeThreshold);
                AddressRangesInUse.doLog(this.outStream, peripheral.name, ranges[0].base, peripheral.totalLength, ranges);
            }
        });
    }
}

let inpFileName: string;
let outFileStream: WriteStream | NodeJS.WriteStream;

program
    .version('0.0.1')
    .option('-m, --merge', 'Merge adjacent addresses', true)
    .option('-M, --no-merge', 'Do not merge adjacent addresses')
    .option('-t, --threshold <number>', 'threshold to use when collapsing', 16)
    .arguments('<input-file> [output-file]')
    .action((inf: string, outf) => {
        inpFileName = inf;
        if (outf) {
            outFileStream = createWriteStream(outf, 'utf-8');
        } else {
            outFileStream = process.stdout;
        }
    })
    .parse(process.argv)
;

// console.log('merge = ', program.merge);
// console.log('threshold = ', program.threshold);

const Obj = new MyMain(inpFileName, outFileStream);
Obj.doiIt(program.merge, program.threshold);
