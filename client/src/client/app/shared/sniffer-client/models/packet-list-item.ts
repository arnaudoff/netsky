interface TransportableEntity {
  src: string,
  dst: string
};

export interface PacketListItem {
    datalink: TransportableEntity,
    network: TransportableEntity,
    transport: TransportableEntity,
    data: any
};
