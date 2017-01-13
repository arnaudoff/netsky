export interface PacketListItem {
    id: number,
    timestamp: Date,
    sourceIp: string,
    destinationIp: string,
    protocol: string,
    info: string
}
