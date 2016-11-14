import { IInterfaceAddressResponseModel } from './interface-address-response-model.interface';

export interface IInterfaceResponseModel {
    name: String,
    description: String,
    addresses: Array<IInterfaceAddressResponseModel>
}
