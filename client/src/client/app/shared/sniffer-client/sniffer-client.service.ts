import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs/Rx';
import { WebSocketService } from './../websocket/index';

import { RetrievedInterfaces } from './models/negotiation/retrieved-interfaces';
import { IConfigurableEntity } from './../sniffer-config-builder/index';

const SNIFFER_SERVER_URL = 'ws://localhost:1903';

@Injectable()
export class SnifferClientService {
  public packets: Subject<Object>;
  public interfaces: Subject<RetrievedInterfaces>;
  public connectionInstance: Subject<Object>;

  constructor(private wsService: WebSocketService) {
    this.connectionInstance = <Subject<Object>>this.wsService
      .connect(SNIFFER_SERVER_URL)
      .map((response: MessageEvent) : Object => {
        return JSON.parse(response.data);
      });

    this.packets = <Subject<Object>>this.wsService
      .connect(SNIFFER_SERVER_URL)
      .filter((response: MessageEvent) => response.data.hasOwnProperty('packet'))
      .map((response: MessageEvent) : Object => {
        let data = JSON.parse(response.data);

        return {
            packet: {
                protocol: data.packet.protocol
            }
        }
      });

    this.interfaces = <Subject<RetrievedInterfaces>>this.wsService
      .connect(SNIFFER_SERVER_URL)
      .filter((response: MessageEvent) => {
          let data = JSON.parse(response.data);
          return data.hasOwnProperty('interfaces');
      })
      .map((response: MessageEvent) : RetrievedInterfaces => {
        let data = JSON.parse(response.data);
        return <RetrievedInterfaces>data;
      });
  }

  public retrieveInterfaces() : void {
    this.wsService.activeConnection.subscribe((v: Object) => {
        this.connectionInstance.next({ "retrieve-interfaces": {} });
    });
  }

  public startSniffer(
      interfaces: IConfigurableEntity,
      filters: IConfigurableEntity,
      listeners: IConfigurableEntity): void {

    let argumentsObject: Object = {
      interfaces: interfaces.values,
      filters: filters.values,
      shared: listeners.values
    };

    let commandObject: Object = {
        "start-packet-sniffer": argumentsObject
    };

    this.connectionInstance.next(commandObject);
  }

}
