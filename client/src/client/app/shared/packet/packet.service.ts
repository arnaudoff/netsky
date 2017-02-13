import { Injectable } from '@angular/core';
import { Observable, Subject, BehaviorSubject } from 'rxjs/Rx';
import { Config } from '../config/env.config';

import { WebSocketService } from './../websocket/index';
import { Packet } from './packet';

declare var SEARCHJS: any;

@Injectable()
export class PacketService {

  public packets: Subject<Packet>;

  private _observedPacket: BehaviorSubject<Packet> = new BehaviorSubject({});

  constructor(private wsService: WebSocketService) {
    this.packets = <Subject<Packet>>this.wsService
      .connect(Config.WS_SERVER_ADDRESS)
      .map((response: MessageEvent) : Packet => {
        let data = JSON.parse(response.data);
        return <Packet>data;
      });
  }

  get observedPacket() : Observable<Packet> {
    return this._observedPacket.asObservable();
  }

  public setObservedPacket(packet: Packet) {
    this._observedPacket.next(packet);
  }

  public filterSingle(packet: Packet, filterExpression: string): boolean {
    return SEARCHJS.matchObject(packet, JSON.parse(filterExpression));
  }

  public filterCollection(
    packets: Packet[],
    filterExpression: string): Packet[] {
      return SEARCHJS.matchArray(packets, JSON.parse(filterExpression));
  }

}
