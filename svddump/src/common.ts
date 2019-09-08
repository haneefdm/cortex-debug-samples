export enum NumberFormat {
    Auto = 0,
    Hexidecimal,
    Decimal,
    Binary
}

export interface NodeSetting {
    node: string;
    expanded?: boolean;
    format?: NumberFormat;
}
