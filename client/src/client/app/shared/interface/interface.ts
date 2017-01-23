import { InterfaceAddress } from './interface-address';

export interface Interface {
    name: string;
    description: string;
    addresses: Array<InterfaceAddress>;
};
