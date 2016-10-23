import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs/Rx';
import { WebSocketService } from './../websocket/index';

import { IPacketResponseModel } from './packet-response-model.interface';
import { IRetrieveInterfacesResponseModel } from './retrieve-interfaces-response-model.interface';

const SNIFFER_SERVER_URL = 'ws://localhost:1903';

@Injectable()
export class SnifferClientService {
  public packets: Subject<IPacketResponseModel>;
  public interfaces: Subject<IRetrieveInterfacesResponseModel>;
  public connectionInstance: Subject<Object>;

  constructor(private wsService: WebSocketService) {
    this.connectionInstance = <Subject<Object>>this.wsService
      .connect(SNIFFER_SERVER_URL)
      .map((response: MessageEvent) : Object => {
        return JSON.parse(response.data);
      });

    this.packets = <Subject<IPacketResponseModel>>this.wsService
      .connect(SNIFFER_SERVER_URL)
      .filter((response: MessageEvent) => response.data.hasOwnProperty('packet'))
      .map((response: MessageEvent) : IPacketResponseModel => {
        let data = JSON.parse(response.data);

        return {
            packet: {
                protocol: data.packet.protocol
            }
        }
      });

    this.interfaces = <Subject<IRetrieveInterfacesResponseModel>>this.wsService
      .connect(SNIFFER_SERVER_URL)
      .filter((response: MessageEvent) => {
          let data = JSON.parse(response.data);
          return data.hasOwnProperty('interfaces');
      })
      .map((response: MessageEvent) : IRetrieveInterfacesResponseModel => {
        let data = JSON.parse(response.data);

        return {
            interfaces: {
                names: data.interfaces.names
            }
        }
      });
  }

  public retrieveInterfaces() : void {
    this.wsService.activeConnection.subscribe((v: Object) => {
        console.log(v);
        this.connectionInstance.next({ "retrieve-interfaces": {} });
    });
  }
}
