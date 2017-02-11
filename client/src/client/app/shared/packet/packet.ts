interface TransportableEntity {
  src?: string;
  dst?: string;
};

interface Payload {
  contents?: string;
}

export interface Packet {
    datalink?: TransportableEntity;
    network?: TransportableEntity;
    transport?: TransportableEntity;
    payload?: Payload;
    data?: any;
};
