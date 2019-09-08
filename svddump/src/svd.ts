import { PeripheralRegisterNode } from './nodes/peripheralregisternode';
import { PeripheralClusterNode } from './nodes/peripheralclusternode';
import { PeripheralNode } from './nodes/peripheralnode';
import { parseInteger, parseDimIndex } from './utils';
import { PeripheralFieldNode, EnumerationMap, EnumeratedValue } from './nodes/peripheralfieldnode';

import * as fs from 'fs';
import * as xml2js from 'xml2js';

export enum AccessType {
    ReadOnly = 1,
    ReadWrite,
    WriteOnly
}

const ACCESS_TYPE_MAP: { [key: string]: AccessType } = {
    'read-only': AccessType.ReadOnly,
    'write-only': AccessType.WriteOnly,
    'read-write': AccessType.ReadWrite,
    'writeOnce': AccessType.WriteOnly,
    'read-writeOnce': AccessType.ReadWrite
};

export class SVDParser {
    public static parseSVD(path: string): Promise<PeripheralNode[]> {
        return new Promise((resolve, reject) => {
            fs.readFile(path, 'utf8', (err, data) => {
                if (err) {
                    reject(path + ': ' + err.message);
                    return;
                }

                xml2js.parseString(data, (err, result) => {
                    if (err) {
                        reject(err);
                        return;
                    }

                    const peripheralMap: { [key: string]: any } = {};
                    const defaultOptions = {
                        accessType: AccessType.ReadWrite,
                        size: 32,
                        resetValue: 0x0
                    };

                    if (result.device.resetValue) {
                        defaultOptions.resetValue = parseInteger(result.device.resetValue[0]);
                    }
                    if (result.device.size) {
                        defaultOptions.size = parseInteger(result.device.size[0]);
                    }
                    if (result.device.access) {
                        const key: string = result.device.access[0];
                        defaultOptions.accessType = ACCESS_TYPE_MAP[key];
                    }

                    result.device.peripherals[0].peripheral.forEach((element: { name: string[] }) => {
                        const name = element.name[0];
                        peripheralMap[name] = element;
                    });

                    // tslint:disable-next-line:forin
                    for (const key in peripheralMap) {
                        const element = peripheralMap[key];
                        if (element.$ && element.$.derivedFrom) {
                            const base = peripheralMap[element.$.derivedFrom];
                            peripheralMap[key] = { ...base, ...element };
                        }
                    }

                    const peripherials = [];
                    // tslint:disable-next-line:forin
                    for (const key in peripheralMap) {
                        peripherials.push(SVDParser.parsePeripheral(peripheralMap[key], defaultOptions));
                    }

                    peripherials.sort((p1, p2) => {
                        if (p1.groupName > p2.groupName) { return 1; }
                        else if (p1.groupName < p2.groupName) { return -1; }
                        else {
                            if (p1.name > p2.name) { return 1; }
                            else if (p1.name < p2.name) { return -1; }
                            else { return 0; }
                        }
                    });

                    peripherials.forEach((p) => { p.markAddresses(); });

                    resolve(peripherials);
                });
            });
        });
    }

    private static cleanupDescription(input: string): string {
        return input.replace('\r', '').replace(/\n\s*/g, ' ');
    }

