// import { Command, TreeItem } from 'vscode';
import { NumberFormat, NodeSetting } from '../common';
import { AddressRangesInUse } from '../addrranges';

export interface Thenable<T> {
    /**
     * Attaches callbacks for the resolution and/or rejection of the Promise.
     * @param onfulfilled The callback to execute when the Promise is resolved.
     * @param onrejected The callback to execute when the Promise is rejected.
     * @returns A Promise for the completion of which ever callback is executed.
     */
    then<TResult>(onfulfilled?: (value: T) => TResult | Thenable<TResult>, onrejected?: (reason: any) => TResult | Thenable<TResult>): Thenable<TResult>;
    // tslint:disable-next-line: unified-signatures
    then<TResult>(onfulfilled?: (value: T) => TResult | Thenable<TResult>, onrejected?: (reason: any) => void): Thenable<TResult>;
}

// export class Promise<T> implements Thenable<T> {
    /**
     * If you call resolve in the body of the callback passed to the constructor,
     * your promise is fulfilled with result object passed to resolve.
     * If you call reject your promise is rejected with the object passed to reject.
     * For consistency and debugging (eg stack traces), obj should be an instanceof Error.
     * Any errors thrown in the constructor callback will be implicitly passed to reject().
     */
    // constructor(callback: (resolve: (value?: T | Thenable<T>) => void, reject: (error?: any) => void) => void);

    /**
     * onFulfilled is called when/if "promise" resolves. onRejected is called when/if "promise" rejects.
     * Both are optional, if either/both are omitted the next onFulfilled/onRejected in the chain is called.
     * Both callbacks have a single parameter , the fulfillment value or rejection reason.
     * "then" returns a new promise equivalent to the value you return from onFulfilled/onRejected after being passed through Promise.resolve.
     * If an error is thrown in the callback, the returned promise rejects with that error.
     *
     * @param onFulfilled called when/if "promise" resolves
     * @param onRejected called when/if "promise" rejects
     */
    // then<U>(onFulfilled?: (value: T) => U | Thenable<U>, onRejected?: (error: any) => U | Thenable<U>): Promise<U>;
    // tslint:disable-next-line: unified-signatures
    // then<U>(onFulfilled?: (value: T) => U | Thenable<U>, onRejected?: (error: any) => void): Promise<U>;

    /**
     * Sugar for promise.then(undefined, onRejected)
     *
     * @param onRejected called when/if "promise" rejects
     */
    // catch<U>(onRejected?: (error: any) => U | Thenable<U>): Promise<U>;
// }

export enum TreeItemCollapsibleState {
    None = 0,
    Collapsed = 1,
    Expanded = 2
}

export class TreeItem {
    public contextValue?: string;
    public description?: string;
    public tooltip?: string;
    constructor(public label: string, public collapsibleState = TreeItemCollapsibleState.None) {
    }
}

export class Command {

}

export abstract class BaseNode {
    public expanded: boolean;

    constructor(protected readonly parent?: BaseNode) {
        this.expanded = false;
    }

    public getParent(): BaseNode | undefined {
        return this.parent;
    }

    public abstract getChildren(): BaseNode[] | Promise<BaseNode[]>;
    public abstract getTreeItem(): TreeItem | Promise<TreeItem>;

    public getCommand(): Command | undefined {
        return undefined;
    }

    public abstract getCopyValue(): string | undefined;
}

export abstract class PeripheralBaseNode extends BaseNode {
    public format: NumberFormat;
    public readonly name: string;

    constructor(protected readonly parent?: PeripheralBaseNode) {
        super(parent);
        this.format = NumberFormat.Auto;
    }

    public selected(): Thenable<boolean> {
        return Promise.resolve(false);
    }

    // public abstract performUpdate(): Thenable<any>;
    // public abstract updateData(): Thenable<boolean>;

    public abstract getChildren(): PeripheralBaseNode[] | Promise<PeripheralBaseNode[]>;
    public abstract getPeripheral(): PeripheralBaseNode;

    public abstract markAddresses(a: AddressRangesInUse): void;

    public abstract saveState(path?: string): NodeSetting[];
    public abstract findByPath(path: string[]): PeripheralBaseNode;
}
