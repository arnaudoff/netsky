import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs/Rx';
import { WebSocketService } from './../websocket/index';

const SNIFFER_SERVER_URL = 'ws://localhost:1903';

export interface RetrieveInterfacesResponseModel {
    interfaces: {
        names: Array<string>
    }
}

export interface PacketResponseModel {
    packet: {
        protocol: string
    }
}

@Injectable()
export class SnifferClientService {
  public packets: Subject<PacketResponseModel>;
  public interfaces: Subject<RetrieveInterfacesResponseModel>;

  constructor(private wsService: WebSocketService) {
    this.packets = <Subject<PacketResponseModel>>this.wsService
      .connect(SNIFFER_SERVER_URL)
      .filter((response: MessageEvent) => response.data.hasOwnProperty('packet'))
      .map((response: MessageEvent) : PacketResponseModel => {
        let data = JSON.parse(response.data);

        return {
            packet: {
                protocol: data.packet.protocol
            }
        }
      });

    this.interfaces = <Subject<RetrieveInterfacesResponseModel>>this.wsService
      .connect(SNIFFER_SERVER_URL)
      .filter((response: MessageEvent) => response.data.hasOwnProperty('interfaces'))
      .map((response: MessageEvent) : RetrieveInterfacesResponseModel => {
        let data = JSON.parse(response.data);

        return {
            interfaces: {
                names: data.interfaces.names
            }
        }
      });
  }
}