    private static parseFields(fieldInfo: any[], parent: PeripheralRegisterNode): PeripheralFieldNode[] {
        const fields: PeripheralFieldNode[] = [];

        fieldInfo.map((f) => {
            let offset;
            let width;
            const description = this.cleanupDescription(f.description ? f.description[0] : '');

            if (f.bitOffset && f.bitWidth) {
                offset = parseInteger(f.bitOffset[0]);
                width = parseInteger(f.bitWidth[0]);
            }
            else if (f.bitRange) {
                let range = f.bitRange[0];
                range = range.substring(1, range.length - 1);
                range = range.split(':');
                const end = parseInteger(range[0]);
                const start = parseInteger(range[1]);

                width = end - start + 1;
                offset = start;
            }
            else if (f.msb && f.lsb) {
                const msb = parseInteger(f.msb[0]);
                const lsb = parseInteger(f.lsb[0]);

                width = msb - lsb + 1;
                offset = lsb;
            }
            else {
                // tslint:disable-next-line:max-line-length
                throw new Error(`Unable to parse SVD file: field ${f.name[0]} must have either bitOffset and bitWidth elements, bitRange Element, or msb and lsb elements.`);
            }

            let valueMap: EnumerationMap = null;
            if (f.enumeratedValues) {
                valueMap = {};

                const ev = f.enumeratedValues[0];
                ev.enumeratedValue.map((ev: { value: string, name: string[], description: string[] }) => {
                    if (ev.value && ev.value.length > 0) {
                        const evname = ev.name[0];
                        const evdesc = this.cleanupDescription(ev.description ? ev.description[0] : '');
                        const val = ev.value[0].toLowerCase();
                        const evvalue = parseInteger(val);

                        valueMap[evvalue] = new EnumeratedValue(evname, evdesc, evvalue);
                    }
                });
            }

            const baseOptions = {
                name: f.name[0],
                description: description,
                offset: offset,
                width: width,
                enumeration: valueMap
            };

            if (f.dim) {
                if (!f.dimIncrement) { throw new Error(`Unable to parse SVD file: field ${f.name[0]} has dim element, with no dimIncrement element.`); }

                const count = parseInteger(f.dim[0]);
                const increment = parseInteger(f.dimIncrement[0]);
                let index = [];
                if (f.dimIndex) {
                    index = parseDimIndex(f.dimIndex[0], count);
                }
                else {
                    for (let i = 0; i < count; i++) { index.push(`${i}`); }
                }

                const namebase: string = f.name[0];
                const offsetbase = offset;

                for (let i = 0; i < count; i++) {
                    const name = namebase.replace('%s', index[i]);
                    fields.push(new PeripheralFieldNode(parent, { ...baseOptions, name: name, offset: offsetbase + (increment * i) }));
                }
            }
            else {
                fields.push(new PeripheralFieldNode(parent, { ...baseOptions }));
            }
        });

        return fields;
    }

    private static parseRegisters(regInfo: any[], parent: PeripheralNode | PeripheralClusterNode): PeripheralRegisterNode[] {
        const registers: PeripheralRegisterNode[] = [];

        regInfo.forEach((r) => {
            const baseOptions: any = {};
            if (r.access) {
                baseOptions.accessType = ACCESS_TYPE_MAP[r.access[0]];
            }
            if (r.size) {
                baseOptions.size = parseInteger(r.size[0]);
            }
            if (r.resetValue) {
                baseOptions.resetValue = parseInteger(r.resetValue[0]);
            }

            if (r.dim) {
                if (!r.dimIncrement) { throw new Error(`Unable to parse SVD file: register ${r.name[0]} has dim element, with no dimIncrement element.`); }

                const count = parseInteger(r.dim[0]);
                const increment = parseInteger(r.dimIncrement[0]);
                let index = [];
                if (r.dimIndex) {
                    index = parseDimIndex(r.dimIndex[0], count);
                }
                else {
                    for (let i = 0; i < count; i++) { index.push(`${i}`); }
                }

                const namebase: string = r.name[0];
                const descbase: string = this.cleanupDescription(r.description ? r.description[0] : '');
                const offsetbase = parseInteger(r.addressOffset[0]);

                for (let i = 0; i < count; i++) {
                    const name = namebase.replace('%s', index[i]);
                    const description = descbase.replace('%s', index[i]);

                    const register = new PeripheralRegisterNode(parent, {
                        ...baseOptions,
                        name: name,
                        description: description,
                        addressOffset: offsetbase + (increment * i)
                    });
                    if (r.fields && r.fields.length === 1) {
                        SVDParser.parseFields(r.fields[0].field, register);
                    }
                    registers.push(register);
                }
            }
            else {
                const description = this.cleanupDescription(r.description ? r.description[0] : '');
                const register = new PeripheralRegisterNode(parent, {
                    ...baseOptions,
                    name: r.name[0],
                    description: description,
                    addressOffset: parseInteger(r.addressOffset[0])
                });
                if (r.fields && r.fields.length === 1) {
                    SVDParser.parseFields(r.fields[0].field, register);
                }
                registers.push(register);
            }
        });

        registers.sort((a, b) => {
            if (a.offset < b.offset) { return -1; }
            else if (a.offset > b.offset) { return 1; }
            else { return 0; }
        });

        return registers;
    }

