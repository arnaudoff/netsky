import { IInterfaceAddress } from './interface-address.model.ts';

export interface IInterface {
    name: string,
    description: string,
    addresses: Array<IInterfaceAddress>
};
