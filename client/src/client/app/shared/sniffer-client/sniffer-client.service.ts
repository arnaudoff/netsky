import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs/Rx';

import { WebSocketService } from './../websocket/index';
import { RetrievedInterfaces } from './models/retrieved-interfaces';
import { PacketListItem } from './models/packet-list-item';

const SNIFFER_SERVER_URL = 'ws://localhost:1903';

@Injectable()
export class SnifferClientService {
  public packets: Subject<PacketListItem>;
  public interfaces: Subject<RetrievedInterfaces>;
  public connectionInstance: Subject<Object>;

  constructor(private wsService: WebSocketService) {
    this.connectionInstance = <Subject<Object>>this.wsService
      .connect(SNIFFER_SERVER_URL)
      .map((response: MessageEvent) : Object => {
        return JSON.parse(response.data);
      });

    this.packets = <Subject<PacketListItem>>this.wsService
      .connect(SNIFFER_SERVER_URL)
      .map((response: MessageEvent) : Object => {
        return JSON.parse(response.data);
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
    interfaces: Array<string>,
    filters: Array<string>,
    listeners: Array<string>): void {

    let argumentsObject: Object = {
      interfaces: interfaces,
      filters: filters,
      shared: listeners
    };

    let commandObject: Object = {
        "start-packet-sniffer": argumentsObject
    };

    this.connectionInstance.next(commandObject);
  }

}