    private static parseClusters(clusterInfo: any, parent: PeripheralNode): PeripheralClusterNode[] {
        const clusters: PeripheralClusterNode[] = [];

        if (!clusterInfo) { return []; }

        clusterInfo.forEach((c: {
            access?: string[],
            size?: string[],
            resetValue?: string,
            dim?: string[],
            dimIncrement?: string[],
            name?: string[],
            dimIndex?: string[],
            description?: string[],
            addressOffset?: string[],
            register?: string[]
        }) => {
            const baseOptions: any = {};
            if (c.access) {
                baseOptions.accessType = ACCESS_TYPE_MAP[c.access[0]];
            }
            if (c.size) {
                baseOptions.size = parseInteger(c.size[0]);
            }
            if (c.resetValue) {
                baseOptions.resetValue = parseInteger(c.resetValue);
            }

            if (c.dim) {
                if (!c.dimIncrement) { throw new Error(`Unable to parse SVD file: cluster ${c.name[0]} has dim element, with no dimIncrement element.`); }

                const count = parseInteger(c.dim[0]);
                const increment = parseInteger(c.dimIncrement[0]);

                let index = [];
                if (c.dimIndex) {
                    index = parseDimIndex(c.dimIndex[0], count);
                }
                else {
                    for (let i = 0; i < count; i++) { index.push(`${i}`); }
                }

                const namebase: string = c.name[0];
                const descbase: string = this.cleanupDescription(c.description ? c.description[0] : '');
                const offsetbase = parseInteger(c.addressOffset[0]);

                for (let i = 0; i < count; i++) {
                    const name = namebase.replace('%s', index[i]);
                    const description = descbase.replace('%s', index[i]);
                    const cluster = new PeripheralClusterNode(parent, {
                        ...baseOptions,
                        name: name,
                        description: description,
                        addressOffset: offsetbase + (increment * i)
                    });
                    if (c.register) {
                        SVDParser.parseRegisters(c.register, cluster);
                    }
                    clusters.push(cluster);
                }

            }
            else {
                const description = this.cleanupDescription(c.description ? c.description[0] : '');
                const cluster = new PeripheralClusterNode(parent, {
                    ...baseOptions,
                    name: c.name[0],
                    description: description,
                    addressOffset: parseInteger(c.addressOffset[0])
                });
                if (c.register) {
                    SVDParser.parseRegisters(c.register, cluster);
                    clusters.push(cluster);
                }
            }

        });

        return clusters;
    }

    private static parsePeripheral(p: any, defaults: { accessType: AccessType, size: number, resetValue: number }): PeripheralNode {
        const ab = p.addressBlock[0];
        const totalLength = parseInteger(ab.size[0]);

        const options: any = {
            name: p.name[0],
            baseAddress: parseInteger(p.baseAddress[0]),
            description: this.cleanupDescription(p.description ? p.description[0] : ''),
            totalLength: totalLength
        };

        if (p.access) { options.accessType = ACCESS_TYPE_MAP[p.access[0]]; }
        if (p.size) { options.size = parseInteger(p.size[0]); }
        if (p.resetValue) { options.resetValue = parseInteger(p.resetValue[0]); }
        if (p.groupName) { options.groupName = p.groupName[0]; }

        const peripheral = new PeripheralNode(options);

        if (p.registers[0].register) {
            SVDParser.parseRegisters(p.registers[0].register, peripheral);
        }
        if (p.registers[0].cluster) {
            SVDParser.parseClusters(p.registers[0].cluster, peripheral);
        }

        return peripheral;
    }
}
