import { TreeItem, TreeItemCollapsibleState, Thenable } from './basenode';
import { AccessType } from '../svd';
import { PeripheralBaseNode } from './basenode';
import { AddrRange, AddressRangesInUse } from '../addrranges';
import { NumberFormat, NodeSetting } from '../common';
import { hexFormat } from '../utils';
import { PeripheralRegisterNode } from './peripheralregisternode';
import { PeripheralClusterNode } from './peripheralclusternode';

export interface PeripheralOptions {
    name: string;
    baseAddress: number;
    totalLength: number;
    description: string;
    groupName?: string;
    accessType?: AccessType;
    size?: number;
    resetValue?: number;
}

export class PeripheralNode extends PeripheralBaseNode {
    private children: Array<PeripheralRegisterNode | PeripheralClusterNode>;

    public readonly name: string;
    public readonly baseAddress: number;
    public readonly description: string;
    public readonly groupName: string;
    public readonly totalLength: number;
    public readonly accessType: AccessType;
    public readonly size: number;
    public readonly resetValue: number;
    protected addrRanges: AddrRange[];
    
    private currentValue: number[];

    constructor(options: PeripheralOptions) {
        super(null);

        this.name = options.name;
        this.baseAddress = options.baseAddress;
        this.totalLength = options.totalLength;
        this.description = options.description;
        this.groupName = options.groupName || '';
        this.resetValue = options.resetValue || 0;
        this.size = options.size || 32;
        this.children = [];
        this.addrRanges = [];
    }

    public getPeripheral(): PeripheralBaseNode {
        return this;
    }
    public getTreeItem(): TreeItem | Promise<TreeItem> {
        const label = `${this.name} @ ${hexFormat(this.baseAddress)}`;
        const item = new TreeItem(label, this.expanded ? TreeItemCollapsibleState.Expanded : TreeItemCollapsibleState.Collapsed);
        item.contextValue = 'peripheral';
        item.tooltip = this.description;
        return item;
    }
    public getCopyValue(): string {
        throw new Error('Method not implemented.');
    }

    public getChildren(): PeripheralBaseNode[] | Promise<PeripheralBaseNode[]> {
        return this.children;
    }

    public setChildren(children: Array<PeripheralRegisterNode | PeripheralClusterNode>) {
        this.children = children;
        this.children.sort((c1, c2) => c1.offset > c2.offset ? 1 : -1);
    }

    public addChild(child: PeripheralRegisterNode | PeripheralClusterNode) {
        this.children.push(child);
        this.children.sort((c1, c2) => c1.offset > c2.offset ? 1 : -1);
    }

    public getBytes(offset: number, size: number): Uint8Array {
        try {
            return new Uint8Array(this.currentValue.slice(offset, offset + size));
        }
        catch (e) {
            return new Uint8Array(0);
        }
    }

    public getAddress(offset: number) {
        return this.baseAddress + offset;
    }

    public getOffset(offset: number) {
        return offset;
    }

    public getFormat(): NumberFormat {
        return this.format;
    }

/*     public updateData(): Thenable<boolean> {
        return new Promise((resolve, reject) => {
            if (!this.expanded) { resolve(false); return; }
            this.readMemory().then((unused) => {
                const promises = this.children.map((r) => r.updateData());

                Promise.all(promises).then((_) => {
                    resolve(true);
                }).catch((e) => {
                    const str = `Failed  to update peripheral ${this.name}:${e}`;
                    console.log(str);
                    reject(str);
                });
            }, (error) => {
                const str = `Failed  to read peripheral ${this.name}:${error}`;
                console.log(str);
                reject(str);
            });
        });
    } */

    public markAddresses(): void {
        this.markAddressesOpt();
    }

    public markAddressesOpt(skipAddressGaps: boolean = true, gapThreshold: number = 16): AddrRange[] {
        let ranges = [new AddrRange(this.baseAddress, this.totalLength)];   // Default range
        
        if (skipAddressGaps) {
            // Split the entire range into a set of smaller ranges. Some svd files specify
            // a very large address space but may use very little of it.
            const addresses = new AddressRangesInUse(this.totalLength);
            this.children.map((child) => child.markAddresses(addresses));
            ranges = addresses.getAddressRangesOptimized(this.baseAddress, false, gapThreshold);
        }

        // OpenOCD has an issue where the max number of bytes readable are 8191 (instead of 8192)
        // which causes unaligned reads (via gdb) and silent failures. There is patch for this in OpenOCD
        // but in general, it is good to split the reads up. see http://openocd.zylin.com/#/c/5109/
        // Anothr benefit, we can minimize gdb timoeouts
        const maxBytes = (4 * 1024); // Should be a multiple of 4 to be safe for MMIO reads
        this.addrRanges = AddressRangesInUse.splitIntoChunks(ranges, maxBytes, this.name, this.totalLength);
        return this.addrRanges;
    }

    public getPeripheralNode(): PeripheralNode {
        return this;
    }

    public selected(): Thenable<boolean> {
        return this.performUpdate();
    }
    
    public saveState(path?: string): NodeSetting[] {
        const results: NodeSetting[] = [];

        if (this.format !== NumberFormat.Auto || this.expanded) {
            results.push({ node: `${this.name}`, expanded: this.expanded, format: this.format });
        }

        this.children.forEach((c) => {
            results.push(...c.saveState(`${this.name}`));
        });

        return results;
    }

    public findByPath(path: string[]): PeripheralBaseNode {
        if (path.length === 0) { return this; }
        else {
            const child = this.children.find((c) => c.name === path[0]);
            if (child) { return child.findByPath(path.slice(1)); }
            else { return null; }
        }
    }

    public performUpdate(): Thenable<any> {
        throw new Error('Method not implemented.');
    }
}
