interface TransportableEntity {
  src?: string;
  dst?: string;
};

export interface Packet {
    datalink?: TransportableEntity;
    network?: TransportableEntity;
    transport?: TransportableEntity;
    data?: any;
};
